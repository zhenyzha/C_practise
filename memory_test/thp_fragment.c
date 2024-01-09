// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * Simple program that allocates as many THP as possible, to the split
 * them and free all but a single subpage. This causes heavy fragmentation.
 *
 * Without memory compaction, other processes won't be able top consume
 * THPs.
 *
 *  Copyright (C) 2023  Red Hat, Inc.
 *  Author: David Hildenbrand <david@redhat.com>
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>

static unsigned long pagesize;
static unsigned long pmd_thpsize;

static uint64_t pagemap_get_entry(int fd, char *start)
{
	const unsigned long pfn = (unsigned long)start / pagesize;
	uint64_t entry;
	int ret;

	ret = pread(fd, &entry, sizeof(entry), pfn * sizeof(entry));
	if (ret != sizeof(entry)) {
		perror("pread");
		exit(-errno);
	}
	return entry;
}

static bool pagemap_is_populated(char *start)
{
	int fd = open("/proc/self/pagemap", O_RDONLY);
	uint64_t entry;

	if (fd < 0) {
		perror("open");
		exit(-errno);
	}
	entry = pagemap_get_entry(fd, start);
	close(fd);

	/* Present or swapped. */
	return entry & 0xc000000000000000ull;
}

static unsigned long detect_thp_size(void)
{
	int fd = open("/sys/kernel/mm/transparent_hugepage/hpage_pmd_size", O_RDONLY);
	unsigned long val;
	char buf[80 + 1];
	int ret;

	if (fd < 0) {
		fprintf(stderr, "Assuming 2 MiB THP\n");
		return 2 * 1024 * 1024u;
	}

	ret = pread(fd, buf, sizeof(buf) - 1, 0);
	if (ret <= 0) {
		fprintf(stderr, "Assuming 2 MiB THP\n");
		val = 2 * 1024 * 1024u;
	} else {
		buf[ret] = 0;
		val = strtoul(buf, NULL, 10);
	}
	close(fd);

	return val;
}

static char *try_alloc_thp(void)
{
	const size_t mmap_size = 2 * pmd_thpsize;
	char *area, *mmap_area;

	mmap_area = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE,
			 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (mmap_area == MAP_FAILED)
		return mmap_area;

	/* We most certainly want THPs. */
	if (madvise(mmap_area, mmap_size, MADV_HUGEPAGE)) {
		perror("madvise(MADV_HUGEPAGE)");
		exit(1);
	}

	/* We need a THP-aligned area such that we can get THPs. */
	area = mmap_area + pmd_thpsize - ((uintptr_t)mmap_area & (pmd_thpsize - 1));

	/* Try populating a THP. */
	*area = 1;

	/* No THP :( */
	if (!pagemap_is_populated(area + pmd_thpsize - pagesize)) {
		munmap(mmap_area, mmap_size);
		return MAP_FAILED;
	}

	return area;
}

int main(void)
{
	char **thps;
	char *thp;
	int i, count = 0, retries = 0;

	pagesize = sysconf(_SC_PAGE_SIZE);
	pmd_thpsize = detect_thp_size();
	thps = malloc(sizeof(*thps));

	/* Try allocating as many THP as possible. */
	while (true) {
		thp = try_alloc_thp();
		if (thp == MAP_FAILED) {
			if (retries++ > 1000)
				break;
			continue;
		}
		retries = 0;
		thps = realloc(thps, (count + 1) * sizeof(*thps));
		thps[count] = thp;
		count++;
	}
	printf("Allocated %d THPs\n", count);

	/* After we allocated these THPs, discard all but a single page. */
	for (i = 0; i < count; i++) {
		thp = thps[i];

		/*
		 * Let's make sure khugepaged won't try re-collapsing
		 * a THP here simply because we leave one page mapped.
		 */
		if (madvise(thp, pmd_thpsize, MADV_NOHUGEPAGE)) {
			perror("madvise(MADV_NOHUGEPAGE)");
			exit(1);
		}

		/*
		 * Let's first try splitting the THP. Probably unnecessary,
		 * but this way they don't end up on the deferred split queue.
		 * And can easily be compacted later when need be.
		 */
		if (madvise(thp + pagesize, pmd_thpsize - pagesize,
			    MADV_COLD)) {
			perror("madvise(MADV_COLD)");
			exit(1);
		}

		/* Now, actually free all but a single page. */
		if (madvise(thp + pagesize, pmd_thpsize - pagesize,
			    MADV_DONTNEED)) {
			perror("madvise(MADV_DONTNEED)");
			exit(1);
		}
	}

	pause();
	return 0;
}
