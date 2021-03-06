/* 什么是变量;所谓变量不要浅显的认为会变得量就是变量。
* 套用我们院长的问话“教室变不变;”变因为每天有不同的人在里面上课但又不变因为教室始终在那没有变大或变小。
* 这就是变量有一个不变的地址和一块可变的存储空间。
* 正常情况下我们只看到变量这个房间里面的东西也就是其内容但不会关注变量的地址但是C语言的指针就是这个房间的地址。
* 我们声明变量就相当于盖了间房子存放东西我们可以直接观看房子里的东西而声明指针就是相当于获得了一个"定位器"
* 当用指针指向某个变量时就是用指针给变量定位以后我们就可以用指针找到他所“跟踪”的变量并可以获得里面的内容。
* 那结构体呢;结构体就相当于是有好几个房子组成的别墅几个房子绑定在一起使用。
* 假设现在有很多这种别墅分布在一个大迷宫里每间别墅里都有一间房子。
* 里面放了另一个别墅的位置信息现在你手拿"定位器"找到了第一栋别墅从里面得到了你想要的东西 链表的数据部分,
* 然后把下一栋别墅的位置计入你的"定位器"再走向下一栋别墅……如此走下去知道走到某地下一栋别墅信息没有了 
*/你的旅行结束。这就是链表一次遍历的过程。p=p->next 的含义了吧
==========================================
typedef struct          // 定义一个结构体类型：DATA
{
    char key[10];       // 结构体成员：key
    char name[20];      // 结构体成员：name
    int age;            // 结构体成员：age
}DATA;
    
DATA data;              // 声明一个结构体变量
DATA *pdata;            // 声明一个指向结构体的指针
    
// 访问数据操作如下：
data.age = 24;          // 结构体变量通过点运算符( . )访问
pdata->age = 24;        // 指向结构体的指针通过箭头运算符( -> )访问


==========================================
#include <stdio.h>
void pound(int n); //函数原型声明，表明该函数接受一个int类型的参数，下面的带入会自动转换
int main(void)
{
    int times = 5;
    char ch = '!';  //ASCII 码是33
    float f = 6.0;
    
    pound(times);   //这里多次调用函数pound
    pound(ch);
    pound(f);
  
    return 0;
}

void pound(int n)   //这里定义了函数的具体内容
{
    while (n-- > 0) /*
                     等同于
                     for (int i = 0; i < n; ++i)
                     意思是n 一直往下减1 直到最后一个值
                    */
        printf("#");
    printf("\n");
}

==========================================
//循环函数
#include <stdio.h>
#define SIZE 4
#define PAR 72
int main(void)
{
    int index, score[SIZE];
    int sum = 0;
    float average;
    
    printf("SIZE: %d \n", SIZE);
    for (index = 0; index < SIZE; index++)
    {
        scanf("%d", &score[index]);  //读取用户 4次分数, 并分别获得这四个变量的内存地址
        printf("%p\n", &score[index]);
    }
    printf("=====\n");
    for (index = 0; index < SIZE; index++)
        printf("%5d", score[index]);   //输入验证, %5d 数字之间的宽度为5个字符
    printf("\n");
    for (index = 0; index < SIZE; index++)
        sum += score[index];        //求总分数
    average = (float) sum / SIZE;   //求平均分
    printf("Sum of scores = %d, average = %.2f\n", sum, average);
    printf("of %.0f.\n", average - PAR);  //%.0f 是输出float 型或double 型数据，按定点格式，小数点以下占0位
    
    return 0;
}

==========================================
//循环加判断
#include <stdio.h>
void display(char cr, int lines, int width);   //提前声明display() 函数和它自带的参数类型
int main(void)
{
    char ch;
    int rows, cols; //行数和列数
    
    printf("Enter a character and two int:\n");
    while ((ch = getchar()) != '\n')    //获取一个字符
    {
        if (scanf("%d %d", &rows, &cols) != 2)
            break;
        display(ch, rows, cols);   //注意这里调用了下面的函数display()
        while (getchar() != '\n') //当获取换行符时跳过
            continue;
        printf("Enter another char and two integers;\n");
        printf("Enter a newline to quit.\n");
    }
    printf("Bye.\n");
    
    return 0;
}

void display(char cr, int lines, int width)
{
    int row, col;
    
    for (row = 1; row <= lines; row++)  //定义从1 开始打印，递增到输入值
    {
        for (col = 1; col <= width; col++)
            putchar(cr);                //输出getchar() 获得的字符
        putchar('\n');
    }
}

==========================================
//用指针传递地址
#include <stdio.h>
void interchange(int * u, int * v);

int main(void)
{
    int x =5, y = 10;
    printf("Originally x = %d and y = %d.\n", x, y);
    interchange(&x, &y); //把地址发送给函数
    printf("Now x = %d and y = %d.\n", x, y);
    
    return 0;
}

void interchange(int * u, int * v)
{
    int temp;
    temp = *u;  //temp 获得u 所指向对象的值, 赋值为x的值
    *u = *v;    //x = y（的值），将x 指针 指向y 地址
    *v = temp;  //y = temp(x的值)  将y指针 指向保存的 x地址
}

==========================================
//二维数组，求每年中各个月份的平均值
#include <stdio.h>
#define MONTHS 12   //一年的月份数
#define YEARS   5   //年数
int main(void)
{
    // 用2010～2014年的降水量数据初始化数值
    const float rain[YEARS][MONTHS] =       //建立2维数组
    {
        {4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
        {8.5, 8.2, 1.2, 3.2, 3.2, 4.2, 4.3, 1.2, 1.6, 4.4, 3.2, 4.1},
        {4.3, 4.3, 5.3, 3.0, 2.0, 1.2, 1.2, 0.2, 2.4, 2.4, 3.5, 6.6},
        {4.3, 1.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 2.4, 2.4, 3.5, 6.6},
        {8.5, 5.2, 1.2, 3.2, 3.2, 4.2, 5.3, 1.2, 3.6, 4.4, 3.2, 4.1},
    };
    int year, month;
    float subtot, total;
    
    printf("year rainfall (inches)\n");
    for (year = 0, total = 0; year < YEARS; year++)     //每年，各月的降水量总和
    {
        for (month = 0, subtot = 0; month < MONTHS; month++)
            subtot += rain[year][month];                //subtot每年各个月的和
        printf("%5d %15.1f\n", 2010 + year, subtot);    //注意year是从0开始的
        total += subtot;    // 5 年的总降水量
    }
    printf("\nThe yearly average is %.1f inches.\n\n", total / YEARS);
    printf("MONTHLY AVERAGES:\n\n");
    printf(" JAN  FEB  MAR  APR  MAY  JUN  JUL  AUG  SEP  OCT ");
    printf(" NOV  DEC\n");
    
    for (month = 0; month < MONTHS; month++)            //每个月 各年的
    {
        for (year = 0, subtot = 0; year < YEARS; year++)
            subtot += rain[year][month];                //指定月份各年的合计
        printf(" %1.1f ", subtot / YEARS);               //指定月份的平均值
    }
    printf("\n");
    
    return 0;
}

==========================================
//用指针打印数组的地址编码
#include <stdio.h>
#define SIZE 4
int main(void)
{
    short dates[SIZE];
    short * pti;        //short 类型的指针
    short index;
    double bills[SIZE];
    double * ptf;       //double 类型的指针
    pti = dates;        //把数组dates地址赋予pti
    ptf = bills;
    printf("%26s %15s\n", "short 2 byte", "double 8 byte");
    for (index = 0; index < SIZE; index++)  //指针+1 增加一个存储单元，一个存储单元对应类型具体需要占用的字节数
        printf("pointers + %d: %10p   %10p\n", index, pti + index, ptf + index);
    return 0;
}

==========================================
//指针间计算，指针之间的计算是他们的位移量
#include <stdio.h>
int main(void)
{
    int urn[5] = { 100, 200, 300, 400, 500 };
    int *ptr1, *ptr2, *ptr3;
    
    ptr1 = urn;
    ptr2 = &urn[2];
    
    printf("ptr1 = %p, *ptr1 = %d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);
    
    // 指针加法
    ptr3 = ptr1 + 4;
    printf("ptr1 + 4 = %p, *(ptr1 + 4) = %d\n", ptr3, *(ptr1 + 4));
    ptr1++;
    printf("ptr1++ = %p, *ptr1 = %d, &ptr1 = %p\n", ptr1, *ptr1, &ptr1);
    ptr2--;
    printf("ptr2-- = %p, *ptr2 = %d, &ptr2 = %p\n", ptr2, *ptr2, &ptr2);
    
    // 回复初始值
    --ptr1;
    ++ptr2;
    printf("========\n");
    printf("--ptr1 = %p, ptr2 = %p\n", ptr1, ptr2);
    //一个指针减去另一个指针
    printf("++ptr2 - ptr1 = %td\n", ptr2 - ptr1);
    //一个指针减去一个整数
    printf("ptr3 = %p, ptr3 -2 = %p\n", ptr3, ptr3 - 2);
    
    return 0;
}


==========================================
//调换字符串指针位置排序
#include <stdio.h>
#include <string.h>
#define SIZE 81
#define LIM 20
#define HALT ""
void stsrt(char *strings [], int num);  //字符串排序函数
char * s_gets(char * st, int n);        //字符串获取函数

int main(void)
{
    char input[LIM][SIZE]; //存储输入的数组
    char *ptstr[LIM];   // 里边元素是指针的数组
    int ct = 0;         //输入计数
    int k;              //输出计数
    
    printf("LIM: %d\n", LIM);
    while (ct < LIM && s_gets(input[ct], SIZE) != NULL
        && input[ct][0] != '\0')
        {
            ptstr[ct] = input[ct]; //设置指针指向字符串
            ct++;
        }
    stsrt(ptstr, ct);   //字符串排序函数
    puts("\nHere's the sorted list:\n");
    for (k = 0; k < ct; k++)
        puts(ptstr[k]); //排序后的指针
    
    return 0;
}

//字符串-指针-排序函数
void stsrt(char *strings [], int num)   // ptstr[ct]元组 实际指向字符串，输入计数
{
    char *temp;
    int top, seek;
    
    for (top = 0; top < num - 1; top++)
        for (seek = top + 1; seek < num; seek++)
            if (strcmp(strings[top], strings[seek]) > 0) /* strcmp() 字符串比较方法
    若参数s0 和s1 字符串相同则返回0。
    s0 若大于s1 返回大于 0
    b > a
    说明字母靠后，需要调整
    s0 若小于s1 返回值小于 0
    a < b
    top seek 前后两个字符串的比较*/
    {
        temp = strings[top];    //temp 指针指向 strings 内含指针字符串的数组
        strings[top] = strings[seek];
        strings[seek] = temp;   //调换前后字符串指针的位置
    }
}

//字符串获取函数
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;
    
    ret_val = fgets(st, n, stdin); //读取一行，标准输入流stdin，存在st里
    if (ret_val)
        {
            while (st[i] != '\n' && st[i] != '\0')
                i++;
            if (st[i] == '\n')  //把换行符变成字符串结尾
            st[i] = '\0';
            else
                while (getchar() != '\n') //从控制台流中读取字符，直到按回车键结束
                    continue;
        }
    return ret_val;
}


==========================================
//结构指针在函数间传递
#include <stdio.h>
#include <string.h>

#define NLEN 30
struct namect{
    char fname[NLEN];
    char lname[NLEN];
    int letters;
};

void getinfo(struct namect *);
void makeinfo(struct namect *);
void showinfo(const struct namect *);
char * s_gets(char * st, int n);

int main(void)
{
    struct namect person;
    
    getinfo(&person);       //指针指向的是地址，所以这里要用取地址值
    makeinfo(&person);
    showinfo(&person);
    return 0;
}

void getinfo(struct namect * pst)
{
    printf("Please enter your first name.\n");
    s_gets(pst->fname, NLEN);                   //这里指针指向第一个元素，为其赋值
    printf("Please enter your last name.\n");
    s_gets(pst->lname, NLEN);
}

void makeinfo(struct namect * pst)
{
    pst->letters = strlen(pst->fname) + strlen(pst->lname);  //获取结构体前两个元素，并为第三个赋值
}

void showinfo(const struct namect * pst)    //因为该函数不改变结构体内容，所以声明为const
{
    printf("%s %s, your name contains %d letters.\n",
           pst->fname, pst->lname, pst->letters);
}

char * s_gets(char * st, int n)     //定义上面用到的s_gets函数
{
    char * ret_val;
    char * find;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');    //查找换行符并将指向换行符的指针，指向空字符
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')   //处理余下的字符
                continue;
    }
    return ret_val;
}


==========================================
//结构体在函数间传递

#include <stdio.h>
#include <string.h>

#define NLEN 30
struct namect {
    char fname[NLEN];
    char lname[NLEN];
    int letters;
};

struct namect getinfo(void);
struct namect makeinfo(struct namect);  //这里要返回一个结构
void showinfo(struct namect);
char * s_gets(char * st, int n);

int main(void)
{
    struct namect person;
    
    person = getinfo();     //将getinfo 的值 都赋值给结构体person，此时letters还没有被赋值
    person = makeinfo(person);
    showinfo(person);
    
    return 0;
}

struct namect getinfo(void)
{
    struct namect temp;                 //这里实例化一个temp，返回temp
    printf("please enter your first name.\n");
    s_gets(temp.fname, NLEN);
    printf("Please enter your last name.\n");
    s_gets(temp.lname, NLEN);
    
    return temp;
}

struct namect makeinfo(struct namect info)  //这里实例化一个info 为letters 赋值，将info返回
                                            //在上面的调用中 person 代表info（info是参数变量）
{
    info.letters = strlen(info.fname) + strlen(info.lname);
    
    return info;
}

void showinfo(struct namect info_2)
{
    printf("%s %s, your name contains %d letters.\n",
           info_2.fname, info_2.lname, info_2.letters);
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}


==========================================
//使用malloc 动态分配地址给指针

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SLEN 81
struct namect {
    char * fname;   //使用指针，这里没有提前分配空间
    char * lname;
    int letters;
};

void getinfo(struct namect *);  //声明结构体为指针
void makeinfo(struct namect *);
void showinfo(const struct namect *);
void cleanup(struct namect *);
char * s_gets(char * st, int n);

int main(void)
{
    struct namect person;
    
    getinfo(&person);   //取地址person，指针所指向的地址
    makeinfo(&person);
    showinfo(&person);
    cleanup(&person);
    
    return 0;
}

void getinfo(struct namect * pst) //pst 是结构体namect 的一个指针
{
    char temp[SLEN];    // 临时数组temp
    printf("Please enter your first name.\n");
    s_gets(temp, SLEN); //把字符串写入临时数组中
    // 分配内存用来存储名
    pst->fname = (char *) malloc(strlen(temp) + 1); //结构体指针指向结构体中一个元素
                                                    //malloc 返回的是内存首地址指针
                                                    //这里有可能申请失败，内存不足时
    // 查看这块内存
    printf("pst->fname = %lu \n", (strlen(temp)+1));
    printf("temp = %p \n", temp);
    // 把temp名拷贝到动态分配的内存（pst->fname）中
    strcpy(pst->fname, temp);
    printf("pst->fname = %p \n", temp);
    printf("Please enter your last name.\n");
    s_gets(temp, SLEN);
    pst->lname = (char *) malloc(strlen(temp) + 1);
    // 查看这块内存
    printf("pst->lname = %s \n", pst->lname);
    printf("pst->lname = %p \n", &(pst->lname));
    strcpy(pst->lname, temp);
}

void makeinfo(struct namect * pst)
{
    pst->letters = strlen(pst->fname) +
        strlen(pst->lname);
}

void showinfo(const struct namect * pst)
{
    printf("%s %s, your name contains %d letters.\n",
           pst->fname, pst->lname, pst->letters);
}

void cleanup(struct namect * pst)
{
    free(pst->fname);
    free(pst->lname);
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;
    
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}


==========================================
//柔性数组 & 伸缩型数组成员
#include <stdio.h>
#include <stdlib.h>

struct flex
{
    size_t count;
    double average;
    double scores []; //伸缩型数组成员
};

void showFlex(const struct flex * p); //函数showFlex 参数是结构体flex 不可变指针
int main(void)
{
    struct flex * pf1, *pf2;    //声明两个结构体的指针
    int n = 5;
    int i;
    int tot = 0;
    
    // 为结构和数组分配存储空间，结构体 + 5 个double的大小
    pf1 = malloc(sizeof(struct flex) + n * sizeof(double));
    pf1->count = n;
    for (i = 0; i < n; i++)
    {
        pf1->scores[i] = 20.0 - i;  //20，19，18，17，16
        tot += pf1->scores[i];
    }
    pf1->average = tot / n;     //这里是指向平均值的指针
    showFlex(pf1);
    
    n = 9;
    tot = 0;
    pf2 = malloc(sizeof(struct flex) + n * sizeof(double));
    pf2->count = n;
    for (i = 0; i < n; i++)
    {
        pf2->scores[i] = 20.0 - i / 2.0;
        tot += pf2->scores[i];
    }
    pf2->average = tot / n;
    showFlex(pf2);
    free(pf1);
    free(pf2);
    
    return 0;
}

void showFlex(const struct flex * p)
{
    int i;
    printf("Scores : ");
    for (i = 0; i < p->count; i++)
        printf("%g ", p->scores[i]);
    printf("\nAverage: %g\n", p->average);
}


==========================================
//结构数组 
#include <stdio.h>
#define FUNDLEN 50
#define N 2

struct funds {
    char    bank[FUNDLEN];
    double  bankfund;
    char    save[FUNDLEN];
    double  savefund;
};

double sum(const struct funds money [], int n);

int main(void)
{
    struct funds jones[N] = {       //这是一个数组，包含了两个funds 结构体
        {
            "Garlic-Melon Bank",
            4032.27,
            "Lucky's Savings and Loan",
            8543.94
            
        },
        {
            "Honest Jack's Bank",
            3620.88,
            "Party Time Savings",
            3802.91
        }
    };
    
    printf("The Joneses have a total of $%.2f.\n",sum(jones, N));
    
    return 0;
}

double sum(const struct funds money [], int n)
{
    double total;
    int i;
    
    for (i = 0, total = 0; i < n; i++)
        total += money[i].bankfund + money[i].savefund;
    
    return (total);
}


==========================================
/* a++ 先赋值后运算，++a 先运算后赋值
   存储在静态数据区的变量会在程序刚开始运行时就完成初始化，
   也是唯一的一次初始化。共有两种变量存储在静态存储区：
   全局变量和 static 变量，只不过和全局变量比起来，static 可以控制变量的可见范围. 
*/
    
#include <stdio.h>

int func(void){
    static int counter = 1;  //对main() 来说 counter的声明时隐藏的，所以每次都会带入新的值
    
    return ++counter;
}

int main(){
    int answer;
    
    answer = func() - func() * func();  //2 - 3 * 4
    printf("answer: %d\n", answer);
}    
    
    
    
    
