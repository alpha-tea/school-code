#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#define Y CHAR_MAX
#define Z CHAR_MIN
#define DIGIT 5
#define ARRAY_SIZE 15
#define SIZE 10

int ideal_number(int a)
{
    int b = a;
    int sum = 1;
    int i = 2;
    while (b > 1) {
        if (b % i == 0) {
            sum += i;
            b /= i;
        } else
            ++i;
    }
    return (a == sum);
}

int prime_number(int number)
{
    int i = 2;
    for (i = 2; i < number && number % i != 0; ++i)
        ;
    return (i == number);
}

int string_size_special(char string[]) // ООЧЕНЬ СПЕЦИАЛЬНАЯ ФУНКЦИЯ!!!
{
    int c = 0;
    while (string[c] != '\0')
        c++;
    return c;
}

void string_reverse_special(char string[])   // Специальная функция для ScriptedEngeneer(по особому заказу)
{
    int size = string_size_special(string);
    for (int j = 0; j < size / 2; ++j) {
        char c = string[j];
        string[j] = string[size - 1 - j];
        string[size - 1 - j] = c;
    }
}

void to_binary(unsigned char byte, char string[])
{
    int i;
    for (i = 0; i < CHAR_BIT && byte > 0; ++i) {
        string[i] = byte % 2 + '0';
        byte = byte >> 1;
    }
    string[i] = '\0';
    //printf("Source string = %s;\n",string);
    string_reverse_special(string);
    //printf("Reverse string = %s;\n",string);
}

void ScriptedEngeneer_1()
{
    int cout = 0;
    unsigned char n = 0;
    printf("Task from ScriptedEngeneer 1:\n");
    printf("Size of unsigned char: %d bytes and bits in char: %d;\n",sizeof (n), CHAR_BIT);
    printf("Size of unsigned short int: %d;\n",sizeof (unsigned short int));
    char binary[CHAR_BIT + 1];
    for (int i = 0; i <= CHAR_BIT; ++i)
        binary[i] = 0;
    for (unsigned short int j = 0x0000; j < 0x100; ++j) {
        n = j & 0x00ff;
        to_binary(n,binary);
        int size = string_size_special(binary);
        int i;
        for (i = 0; i < size && binary[i] == binary[size - i - 1]; ++i)
            ;
        if (i == size) {
            printf("%d\t%s\n",n,binary);
            ++cout;
        }
    }
    printf("Total palindroms[0..255]: %d", cout);
}

int natural_number(int n)
{
    int k = 0, x = 0, sum = 0, product = 1, sred_arif = 0;
    int sum_square = 0, sum_cube = 0, first_number = 0, sum_first_and_last = 0;
    while (n > 0) {
        x = n % 10;
        sum += x;
        product *= x;
        sum_square += x * x;
        sum_cube += pow(x,3);
        n /= 10;
        ++k;
        if (k == 1)
            first_number = x;
    }
    sred_arif = sum / k;
    sum_first_and_last = first_number + x;
    printf("a)the number of digits in it: %d\n",k);
    printf("b)the sum of his digits: %d\n",sum);
    printf("v)product of its numbers: %d\n",product);
    printf("g)arithmetic mean of its digits: %d\n",sred_arif);
    printf("d)the sum of the squares of its digits: %d\n",sum_square);
    printf("e)the sum of the cubes of its digits: %d\n",sum_cube);
    printf("zh)its first digit: %d\n",first_number);
    printf("z)the sum of its first and last digits: %d\n\n",sum_first_and_last);
    return 0;
}

int arif_sequence (int n, int f, int s)
{
    printf("Sequence: ");
    for (int i = 0; f < n; ++i, f += s)
        printf("%d ",f);
    printf("\n");
    return f;
}

int geom_seqence (int m, int g, int z)
{
    printf("Sequence: ");
    for (int i = 0; g < m; ++i, g *= z)
        printf("%d ",g);
    printf("\n");
    return g;
}

void fibonachi (int n)
{
    int a = 1, b = 1, c = 0;
    printf("Fibonachi: %d %d ", a, b);
    while (c < n) {
        c = a + b;
        a = b;
        b = c;
        printf("%d ",c);
    }
    if (c == n)
        printf("\nYes, n is a fibonacci number!\n\n");
    else
        printf("\nNo, n is not a Fibonacci number!\n\n");
}

void number_of_degrees (int n)
{
    int i,k,a = 1;
    for ( i = 3, k = 5; (i <= n || k <= n) && i != n && k != n; i *= 3, k *= 5) {
        ++a;
        printf("%d:%d\n",i,k);
    }
    if ( i == n)
        printf("n - %d power of 3\n\n",a);
    else
        printf("Number n is not a power of 3\n");
    if (k == n)
        printf("n - %d power of 5\n\n",a);
    else
        printf("Number n is not a power of 5\n\n");
}

int evklid_first_step(int a, int b)
{
    int c,d,i = 0;
    printf("Algoritm Evklida\n");
    while (a != 0 && b != 0) {
        if (a > b) {
            c = a;
            a %= b;
            ++i;
            printf("%d)a(%d) > b(%d);\nTotal: a = %d;\n\n",i,c,b,a);
        } else {
            d = b;
            b %= a;
            ++i;
            printf("%d)b(%d) > a(%d)\nTotal: b = %d;\n\n",i,d,a,b);
        }
    }
    return a + b;
}

int factorial(int n);

int lcm (int a, int b)
{
    return (abs(a * b) / evklid_first_step(a,b));
}

double summary(int n)
{
    if (n <= 1 && n > 10) {
        printf("You entered incorrect value!!!!\n");
        return -1;
    }
    double result = 1;
    for (int i = 1; i <= n; ++i)
        result += 1.0 / (double)factorial(i);
    return result;
}

int factorial(int n)
{
    int result = 1;
    for (; n > 0; --n) {
        result = result * n;
    }
    return result;
}

int value(int a, int n, int base)
{
    if (n <= 0 && a <= 0) {
        printf("You entered incorrect value!!\n");
        return -1;
    }
    int s = 0;
    printf("Binary:");
    for (int i = 1; i <= n && a > 0; ++i) {
        printf("%d",a % base);
        s += a % base;
        a = a / base;
    }
    printf("\n");
    return s;
}

int cubing(int n)
{
    /*    int m = 1, r = 0;
    for (int i = 1; i < n; ++i)
        m += i * 2;
    r += m;
    for (int i = 1; i< n; ++i) {
        m += 2;
        r += m;
    }
    return r; */
    int value = 1; int value_help_1 = 2; int value_help_2 = 1; int k = 1;
    printf("Making cube of %d; ",n);
    for (int i = 1; i < n; ++i) {
        value += value_help_1;
        value_help_1 += 2;
        value_help_2 = value;
        printf(" i = %d: value = %d;",i,value);
        for (k = 1; k <= i;++k) {
            value_help_2 += value + (2 * k);
            printf("r = %d; ",value_help_2);
        }
    }
    printf("\n");
    return value_help_2;

}

int squaring(int n)
{
    int value = 1;
    int help_value = 2;
    for (int i = 1; i <= n; ++i) {
        printf("%d ^ 2 = %d;\n",i,value);
        value += help_value + 1;
        help_value += 2;
    }
    return 0;
}

int sqrt_5_92()
{
    double sqrt = 0, prev_sqrt = sqrtf(50);
    for (int i = 49; i > 0; --i) {
        sqrt = sqrtf(i) + prev_sqrt;
        prev_sqrt = sqrt;
    }
    printf("%.5f\n\n",sqrt);
    return 0;
}

int numerical_generation_int()
{
    srand(time(NULL));
    int i = 1, a = 0, sum = 0;
    while (i <= 10) {
        a = rand() % 10;
        sum += a;
        printf("%d ",a);
        ++i;
    }
    printf("\n");
    return sum;
}

void invert_1(const char s[], int len)
{
    if (len <= 0) {
        printf("You entered incorrect lenth\n");
        return;
    }
    while (--len >= 0)
        printf("%c",s[len]);
}

int multiply(int x, int y)
{
    //1 вариант, сделать битовый сдвиг.
    int result =  0;
    for ( int i = 0; i < y; ++i) {
        result += x;
    }
    return result;
}

double exponentiation(double a, unsigned int n)
{
    if (n == 0) {
        printf("n not natural value\n");
        return -1;
    }
    double r = a;
    for (unsigned int i = 1; i < n; ++i) {
        r *= a;
    }
    return r;
}

int group_values(int n,int g)
{
    if (n % g != 0) {
        printf("chisla ne delyatsa na gropy.\n");
        return -1;
    }
    int raznost_1 = 0,raznost_2 = 0;
    for (int i = n; i > 0; i -= g) {
        raznost_2 = i * i;
        for (int j = 1; j < g; ++j) {
            int m = (i - j) * (i - j);
            raznost_2 -= m;
            printf("r2 = %d\n",raznost_2);
        }
        raznost_2 *= raznost_2;
        printf("r2 ^ 2 = %d\n",raznost_2);
        if ( raznost_1 == 0)
            raznost_1 = raznost_2;
        else
            raznost_1 -= raznost_2;
        printf("r1 = %d\n",raznost_1);
    }
    return raznost_1;
}

void intro()
{
    // 10101110 = 0 * 2^0 + 1 * 2^1 + 1 * 2^2 + 1 * 2^3 + 0 * 2^4 + 1 * 2^5 + 0 * 2^6 + 1 * 2^7 =
    // 0 + 2 + 4 + 8 + 0 + 32 + 0 + 128 = 174
    // = 0xAE
    printf("Hello World!\n");
    int a = 10;
    printf("5\n");
    printf("Integer a = %d\n", a);
    char b = 's';
    printf("Char b = %d\n", b);
    char c[7] = "Hello!";
    printf("String c = %s\n",c);
    double pi = 3.14;
    printf("Pi = %3.1f\n",pi);
    printf("int a:");
    scanf("%d", &a);
    printf("A = %d\n", a);
    printf("Enter string:");
    scanf("%s",c);
    printf("String = %s\n",c);
    printf("1 13 49\n");
    printf("%c\n%c\n%c\n%c\n%c\n%c\n%c\n",c[0],c[1],c[2],c[3],c[4],c[5],c[6]);
    int x = 5, y = 5;
    printf("X * 25 =%d * 25 = %d\n",x, x * 25);
    printf("X * Y = %d * %d = %d\n",x, y, x * y);
    printf("2 * x = %d\n", 2 * x);
    printf("X^2 = %d\n", x * x);
    printf("-7.5 * x^2 = %f\n", -7.5 * x * x);
    printf("sin (0..1) = %3.2f..%3.2f\n", sin(0.0), sin(1.0));
}

void chapter_1()
{
    //Задачи Златопольского
    //Глава 1
    double a = 5,b = 5,c = 5,d = 0,x = 5;
    double r = (-b + 1 / a) / (2 / c);
    printf("1.15g:(-b + 1 / a) / (2 / c) = (-%1.0f + 1 / %1.0f) / (2 - %1.0f) = %3.2f\n",b,a,c,r);
    r = 1 / (1 + (a + b) / 2 );
    printf("1.15z:1 / (1 + (a + b) / 2) = 1 / (1 + (%1.0f + %1.0f) / 2) = %1.2f\n",a,b,r);
    int m = 2, n = 3;
    printf("1.15k:(2 ^ (m ^ n)) = 2 ^ %d ^ %d = %d\n",m,n,(int)pow(2,pow(m,n)));
    printf("1.16F:\na * x + b \n---------\nc * x + d = \n");
    a = 1, b = 2, c = 3, d = 4, x = 5;
    double r1 = a * x + b;
    double r2 = c * x + d;
    printf("r1 / r2 = %.2f / %.2f = %.2f\n",r1,r2,r1 / r2);
    printf("1.16H:\n2 * sin a + b \n-------------\n2 * cos a - b\n-------------\n      2\n");
    r1 = 2 * sin(a) + b;
    r2 = 2 * cos(a) - b;
    printf("r1 / r2 = %.2f / %.2f = %.2f\n",r1,r2,r1 / r2);
    double Pi = 3.14;
    int R = 5;
    printf("1.17g:2PiR = 2 * %1.2f * %d = %3.1f\n",Pi,R, 2 * Pi * R);
    a = 20,b = 15,c = 56,d = 17;
    printf("1.17H:(a * d) + (b * c) / a * d = (%2.1f * %2.1f) + (%2.1f * %2.1f) / %2.1f * %2.1f = %1.3f\n",
           a,d,b,c,a,d,((a * d) + (b * c)) / (a * d));

    double m1 = 5, v = 10, g = 10, h = 50;
    printf("1.17G:((m * v ^ 2) / 2) + (m * g * h) = ");
    r = (m1 * v * v) / 2 + (m1 * g * h);
    printf("(%1.0f * %2.0f ^ 2) / 2) + (%1.0f * %2.0f * %2.0f) = %4.0f\n",m1,v,m1,g,h,r);
    int s1 = 14,k1 = -3,d1 = 0;
    printf("d:= s + 1 = %d + 1 = %d\n",s1,s1 + 1);
    d = s1 + 1;
    printf("s:= d = %d\n",d1);
    s1 = d1;
    k1 = 2 * s1;
    printf("k:= 2 * s = 2 * %d = %d\n",s1,k1);
    s1 = 0,d1 = 0,k1 = 30;
    d1 = k1 - 5;
    printf("d:= k - 5 = %d - 5 = %d\n",k1,d1);
    k1 = 2 * d1;
    printf("k:= 2 * d = 2 * %d = %d\n",d1,k1);
    s1 = k1 - 100;
    printf("s:= k - 100 = %d - 100 = %d\n",k1,s1);
    //1.23 Вычисление по известным формулам.
    printf("1.23:y = (a ^ 2 + 10) / (sqrt(a ^ 2 + 1)) = ");
    a = 3;
    r1 = pow(a,2) + 10;
    r2 = sqrt(pow(a,2) + 1);
    printf("r1 / r2 = %.3f / %.3f = %.3f\n",r1,r2,r1 / r2);
    printf("abs(-10.0)%f\n",fabs(-10.0));
    int x1 = 3 , y1 = 0;
    printf("1.22a:y = 7 * x ^ 2 - 3 * x + 6 = 7 * %d ^ 2 - 3 * %d + 6 = ",x1,x1);
    y1 = 7 * (x1 * x1) - (3 * x1) + 6;
    printf("%d\n",y1);
    double h1 = 10, r3, r4, R1 = 6350;
    printf("1.27:Gorizont = (R + h1) ^ 2 - (R ^ 2) = (%.2f + %.2f) ^ 2 - %.2f = ",R1,h1,R1);
    r3 = pow((R1 + h1),2);
    r4 = pow(R1,2);
    printf("r3 - r4 = %.2f - %.2f = %.2f\n",r3,r4,sqrt(r3 - r4));
    int s = 0, v_i = 0, a_i = 10;
    v_i = pow(a_i,3);
    s = 6 * pow(a_i,2);
    printf("1.28:V = a ^ 3 = %d ^ 3 = %d; ",a_i,v_i);
    printf("S = 6 * a ^ 2 = 6 * %d ^ 2 = %d\n",a_i,s);
    double  z = 0, x2 = 5, y = 8;
    printf("1.30a:z = x ^ 3 - 2.5xy + 1.78x ^ 2 - 2.5y + 1 = ");
    z = pow(x2,3) - (2.5 * x2 * y) + (1.78 * pow(x2,2)) - (2.5 * y) + 1;
    printf("%.1f ^ 3 - 2.5 * %.1f * %.1f + 1.78 * %.1f ^ 2 - 2.5 * %.1f + 1 = ",x2,x2,y,x2,y);
    printf("%3.2f\n",z);
    int n1 = 13, f = 42;
    double sred_arif = 0, sred_geom = 0;
    sred_arif = (n1 + f) / 2;
    printf("1.31: sred_arif = (n + f) / 2 = (%d + %d) / 2 = %3.1f;\n",n1,f,sred_arif);
    sred_geom = pow(n1 * f, 1.0 / 2.0);
    printf("\tsred_geom = pow(n * f, 1.0 / 2.0) = pow(%d * %d, 1.0 / 2.0) = ",n1,f);
    printf("%0.2f\n",sred_geom);
    int kat_1 = 3, kat_2 = 4, gip = 0 , P = 0;
    gip = sqrt(pow(kat_1,2) + pow(kat_2,2));
    printf("1.37: Gipoteniza = sqrt(pow(kat_1,2) + pow(kat_2,2)) = ");
    printf("sqrt(pow(%d,2) + pow(%d,2)) = %d;\n",kat_1,kat_2,gip);
    P = kat_1 + kat_2 + gip;
    printf("P = kat_1 + kat_2 + gip = %d + %d + %d = %d\n",kat_1,kat_2,gip,P);
    double b1 = 5, a1 = 5;
    x = 0;
    y = 0;
    x = ((2 / (pow(a1,2) + 25)) + b1) / (sqrt(b1) + (a1 + b1) / 2);
    printf("1.40:x = ((2 / (pow(a,2) + 25)) + b) / (sqrt(b) + (a + b) / 2) = \n");
    printf("((2 / (pow(%.2f,2) + 25)) + %.2f) / (sqrt(%.2f) + (%.2f + %.2f) / 2) = ",a1,b1,b1,a1,b1);
    printf("%.3f\n",x);
    y = (fabs(a1) + 2 * sin(b1)) / (5.5 * a1);
    printf("y = (abs(a) + 2 * sin(b)) / (5.5 * a) = ");
    printf("(abs(%.2f) + 2 * sin(%.2f)) / (5.5 * %.2f) = ",a1,b1,a1);
    printf("%.3f\n",y);
    double apple = 30.5, candy = 115, cookies = 20.99, m4 = 1, m2 = 2, m3 = 3, SUMM = 0;
    printf("1.52: SUMM = apple * m1 + candy * m2 + cookies * m3 = ");
    SUMM = apple * m4 + candy * m2 + cookies * m3;
    printf("%.2f * %.2f + %.2f * %.2f + %.2f * %.2f = %.2f\n",apple,m4,candy,m2,cookies,m3,SUMM);
    double t_age = 11, m_age = 24;
    printf("1.54:Average age = (t_age + m_age) / 2 = ");
    b = (t_age + m_age) / 2;
    printf("(%.1f + %.1f) / 2 = %.1f\n",t_age,m_age,b);
    x = fabs(t_age - b);
    y = fabs(m_age - b);
    printf("difference_Tanya = %.1f\n",x);
    printf("difference_Mitya = %.1f\n",y);
    double cl = 20 , kv , fg;
    fg = cl * 1.8 + 32;
    printf("1.57: Fahrenheit = cl * 1.8 + 32 = %.1f * 1.8 + 32 = %.1f\n",cl,fg);
    kv = (cl + 273.15);
    printf("Kelvin = cl + 273.15 = %.1f + 273.15 = %.1f",cl,kv);
    fg = 451;
    cl = (fg - 32) / 1.8;
    printf("1.58:cl = (fg - 32) / 1.8 = (%.1f - 32) / 1.8 = %0.1f\n",fg,cl);
    int t = 5, u = 2;
    printf("1.59: t = %d; u = %d > ",t,u);
    t = t - u;
    u = t + u;
    t = u - t;
    printf("t = %d; u = %d\n",t,u);
    int b2 = 5, c1 = 10, a2 = 1;
    t = 0;
    printf("1.60a: b = %d; a = %d; c = %d > b = c = %d;",b2,a2,c1,c1);
    t = b2;
    b2 = c1;
    c1 = a2;
    a2 = t;
    printf(" a = b = %d;",a2);
    printf(" c = a = %d\n",c1);
    b2 = 5;
    c1 = 10;
    a2 = 1;
    t = b2;
    b2 = a2;
    printf("1.60b: b = %d; a = %d; c = %d > b = a = %d;",t,a2,c1,b2);
    a2 = c1;
    c1 = t;
    printf(" c = b = %d;",c1);
    printf(" a = c = %d\n", a2);
    int j = 2, k = 0, l = 0, m5 = 0;
    k = j * j;
    k = k * j;
    k = k * k;
    k = k * j;
    printf("1.61v:j = %d ;j ^ 7 = %d\n",j,k);
    j = 2;
    k = 0;
    l = 0;
    k = j * j; // j^2
    l = k * j; // j^3
    m5 = k * l; // j^5
    printf("m = j^5 = %d\n",m5);
    n = m5 * m5 * l * l * l;
    printf("n = m ^ 2 + l ^ 3 = %d ^ 2 * %d ^ 3 = %d\n",m5,l,n);
    printf("j ^ 3 = %d;",l);
    k = l * k; // j^5
    k = k * k; // j^10
    printf("j ^ 10 = %d",k);
    printf("7 / 3 = %d,%d\n",7/3,7%3);
}

void chapter_2()
{
    //Задачи Златопольского
    //Глава 2
    printf("2.1\n");
    int sm = 134, m = 100;
    m = sm / m;
    printf("%dsm in m = %d\n\n",sm,m);
    printf("2.3\n");
    int kg = 1500, t = 0;
    t = kg / 1000;
    printf("kg / 1000 = %d / 1000 = %d\n\n",kg,t);
    printf("2.6\n");
    int min = 0, sec = 4632, hour = 0, a = 3600;
    // double a = 0;
    printf("sec = %d\n", sec);
    hour = sec / 3600;
    printf("hour = %d\n",hour);
    a = sec - a;
    min = (sec % 3600) / 60;
    printf("min = %d\n",min);
    a = sec % 60;
    printf("sec = %d\n\n",a);
    printf("2.12\n");
    int b = 194,b1 = 0, b2 = 0, b3 = 0, help = 0;
    b1 = b % 10;
    b2 = b % 100 / 10;
    b3 = b / 100;
    printf("edenitsy = %d\n",b1);
    printf("desyatky = %d\n",b2);
    printf("sotny = %d\n",b3);
    help = b1 + b2 + b3;
    printf("summ = %d + %d + %d = %d\n",b1,b2,b3,help);
    help = b1 * b2 * b3;
    printf("proizv = %d * %d * %d = %d\n\n",b1,b2,b3,help);
    printf("2.13\n");
    b = 123;
    b1 = b % 10;
    b2 = b % 100 / 10;
    b3 = b / 100;
    help = b1;
    b1 = b3;
    b3 = help;
    int invert = b1 + b2 * 10 + b3 * 100;
    printf("%d > %d\n\n",b,invert);
    printf("2.14\n");
    b1 = b % 10;
    b2 = b % 100 / 10;
    b3 = b / 100;
    help = b3;
    b3 = b2;
    b2 = b1;
    b1 = help;
    int roll_l = b1 + b2 * 10 + b3 * 100;
    printf("%d sdig cifr v levo po cikly %d\n\n",b,roll_l);
    printf("2.16\n");
    b1 = b / 100;
    b2 = b % 100 / 10;
    b3 = b % 10;
    help = b1;
    b1 = b2;
    b2 = help;
    int numm = b3 + b2 * 10 + b1 * 100;
    printf("%d > %d\n\n",b,numm);
    help = b3;
    b3 = b2;
    b2 = help;
    int numm_2 = b3 + b2 * 10 + b1 * 100;
    printf("2.17: %d > %d\n\n",numm,numm_2);
    printf("2.18\n");
    b = 123;
    b1 = b % 10;
    b2 = b % 100 / 10;
    b3 = b / 100;
    printf("%d%d%d\n",b3,b2,b1);
    printf("%d%d%d\n",b1,b2,b3);
    printf("%d%d%d\n",b1,b3,b2);
    printf("%d%d%d\n",b3,b1,b2);
    printf("%d%d%d\n",b2,b3,b1);
    printf("%d%d%d\n\n",b2,b1,b3);
    printf("2.23\n");
    int hund = 0, thous = 0;
    b = 3649;
    hund = b / 100 % 10;
    printf("hundred = %d\n",hund);
    thous = b / 1000;
    printf("thousend = %d\n\n",thous);
    printf("2.24\n");
    b = 237;
    //help = b / 100;
    //b1 = b % 100;
    int x = 2;
    x += 37 * 10;
    printf("%d > %d\n",x,b);
    int x1 = x - (x % 10);
    printf("372 - (372 %% 10) = %d\n",x1);
    int x2 = x1 / 10;
    printf("370 / 10 = %d\n",x2);
    int x3 = (x % 10) * 100 + x2;
    printf("(372 %% 10) * 100 + %d = %d\n\n",x2,x3);
    printf("2.26\n");
    b = 564;
    x = b % 10 * 100;
    printf("%d = b %% 10 * 100 = %d\n",b,x);
    x1 = (b / 10) + x;
    printf("%d = (%d / 10) + %d = %d\n\n",x1,b,x,x1);
    printf("2.28\n");
    b = 546;
    b1 = b % 10;
    b2 = b % 100 / 10;
    b3 = b / 100;
    x = (b2 * 100) + (b3 * 10) + b1;
    printf("%d = %d\n\n",b,x);
    printf("2.43\n");
    int y = 2;
    x = 5;
    x1 = x % y;
    printf("(x / y) or (y / x) = 1 else any\n\n");
    int y1 = y % x;
    int r = 0;
    //r = (x % y == 0) || (y % x == 0);
    r = (x1 * y1) + 1;
    printf("(%d / %d) or (%d / %d) = %d\n\n",x,y,y,x,r);
    printf("2.34\n");
    int summ_1 = 0, summ_2 = 0, m1 = 8, n1 = 2, n2 = 7;
    printf("n = %d%d, m = %d\n",m1,n1,n2);
    summ_1 = n1 + n2;
    summ_2 = m1 + summ_1 / 10 + summ_1 % 10;
    printf("summ_numbers = %d\n\n",summ_2);
    printf("2.37\n");
    int k = 3;
    printf("para = %d\n",k / 2);
    printf("number = %d - 1 + 10 = %d\n",k,k + 9);
}

double kalk (int c1, int c2)
{
    //Задачи Златопольского
    // калькулятор для главы 3
    double c3 = 0;
    c3 = c1 + c2;
    printf("SUMM = %.0f\n",c3);
    c3 = c1 - c2;
    printf("DIFFER = %.0f\n",c3);
    c3 = c1 * c2;
    printf("PROD = %.0f\n",c3);
    c3 = c1 / c2;
    printf("DIVIS = %.0f,",c3);
    c3 = c1 % c2;
    printf("%.0f\n",c3);
    c3 = pow(c1,c2);
    printf("EXPON = %.0f\n",c3);
    c3 = sqrt(c1);
    printf("sqrt(a1) = %.1f\n",c3);
    c3 = sqrt(c2);
    printf("sqrt(a2) = %.1f\n",c3);
    return c3;
}

int chars_counter(char s[],  char c)
{
    int index = 0, counter = 0;
    while (s[index] != '\0'){   //Частота определённой буквы.
        if (s[index] == c)
            counter++;
        index++;
    }
    return counter;
}

int length(char s[])
{
    int len = 0;                //Длинна строки.
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

void invert(char s[])
{
    int len = length(s);
    while (--len >= 0)
        printf("%c",s[len]); //Инвертирование имени.
}

void lesson_test_1()
{
    //int i1 = 1;
    //printf("i = ++i + ++i = %d\n",++i1 + ++i1);   //DANGER CODE!!!!!
    unsigned char x = ' ';
    const unsigned char end_x = 129;
    printf("Code    16-x system     symbol\n\n");
    while (x < end_x)
    {
        int k = 0;
        while (k < 3) {
            printf("%3d",x);
            printf("%#11x",x);
            printf("%13c\t",x);
            ++x;
            ++k;
        }
        printf("\n");
    }
    // Номер 3.
    char i = 1;
    unsigned char i2 = 1, bits = 0;
    while (i > 0) {
        bits++;
        i *= 2;
    }
    printf("bits in char = %d,bytes = %d\n",bits,bits / 8);
    bits = 0;
    while (i2 > 0) {
        bits++;
        i2 *= 2;
    }
    printf("bits in unsigned char = %d, bytes = %d\n",bits,bits / 8);
    printf("\nNumber 3.\nChar = %d\n%d..%d\n",sizeof i,Z,Y);
    printf("Unsigned char = 0..%d\n",UCHAR_MAX);
    // Номер 4.
    double c = 1, f = 0, k = 0;
    const double m = 32;
    const double n = 1.8;
    const double l = 273.15;
    printf("\nNumber 4.\nCelsius\t   Fahrenheit\tKelvin\n\n");
    while (c < 55) {
        k = c + l;
        f = c * n + m;
        printf("%5.1f\t%10.1f\t%6e\n",c,f,k);
        c += 5.5;
    }
    //Номер 5.
    const double  dollars = 1 / 73.61;
    const double  euro = 1 / 79.63;
    double Dollar = 0, Euro = 0;
    int Ruble = 0, a1 = 1, help = 0;
    char name[15];
    printf("\nNumber 5\nPlease, enter your name!: ");
    scanf("%s", name);
    printf("Hello, %s!\n",name);
    printf("Your name consists of %d letters\n",length(name));
    printf("And also the name takes %d bytes in memory\n",sizeof (name));
    //size_t v1;
    //printf("%d",sizeof char );
    printf("Your inverted name:");
    invert(name);
    printf("\n");
    help = chars_counter(name,'a');
    printf("Quantity a in your name = %d\n",help);
    printf("Ok,now indicate your salary month in Ruble: ");
    scanf("%d", &Ruble);
    printf("\nHere is painted all your salary for the year in different currencies\n");
    printf("\nMounth\tRuble\tDollars\t Euro\n");
    help = Ruble;
    while (a1 < 13) {
        Dollar = Ruble * dollars;
        Euro = Ruble * euro;
        printf("%d\t%4d\t%4.f\t%4.f\n",a1,Ruble,Dollar,Euro);
        Ruble += help;
        a1++;
    }
    int per = 0;
    int per2 = 1, per3;
    per3 = (per || per2);
    printf("%d",per3);
    getchar();
}

void chapter_3()
{
    //Задачи Златопольского
    //Глава 3
    //calc
    int a1 = 0, a2 = 0;
    printf("Hello my friend!!!\n");
    printf("This is Calculator 3000 SUPER\n");
    printf("Please enter two numbers: ");
    scanf("%d %d",&a1,&a2);
    kalk(a1,a2);
    //glava 3
    //3.9
    printf("3.9:\n");
    int X1 = 1, Y1 = 0, Z1 = 0, help1, help2, help3;
    help1 = !X1 || !Y1 || !Z1;
    help2 = (!X1 || !Y1) && (X1 || Y1);
    help3 = (X1 && Y1) || (X1 && Z1) || !Z1;
    printf("NOT X OR NOT Y OR NOT Z = !%d || !%d || !%d = %d\n",X1,Y1,Z1,help1);
    printf("(NOT X OR NOT Y) AND (X OR Y) = (!%d || !%d) && (%d || %d) = %d\n",X1,Y1,X1,Y1,help2);
    printf("X AND Y OR X AND Z OR NOT Z = ");
    printf("%d && %d || %d && %d || !%d = %d\n\n",X1,Y1,X1,Z1,Z1,help3);
    //3.10
    printf("3.10:\n");
    int A = 0, B = 0, C = 1;
    help1 = (!A || !B) && !C;
    printf("(NOT A OR NOT B) AND NOT C = (!%d || !%d) && !%d = %d\n",A,B,C,help1);
    help2 = (!A || !B) && (A || B);
    printf("(NOT A OR NOT B) AND (A OR B) = (!%d || !%d) && (%d || %d) = %d\n",A,B,A,B,help2);
    help3 = (A && B) || (A && C) || !C;
    printf("(A AND B) OR (A AND C) OR !C = (%d && %d) || (%d && %d) || !%d = %d\n\n",A,B,A,C,C,help3);
    //3.11
    int x = 1, y = 2, help = 0;
    help = (!(x * y < 0)) || (y > x);
    printf("3.11(x = 1, y = 2):\n");
    printf("zh:(!(x * y < 0)) || (y > x) = %d\n",help);
    help = (x >= 0) || (pow(y,2) != 4);
    printf("b:(x >= 0) || (pow(y,2) != 4) = %d\n",help);
    help = ((x * y) != 0) || (y > x);
    printf("d:((x * y) != 0) || (y > x) = %d\n\n",help);

    //3.13
    int a = 0, b = 0;
    printf("3.13:\n");
    while (a <= 1) {
        b = 0;
        while (b <= 1) {
            help = !(a && b);
            printf("a: NOT (A AND B) = !(%d && %d) = %d\n",a,b,help);
            help = !a || b;
            printf("b: NOT A OR B = !%d || %d = %d\n",a,b,help);
            help = a || !b;
            printf("v:A OR NOT B = %d || !%d = %d\n\n",a,b,help);
            ++b;
        }
        ++a;
    }
    //3.26
    int n = 0;
    printf("3.26:\na)");
    while (n < 8) {
        X1 = n % 2;
        Y1 = n % 4 / 2;
        Z1 = n / 4;
        printf("x = %d, y = %d,z = %d\n",X1,Y1,Z);
        help = !(X1 || Y1) && (!X1 || !Z) ;
        printf("a: NOT(X OR Y) AND (NOT X OR NOT Z) = ");
        printf("!(%d || %d) && (!%d || !%d) = %d\n",X1,Y1,X1,Z,help);
        help = !(!X1 && Y1) || (X1 && !Z);
        printf("b: NOT (NOT X AND Y) OR (X AND NOT Z) = ");
        printf("!(!%d && %d) || (%d && !%d) = %d\n",X1,Y1,X1,Z,help);
        help = X1 || (!Y1 && !(X1 || !Z));
        printf("c: X OR (NOT Y AND NOT(X OR NOT Z)) = ");
        printf("%d || (!%d && !(%d || !%d)) = %d\n\n",X1,Y1,X1,Z,help);
        ++n;
    }
    //3.27
    x = 5;
    y = 4;
    printf("a)3.27: a)X > 2 && Y > 3 = %d > 2 &&  %d > 3 = %d\n", x, y, (x > 2 && y > 3));
    help = 0 < (y <= 4) && (x < 5);
    printf("i)0 < y <= 4 && x < 5 = 0 < %d <= 4 && %d < 5 = %d\n",x,y,help);
    help = !((x > 0) && (x < 5));
    printf("zh)NOT((x > 0) AND (x < 5)) = %d\n",help);
    help = (x >= 0) && (y < 5);
    printf("v)(x >= 0) AND (y < 5) = %d\n\n",help);
    //3.31
    x = 10;
    help = (x % 5 == 0) || (x % 7 == 0);
    printf("3.31:\na)(N %% 5 == 0) || (N %% 7 == 0) = (%d %% 5 == 0) || (%d %% 7 == 0) = %d\n",x,x,help);
    help = (x % 4 == 0) || (x % 10 != 0);
    printf("b)(x %% 4 == 0) || (x %% 10 != 0) = (%d %% 4 == 0) || (%d %% 10 != 0) = %d\n\n",x,x,help);
    //3.19
    int a3 = 0, b1 = 0;
    printf("3.19:\n");
    while (a3 <= 1) {
        b1 = 0;
        while (b1 <= 1) {
            help = !(! a3 && ! b1) && a3;
            printf("NOT (NOT A AND NOT B) AND A = !(!%d && !%d) && %d = %d\n",a3,b1,a3,help);
            help = !(!a3 || !b1) || a3;
            printf("NOT (NOT A OR NOT B) OR A = !(!%d || !%d) || %d = %d\n",a3,b1,a3,help);
            help = !(!a3 || !b1) && b1;
            printf("NOT (NOT A OR NOT B) AND B = !(!%d || !%d) && %d = %d\n\n",a3,b1,b1,help);
            ++b1;
        }
        ++a3;
    }
    //3.25
    int n1 = 0, c1 = 0;
    printf("3.25:\na)");
    while (n1 < 8) {
        a1 = n1 % 2;
        b1 = n1 % 4 / 2;
        c1 = n1 / 4;
        printf("a = %d, b = %d,c = %d\n",a1,b1,c1);
        help = !(a1 && b1) && (!a1 || !c1);
        printf("NOT (A AND B) AND (NOT A OR NOT C)= %d\n",help);
        help = !(a1 && !b1) || (a1 || !c1);
        printf("NOT (A AND NOT B) OR (A OR NOT C) = %d\n", help);
        help = (a1 && !b1) || !(a1 || !c1);
        printf("A AND NOT B OR NOT (A OR NOT C) = %d\n\n",help);
        ++n1;
    }
    x = 3;
    y = 1;
    //3.32(А - З)
    printf("\n3.32\n");
    help = y >= 1 && x <= -2;
    printf("a)y >= 1 && x <= -2 = %d\n",help);
    help = y >= -2 && y <= 1.5;
    printf("b)-2 >= y <= 1.5 = %d\n",help);
    help = y <= 4 && x >= 1 && x <= 2;
    printf("v)y <= 4 && 1 <= x <= 2 = %d\n",help);
    help = x >= 1 && y >= 2 && y <= 4;
    printf("g)x >= 1 && 2 <= (y <= 4) = %d\n",help);
    help = (y >= 0 && x >= 2) || (y <= -1 && x >= 1);
    printf("d)(y >= 0 && x >= 2) || (y <= -1 && x >= 1) = %d\n",help);
    help = (y >= 1 && x >= 2) || (y <= -1.5 && x >= 2);
    printf("e)(y >= 1 && x >= 2) || (y <= -1.5 && x >= 2) = %d\n",help);
    help = x >= 1 && x <= 3 && y >= -2 && y <= -1;
    printf("zh)1 <= (x <= 3) && -2 <= (y <= -1) = %d\n",help);
    help = (y >= 0 && y <= 2 && x < 2) || (x >= 2);
    printf("z)(0.5 <= y <= 1.5 && x <=2) || (x >= 2) = %d\n\n",help);
    //3.34
    printf("3.34\n");
    int c_a = 0, c_b = 0, c_c = 0, c_d = 0;
    c_c = 7;
    help = (c_a == c_c) || (c_d == c_b);
    printf("a)%d\n",help);
    c_a = 3; // слон
    c_b = 4;
    c_c = 1; // пешка
    c_d = 6;
    help = abs(c_c - c_a) == abs(c_d - c_b);
    printf("b)slon on (%d,%d) and peshka (%d,%d) = %d\n",c_a,c_b,c_c,c_d,help);
    c_a = 5; // Ферзь
    c_b = 4;
    help = ((c_a == c_c) || (c_d == c_b)) || (abs(c_c - c_a) == abs(c_d - c_b));
    printf("v)ferz on (%d,%d) and peshka on(%d,%d) = %d\n",c_a,c_b,c_c,c_d,help);
}

void chapter_4()
{
    //Задачи Златопольского
    //Глава 4
    printf("Hello World!\n");
    int a_test = 0;
    while ((a_test = 0) != 0) {
        ;
    }
    for (int i = 0; i < 5;++i){
        continue;
        printf("da\n");
        break;
    }
    do {
        printf("net\n");
    } while (a_test != 0);
    if (a_test < 10) {
        printf("Hello ");
        if (a_test == 0)
            printf("World!!\n");
    } else {
        printf("Hi\n");
    }
    switch (a_test) {
    case 0:
        printf("Hello A!\n");
        break;
    case 1:
        printf("Hello B!\n");
        break;
    default:
        printf("Hello C!\n");
    }
    goto lab_1;
    printf("bez metki\n\n");
lab_1:
    printf("s metkoy\n\n");
    // glava 4
    int y = 0, x = 5;
    printf("4.1\n");
    if (x > 5) {
        y = pow(sin(x),2);
        printf("y = sin ^ 2 * x = sin ^ 2 %d = %d;\n\n",x,y);
    } else {
        y = 1 - 2 * sin(pow(x,2));
        printf("y = 1 - 2 * sin x ^ 2 = 1 - 2 * sin %d ^ 2 = %d;\n\n",x,y);
    }
    printf("4.5\n");
    y = 0;
    x = 1;
    if (x <= 2) {
        y = x;
        printf("1)y = x = %d\t(x = %d)\n",y,x);
    } else {
        y = 2;
        printf("1)y = %d\t\t(x = %d)\n",y,x);
    }
    y = 0;
    x = 3;
    if (x <= 3) {
        y = -x;
        printf("2)y = -x = %d\t(x = %d)\n\n",y,x);
    } else {
        y = -3;
        printf("2)y = %d\t(x = %d)\n\n",y,x);
    }
    double m1 = 0.75, v1 = 0.3;
    double m2 = 1.25, v2 = 0.75;
    double help = 0;
    printf("4.11\n");
    if ((m1 / v1) > (m2 / v2)) {
        help = m1 / v1;
        printf("the first material is denser than the second and equal to %.2f (kg / m ^ 3);\n\n",help);
    } else {
        help = m2 / v2;
        printf("the second material is denser than the first and equal to %.2f (kg / m ^ 3);\n\n",help);
    }
    double r1 = 5, u1 = 220;
    double r2 = 7, u2 = 110;
    printf("4.12\n");
    if ((u1 / r1) > (u2 / r2)) {
        help = u1 / r1;
        printf("The current in the first circuit is greater than in the second and equal to %.2f ampere;\n\n",help);
    } else {
        help = u2 / r2;
        printf("The current in the second circuit is greater than in the first and equal to %.2f ampere;\n\n",help);
    }
    printf("4.13(14)\n");
    double a = 1, b = 2, c = -3, disc = 0, r3, r4;
    disc = b * b - 4 * a * c;
    if (disc >= 0 && a != 0) {
        r3 = (-b + sqrt(disc)) / 2 * a;
        r4 = (-b - sqrt(disc)) / 2 * a;
        printf("disc > 0, %.2fx ^ 2 + %.2fx + %.2f = 0 \n",a,b,c);
        printf("x1 = %.2f; x2 = %.2f\n\n",r3,r4);
    } else {
        printf("disc < 0, no results.\n\n");
    }
    printf("4.15\n");
    int year = 1999, month = 5, day = 28;
    int year1 = 2020, month1 = 5, day1 = 27;
    if (month - month1 >= 1) {
        year = year1 - year;
        printf("He have %d years old\n\n",year);
    } else {
        if (day - day1 < 1) {
            year = year1 - year;
            printf("Days = %d;He have %d years old\n\n",day - day1,year);
        } else {
            year = year1 - year - 1;
            printf("He have %d years old\n\n",year);
        }
    }
    printf("4.16\n");
    int s1 = 10, s2 = 5; //s1 - площадь круга, s - площадь круга
    double pi = M_PI;
    if ((s1 / pi) <= (sqrt(s2) / 2))
        printf("a)Yes, will fit!\n");
    else
        printf("a)No, it does not fit!\n");
    s1 = 10, s2 = 4; //s1 - площадь круга; s2 - площадь квадрата.
    double l = sqrt(s2);
    double h = sqrt(pow((l / 2),2) + pow((l / 2),2)) ;
    if ((s1 / pi) >= h) {
        printf("b)Yes, will fit!\n\n");
    } else {
        printf("b)No, it does not fit!\n\n");
    }
    printf("4.37\n");
    int a1 = 2;
    if (a1 > -5 && a1 < 3) {
        printf("Yes belongs!\n\n");
    } else {
        printf("No does not belong!\n\n");
    }
    printf("4.39\n");
    a1 = 5;
    if (a1 == 5 || a1 == -1) {
        printf("Variable out of area!\n\n");
    } else {
        if (a1 < -1) {
            printf("Variable in the third area!\n\n");
        } else {
            if (a1 > 5)
                printf("Variable in the first area!\n\n");
            else
                printf("Variable in the second area!\n\n");
        }
    }
    printf("4.40\n");
    double f = 0, x1 = 3.1;
    if (x1 >= -2.4 && x1 <= 5.7) {
        f = pow(x1,2);
        printf("f(x) = f(%.2f ^ 2) = %.2f\n\n",x1,f);
    } else {
        f = 4;
        printf("f(x) = f(%.0f) = %.0f\n\n",x1,f);
    }
    printf("4.45\n");
    int b1 = 5, c1 = 6;
    a1 = 5;
    if (a1 == b1 || a1 == c1 || b1 == c1) {
        printf("Yes there is!\n\n");
    } else {
        printf("No, not available!\n\n");
    }
    printf("4.48\n");
    int h1 = 160, h2 = 170, h3 = 180;
    if (h1 == h2 && h1 == h3 && h2 == h3) {
        printf("Yes there is!\n\n");
    } else {
        printf("No, not available!\n\n");
    }
    printf("4.42\n");
    a1 = 1;
    b1 = 2;
    c1 = 3;
    if (b1 > a1 && b1 < c1) {
        printf("a)Yes, it does!\n\n");
    } else {
        printf("a)No, it does not!\n\n");
    }
    a1 = 1;
    b1 = 2;
    c1 = 3;
    if (a1 < b1 && a1 > c1) {
        printf("b)Yes, it does!\n\n");
    } else {
        printf("b)No, it does not!\n\n");
    }
    printf("4.49\n");
    a = 2;
    b = 1;
    c = -6;
    disc = b * b - 4 * a * c;
    if (a != 0 && disc >=0) {
        printf("disc > 0; disc = %.2f\n",disc);
        r3 = (-b + sqrt(disc)) / 2 * a;
        r4 = (-b - sqrt(disc)) / 2 * a;
        if (r3 == r4)
            printf("x = %.2f;\n\n",r3);
        else
            printf("x1 = %.2f; x2 = %.2f\n\n",r3,r4);
    } else
        printf("disc < 0, disc = %.2f or a = 0, no results.\n\n",disc);
    printf("4.50\n");
    int d = 5;
    a = 5;
    b = 7;
    c = 9;
    if (((a > c) && (b > d)) || ((a > d) && (b > c)))
        printf("No you can't!\n\n");
    else
        printf("Yes, you can!\n\n");
    printf("4.53\n");
    a1 = 1;
    b1 = 6;
    c1 = 6;
    x = 5;
    y = 3;
    if ((((x > a1) && (y > b1)) ||
         ((x > b1) && (y > a1))) ||
            ((y > c1) && (x > a1)) ||
            ((y > a1) && (x > c1)) ||
            ((y > c1) && (x > b1)) ||
            ((y > b1) && (x > c1)))
        printf("Yes, will fit!\n\n");
    else
        printf("No, it does not fit!\n\n");
    printf("4.60\n");
    a1 = 2376;
    int help1 = 0, help2 = 0, help3 = 0, help4 = 0;
    help1 = a1 % 10;
    help2 = a1 / 1000;
    help3 = a1 / 100 % 10;
    help4 = a1 / 10 % 10;
    if ((help1 == 2) ||
            (help1 == 7) ||
            (help2 == 2) ||
            (help2 == 7) ||
            (help3 == 2) ||
            (help3 == 7) ||
            (help4 == 2) ||
            (help4 == 7))
        printf("%d;\na)Included!\n\n",a1);
    else
        printf("%d;\na)Not included!\n\n",a1);
    if ((help1 == 3) ||
            (help1 == 6) ||
            (help1 == 9) ||
            (help2 == 3) ||
            (help2 == 6) ||
            (help2 == 9) ||
            (help3 == 3) ||
            (help3 == 6) ||
            (help3 == 9) ||
            (help4 == 3) ||
            (help4 == 6) ||
            (help4 == 9))
        printf("%d;\nb)Included!\n\n",a1);
    else
        printf("%d;\nb)Not included!\n\n",a1);
    printf("4.61\n");
    a1 = 1241;
    help1 = a1 / 1000;
    help2 = a1 / 100 % 10;
    help3 = a1 / 10 % 10;
    help4 = a1 % 10;
    printf("n = %d(%d,%d,%d,%d)\n",a1,help1,help2,help3,help4);
    if ((help1 == help4) && (help2 == help3))
        printf("Yes, palindrom!\n\n");
    else
        printf("No, not palindrom!\n\n");
    printf("4.64\n");               //  Тест на палиндромность
    char lucky[7] = "123987";       //
    int i = 0, s_l = 0, s_r = 0;    //
    while (i < 3)                   //
        s_l += lucky[i++];          //
    while (i < 6)                   //
        s_r += lucky[i++];          //
    if (s_l == s_r)                 //
        printf("%s; s_l = %d; s_r = %d; Yes!\n\n",lucky,s_l,s_r); //
    else                                                         //
        printf("%s; s_l = %d; s_r = %d; No!\n\n",lucky,s_l,s_r);//
    printf("4.65\n");
    int n = 1900;
    if (n % 4 == 0) {
        if (n % 100 == 0 ) {
            if (n % 400 == 0) {
                printf("Yes!\n\n");
            } else
                printf("No!\n\n");
        } else
            printf("Yes!\n\n");
    } else
        printf("No!\n\n");
    printf("4.67\n");
    int k = 400;
    if (k >= 1 && k <= 365){
        if ((k % 7 == 6) || (k % 7 == 0))
            printf("Day off!\n\n");
        else
            printf("Working day!\n\n");
    } else
        printf("error, k not in (1..365)\n\n");
    printf("4.71\n");
    double x2 = 32, min = 0, max = 0;
    x1 = 32.1;
    //A
    if (x1 > x2)
        printf("a)min = %.2f, max = %.2f\n",x2,x1);
    if (x2 > x1)
        printf("a)min = %.2f, max = %.2f\n",x1,x2);
    //Б
    min = x1;
    max = x2;
    if (x1 > x2) {
        min = x2;
        max = x1;
    }
    printf("b)min = %.2f, max = %.2f\n\n",min,max);
    printf("4.73\n");
    double x3 = 51.6, x4 = 72.4;
    x2 = 32;
    x1 = 32.1;
    //А
    if (x1 > x2 && x1 > x3 && x1 > x4)
        printf("a)x1 > x2,x3,x4\n");
    if (x2 > x1 && x2 > x3 && x2 > x4)
        printf("a)x2 > x1,x3,x4\n");
    if (x3 > x2 && x3 > x1 && x3 > x4)
        printf("a)x3 > x2,x1,x4\n");
    if (x4 > x2 && x4 > x3 && x4 > x1)
        printf("a)x4 > x2,x3,x1\n");
    //Б
    if (x1 < x2 && x1 < x3 && x1 < x4)
        printf("b)x1 < x2,x3,x4\n\n");
    if (x2 < x1 && x2 < x3 && x2 < x4)
        printf("b)x2 < x1,x3,x4\n\n");
    if (x3 < x2 && x3 < x1 && x3 < x4)
        printf("b)x3 < x2,x1,x4\n\n");
    if (x4 < x2 && x4 < x3 && x4 < x1)
        printf("b)x4 < x2,x3,x1\n\n");
    printf("4.75\n");
    x1 = 3.4;
    x2 = -1.76;
    double x1_abs = 0, x2_abs = 0, half_sum_abs = 0, sqrt_abs = 0;
    if (x1 > 0)
        x1_abs = x1;
    else
        x1_abs = -x1;
    if (x2 > 0)
        x2_abs = x2;
    else
        x2_abs = -x2;
    half_sum_abs = (x2_abs + x1_abs) / 2;
    printf("a)half sum abs = %.2f\n",half_sum_abs);
    sqrt_abs = sqrt(x1_abs * x2_abs);
    printf("b)sqrt abs = %.2f\n\n",sqrt_abs);
    printf("4.76\n");
    x1 = 5.23;
    x2 = 9.82;
    x1_abs = fabs(x1);
    x2_abs = fabs(x2);
    if (x1_abs < x2_abs)
        x1 = x1 / 2;
    printf("x1 = %.2f\n\n",x1);
    printf("4.78(79,80)\n");
    a1 = 2;
    b1 = 3;
    c1 = 6;
    //4.78
    if (a1 % 2 == 0)
        printf("4.78) a ");
    if (b1 % 2 == 0)
        printf("b ");
    if (c1 % 2 == 0)
        printf("c");
    //4.79
    x1 = 3.7;
    x2 = -6.1;
    x3 = 5.5;
    printf("\n\n2)");
    if (x1 >= 0) {
        x1 *= x1;
        printf("x1 = %.2f, ",x1);
    }
    if (x2 >= 0) {
        x2 *= x2;
        printf("x2 = %.2f, ",x2);
    }
    if (x3 >=    0) {
        x3 *= x3;
        printf("x3 = %.2f\n",x3);
    }
    //4.80
    x1 = 3.7;
    x2 = -6.1;
    x3 = 5.5;
    printf("3) a)");
    //A
    if (x1 > 1.6 && x1 < 3.8) //1,6—3,8
        printf("(1,6-3,8) x1 = %.2f, ",x1);
    if (x2 > 1.6 && x2 < 3.8) //1,6—3,8
        printf("x2 = %.2f, ",x2);
    if (x3 > 1.6 && x3 < 3.8) //1,6—3,8
        printf("x3 = %.2f",x3); // 0,7-5,1
    //Б
    printf("\n   b)");
    if (x1 > 0.7 && x1 < 5.1) //0,7-5,1
        printf("(0.7-5,1) x1 = %.2f, ",x1);
    if (x2 > 0.7 && x2 < 5.1) //
        printf("x2 = %.2f, ",x2);
    if (x3 > 0.7 && x3 < 5.1) //
        printf("x3 = %.2f\n",x3);
    printf("\n4.86\n");
    int z = 0;
    int a2;
    a2 = -2;
    if (a2 > 0)
        z = 1;
    if (a2 < 0)
        z = -1;
    printf("z = %d\n\n",z);
    printf("4.88\n");
    int f1 = 0;
    y = -2;
    f1 = -3 * y;
    if (y > 0 && y <= 2)
        f1 = 0;
    if (y > 2)
        f1 = 2;
    printf("f = %d\n\n",f1);
    printf("4.90\n");
    double k1 = 0;
    x1 = 2;
    if (sin(x1) >= 0)
        k1 = pow(x1,2);
    if (sin(x1) < 0)
        k1 = fabs(x1);
    if (x1 < k1)
        f = fabs(x1);
    if (x1 >= k1)
        f = x1 * k1;
    printf("f = %.2f;\nk = %.2f;\n\n",f,k1);
    printf("4.91\n");
    x1 = -0.5;
    double y1 = 0;
    //A
    if (x1 <= -1)
        y1 = 0;
    if (x1 > - 1 && x1 < 0)
        y1 = -x1;
    if (x1 >= 0)
        y1 = 1;
    printf("a)y = %0.2f\n",y1);
    //Б
    y1 = 0;
    if (x1 <= -1)
        y1 = 1;
    if (x1 > -1 && x1 < 0)
        y1 = fabs(x1);
    if (x1 > 0 && x1 <= 1)
        y1 = -x1;
    if (x1 > 1)
        y1 = -1;
    printf("b)y = %0.2f\n",y1);
    // V
    x1 = -0.5;
    y1 = 0;
    if (x1 <= -1)
        y1 = 1;
    if (x1 > -1 && x1 < 0)
        y1 = 0.95 + ((0.9 + x1) * 10) * -0.05;
    if (x1 > 0 && x1 < 1)
        y1 = 0.95 + ((0.9 + fabs(x1)) * 10) * -0.05;
    if (x1 >= 1)
        y1 = 1;
    if (x1 == 0)
        y1 = 0.5;
    printf("v)y = %.2f\n\n",y1);
    printf("4.94\n");
    x = 1;
    if (x != 0 && x != 1 && x != 3)
        printf("You entered the wrong score\n\n");
    if (x == 0)
        printf("Lose!\n\n");
    if (x == 1)
        printf("Draw!\n\n");
    if (x == 3)
        printf("Win!\n\n");
    printf("4.96\n");
    a = 2;
    b = 1;
    c = -6;
    disc = b * b - 4 * a * c;
    if (a != 0 && disc >=0) {
        printf("disc > 0; disc = %.2f\n",disc);
        r3 = (-b + sqrt(disc)) / 2 * a;
        r4 = (-b - sqrt(disc)) / 2 * a;
        if (r3 == r4)
            printf("x = %.2f;\n\n",r3);
        if (r3 != r4)
            printf("x1 = %.2f; x2 = %.2f\n\n",r3,r4);
    }
    if (a == 0 || disc < 0)
        printf("disc < 0, disc = %.2f or a = 0, no results.\n\n",disc);
    printf("4.98(100)\n");
    x1 = 3;
    y1 = 4;
    double z1 = 5;
    if(z1 < x1 && z1 < y1)
        printf("min = z;\n");
    if(x1 < z1 && x1 < y1)
        printf("min = x;\n");
    if(y1 < x1 && y1 < z1)
        printf("min = y;\n");
    if (z1 > x1 && z1 > y1) {
        z1 = x1 * y1;
        printf("max = z;\n\n4.100\nx * y = %.2f\n\n",z1);
    }
    if (x1 > z1 && x1 >y1) {
        x1 = z1 * y1;
        printf("max = x;\n\n4.100\nz * y = %.2f\n\n",x1);
    }
    if (y1 > x1 && y1 >z1) {
        y1 = x1 * z1;
        printf("max = y;\n\n4.100\nz * x = %.2f\n\n",y1);
    }
    printf("4.102\n");
    x = 2;
    y = - 3;
    if (x != 0 && y != 0){
        if (x > 0) {
            if (y > 0)
                printf("First quarter(%d,%d)\n\n",x,y);
            if (y < 0)
                printf("Fourth quarter(%d,%d)\n\n",x,y);
        }
        if (x < 0) {
            if (y > 0)
                printf("Second quarter(%d,%d)\n\n",x,y);
            if (y < 0)
                printf("Third quarter(%d,%d)\n\n",x,y);
        }
    }
    if (x == 0 || y == 0)
        printf("You entered incorrect values!!!\n\n");
    printf("4.110\n");
    x = 3;
    y = 12;
    if ((x >= 1 && x <= 4) && (y >= 6 && y <= 14)){
        switch (y) {
        case 6:
            printf("Shestyorka ");
            break;
        case 7:
            printf("Semyorka ");
            break;
        case 8:
            printf("Vosmyorka ");
            break;
        case 9:
            printf("Devyatka ");
            break;
        case 10:
            printf("Desyatka ");
            break;
        case 11:
            printf("Valyet ");
            break;
        case 12:
            printf("Dama ");
            break;
        case 13:
            printf("Korol ");
            break;
        case 14:
            printf("Tyz ");
            break;
        }
        switch (x) {
        case 1:
            printf("piki\n\n");
            break;
        case 2:
            printf("trefy\n\n");
            break;
        case 3:
            printf("bybny\n\n");
            break;
        case 4:
            printf("chervy\n\n");
            break;
        }
    }
    else
        printf("You entered incorrect values!!!\n\n");
    //---------------------------------------------------------------------
    // HARDCORE!!!!!!!!!
    printf("HARDCORE!-------------------------------\n\n");
    printf("4.118\n");
    int a3, b2;
    a3 = 2;
    a2 = 3;
    a1 = 5;
    b2 = 4;
    b1 = 9;
    if (b1 > a1) {
        a2 -= 1;
        a1 = a1 - b1 + 10;
    } else
        a1 -= b1;
    if (b2 > a2) {
        a2 = a2 - b2 + 10;
        a3 -= 1;
    } else {
        a2 = a2 - b2;
    }
    if (a3 <= 0)
        printf("You entered incorrect values!\n\n");
    else
        printf("sotny = %d, desyatki = %d, edenytsy = %d\n\n",a3,a2,a1);
    printf("4.119\n");
    a1 = 3; //x1(vertical)
    b1 = 2; //y1(gorizont)
    c1 = 6; //x2
    int d1 = 3; //y2
    // ладья
    a1 = 2;
    b1 = 4;
    // жертва
    c1 = 2;
    d1 = 7;
    if (a1 <= 8 && a1 >=1 &&
            b1 <= 8 && b1 >=1 &&
            c1 <= 8 && c1 >=1 &&
            d1 <= 8 && d1 >=1) {
        //a
        if (c1 == a1 || d1 == b1)
            printf("a)ladya ugrozhaet peshke!\n");
        else
            printf("a)ladya ne ugrozhaet peshke!\n");
        //b
        // слон
        a1 = 2;
        b1 = 4;
        // жертва
        c1 = 3;
        d1 = 5;
        if (abs(c1 - a1) == abs(d1 - b1))
            printf("b)slon ugrozhaet peshke!\n");
        else
            printf("b)slon ne ugrozhaet peshke!\n");
        //c
        // король
        a1 = 2;
        b1 = 4;
        // другое поле
        c1 = 2;
        d1 = 3;
        if (abs(c1 - a1) <= 1 && abs(d1 - b1) <= 1)
            printf("c)Korol mozhet pereity!\n\n");
        else
            printf("c)No!\n\n");
    }
    printf("4.124(a)\n");
    a = 8;
    b = 8;
    c = 8;
    if ((c < b + a) && (a < b + c) && (b < c + a)) {
        if (pow(c,2) == pow(a,2) + pow(b,2) ||
                pow(b,2) == pow(a,2) + pow(c,2) ||
                pow(a,2) == pow(c,2) + pow(b,2))
            printf("Pryamoygolniy treugolynk!\n\n");
        else
            if (pow(c,2) < pow(a,2) + pow(b,2) &&
                    pow(b,2) < pow(a,2) + pow(c,2) &&
                    pow(a,2) < pow(c,2) + pow(b,2))
                printf("Ostrougolniy treugolynk!\n\n");
            else
                printf("Tupoygolniy treugolnyk!\n\n");
    }
    else
        printf("This is not a triangle!\n\n");
    printf("4.125\n");
    n = 12;
    if (n >= 1 && n <= 99) {
        if (n % 10 == 1 && n != 11)
            printf("MHE %d GOT\n\n",n);
        else
            if (n % 10 >= 2 && n % 10 <= 4 && n > 15)
                printf("MHE %d GODA\n\n",n);
            else
                printf("MHE %d LET\n\n",n);
    } else
        printf("You entered incorrect values!\n\n");
    printf("4.128\n");
    year = 0;
    month = 0;
    n = 28;
    if (n >= 1 && n <= 1188) {
        if (n % 12 == 0) {
            year = n / 12;
        } else {
            year = n / 12;
            month = n % 12;
        }
    } else
        printf("You entered incorrect values!\n\n");
    printf("year = %d,month = %d\n\n",year,month);
    printf("4.132\n");
    a1 = 10;
    b1 = 56;
    c1 = 12;
    d1 = 55;
    n = 9;
    int m = 55;
    if (n > a1 && n < c1)
        printf("Popal, mezhdy chasamy!\n\n");
    else
        if ((n == a1 && m >= b1) || (n == c1 && m <= d1))
            printf("Popal mezhdy minutamy!\n\n");
        else
            printf("Ne popal!\n\n");
    enum Months { January = 1, February, March, April, May, June, July, August, September, October, November, December };
    const int months_in_year = 12;
    const int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int y_prev = 0, m_prev = 0, d_prev = 0, y_next = 0, m_next = 0, d_next = 0;
    y = -1, m = 12, d = 32;
    printf("4.134. Year %d, month %d and day %d. ", y, m, d);
    int diff;
    if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) {
        printf("Leap year, using delta = 1.\n");
        diff = 1;
    } else {
        printf("Not a leap year, using delta = 0.\n");
        diff = 0;
    }
    // Better IF expression, using 'days' array, "if (d < days_in_month[m]))...". Using 'days' only for consts.
    d_prev = d - 1; d_next = d + 1;     // Better in if-else statesments, but default (else) here.
    m_prev = m_next = m;                // If not changing, then as current date.
    y_prev = y_next = y;
    if (d == 1) {
        if (m == March)
            d_prev = days_in_month[February] + diff;
        else if ((m == May || m == July || m == October || m == December))
            d_prev = days_in_month[April]; // Or any other 30 day, or better constant with name.
        else
            d_prev = days_in_month[March];    // 31 day.
        // Only if January, then first expression divided will be 1, second will 0. Or just use IF. ;)
        printf("Day was 1, switch to previos month.\n");
        m_prev = ((months_in_year - (m - 1)) / months_in_year) * months_in_year + (m - 1);
        if (m == 1) {
            printf("Month was January, switch to previous year.\n");
            y_prev = y - 1;
            if (y_prev == 0) {
                printf("Changing year scale to BC.\n");
                y_prev = - 1;
            }
        }
    } else {    // One IF possible, other way.
        int l1 = (m == February && d == days_in_month[February] + diff);
        int l2 = ((m == April || m == June || m == September || m == November) && d == days_in_month[April]);
        int l3 = (d == days_in_month[January]); // Any of 31-day month.
        if (l1 || l2 || l3) {
            d_next = 1;
            // (++(m - 1)) % 12 + 1. Next month index, and increment after modulus, as months starts from 1 = January.
            printf("Day was last in month, switch to next.\n");
            m_next = (m % months_in_year) + 1;
            if (m == 12) {
                printf("Month was december, switch to next year.\n");
                y_next = y + 1;
                if (y_next == 0) {
                    printf("Changing year scale to AD.\n");
                    y_next = 1;
                }
            }
        }
    }
    printf("Previous date year %d ", abs(y_prev));
    if (y_prev > 0)
        printf("A.D., ");
    else
        printf("B.C., ");
    printf("month %d, day %d.\n", m_prev, d_prev);
    printf("Next date year %d ", abs(y_next));
    if (y_next > 0)
        printf("A.D., ");
    else
        printf("B.C., ");
    printf("month %d, day %d.\n", m_next, d_next);;
    printf("4.141\n");
    a1 = 12; // Номер 1-й квартиры
    n = 7;  // Кол-во квартир
    i = 0;
    int summ = 0;
    while (i < n) {
        summ = summ + a1;
        a1++;
        ++i;
    }
    if (summ % 2 == 0)
        printf("summ = %d; Yes!\n\n",summ);
    else
        printf("summ = %d; No!\n\n",summ);
    printf("4.135\n");
    a1 = 16;
    help1 = a1 % 6;
    if (help1 >= 0 && help1 < 3)
        printf("Green!\n\n");
    else
        if (help1 >= 3 && help1 < 4)
            printf("Yellow!\n\n");
        else
            printf("Red!\n\n");
    printf("4.140\n");
    n = 0;
    k = 29;
    if (k >= 1 && k <= 9)
        n = k;
    else if (k >= 10 && k <= 187) {
        if (k % 2 == 0)
            n = ((k - 10) / 20) +1;
        else {
            n = ((k - 10) % 20 ) / 2;
        }
    } else if (k >= 188 && k <=222) {
        n = k - 188;
        if (n % 3 == 0)
            n = 1;
        else if (n % 3 == 1)
            n = k / 30;
        else
            n = k / 3;
    }
    printf("N[k] = N[%d] = %d\n\n",k,n);
}

void chapter_5()
{
    printf("5.3\n\n");
    int i = 0, a = 20, b = 15, i1 = 10, a1 = 7, result = 0;
    printf("Numbers\tSquare\tDegree(3)\n\n");
    while (i <= 5) {
        printf("a)%3d %3d\n",i, a + i);
        if (i1 + i <= b) {
            result = pow(i1 + i,2);
            printf("b)%3d %3d\n",i1 + i, result);
        } else
            printf("b)--");
        if (a1 + i <= 50) {
            result = pow(a1 + i,3);
            printf("c)%3d %3d\n",a1 + i, result);
        } else
            printf("c)znacheniye bolshe chem 50!\n");
        if (i >= 1 && i <= 4) {
            printf("d)%3d\n",i);
        }
        ++i;
    }
    printf("\n");
    printf("5.8. Tablitsa funty v kilogramy\n");
    double funt = 1, kilograms = 0;
    const double grams_in_funt = 453.0;
    while (funt <= 10) {
        kilograms = funt * grams_in_funt / 1000;
        printf("%2.0f lb = %2.3f kg\n",funt,kilograms);
        ++funt;
    }
    printf("\n5.9.Duymy v samtimetry\n");
    double inch = 10, cm = 0;
    const double sm_per_inch = 2.54;
    while (inch <= 22) {
        cm = inch * sm_per_inch;
        printf("%2.0f inch = %2.2f cm\n",inch, cm);
        ++inch;
    }
    printf("\n5.10.Konverter: doll v rub\n");
    const double doll = 68.78;
    int help = 1;
    while (help <= 20) {
        printf("%d doll = %0.2f rub\n",help, help * doll);
        ++help;
    }
    printf("\n5.11.Rastoyanie do linii gorizonta.\n");
    int R = 6350, h = 1, gorizont = 0;
    while (h <= 10) {
        gorizont = pow(R + h,2) - pow(R,2);
        printf("length = %0.f km\n",sqrt(gorizont));
        ++h;
    }
    printf("\n5.15.Tablitsa umnozheniya\n");
    int n = 7;
    help = 1;
    while (help <= 10) {
        printf("%d * %d = %d;\n",n, help, n * help);
        ++help;
    }
    i = 3;
    printf("\n5.16. Talitsa sin.\n");
    while (i <= 20) {
        printf("sin(%d) = %0.6f\n",i,sin(i));
        ++i;
    }
    printf("\n5.18.Raschet z po formyle.\n");
    a = 2;
    double t = 0, z = 0;
    while (a <= 17) {
        t = 4 * a;
        z = (3.5 * pow(t,2)) - (7 * t) + 16;
        printf("z = %.f, a = %d\n",z, a);
        ++a;
    }
    printf("\n5.20Tablisa korney.\n");
    i = 1;
    double help1 = 0.1;
    while (i <= 9) {
        printf("sqrt(%.1f) = %.5f\n",help1, sqrt(help1));
        help1 += 0.1;
        ++i;
    }
    printf("\n5.22.Raschet stoimosti konfet.\n");
    double cost = 289.45;
    double mass = 0.1;
    i = 1;
    while ( i <= 20) {
        printf("cost(%.1f kg) = %.2f rub\n",mass,cost * mass);
        mass += 0.1;
        ++i;
    }
    printf("\n5.24.Posledovatelnost chisel.\n");
    i = 1;
    help1 = 3.2;
    while (i <= 8) {
        printf("%.1f\n%.1f\n",help1, help1);
        ++i;
        help1 += 0.1;
    }
    printf("\n5.26Posledovatelnost chisel.\n");
    i = 1;
    help1 = 4.4;
    while (i <= 11) {
        printf("%.1f\n",help1);
        ++i;
        help1 += 0.2;
    }
    printf("\n5.30\n");
    //a
    i = 20;
    int summ = 0;
    while (i <= 40) {
        summ += pow(i,3);
        ++i;
    }
    printf("c)Sum of squares = %d\n",summ);
    summ = 0;
    a = 1;
    n = 5;
    while (a <= n) {
        summ += a * a;
        ++a;
    }
    printf("d)Sum of squares = %d\n\n",summ);
    n = 10;
    printf("5.31 - 5.35. n = %d\n",n);
    printf("idx\t5.31:\t5.32:\t5.33:\t5.34:\t5.35:\n");
    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, p3 = 1, p4 = 1;
    for (i = 0; i < n; ++i) {
        double e1 = (n + i) * (n + i);
        double e2 = 1.0 / (i + 1);
        double e3 = (double) (2 + i) / (double) (3 + i);
        double e4 = 1.0 / p3;
        p3 *= 3;
        double e5 = 1.0 / (i + 1) * p4;
        p4 *= -1;
        sum += e1;
        sum1 += e2;
        sum2 += e3;
        sum3 += e4;
        sum4 += e5;
        printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",i,e1,e2,e3,e4,e5);
    }
    printf("sum:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n\n",sum,sum1,sum2,sum3,sum4);
    printf("5.39:summa posledovatelnosty\n");
    srand(time(NULL));
    i = 1;
    summ = 0;
    summ += numerical_generation_int();
    printf("Sum = %d\n\n",summ);
    printf("5.42:Ocency na ekzamenax\n");
    i = 1;
    summ = 0;
    while (i <= 4) {
        a = 1 + rand() % 5;
        summ += a;
        printf("%d ",a);
        ++i;
    }
    printf("\n");
    printf("Points = %d\n\n",summ);
    printf("5.45:Obshee soprotevleniye elementov\n");
    i = 0;
    summ = 0;
    a = 1 + rand() % 10;
    while (i <= a) {
        a = 1 + rand() % 10;
        summ += a;
        printf("%d ",a);
        ++i;
    }
    printf("\n");
    printf("Sum = %d\n\n",summ);
    printf("5.48:Summa kvadratov chisel\n");
    i = 0;
    summ = 0;
    a = 1 + rand() % 10;
    while (i <= a) {
        a = 1 + rand() % 10;
        summ += a * a;
        printf("%d ",a);
        ++i;
    }
    printf("\n\n");
    printf("Sum of squares = %d\n\n",summ);
    printf("5.51\n");
    srand(time(NULL));
    n = 3;
    sum = 0;
    for (i = 0; i < 3; ++i) {
        double e = (double)(rand() % 10) / (double)(1 + rand() % 10);
        sum += e;
        printf("%.1f ",e);
    }
    printf("SRED.ARIF = %.2f\n\n",sum / n);
    printf("5.54\n");
    n = 10;
    srand(time(NULL));
    sum = 0;
    for (i = 0; i < n; ++i) {
        a = 1 + rand() % 5;
        sum += a;
        printf("%d ",a);
    }
    printf("SRED.OCENKA = %.0f\n\n",sum / n);
    printf("5.56\n");
    //a
    n = 1 + rand() % 5;
    i = 1;
    summ = 0;
    while (i <= n) {
        a = rand() % 10;
        summ += abs(a);
        printf("%d ",a);
        ++i;
    }
    printf("\n");
    printf("a)Sum = %d\n\n",summ);
    //Б
    n = 1 + rand() % 5;
    i = 1;
    summ = 1;
    while (i <= n) {
        a = 1 + rand() % 10;
        summ *= abs(a);
        printf("%d ",a);
        ++i;
    }
    printf("\n");
    printf("b)Sum = %d\n\n",summ);
    //c
    summ = 0;
    b = 0;
    n = 1 + rand() % 8;
    i = 1;
    printf("c)\n");
    a = 1 + rand() % 10;
    while (i <= n) {
        b = 1 + rand() % 10;
        summ += a + b;
        printf("%d + %d = %d\n",a,b,summ);
        ++i;
        a = b;
    }
    printf("Sum = %d\n",summ);
    // D
    n = 1 + rand() % 5;
    i = 1;
    summ = 0;
    b = 1;
    while (i <= n) {
        a = rand() % 10;
        summ += a * b;
        printf("%d ",a * b);
        ++i;
        b *= -1;
    }
    printf("\n");
    printf("d)Sum = %d\n\n",summ);
    printf("\n5.57\n");
    int summ1 = 0;
    i = 1;
    summ = 0;
    printf("Two student: ");
    while (i <= 4) {
        a = 1 + rand() % 5;
        b = 1 + rand() % 5;
        summ += a;
        summ1 += b;
        printf("%d - %d; ",a,b);
        ++i;
    }
    printf("\nTotal: %d - %d; \n\n",summ, summ1);
    printf("5.60\n");
    int january = 0, march = 0;
    i = 1;
    printf("Januaty\t\tMarch\n");
    while (i <= 31) {
        a = 1 + rand() % 40;
        january += a;
        b = 1 + rand() % 15;
        march += b;
        printf("%4d\t\t%4d\n",a,b);
        ++i;
    }
    printf("\nTotal:\n%4d\t\t%4d\n\n",january / 31,march / 31);
    printf("5.63\n");
    srand(time(NULL));
    n = 10;
    summ = 0;
    for (i = 1; i <= 10;++i) {
        a = 1 + rand() % 7;
        b = 1 + rand() % 5;
        printf("%d - %d; ",a,b);
        summ += a * b;
    }
    printf("SUMM.UROZHAY = %d\n",summ);
    printf("SRED.UROZHAYNOST = %.2f\n\n",(double)summ / 10.0);
    printf("5.66.posledovatelnost: ");
    n = 5;
    double a2 = 0, a3 = 0, k = 0;
    for (k = 1;k <= n;++k) {
        a3 = k * (a2) + 1 / k;
        printf("a%.f = %.2f; ",k,a3);
        a2 = a3;
    }
    printf("\n5.67\n");
    //A
    k = 7;
    n = 10;
    a = 1;
    a1 = 1;
    b = 1;
    summ = 2;
    printf("Fibonnachi: %d %d ", a, a1);
    for (i = 3; i <= n; ++i) {
        b = a1 + a;
        a = a1;
        a1 = b;
        summ += b;
        printf("%d(%d) ",b,summ);
        if (i == k) {
            printf("Nayden element - k; ");
        }
    }
    if (summ % 2 == 0)
        printf("Yes!\n\n");
    else
        printf("No!\n\n");
    printf("5.68\n");
    double p = 1, p1 = 0;
    k = 1;
    int k1 = 5;
    for (i = 1; i < k1; ++i) {
        p1 = k;
        k += p;
        p = p1;
    }
    printf("a)k = %d; k / p = %.f / %.f = %.3f\n", k1, k, p,k / p);
    p = 1, p1 = 0;
    k = 1;
    n = 6;
    a = 7;
    sum = 0;
    printf("b)");
    for (i = 1; i <= n; ++i) {
        printf("%d) %.3f; ",i,k / p);
        sum += k / p;
        p1 = k;
        k += p;
        p = p1;
    }
    if (sum > a)
        printf("\nc)Yes, sum > A; %.3f > %d;\n\n",sum, a);
    else
        printf("\nc)No, sum < A; %.3f < %d;\n\n",sum, a);
    printf("5.69\n");
    double v1 = 0, v2 = 0, v3 = 1.5, v4 = 0;
    n = 7;
    printf("Posledovatelnost: ");
    for (i = 4; i < n; ++i) {
        v4 = ((i - 1) / (pow(i,2) + 1)) * v3 - v2 + v1;
        printf("%.2f; ",v4);
    }
    printf("\n\n5.70\n");
    a = 1;
    for (i = 1; i <= 24 / 3; ++i) {
        a *= 2;
        printf("%d hours = %d amoebas\n",i * 3,a);
    }
    printf("\n5.71\n");
    double score = 1000, profit = 0, summ_score = 0;
    const double percent = 2;
    for (i = 1; i <= 5; ++i) {
        if (i >= 3 && i <= 5)
            printf("%d)%.2f\t%.2f\n",i,score,profit);
        else
            printf("%d)%.2f\t-\n",i,score);
        summ_score = score + (score / 100 * percent);
        profit =  summ_score - score;
        score = summ_score;

    }
    printf("\n5.72\n");
    printf("a)\n");
    double way = 10,sum_way = 0;
    for (i = 1; i <= 10; ++i) {
        way += way / 10;
        if (i <= 7)
            sum_way += way;
        printf("Way = %.2f km\n",way);
    }
    printf("b) summ = %.2f\n\n",sum_way);
    printf("5.73\n");
    v1 = 100.0; v2 = 20; v3 = 0.05; v4 = 0.02;
    sum = 0;
    n = 8;
    printf("God:\tPloshad:\tUrozhaynost:\tUrozhay:\tSumma:\n");
    for (i = 1; i < 8; ++i) {
        double v5 = v1 * v2;
        sum += v5;
        printf("%d\t",i);
        if (i <= 7 && i >= 4)
            printf("%.f\t\t",v1);
        else
            printf("-\t\t");
        if (i >= 2)
            printf("%.2f\t\t",v2);
        else
            printf("-\t\t");
        if (i <= 6)
            printf("%.f\t\t%.f",v5,sum);
        else
            printf("-\t\t-");
        printf("\n");
        v1 = v1 + (v1 * v3);
        v2 = v2 + (v2 * v4);
    }
    printf("\n5.74\n");
    v1 = 10; v2 = 10; v3 = 0.5; v4 = M_PI / 6 * v1 * v1 * v1; sum = v4;
    n = 12;
    printf("Posledovatelnost: ");
    for (i = 1; i < n; ++i) {
        v2 += v1 + v3;
        double v5 = M_PI / 6 * v2 * v2 * v2;
        sum += v5 - v4;
        v1 = v2;
        v4 = M_PI / 6 * v1 * v1 * v1;
        printf("%3.1f - %3.1f: %3.1f - %3.1f; ", v1, v4, v2, v5);
    }
    printf("\n\n5.75\n");
    summ = 0;
    help = 2 * 2;
    for (i = 1; i <= 10; ++i) {
        summ += help;
        help *= 2;
    }
    printf("%d\n\n",summ);
    printf("5.76\n");
    a2 = 2.2;
    help1 = a2;
    n = 5;
    for (i = 1; i <= n; ++i) {
        help1 *= a2;
        printf("%.2f\n",help1);
    }
    printf("\n5.77\n");
    b = -1;
    summ = 0;
    for (i = 1; i <= 10; ++i) {
        summ += i * i * b;
        b *= -1;
        printf("i = %d;  sum = %d; sign = (%d)\n",i, summ, b);
    }
    printf("\n5.78\n");
    double x1 = 2, x2 = -1, S_sin = 0;
    if (x2 >= x1 && x1 >= 0 && x2 <= M_PI ) {
        S_sin = cos(x1) - cos(x2);
        printf("Ploshyad arki sinusoidy = %.5f\n\n",S_sin);
    } else {
        printf("Nekorektnoe znacheniye\n\n");
    }
    printf("5.81\n");
    int x = 5, y = 7;
    result = multiply(x,y);
    printf("x * y = %d * %d = %d\n\n",x,y,result);
    printf("5.82\n");
    n = 1;
    result = factorial(n);
    printf("n = %d;n! = %d;\n\n",n,result);
    printf("5.83\n");
    a = 3; // Степень
    p3 = 3; // Возводимое число
    printf("a ^ n = %.f ^ %d = %.f\n",p3,a,exponentiation(p3,a));
    printf("5.84\n");
    group_values(9,3);      // ((4 ^ 2 - 3 ^ 2) ^ 2 - (2 ^ 2 - 1 ^ 2) ^ 2)
    printf("5.85\n");
    const char s[] = "12345";
    printf("Inverted value = ");
    invert_1(s,-1);
    printf(";\n\n");
    printf("5.86.n^2 = 1 + 3 + 5 + 7 + ... 2n + 1\n");
    n = 4;
    squaring(n);
    printf("\n5.88.Cubing\n");
    for (i = 1; i <= 5; ++i) {
        result = cubing(i);
        printf("%d ^ 3 = %d;\n",i,result);
    }
    printf("\n5.90\n");
    n = 5;
    double result_1 = 0;
    result_1 = summary(n);
    printf("result = %.2f;\n",result_1);
    printf("\n5.92\n");
    sqrt_5_92();
    printf("\n5.94\n");
    n = 178;
    result = value(n,8,2);
    printf("Sum of digits of a six-digit number %d = %d",n,result);

}

void chapter_6()
{
    srand(0);
    printf("6.1\n");
    int n = 0, sum = 0, quantity = 1;
    printf("Hello! Please enter any integers in turn or write 0 to complete;\n");
    scanf("%d",&n);
    while (n != 0) {
        sum += n;
        ++quantity;
        scanf("%d",&n);
    }
    printf("Sum of %d numbers equals = %d;\n\n",quantity,sum);
    printf("6.4\n");
    n = 5;
    int a1 = 0;
    while ((a1 = rand() % 10) > 5  && (n > 0)) {
        printf("%d; ",a1);
        --n;
    }
    n = 99;
    printf("\n\n6.8.posledowatelnost kvadratov chisel < n(%d)\n",n);
    for (int i = 1; i * i < n;++i)
        printf("%d; ",i * i);
    printf("\n\n6.11.posledowantelnost v intervale ot 1 do 1.5\n");
    double a = 1.3;
    n = 7;
    if (a > 1.0 && a <= 1.5) {
        for (int i = 2; i < n; ++i) {
            double double_value = 1.0 + (1.0 / i);
            if (double_value < a)
                printf("1 + (1 / %d) < a(%.1f)\n",i,a);
            else
                printf("Value(%.2f) not printed\n",double_value);
        }
    } else
        printf("You entered incorrect value!\n\n");
    a = 1.1;
    printf("\n6.14.max n pri a = %.2f\n",a);
    double double_value = 1.0 + (1.0 / 2);
    if (a > 1 && a <= 1.5) {
        for (int i = 2; double_value > a; ++i) {
            double_value = 1.0 + (1.0 / i);
            if (double_value > a)
                printf("1.0 + 1.0 / %d > a(%.1f), n = %d\n",i,a,i);
        }
    } else
        printf("You entered incorrect value!\n\n");
    a = 2.5;
    double summ = 30;
    printf("6.17.summa 1 + 1 / 2 + 1 / 3 ... + 1 / n > a, a = %.2f\n",a);
    for (n = 2; summ < a || n == 2; ++n) {
        printf("n = %d: ",n);
        int x = 1;
        summ = 0;
        while (x <= n) {
            summ += 1.0 / x;
            printf("summ = %.2f; ",summ);
            ++x;
        }
        if (summ < a)
            printf("summ < a, next n;\n");
        else
            printf("summ > a, end;\n");
    }
    double eps = 0.000001;
    printf("\n6.20.posledowatelnost y(n), eps = %.2f\n",eps);
    double double_x = 5;
    double prev_y = 0.5 * (double_x / -1), y = 0.5 * (prev_y + (double_x / (prev_y - 1)));
    for (int i = 1; fabs(y * y - prev_y * prev_y) >= eps;++i) {
        prev_y = y;
        y = 0.5 * (prev_y + (double_x / (prev_y - 1)));
        double delta = fabs(y * y - prev_y * prev_y);
        printf("%.9f; ",delta);
    }
    n = 124236;
    printf("\n\n6.23, n = %d\n",n);
    int value = 0;
    int x1 = 3; int x2 = 0; // a
    int x3 = 4; int x4 = 0; // б
    int x5 = 5; sum = 0;    // в
    int x6 = 3;int x7 = 2;int x8 = 0;int x9 = 0; //г
    while (n > 0) { // Длинна числа.
        value = abs(n) % 10;
        n /= 10;
        if (x1 == value)
            ++x2;
        if (value % x3 == 0)
            ++x4;
        if (value > x5 && x5 <= 8 && x5 >= 0)
            sum += value;
        if (x6 == value)
            ++x8;
        if (x7 == value)
            ++x9;
    }
    if (x8 > x9)
        x8 = x9;
    printf("a)%d;\nb)%d;\nv)%d;\ng)%d\n",x2,x4,sum,x8);
    n = 246957;
    printf("\n6.26 and 6.29, number is %d;\n",n);
    int k = 0;
    int x_max = 0;
    int x_min = 9;
    int max_pos = 0, min_pos = 0;
    x3 = 0;
    x4 = 0;
    while (n > 0) {
        value = n % 10;
        n /= 10;
        ++k;
        if (value > x_max) {
            x_max = value;
            max_pos = k;
        }
        if (value < x_min) {
            x_min = value;
            min_pos = k;
        }
    }
    printf("a)max = %d;\nfrom start = %d;\nfrom the end = %d\n",x_max,max_pos,k - max_pos + 1);
    printf("b)min = %d;\nfrom start = %d;\nfrom the end = %d\n",x_min,min_pos,k - min_pos + 1);
    n = 12345;
    printf("\n6.32, n = %d\n",n);
    x_min = 9;
    int x_amount = 0;
    while (n > 0) {
        value = n % 10;
        n /= 10;
        if (value < x_min) {
            x_amount = 0;
            x_min = value;
        }
        if (value == x_min)
            ++x_amount;
    }
    printf("min = %d,quantity = %d;\n\n",x_min,x_amount);
    printf("6.35\n");
    x1 = 0;
    for (n = 500;x1 < 10;++n) {
        if (n % 13 == 0) {
            ++x1;
            printf("%d %% 13 = 0;\n",n);
        }
        if (n % 17 == 0) {
            ++x1;
            printf("%d %% 17 = 0;\n",n);
        }
    }
    n = 1237174;
    x1 = n;
    x2 = 0;
    printf("\n6.38, n = %d\n",n);
    while (n > 0) {
        value = n % 10;
        n /= 10;
    }
    while (x1 > 0) {
        x2 = x1 % 10;
        x1 /= 10;
        if (x2 == value)
            ++n;
    }
    printf("first number %d; quantity %d;\n\n",value,n);
    n = 987123;
    printf("6.41, n = %d\n",n);
    x1 = 0;
    x2 = 9;
    x3 = 0;
    x4 = 0;
    while (n > 0) {
        value = n % 10;
        n /= 10;
        if (value > x1) {
            x3 = x1;
            x1 = value;
        } else
            if (value > x3 && x1 > x3 && value != x1)
                x3 = value;
        if (value < x2) {
            x4 = x2;
            x2 = value;
        } else
            if (value < x4 && x2 < x4 && value != x2)
                x4 = value;
    }
    printf("max(1) = %d; max(2) = %d\n",x1,x3);
    printf("min(1) = %d; min(2) = %d\n",x2,x4);
    printf("\n6.43 - 6.44\n");
    srand(3);
    n = 10;
    int is_seq = 0;
    int seq_am = 0;
    x3 = 0;
    k = 0;
    int mass[n], digits[n];
    printf("Sequence: %d\n",n);
    for (int i = 0;i < n;++i) {
        mass[i] = k;
        k += rand() % 2;
        printf("%d ",mass[i]);
        digits[i] = 0;
    }
    for (int i = 0;i < n;++i) {
        if (i > 0 && !is_seq && mass[i] == mass[i - 1]) {
            is_seq = 1;
            ++seq_am;
        } else  if (mass[i] != mass[i - 1])
            is_seq = 0;
        ++digits[mass[i]];
    }
    printf("\nresult = %d\n",seq_am);
    printf("Chastota chisel :=");
    for (int i = 0; i < n;++i)
        printf(" %d:%d",i,digits[i]);
    printf("\n\n6.45\n");
    x1 = 7;//a
    x2 = 35;//b
    x3 = 33;//c
    if (x1 > 0 && x2 > 0 && x3 > 0) {
        int help_nod_first_step = 0, help_nod_second_step = 0;
        help_nod_first_step = evklid_first_step(x1,x2);
        printf("NOD(a,b) = NOD(%d,%d) = %d\n",x1,x2,help_nod_first_step);
        help_nod_second_step = evklid_first_step(help_nod_first_step,x3);
        printf("NOD(a,b,c) = NOD(%d,%d,%d) = %d\n\n",x1,x2,x3,help_nod_second_step);
    } else {
        printf("You entered incorrect numbers!!\n\n\a");
    }
    value = 12345;
    printf("6.48, value = %d,digits: ",value);
    sum = 0;
    k = 7;
    quantity = 0;
    int b = 1234;
    int x = 1;
    x1 = 0;
    int y1 = 6, y2 = 0;
    a1 = 13;
    int prod_numbers = 1;
    int m = 3;
    n = 5;
    int help = value, help1 = 0;
    while (help > 0) {
        help1 = help % 10;
        help /= 10;
        sum += help1;
        prod_numbers *= help1;
        ++quantity;
        if (quantity == 1)
            y2 = help1;
        printf("%d ",help1);
    }
    x1 = help1;
    printf("\n");
    if (sum > k)
        printf("a) Sum numbers(%d) > k(%d), ",sum,k);
    else
        printf("a) Sum numbers(%d) < k(%d), ",sum,k);
    if (value % 2 == 0)
        printf("value is even;\n");
    else
        printf("value is odd;\n");
    if (quantity % 2 == 0)
        printf("b) Number of digits(%d) - even number, ",quantity);
    else
        printf("b) Number of digits(%d) - odd number, ",quantity);
    if (value < b)
        printf("value < b(%d);\n",b);
    else
        printf("value > b(%d);\n",b);
    if (x == x1)
        printf("v) Number starts with x(%d), ",x);
    else
        printf("v) Number does not start with x(%d), ",x);
    if (y1 == y2)
        printf("number ends on y(%d);\n",y1);
    else
        printf("number does not end on y(%d);\n",y1);
    if (prod_numbers < a1)
        printf("g) Product of digits less than a(%d), ",a1);
    else
        printf("g) Product of digits greater than a(%d), ",a1);
    if (value % b == 0)
        printf("number is divisible by b(%d);\n",b);
    else
        printf("number is not divisible by b(%d);\n",b);
    if (sum > m)
        printf("d) Sum numbers(%d) > m(%d), ",sum,m);
    else
        printf("d) Sum numbers(%d) < m(%d), ",sum,m);
    if (value % n == 0)
        printf("number is divisible by n(%d);\n\n",n);
    else
        printf("number is not divisible by n(%d);\n\n",n);
    printf("6.51\n");
    n = 123321;
    help = n;
    k = 0;
    x = 0;
    while (help > 0) {
        help /= 10;
        ++k;
    }
    printf("Value = %d have %d digits: ",n,k);
    help = n;
    int mass1[k];
    k = 0;
    while (help > 0) {
        help1 = help % 10;
        help /= 10;
        mass1[k] = help1;
        ++k;
        printf("%d ",help1);
    }
    printf("\nCheck palindrom: ");
    while (x < k && mass1[x] == mass1[k - 1]) {
        printf("%d[%d]:%d[%d] ",mass1[x],x,mass1[k - 1],k - 1);
        ++x;
        --k;
    }
    if (x >= k)
        printf("\nThis is palindrom\n\n");
    else
        printf("\nThis is not palindrom\n\n");
    printf("6.54\n");
    n = 103;
    x = 0;
    k = 0;
    x2 = 0;
    x1 = 0;
    printf("Value, digits: %d\n",n);
    while (n > 0) {
        x = n % 10;
        n /= 10;
        x1 = x;
        x = n % 10;
        if (x1 <= x)
            ++x2;
        ++k;
        printf("%d:%d ",x,x1);
    }
    if (k > 1) {
        if (k - 1 == x2)
            printf("cifry po ne ubyvaniy\n\n");
        else
            printf("cifry po ubyvaniy\n\n");
    } else
        printf("nedostatochno cifr dla posledovatelnosty\n\n");
    printf("6.57, double data array, size %d: ",ARRAY_SIZE);
    double mass2[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE ; ++i) {
        mass2[i] = (double)(rand() % 10) / (double)(1 + rand() % 10);
        printf("%.2f ",mass2[i]);
    }
    printf("\n");
    y = 3.61; //n
    a = 0;
    x = 0;
    double d1 = 0;
    d1 = fabs(mass2[0] - y);
    for (int i = 1;i < ARRAY_SIZE;++i) {
        a = fabs(mass2[i] - y);
        if (a < d1) {
            d1 = a;
            x = i;
        }
    }
    printf("%.2f:%d\n\n",mass2[x],x + 1);
    printf("6.60\n");
    srand(time(NULL));
    n = 0;
    int i;
    printf("Sequence: ");
    for (i = 1;i <= 10 && n % 10 != 7;++i) {
        n = rand() % 100;
        printf("%d ",n);
    }
    if (n % 10 == 7)
        printf("\n%d:%d\n\n",n,i - 1);
    else
        printf("\nThere is no number in the sequence that ends in 7\n\n");
    printf("6.63\n");
    srand(time(NULL));
    n = 0;
    k = 0;
    printf("Appraisals: ");
    for (int i = 1; i <= 5; ++i) {
        n = 1 + rand() % 5;
        printf("%d ",n);
        if (n == 2)
            ++k;
    }
    if (k != 0)
        printf("\nYes!\nTwos in class: %d\n\n",k);
    else
        printf("\nNo twos!\n\n");
    printf("6.66\n");
    srand(time(NULL));
    n = 0;
    k = 1;
    x = 0;
    x1 = 0;
    x2 = 0;
    printf("Values: ");
    for (int i = 1; n != -1; ++i) {
        x = n;
        n = k + rand() % 10;
        printf("%d ",n);
        if (i > 2) {
            k = -1;
        }
        if (x == n && x2 != -1) {
            x2 = -1;
            x1 = i;
        }
    }
    if (x2 == -1) {
        printf("\n%d:%d\n\n",x1 - 1,x1);
    } else
        printf("\nNo couple;\n\n");
    printf("6.69\n");
    k = 0;
    printf("Sequence: ");
    srand(time(NULL));
    int mass3[ARRAY_SIZE];
    x = 1 + rand() % ARRAY_SIZE;
    for (int i = 0; i < ARRAY_SIZE; ++i)
        if (i == x)
            mass3[i] = i + rand() % 2;
        else
            mass3[i] = i + 1;
    for (int i = 0;i < ARRAY_SIZE - 1; ++i)
        if (mass3[i] < mass3[i + 1])
            printf("%d ",mass3[i]);
        else {
            k = -1;
            printf("|%d| ",mass3[i]);
        }
    if (k != 0)
        printf("\nThe sequence was broken!!!\n\n");
    else
        printf("\nThe sequence is normal!!!\n\n");
    printf("6.72\n");
    const int com_table = 3;
    int commands[com_table];
    printf("Score:\n");
    for (int i = 0; i < com_table; ++i) {
        commands[i] = rand() % 25;
        printf("%d) %d\n",i + 1, commands[i]);
    }
    for (i = 0; i < com_table - 1; ++i) {
        if (commands[i] < commands[i+1]) {
            printf("\nItems are not in the correct order!\n\n");
            break;
        }
    }
    if (i == 2)
        printf("Everything is OK):D)\n\n");
    printf("6.75\n");
    printf("Create bazaar: ");
    const int bazaar_size = 28;
    const int bone_size = 2;
    const int total_dots = 7;
    int bazaar_mass[bazaar_size][bone_size];
    for (int i = 0, m = 0, n = 0, j = 0; i < total_dots * total_dots; ++i) {
        if (m <= n){
            bazaar_mass[j][0] = m;
            bazaar_mass[j][1] = n;
            ++j;
            printf("%d:%d ",m,n);
        }
        ++n;
        if (n == 7) {
            n = 0;
            ++m;
        }
    }
    for (int i = 0; i < bazaar_size; ++i) {
        int p1 = rand() % bazaar_size;
        int p2 = rand() % bazaar_size;
        int m = bazaar_mass[p1][0];
        int n = bazaar_mass[p1][1];
        bazaar_mass[p1][0] = bazaar_mass[p2][0];
        bazaar_mass[p1][1] = bazaar_mass[p2][1];
        bazaar_mass[p2][0] = m;
        bazaar_mass[p2][1] = n;
    }
    printf("\nbazar ready to game: ");
    for (int i = 0; i < bazaar_size; ++i)
        printf("%d:%d ",bazaar_mass[i][0], bazaar_mass[i][1]);
    int left = bazaar_mass[0][0];
    int right = bazaar_mass[0][1];
    printf("\n");
    printf("Start bone: %d:%d\n", left, right);
    for (int i = 1; i < bazaar_size; ++i) {
        if (bazaar_mass[i][0] == left || bazaar_mass[i][1] == left) {
            printf("left: bazar: %d:%d, old left: %d, ", bazaar_mass[i][0], bazaar_mass[i][1], left);
            if (bazaar_mass[i][0] == left)
                left = bazaar_mass[i][1];
            else
                left = bazaar_mass[i][0];
            printf(" new left: %d;\n",left);
            continue;
        }
        if (bazaar_mass[i][0] == right || bazaar_mass[i][1] == right) {
            printf("right: bazar: %d:%d, old right: %d, ", bazaar_mass[i][0], bazaar_mass[i][1], right);
            if (bazaar_mass[i][0] == right)
                right = bazaar_mass[i][1];
            else
                right = bazaar_mass[i][0];
            printf(" new right: %d;\n",right);
            continue;
        }
        break;
    }
    n = 2187;
    printf("\n6.76(a and b), number: %d\n",n);
    number_of_degrees(n);
    n = 113;
    printf("6.77, n: %d\n",n);
    fibonachi(n);
    n = 21;
    int f = 0;
    int s = 7;
    printf("6.78, n = %d, f = %d, s = %d;\n",n,f,s);
    int result = arif_sequence(n,f,s);
    if (result == n)
        printf("Yes;\n\n");
    else
        printf("No;\n\n");
    m = 48;
    int g = 3;
    int z = 2;
    printf("6.79, m = %d, g = %d, z = %d;\n", m, g, z);
    result = geom_seqence(m,g,z);
    if (result == m)
        printf("Yes;\n\n");
    else
        printf("No;\n\n");
    n = 905090955;
    int nine = 0;
    int zero = 0;
    printf("6.80, n = %d;\n",n);
    while (n > 0) {
        x = n % 10;
        printf("%d ",x);
        n /= 10;
        if (x == 9)
            ++nine;
        if (x == 0)
            ++zero;
    }
    if (nine > zero)
        printf("\nThere are more nines(%d) than zeros(%d);\n\n",nine,zero);
    else
        if (zero > nine)
            printf("\nThere are more zeros(%d) than nines(%d);\n\n",zero,nine);
        else
            printf("\nThe number of zeros(%d) and nines(%d) is the same;\n\n",zero,nine);
    n = 20311;
    int max = 0;
    int min = 9;
    max_pos = 0;
    min_pos = 0;
    k = 0;
    printf("6.82, 6.84, n = %d\n",n);
    while (n > 0) {
        x = n % 10;
        n /= 10;
        if (x > max) {
            max = x;
            max_pos = k;
        }
        if (x < min) {
            min = x;
            min_pos = k;
        }
        ++k;
    }
    printf("(min: %d + max: %d) %% 2 =  ", min, max);
    if ((min + max) % 2 == 0)
        printf("even;\n");
    else
        printf("odd;\n");
    if (max_pos > min_pos)
        printf("Maximum value: %d to the left; Max pos = %d\n\n",max,max_pos);
    else {
        if (min_pos > max_pos) {
            printf("Minimum value: %d to the left; Min pos = %d\n\n",min, min_pos);
        } else
            printf("Values(%d:%d), position(%d:%d);\n\n",max,min,max_pos,min_pos);
    }
    x = 3; //a
    b = 4; //b
    n = 12345;
    help = 0;
    help1 = 0;
    k = 0;
    printf("6.86, a = %d, b = %d, n = %d\n",x,b,n);
    while (n > 0) {
        x1 = n % 10;
        n /= 10;
        ++k;
        if (x1 == x && help == 0)
            help = k;
        if (x1 == b && help1 == 0)
            help1 = k;
    }
    if (help < help1)
        printf("a(%d) is more to the right than b(%d);\n\n",help, help1);
    else
        printf("b(%d) is more to the right than a(%d);\n\n",help1, help);
    printf("6.90\n");
    i = 10;
    x = 15;
    printf("a,number: power 1) ");
    while (i <= x) {
        printf("%d:%d ", i, i * i);
        ++i;
    }
    printf("\nb,number: power 2) ");
    i = 10;
    x = 15;
    do {
        printf("%d:%d ", i, i * i);
        ++i;
    } while (i <= x);
    printf("\n\n");
    n = 908809;
    printf("6.91, n = %d\n",n);
    natural_number(n);
    printf("6.93\n");
    srand(time(NULL));
    int precipitation[31];
    precipitation[0] = 0;
    printf("Sequance: %d ", precipitation[0]);
    for (int i = 1; i <= 30; ++i) {
        precipitation[i] = rand() % 10;
        printf("%d ",precipitation[i]);
    }
    i = 1;
    while (precipitation[i] != 0) {
        printf("\nDay: %d, precipiatation: %d;", i, precipitation[i]);
        ++i;
    }
    if (i == 30) {
        printf("\nNo precipitation in May\n\n");
    } else
        printf("\nfirst dry day: %d\n",i);
    printf("\n6.95\n");
    for (i = 5000; i % 39 != 0 && i >= 39; --i)
        ;
    printf("i: %d;\n\n",i);
    printf("6.102\n");
    int NOK = 0;
    n = 64;
    x = 48;
    NOK = lcm(n,x);
    printf("NOK(%d,%d):= %d\n\n",n,x,NOK);
    printf("6.103\n");
    n = 75; // числитель
    x = 125; // знаменатель
    result = evklid_first_step(n,x);
    printf("NOD = %d;\n",result);
    printf("Was: %d/%d;\n",n,x);
    x /= result;
    n /= result;
    printf("Became: %d/%d;\n\n",n,x);
    printf("6.105\n");
    x = 13;  //a
    n = 4;  //b
    i = 1;
    while (x > 0 && n > 0) {
        if (x > n) {
            x -= n;
            printf("%d)square: %dx%d;\n",i,n,n);
        } else {
            n -= x;
            printf("%d)square: %dx%d;\n",i,x,x);
        }
        ++i;
    }
    x = 21;
    b = 7;
    printf("\n6.106, a = %d, b = %d\n",x,b);
    i = 0;
    while (x - b >= 0) {
        x -= b;
        ++i;
    }
    printf("a) a / b = %d;\n",i);
    printf("b) a %% b = %d;\n\n",x);
    m = 64;
    n = 48;
    printf("6.107, m = %d, n = %d\n",m,n);
    for (i = 1; i <= m * n; ++i) {
        while (m % i == 0) {
            printf("%d cratno %d\n",i,m);
            break;
        }
        while (n % i == 0) {
            printf("%d cratno %d\n",i,n);
            break;
        }
    }
    n = 256;
    printf("\n6.108, money = %d\n",n);
    int money[7] = {0,0,0,0,0,0,0};
    for (i = 0, x = 64; x >= 1; ++i, x /= 2)
        while (n >= x) {
            n -= x;
            ++money[i];
        }
    for (i = 0, x = 64; i <= 6; ++i, x /= 2)
        printf("%d = %d;\n",x,money[i]);
    printf("\n6.110\n");
    n = 12345;
    x = n;
    m = 3; //a
    k = 0;
    printf("a) ");
    while (x > 0) {
        x1 = x % 10;
        x /= 10;
        printf("%d",x1);
        ++k;
    }
    x1 = k;
    int number_1[x1];
    for (i = 0; n > 0; ++i) {
        x = n % 10;
        number_1[i] = x;
        n /= 10;
    }
    printf("\nb) N = ");
    int n1 = 0;
    for (i = -1, x = 1;i <= x1; ++i, x *= 10) {
        if (i == -1)
            n1 += 2;
        else if (i == x1)
            n1 += 2 * x;
        else
            n1 += number_1[x1 - i - 1] * x;
        printf("%d, ",n1);
    }
    printf("\nv) ");
    for (i = x1 - 1; i >= 0; --i)
        if (number_1[i] != m)
            printf("%d",number_1[i]);
    printf("\ng) ");
    x = number_1[0];
    number_1[0] = number_1[x - 1];
    number_1[x - 1] = x;
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    number_1[x - 1] = number_1[0];
    number_1[0] = x;
    printf("\nd) ");
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    for (i = x1 - 1; i >= 0; --i)
        printf("%d",number_1[i]);
    printf("\n\n6.111\n");
    n = 362880;
    x = 1;
    for (i = 0; x < n; ++i)
        x *= i + 1;
    if (x == n)
        printf("Factorial = %d, number = %d;\n", n, i);
    else
        printf("This is not a factorial!\n\n");
}

void chapter_7()
{
    int a = 10;
    int b = 20;
    int c = 5;
    int help = 0;
    printf("7.2(7.4), a = %d, b = %d, c = %d\n",a,b,c);
    if (b > a) {
        help = a;
        a = b;
        b = help;
    }
    printf("All numbers devided by %d or 4: ",c);
    for (; a >= b; a--) {
        if (a % c == 0)
            printf("%d(%d) ",a,c);
        if (a % 4 == 0)
            printf("%d(4) ",a);
    }
    printf("\n\n");
    printf("7.6, searching numbers from 1000 to 9999, devided by 133 and 134.\n");
    for (int i = 1000; i <= 9999; ++i)
        if (i % 133 == 125 && i % 134 == 111)
            printf("%d ",i);
    int n = 6;
    printf("\n\n7.8, In range [100..999], Sum of digits,n = %d\n",n);
    int sum = 0;
    b = 0;
    c = 0;
    if (n <= 27 && n > 0) {
        for (int i = 100; i <= 999; ++i, sum = 0, c = i) {
            while (c > 0) {
                a  = c % 10;
                c /= 10;
                sum += a;
            }
            if (sum == n) {
                ++b;
                printf("%d ",i);
            }
        }
        printf("\nQuantity: %d", b);
    } else
        printf("You entered incorrect value!\n\n");
    n = 7;
    printf("\n\n7.10. in range [10..99], devided by n(or digit n), n = %d\n",n);
    for (int i = 10; i <= 99; ++i) {
        a = i % 10;
        b = i / 10;
        if (i % n == 0 || (a == n || b == n))
            printf("%d ",i);
    }
    printf("\n\n7.12. in range[30..100], devided by 3 and tail 2,4,8;\n");
    sum = 0;
    for (int i = 30; i <= 100; ++i)
        if (i % 3 == 0 && (i % 10 == 2 || i % 10 == 8 || i % 10 == 4)) {
            printf("%d ",i);
            sum += i;
        }
    printf("\nsum = %d;\n\n",sum);
    printf("7.14(7.16)\n");
    srand(time(NULL));
    double mass_d[8];
    double sum_d = 0;
    sum = 0;
    for (int i = 0; i < 8; ++i) {
        mass_d[i] = (double)(rand() % 100) / (double)(1 + rand() % 7);
        if (mass_d[i] < 10.5)
            sum_d += mass_d[i];
        printf("double(%.2f)\n",mass_d[i]);
        a = rand() % 11;
        if (a % 2 == 0) {
            sum += a;
            printf("int(%d)\n",a);
        }
    }
    printf("\nSum(< 10.75) = %.2f",sum_d);
    printf("\nSum(%% 2 == 0) = %d\n\n",sum);
    printf("7.20,sequence A, n = %d\n",SIZE);
    int mass[SIZE];
    a = 0;
    b = 1;
    for (int i = 0; i < SIZE; ++i) {
        mass[i] = rand() % 21;
        printf("%d ",mass[i]);
        a += mass[i] * b;
        b *= -1;
    }
    c = mass[0] + mass[SIZE - 1];
    help = mass[0] - mass[1];
    printf("\na(a1 - a2 + a3 ...)) %d\n",a);
    printf("b(a1 + A)) %d\n",c);
    printf("c(a1 - a2)) %d\n\n", help);
    printf("7.24, students in classes, sum of odd;\n");
    srand(time(NULL));
    int student_mass[11];
    sum = 0;
    for (int i = 0; i < 11; ++i) {
        student_mass[i] = 1 + rand() % 35;
        printf("class(%d): %d students\n", i + 1, student_mass[i]);
        if ((i + 1) % 2 != 0)
            sum += student_mass[i];
    }
    printf("Sum of students: %d\n\n",sum);
    printf("7.27. Doubles less than 100;\n");
    srand(time(NULL));
    a = 0;
    for (int i = 0; i < 8; ++i) {
        mass_d[i] = (double)(rand() % 1001) / (double)(1 + rand() % 8);
        printf("%.2f ",mass_d[i]);
        if (mass_d[i] < 100)
            ++a;
    }
    printf("\nQuantity: %d\n\n",a);
    printf("7.32. students and exams;\n");
    int undergrad_mass[15][2];
    help = 0;
    srand(time(NULL));
    for (a = 0; a < 15; ++a) {
        undergrad_mass[a][0] = 1 + rand() % 5;
        undergrad_mass[a][1] = 1 + rand() % 5;
        if (undergrad_mass[a][1] == 2 || undergrad_mass[a][0] == 2)
            ++help;
        printf("student #%d received %d and %d;\n", a + 1, undergrad_mass[a][1], undergrad_mass[a][0]);
    }
    printf("Number of students who received 2: %d\n\n",help);
    printf("7.33 - 7.37. Sequence of digits;\n");
    srand(time(NULL));
    help = 0;
    c = 0;
    int multiple_three = 0;
    int multiple_seven = 0;
    int identical_couples = 0;
    int zero_couples = 0;
    int even_couples = 0;
    int couples_five = 0;
    int difference = 0;
    for (int i = 0; i < SIZE; ++i) {
        a = rand() % 2;
        if (a == 0)
            mass[i] = rand() % 10;
        else
            mass[i] = -1 * rand() % 10;
        printf("%d ",mass[i]);
    }
    for (int i = 0; i < SIZE; ++i) {
        if (mass[i] < 0)
            ++help;
        if (mass[i] % 3 == 0)
            ++multiple_three;
        if (mass[i] % 7 == 0)
            ++multiple_seven;
        if (i < SIZE - 1 && mass[i] == mass[i + 1]) {
            if (mass[i] == 0 && mass[i + 1] == 0)
                ++zero_couples;
            if (mass[i] %2 == 0 && mass[i + 1] % 2 == 0)
                ++even_couples;
            if (mass[i] % 10 == 5 && mass[i + 1] % 10 == 5)
                ++couples_five;
            ++identical_couples;
        }
        if (i > 0 && i < SIZE - 1 && mass[i] > mass[i + 1] && mass[i] > mass[i - 1])
            ++c;
        if (i < SIZE - 1 && ((mass[i] > 0 && mass[i + 1] < 0) || (mass[i] < 0 && mass[i + 1] > 0)))
            ++difference;
    }
    printf("\n7.33) Number of negative numbers and number of positive numbers: %d:%d;\n", help, SIZE - help);
    printf("7.34) The number of multiples of three, and the number of multiples of seven: %d:%d;\n", multiple_three, multiple_seven);
    printf("7.35(a)) The number of pairs of adjacent numbers equal to each other: %d;\n", identical_couples);
    printf("7.35(b)) The number of pairs of adjacent numbers equal to zero: %d;\n", zero_couples);
    printf("7.35(v)) The number of pairs of adjacent numbers that are even numbers: %d;\n", even_couples);
    printf("7.35(g)) The number of pairs of adjacent numbers ending in digit 5: %d;\n", couples_five);
    printf("7.36) The number of real numbers that are larger than their neighbors: %d;\n", c);
    printf("7.37) How many signs in the sequence change: %d;\n", difference);
    printf("7.39\n");
    n = 5;
    const double g = 9.8;
    int alpha = 0;
    int start_speed = 0;
    double y = 0;
    double t = 0.01;
    double P = 20000.0, H = 5.0, R = 25.0;
    a = 0;
    b = 0;
    for (int i = 1; i <= n; ++i) {
        alpha = 1 + rand() % 46;
        start_speed = 1 + rand() % 1000;
        printf("%d) alpha = %d;\nstart speed = %d;\n\n",i,alpha,start_speed);
        /*
        while (x <= R) {
            x = start_speed * t * cos(alpha);
            y = start_speed * t * sin(alpha) - (g * pow(t,2)) / 2;
            t += 0.01;
        }
        */
        t = R / (cos(alpha) * start_speed);
        y = start_speed * t * sin(alpha) - (g * pow(t,2)) / 2;
        if (y <= P + H && y >= H)
            ++a;
        else
            ++b;
    }
    c = (100 / (b + a)) * a;
    printf("Hit percentage: %d; a(%d), b(%d)\n\n",c,a,b);
    printf("7.42.Score of football team.\n");
    b = 0;
    c = 0;
    help = 0;
    int score_table[3] = {0, 1, 3};
    for (int i = 0; i < 5; ++i) {
        a = rand() % 3;
        if (score_table[a] == 1)
            ++help;
        if (score_table[a] == 0)
            ++c;
        if (score_table[a] == 3)
            ++b;
        printf("%d[%d] ",score_table[a],a);
    }
    printf("\nWin = %d;\nLose = %d;\nDraw = %d;\n\n",b,c,help);
    srand(time(NULL));
    n = 8;
    c = 5;
    a = 10;
    sum = 0;
    help = 0;
    int sum1 = 0, help1 = 0, rand_1 = 2, rand_2 = 2;
    printf("7.44, 7.46. Average, n = %d, a = %d\n",n,a);
    for (int i = 0; i < a; ++i) {
        if (rand() % (a - rand_1 - rand_2 - i) == 0) {
            if (rand_1 > 0) {
                b = 1 + n + rand() % 5;
                rand_1--;
            } else if (rand_2 > 0) {
                b = c * (rand() % 5 + 1);
                rand_2--;
            }
        } else
            b = rand() % 17;
        if (b > n) {
            sum += b;
            ++help;
        }
        if (b % c == 0) {
            sum1 += b;
            ++help1;
        }
        printf("%d ",b);
    }
    printf("\n7.44. More than n) %d;\n",sum / help);
    printf("7.46. Which are multiples of n) %d, sum = %d, quantity = %d\n\n",sum1 / help1, sum1, help1);
    printf("7.51.Find the number of the last negative number, help = %d;\n",help);
    srand(time(NULL));
    b = 0;
    int i = 0;
    int a1 = 0, b1 = 0;
    for (i = 1; i <= a; ++i) {
        if (b1 < help) {
            a1 = rand() % 6;
            c = 1 + rand() % 9;
            if (a1 == 0) {
                c *= -1;
                b = i;
            }
            if (c > 0)
                ++b1;
        } else {
            if (c > 0) {
                c = -c;
                b1 = 0;
                b = i;
            }
        }

        printf("%d ",c);
    }
    printf("\nNumber of the last negative number: %d\n\n",b);
    printf("7.52, 7.54, Finding the minimum and maximum value\n");
    srand(time(NULL));
    n = 10;
    t = 0;
    help1 = 0;
    help = 0;
    double x = 100;
    y = 0;
    for (i = 0;i < n; ++i) {
        y = (double)(rand() % 100) / (double)(1 + rand() % 100);
        if (y >= t) {
            help = i;
            t = y;
        }
        if (y <= x) {
            help1 = i;
            x = y;
        }
        printf("%.2f ",y);
    }
    printf("\nMin(%d) = %.2f;\nMax(%d) = %.2f;\n\n",help1,x,help,t);
    printf("7.56, The longest path:\n");
    int city = 0;
    n = 5;
    a = 0;
    for (int i =0; i < n; ++i) {
        city = rand() % 9001;
        if (city > a)
            a = city;
        printf("%d)%d;\n",i + 1, city);
    }
    printf("The most remote: %d;\n\n",a);
    printf("7.59, Finding the diagonal of a square:\n");
    double S = 0, diagonal = 0, side = 0;
    x = 0;
    for (i = 0; i <= 5; ++i) {
        S = 1 + rand() % 100;
        side = sqrt(S);
        diagonal = sqrt(pow(side,2) * 2);
        if (diagonal > x)
            x = diagonal;
        printf("S = %.0f, diagonal = %.2f, side = %.2f;\n",S,diagonal,side);
    }
    printf("Max diagonal = %.2f;\n\n",x);
    printf("7.63, precipitation:\n");
    a = 0;
    for (i = 1; i <= 31; ++i) {
        b = rand() % 15;
        if (b >= a) {
            a = b;
            help = i;
        }
        printf("%d ",b);
    }
    printf("\nThe largest amount of precipitation was equal to %d, day = %d;\n\n",a,help);
    printf("7.66,biggest class:\n");
    a = 0;
    b = 30;
    c = b;
    for (i = 1; i <= 20; ++i) {
        help = 1 + rand() % c;
        if (help > a)
            a = help;
        if (help < b)
            b = help;
        printf("%d ",help);
    }
    printf("\nmax = %d, min = %d;\nexcess - %d;\n\n", a, b, a - b);
    printf("7.67, pairs of numbers:\n");
    n = 10;
    sum = 0;
    int product = n * n;
    for (i = 0; i < n; ++i) {
        a = rand() % n;
        b = rand() % n;
        if (sum < a + b)
            sum = a + b;
        if (product > a * b)
            product = a * b;
        printf("%d:%d(sum = %d)(prod = %d)\n",a,b,a + b,a * b);
    }
    printf("\nMax sum = %d;\nMin product = %d;\n\n",sum,product);
    printf("7.70,Minimum population density:\n");
    for (i = 0; i < 5; ++i) {
        a = 1 + rand() % 1000; // количество людей
        b = 1 + rand() % 1000; // площадь
        y = (double)b / (double)a; // МПН
        if (i == 0)
            t = y;
        if (y < t)
            t = y;
        printf("%d:%d(%.2f), ",b,a,y);
    }
    printf("\nMinimum population density: %.2f;\n\n",t);
    printf("7.76, Minimum temperature:\n");
    help = 0;
    for (i = 1; i <= 31; ++i) {
        a = rand() % 15;
        if (i == 1)
            b = a;
        if (a < b) {
            b = a;
            help = 0;
        }
        if (a == b)
            ++help;
        printf("%d ",a);
    }
    printf("\nMinimum temperature = %d, quantity = %d;\n\n",b,help);
    printf("7.79\n");
    n = 10;
    b = rand() % 256;
    printf("%d;\n",b);
    int binary[CHAR_BIT] = {0, 0, 0, 0, 0, 0, 0, 0};
    i = CHAR_BIT - 1;
    while (b > 0) {
        int bit = b%2;
        binary[i--] = bit;
        b /= 2;
    }
    printf("binary = ");
    int bits_len[2] = {CHAR_BIT,CHAR_BIT};
    int bits_type = binary[0], bits = 1;
    printf("%d",bits_type);
    for (i = 1; i < CHAR_BIT; ++i) {
        if (binary[i] == bits_type) {
            bits++;
            printf(".");
        }
        else {
            if ( bits_len[bits_type] > bits)
                bits_len[bits_type] = bits;
            bits = 1;
            bits_type = binary[i];
            printf("-");
        }
        printf("%d",binary[i]);
    }
    if ( bits_len[bits_type] > bits)
        bits_len[bits_type] = bits;
    printf("\nMin bits(zero) = %d, min bits(one) = %d;\n",bits_len[0], bits_len[1]);
    if (bits_len[0] > bits_len[1])
        printf("bits(1) more than bits(0);\n\n");
    else
        printf("bits(0) less or equal than bits(1);\n\n");
    printf("7.80, customer service:\n");
    n = 10;
    int time = 0;
    a = 0;
    int people_1[n];
    b = 0; // номер покупателя
    for (i = 0; i < n; ++i) {
        time = 1 + rand() % 10;
        if (i == 0)
            a = time;
        if (time < a)
            a = time;
        people_1[i] = time;
        printf("buyer: #%d, time = %d;\n",i,time);
    }
    printf("Fastest customer numbers: ");
    for (i = 0; i < n; ++i)
        if (people_1[i] == a)
            printf("%d; ",i);
    printf("\n\n");
    printf("7.81, min and max sum of pairs:\n");
    n = 20;
    a = -1;
    b = 0;
    c = 0;
    int min_sum = -1, max_sum = -1;
    if (n >= 3) {
        int mass_1[n];
        for (i = 0; i < n; ++i) {
            mass_1[i] = rand() % 10;
            printf("%d ",mass_1[i]);
        }
        for (i = 0; i < n - 1; ++i) {
            sum = mass_1[i] + mass_1[i + 1];
            if (a == -1) {
                max_sum = sum;
                min_sum = sum;
                a = 0;
            }
            if (sum > max_sum) {
                max_sum = sum;
                b = i;
            }
            if (sum < min_sum) {
                min_sum = sum;
                c = i;
            }
        }
        if (max_sum != -1 && min_sum != -1)
            printf("\nmax sum(%d,%d) = %d;\nmin sum(%d,%d) = %d;\n\n", b, b+1, max_sum, c, c+1, min_sum);
        else
            printf("\nNo pairs!;\n\n");
    } else
        printf("You entered incorrect value!\n\n");
    printf("7.82 - 7.83, determine the amount of min and max points:\n");
    const int amount = 3;
    n = 10;
    sum = 0;
    sum1 = 0;
    a = 0;
    b = 0;
    c = 0;
    b1 = 0;
    int b2 = 0, c1 = 0, c2 = 0;
    int football[n], max_scores[amount], min_scores[amount];
    for (i = 0; i < amount; ++i) {
        max_scores[i] = -1;
        min_scores[i] = 11;
    }
    for (i = 0; i < n; ++i) {
        football[i] = rand() % 11;
        printf("%d ",football[i]);
        if (football[i] > a)
            a = football[i];
    }
    for (i = 0; i < n; ++i) {
        b1 = 0;
        b2 = 0;
        c2 = min_scores[b2];
        c1 = max_scores[b1];
        for (int j = 1; j < amount; ++j)  {   // Подумать над итерациями!
            if (max_scores[j] < c1) {
                c1 = max_scores[j];
                b1 = j;
            }
            if (min_scores[j] > c2) {
                c2 = min_scores[j];
                b2 = j;
            }
        }
        if (football[i] > max_scores[b1])
            max_scores[b1] = football[i];
        if (football[i] < min_scores[b2])
            min_scores[b2] = football[i];
    }
    printf("\nMax scores: ");
    for (int j = 0; j < amount; ++j) {
        sum += max_scores[j];
        printf("%d ",max_scores[j]);
    }
    printf("\nMin scores: ");
    for (int j = 0; j < amount; ++j) {
        sum1 += min_scores[j];
        printf("%d ",min_scores[j]);
    }
    printf("\nSum of winners: max = %d, min = %d;\n\n", sum, sum1);
    printf("7.86 - 7.89;\n");
    n = 10;
    b = 50;
    c = 2;
    sum = 0;
    for (i = 0; i < 10; ++i) {
        a = rand() % 15;
        sum += a;
        printf("%d ",a);
    }
    printf("\nSum = %d",sum);
    printf("\n1) Amount is more than(100,78): ");
    if (sum > 78)
        printf("78");
    else
        printf("-");
    if (sum > 100)
        printf("100");
    printf("\n2) Is it true that the sum numbers less than b(%d)? - ",b);
    if (sum > b)
        printf("Yes!\n");
    else
        printf("No!\n");
    printf("3) Sum is even number? - ");
    if (sum % 2 == 0)
        printf("Yes!\n");
    else
        printf("No!\n");
    printf("4) It is true that the sum is a multiple of c(%d)? - ",c);
    if (sum % c == 0)
        printf("Yes!\n\n");
    else
        printf("No!\n\n");
    printf("7.93, the cheapest item:\n");
    c = 100;
    for (i = 0; i < 8; ++i) {
        a = rand() % 100; // 1
        b = rand() % 100; // 2
        printf("%d) 1(%d),2(%d);\n",i,a,b);
        if (a < c) {
            c = a;
            help = 1;
            help1 = i;
        }
        if (b < c) {
            c = b;
            help = 2;
            help1 = i;
        }
    }
    printf("Product number: ");
    if (help == 1)
        printf("%d(1)\n\n",help1);
    else
        printf("%d(2)\n\n",help1);
    printf("7.95\n");
    n = 50;
    product = 1;
    for (i = 0; i < 5; ++i) {
        a = rand() % 10;
        product *= a;
        printf("%d ",a);
    }
    if (product > n)
        printf("\nYes, product(%d) > n(%d)",product,n);
    else
        printf("\nNo, product(%d) > n(%d)",product,n);
    /*
    srand(time(NULL));
    int a = 1, mass[CHAR_BIT] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i = CHAR_BIT - 1;
    printf("a = %d;\n",a);
    while (a > 0) {
        mass[i--] = a % 2;
        a /= 2;
    }
    printf("number: = ");
    for (i = 1 ;i < CHAR_BIT; ++i) {
        printf("%d",mass[i]);
    }
    printf(";\n");
    */
    a = 5; //m
    b = 2; //p
    printf("7.100, 7.106, 7.108, checking the multiplicity of the sum, m = %d, p = %d:\n",a,b);
    n = 10;
    sum = 0;
    sum1 = 0;
    printf("numbers: ");
    for (i = 0; i < n; ++i) {
        c = rand() % 10;
        if (c > a)
            sum += c;
        printf("%d ",c);
        if (c % 2 == 0)
            sum1 += c;
    }
    if (sum % b == 0)
        printf("\nsum = %d, p = %d, YES! The sum is a multiple of p\n",sum,b);
    else
        printf("\nsum = %d, p = %d? NO! The sum is not a multiple of p\n",sum,b);
    if (sum1 % 3 == 0)
        printf("the sum of positive numbers is a multiple of 3;\n\n");
    else
        printf("the sum of positive numbers is not a multiple of 3;\n\n");
    printf("7.102, street:\n");
    n = 10;
    sum = 0;
    sum1 = 0;
    printf("Number of residents: ");
    for (i = 1; i <= 10; ++i) {
        a = rand() % 10;
        if (i % 2 == 0)
            sum += a;
        else
            sum1 += a;
        printf("%d ",a);
    }
    if (sum > sum1)
        printf("\nMost residents live in houses with even numbers: even = %d, odd = %d;\n\n",sum,sum1);
    else if (sum1 > sum)
        printf("\nMost residents live in houses with odd numbers: even = %d, odd = %d;\n\n",sum,sum1);
    else
        printf("\nThe even and odd sides have the same number of people: even = %d, odd = %d;\n\n",sum,sum1);
    printf("7.112, average height of students:\n");
    n = 15;
    sum = 0;
    sum1 = 0;
    for (i = 0; i < n; ++i) {
        a = -1 * ((rand() % 51) + 150); // мальчики
        b = 150 + rand() % 27;          // девочки
        sum += abs(a);
        sum1 += b;
        printf("boy = %d, girl = %d;\n",a,b);
    }
    if ((sum / n) - (sum1 / n) > 10)
        printf("The average height of boys is 10 cm more than girls: boy = %d, girl = %d\n\n",sum / n,sum1 / n);
    else
        printf("The average height of boys is 10 cm smaller than girls: boy = %d, girl = %d\n\n",sum / n,sum1 / n);
    c = rand() % 3;
    printf("7.115, average:, c = %d\n",c);
    help = 0;
    sum = 0;
    printf("numbers: ");
    for (i = 0; i < 12; ++i) {
        if (c == 0) {
            a = rand() % 9;
            if (a % 2 == 0)
                ++a;
        } else {
            a = rand() % 10;
            if (a % 2 == 0) {
                sum += a;
                ++help;
            }
        }
        printf("%d ",a);
    }
    if (help > 0)
        printf("\nAverage = %d;\n\n",sum / help);
    else
        printf("\nThere are no even numbers in the sequence;\n\n");
    b = rand() % 3;
    printf("7.118, Find number by the last negative number, b = %d\n",b);
    n = 10;
    help = 0;
    printf("numbers: ");
    for (i = 1; i <= n; ++i) {
        if (b == 0)
            c = rand() % 10;
        else {
            a = rand() % 3;
            c = 1 + rand() % 9;
            if (a == 0)
                c *= -1;
        }
        if (c < 0)
            help = i;
        printf("%d ",c);
    }
    if (help == 0) {
        printf("\nThere are no negative numbers in the sequence;\n\n");
    } else
        printf("\nNumber of the last negative number: %d\n\n",help);
    printf("7.122, determining the minimum and maximum age among a group of people:\n");
    n = 10;
    int min_age = 100, max_age = 0;
    printf("Age: ");
    for (i = 0; i < n; ++i) {
        a = 1 + rand() % 100;
        if (max_age < a) {
            max_age = a;
            help = i;
        }
        if (min_age > a) {
            min_age = a;
            help1 = i;
        }
        printf("%d ",a);
    }
    if (help > help1)
        printf("\nThe person with the minimum age appeared in the sequence earlier \n"
               "than the person with the maximum age: min = %d, max = %d,"
               " min and max pos: %d:%d;\n\n", min_age,max_age,help1,help);
    else
        printf("\nThe person with the maximum age appeared in the sequence earlier \n"
               "than the person with the minimum age: min = %d, max = %d,"
               " min and max pos: %d:%d;\n\n", min_age,max_age,help1,help);
    printf("7.124 - 7.125, sequence of not descending numbers:\n");
    int numbers[10];
    a = 0;
    help = 0;
    help1 = 1;
    numbers[0] = rand() % 10;
    for (i = 1; i < 10; ++i)
        numbers[i] = numbers[i - 1] + rand() % 3;
    for (i = 0; i < 9; ++i) {
        if (numbers[i] == numbers[i + 1] && a == 0) {
            ++help;
            a = 1;
        } else if (numbers[i] != numbers[i + 1]) {
            ++help1;
            a = 0;
        }
    }
    for (i = 0; i < 10; ++i)
        printf("%d ",numbers[i]);
    printf("\nSequences = %d,different numbers = %d;\n\n",help,help1);
    a = 6;
    printf("7.128, number = %d:\n",a);
    int result = ideal_number(a);
    if (result != 0)
        printf("Number is ideal\n\n");
    else
        printf("Number is not ideal\n\n");
    ScriptedEngeneer_1();
}

void chapter_8()
{
    printf("8.3\na)\n");
    //a
    int i = 1, j = 0;
    for (i = 1; i <= 5; ++i) {
        for (j = 0; j < i; ++j)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nb)\n");
    //b
    int k = 1;
    j = 5;
    for (i = 5; i <= 9; ++i){
        for (j = 1;j <= 10 - i; ++j)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nc)\n");
    //c
    j = 1;
    for (i = 10; i <= 50;i += 10, ++j) {
        for (k = 1; k <= j; ++k)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nd)\n");
    //d
    k = 1, j = 5;
    for (i = 5; i <= 25; i += 5, --j){
        for (k = 1;k <= j; ++k)
            printf("%-3d",i);
        printf("\n");
    }
    printf("\n");
    printf("8.7, Multiplication table:\n");
    j = 1;
    for (i = 1; i <= 9; ++i) {
        for (j = 1; j <= 9; ++j)
            printf("%d x %d = %2d; ", i, j, i * j);
        printf("\n");
    }
    int n = 5, a = 3;
    printf("\n8.9, scores of students:, exams = %d, students = %d;\n",a,n);
    srand(time(NULL));
    printf("\t1\t2\t3, - lessons:\n\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t",i);
        for (j = 0; j < a; ++j)
            printf("%d\t", 1 + rand() % 5);
        printf("\n");
    }
    printf("\nB)\t");
    for (i = 1; i <= n; ++i)
        printf("%d\t",i);
    printf("\n\n");
    for (k = 0; k < a; ++k) {
        printf("%d)\t",k);
        for (j = 1; j <= n; ++j)
            printf("%d\t", 1 + rand() % 5);
        printf("\n");
    }
    a = 3;
    n = 5;
    int sum = 0, sum1 = 0, salary = 0;
    int salary_mass[a];
    for (i = 0; i < a; ++i)
        salary_mass[i] = 0;
    printf("\n8.11,salary for workers, workers = %d, months = %d;\n",n,a);
    printf("Worker:\\Month:\t");
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Total:\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t\t",i);
        sum1 = 0;
        for (j = 0; j < a; ++j) {
            salary = 10 + rand() % 90;
            sum1 += salary;
            sum += salary;
            salary_mass[j] += salary;
            printf("%d\t",salary);
        }
        printf("%d\n",sum1);
    }
    printf("Total:\t\t");
    for (i = 0; i < a ; ++i)
        printf("%d\t",salary_mass[i]);
    printf("%d\n\n",sum);
    n = 5;
    a = 3;
    int c = 1, help = 1;
    printf("8.14, scores of students, students = %d, lessons = %d;\n",n,a);
    sum = 0;      // Количество студентов, сдавшие экзамены без двоек.
    sum1 = 0;     // Количество предметов, по которым были получены только оценки "5" и "4".
    int scores_mass[a], scores_mass1[a];
    printf("Students:\\Lessons:\t");
    for (i = 0; i < a; ++i) {
        scores_mass[i] = 0;
        scores_mass1[i] = 0;
    }
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("\n");
    for (i = 0; i < n; ++i, c = 1, help = 1) {
        printf("%d)\t\t\t",i);
        for (j = 0; j < a; ++j) {
            int score = 1 + rand() % 5;
            if (score < 3)
                scores_mass[j]++;
            if (score < 2 && c == 1)
                c = 0;
            if (score < 2)
                scores_mass1[j]++;
            printf("%d\t",score);
        }
        if (c == 1) {
            sum++;
            printf("Passed without negative scores.");
        } else
            printf("Passed with negative scores.");
        printf("\n");
        if (help == 0)
            sum1++;
    }
    printf("Total negatives:\t");
    for (i = 0; i < a; ++i)
        printf("%d\t",scores_mass[i]);
    printf("\nLucky students: %d;\n",sum);
    printf("Positive lessons:\t");
    for (i = 0; i < a; ++i)
        if (scores_mass1[i] == 0)
            printf("Yes\t");
        else
            printf("No\t");
    printf("\n\n");
    n = 5; // кол-во работников.
    a = 3; // кол-во месяцев.
    printf("8.17, salary for workers, workers = %d, months = %d;\n",n,a);
    int salary_month[a];// для каждого месяца.(б)
    int salary_workers[a];
    printf("Worker:\\Month:\t");
    for (k = 0; k < a; ++k) {
        salary_workers[k] = 0;
        salary_month[k] = 0;
    }
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Max salary on month:\n");
    for (i = 0; i < n; ++i) {
        int max_salary = 0;
        printf("%d)\t\t",i);
        for (j = 0; j < a; ++j) {
            salary = 1 + rand() % 100;
            printf("%d\t",salary);
            if (salary > max_salary)
                max_salary = salary;
            if (i == 0) {
                salary_workers[j] = i;
                salary_month[j] = salary;
            } else if (salary > salary_month[j]) {
                salary_month[j] = salary;
                salary_workers[j] = i;
            }
        }
        printf("%d\n",max_salary);
    }
    printf("Max salary:\t");
    for (i = 0; i < a; ++i)
        printf("%d\t",salary_workers[i]);
    n = 3;  // магазины.
    a = 5;  // дни.
    printf("\n\n8.20, Shop revenue;\n");
    int income_days[a], income_shops[n];
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    int max_income = 0,x = 0, y = 0; // номер дня и магазина с максимальным доходом.
    printf("Shops:\\Days:\t");
    for (k = 0; k < a; ++k)
        income_days[k] = 0;
    for (k = 0; k < n; ++k)
        income_shops[k] = 0;
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Sum of income:\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t\t",i);
        for (j = 0; j < a; ++j) {
            int income = 1 + rand() % 100;
            income_shops[i] += income;
            income_days[j] += income;
            printf("%d\t",income);
            if (income > max_income) {
                max_income = income;
                x = j;
                y = i;
            }
        }
        printf("%d\n",income_shops[i]);
    }
    printf("Sum of shops:\t");
    for (i = 0; i < n; ++i)
        if (income_shops[i] > r1) {
            r1 = income_shops[i];
            r3 = i;
        }
    for (i = 0; i < a; ++i) {
        printf("%d\t",income_days[i]);
        if (income_days[i] > r2) {
            r2 = income_days[i];
            r4 = i;
        }
    }
    printf("\na)Max sum of days: %d;\n",r3);
    printf("b)Max sum of shops: %d;\n",r4 + 1);
    printf("c)Shop = %d, Day = %d, Max income = %d;\n\n",y,x + 1, max_income);
    n = 5;
    a = 5;
    printf("8.23,goods and sales in days, goods = %d, sales = %d\n",n,a);
    int prices[n], sum_days[a];
    printf("Goods(prices):\\Sales(cost):\t");
    for (i = 0; i < a; ++i) {
        printf("%d:\t", i + 1);
        sum_days[i] = 0;
    }
    printf("Total:\n");
    int all_sum = 0, max_cost = 0, pos_cost= 0, max_day_cost = 0, pos_day_cost = 0;
    for (i = 0; i < n; ++i) {
        prices[i] = 1 + rand() % 9;
        int sum = 0;
        printf("%d(%d):\t\t\t\t",i,prices[i]);
        for (j = 0; j < a; ++j) {
            int quantity = 1 + rand() % 9;
            printf("%d(%d)\t",quantity,prices[i] * quantity);
            sum += quantity * prices[i];
            sum_days[j] += quantity * prices[i];
        }
        printf("%d\n",sum);
        if (sum > max_cost) {
            max_cost = sum;
            pos_cost = i;
        }
        all_sum += sum;
    }
    printf("B) Sum of days:\t\t\t");
    const int limit = 150;
    for (i = 0, n = 0; i < a; ++i) {
        if (sum_days[i] > max_day_cost) {
            max_day_cost = sum_days[i];
            pos_day_cost = i + 1;
        }
        if (sum_days[i] > limit)
            ++n;
        printf("%d\t",sum_days[i]);
    }
    printf("\nV) Total sales for all days: %d;\n",all_sum);
    printf("G) Max cost is: %d and good: %d;\n",max_cost,pos_cost);
    printf("D) Max cost is: %d and day: %d;\n",max_day_cost, pos_day_cost);
    printf("E) Days bigger than limit(%d): %d;\n\n",limit,n);
    n = 20;
    int divs_sum[n], max_divisor = 0, min_divisor = n, m = 2;
    c = 3; //k.
    int max_sum = 0, min_sum = 0, quantity = 0;
    const char* answ[] = {"NO","YES"};
    printf("8.25 - 8.38, Finding divisors, N = %d, C = %d, M = %d:\n",n,c,m);
    printf("T - total, Q - quantity;\n");
    printf("Number:\tDividers(T,Q):\tDivs=C:\tSum %% M:Prime:\tIdeal:\tPairs:\t\n");
    for (i = 0; i < n; ++i) {
        divs_sum[i] = 1;
        printf("%d:\t%d ",i + 1,divs_sum[i]);
        a = i + 1; k = 2; quantity = 1;
        int num = a;
        while (a > 1) {
            while (a % k == 0 && a > 1) {
                printf("%d ",k);
                divs_sum[i] += k;
                ++quantity;
                a /= k;
            }
            ++k;
        }
        printf("(%d,%d)",divs_sum[i],quantity);
        if (quantity == 1)
            printf("\t");
        printf("\t%s\t%s",answ[quantity == c],answ[divs_sum[i] % m == 0]);
        printf("\t%s\t%s\t",answ[prime_number(num)], answ[ideal_number(num)]);
        if (quantity > max_divisor) {
            max_divisor = quantity;
            r1 = num;
        }
        if (quantity < min_divisor) {
            min_divisor = quantity;
            r2 = num;
        }
        if (i == 0) {
            min_sum = divs_sum[i];
            r3 = num;
        }
        if (divs_sum[i] > max_sum) {
            max_sum = divs_sum[i];
            r4 = num;
        }
        if (divs_sum[i] < min_sum) {
            min_sum = divs_sum[i];
            r3 = num;
        }
        for (j = i - 1;j > 0; --j)
            if (divs_sum[j] == divs_sum[i])
                printf("%d:%d ",j + 1,i + 1);
        printf("\n");
    }
    printf("Number with min divisors: %d, divisors = %d;\n",r2,min_divisor);
    printf("Number with max divisors: %d, divisors = %d;\n",r1,max_divisor);
    printf("Number with max sum: %d, max sum = %d;\n",r4,max_sum);
    printf("Number with min sum: %d, min sum = %d;\n",r3,min_sum);
    /*
 *
        printf("%d:",i);
        a = i;
        if (prime_number(a) == 1)
            printf(" prime number;");
        if (ideal_number(a) == 1)
            printf(" ideal number;");
        printf("\ndivisors: ");
        for (j = 1; j <= a; ++j) {
            if (i % j == 0) {
                printf(" %d",j);
                sum += j;
                ++mults;
                if (j % m == 0)
                    printf("+");
            }
        }
        printf("\nTotal = %d, Sum = %d;\n\n",b,sum);
*/
}

int main()
{
    chapter_8();
    //getchar(); - не снимать.
    return 0;
}
