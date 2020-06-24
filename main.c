#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#define Y CHAR_MAX
#define Z CHAR_MIN

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
}
int main()
{
    chapter_5();
    //getchar(); - не снимать.
    return 0;
}
