﻿#include <stdio.h>
#include <math.h>

/*
 *  Глава 1. Ввод и вывод числовых данных. Оператор присваивания.
 */

void chapter_1()
{
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
    printf("s:= d = %d\n",d1);
    s1 = d1;
    k1 = 2 * s1;
    printf("k:= 2 * s = 2 * %d = %d\n",s1,k1);
    k1 = 30;
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
    printf("1.60a: b = %d; a = %d; c = %d > b = c = %d;",b2,a2,c1,c1);
    t = b2;
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
