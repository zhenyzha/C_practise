#include <stdlib.h>
#include <stdio.h>

int
compare_integers( void const *a, void const *b)
{
    register int    const *pa = a;
    register int    const *pb = b;
    
    return *pa > *pb ? 1 : *pa < *pb ? -1 : 0;
}

int
main()
{
    int *array;
    int n_values;
    int i;
    
    printf("How many values are there? ");
    if(scanf("%d", &n_values ) != 1 || n_values <= 0){
        printf("Illegal number of values.\n");
        exit( EXIT_FAILURE );
    }

    array = malloc( n_values * sizeof( int ) );
    if( array == NULL ){
        printf( "Can't get memory for that many values.\n" );
        exit( EXIT_FAILURE );
    }

    //读取数值
    for( i = 0; i < n_values; i++ ){
        printf("Please enter values ");
        if( scanf( "%d", array + i) != 1 ){  //scanf 返回成功匹配赋值的个数
            printf("Error reading value #%d\n", i);
            free( array );
            exit( EXIT_FAILURE );
        }
    }

    //数值排序
    qsort( array, n_values, sizeof(int), compare_integers );

    //打印数值
    for( i = 0; i < n_values; i++ )
        printf("%d\n", array[i]);

    free(array);
    return EXIT_SUCCESS;
}
