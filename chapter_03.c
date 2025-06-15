#include <stdio.h>
#include <math.h>

/*
 * Перечитать и проверить оформление и подписать название главы.
 */

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
    //3.6
    printf("3.6:\n");
    int x = 1, y = 0, z = 0; int help1, help2, help3;
    help1 = (x || y) && !z;
    printf("a)(%d OR %d) AND NOT %d = %d\n", x, y, z, help1);
    help2 = !x && !y;
    printf("b)NOT %d && NOT %d = %d\n", x, y, help2);
    help3 = !(x && z) || y;
    printf("v)NOT (%d AND %d) OR %d = %d\n", x, z, y, help3);
    help1 = (x && !y) || z;
    printf("g)%d AND (NOT %d OR %d) = %d\n",x,y,z,help1);
    help2 = x && (!y || z);
    printf("d) %d AND (NOT %d OR %d) = %d\n",x,y,z,help2);
    help3 = x || (!(y || z));
    printf("e) %d || (NOT(%d OR %d)) = %d\n\n",x,y,z,help3);
    //3.7
    printf("3.7:\n");
    int a = 0, b = 1, c = 0;
    help1 = a || !(a && b) || c;
    printf("a) %d OR NOT (%d AND %d) OR %d = %d\n",a,a,b,c,help1);
    help2 = !a || (a && (b || c));
    printf("b) NOT %d OR (%d AND (%d OR %d)) = %d\n", a, a, b, c, help2);
    help3 = (a || (b && !c)) && c;
    printf("v) (%d OR (%d AND NOT %d)) AND %d = %d\n\n", a, b, c, c, help3);
    //3.8
    printf("3.8:\n");
    x = 0; y = 0; z = 0;
    help1 = (x && !(z || y)) || !z;
    printf("a) %d AND NOT (%d OR %d) OR NOT %d = %d\n", x, z, y, z, help1);
    help2 = !x || (x && (y || z));
    printf("b) NOT %d OR %d AND (%d OR %d) = %d\n", x, x, y, z, help2);
    help3 = (x || (y && !z)) && z;
    printf("v) (%d OR %d AND NOT %d) AND %d = %d\n\n", x, y, z, z, help3);
    //3.9
    printf("3.9:\n");
    x = 1, y = 0, z = 0;
    help1 = !x || !y || !z;
    help2 = (!x || !y) && (x || y);
    help3 = (x && y) || (x && z) || !z;
    printf("NOT x OR NOT y OR NOT z = !%d || !%d || !%d = %d\n",x,y,z,help1);
    printf("(NOT x OR NOT y) AND (x OR y) = (!%d || !%d) && (%d || %d) = %d\n",x,y,x,y,help2);
    printf("x AND y OR x AND z OR NOT z = ");
    printf("%d && %d || %d && %d || !%d = %d\n\n",x,y,x,z,z,help3);
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
    x = 1, y = 2; int help = 0;
    help = (!(x * y < 0)) || (y > x);
    printf("3.11(x = 1, y = 2):\n");
    printf("zh:(!(x * y < 0)) || (y > x) = %d\n",help);
    help = (x >= 0) || (pow(y,2) != 4);
    printf("b:(x >= 0) || (pow(y,2) != 4) = %d\n",help);
    help = ((x * y) != 0) || (y > x);
    printf("d:((x * y) != 0) || (y > x) = %d\n\n",help);

    //3.13
    a = 0;
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
    //3.17
    printf("3.17\n");
    a = 0, b = 1;
    help1 = (!a && !b) || a;
    printf("a) NOT %d AND NOT %d OR %d = %d\n", a, b, a, help1);
    help2 = b || (!a && !b);
    printf("b) %d OR NOT %d AND NOT %d = %d\n", b, a, b, help2);
    help3 = b && !(a && !b);
    printf("v) %d AND NOT (%d AND NOT %d) = %d\n\n", b, a, b, help3);
    //3.19
    int b1 = 0;
    a1 = 0;
    printf("3.19:\n");
    while (a1 <= 1) {
        b1 = 0;
        while (b1 <= 1) {
            help = !(! a1 && ! b1) && a1;
            printf("NOT (NOT A AND NOT B) AND A = !(!%d && !%d) && %d = %d\n",a1,b1,a1,help);
            help = !(!a1 || !b1) || a1;
            printf("NOT (NOT A OR NOT B) OR A = !(!%d || !%d) || %d = %d\n",a1,b1,a1,help);
            help = !(!a1 || !b1) && b1;
            printf("NOT (NOT A OR NOT B) AND B = !(!%d || !%d) && %d = %d\n\n",a1,b1,b1,help);
            ++b1;
        }
        ++a1;
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
    //3.26
    int n = 0;
    printf("3.26:\na)");
    while (n < 8) {
        x = n % 2;
        y = n % 4 / 2;
        z = n / 4;
        printf("x = %d, y = %d,z = %d\n",x,y,z);
        help = !(x || y) && (!x || !z) ;
        printf("a: NOT(x OR y) AND (NOT x OR NOT z) = ");
        printf("!(%d || %d) && (!%d || !%d) = %d\n",x,y,x,z,help);
        help = !(!x && y) || (x && !z);
        printf("b: NOT (NOT x AND y) OR (x AND NOT z) = ");
        printf("!(!%d && %d) || (%d && !%d) = %d\n",x,y,x,z,help);
        help = x || (!y && !(x || !z));
        printf("c: x OR (NOT y AND NOT(x OR NOT z)) = ");
        printf("%d || (!%d && !(%d || !%d)) = %d\n\n",x,y,x,z,help);
        ++n;
    }
    //3.27
    x = 5;
    y = 4;
    printf("a)3.27: a)x > 2 && y > 3 = %d > 2 &&  %d > 3 = %d\n", x, y, (x > 2 && y > 3));
    help = 0 < (y <= 4) && (x < 5);
    printf("i)0 < y <= 4 && x < 5 = 0 < %d <= 4 && %d < 5 = %d\n",x,y,help);
    help = !((x > 0) && (x < 5));
    printf("zh)NOT((x > 0) AND (x < 5)) = %d\n",help);
    help = (x >= 0) && (y < 5);
    printf("v)(x >= 0) AND (y < 5) = %d\n\n",help);
    //3.29
    x = 254; y = 0; z = -259;
    printf("3.29: x = %d, y = %d, z = %d\n", x, y, z);
    help1 = (x % 2) && (y % 2);
    printf("a) x AND y odd = %d\n", help1);
    help2 = (x < 20) ^ (y < 20);
    printf("b) (x < 20) xOR (y < 20) = %d\n", help2);
    help3 = (x == 0) || (y == 0);
    printf("v) (x == 0) OR (y == 0) = %d\n",help3);
    help1 = x < 0 && y < 0 && z < 0;
    printf("g) x,y and z negative = %d\n", help1);
    help2 = ((x % 5 == 0) + (y % 5 == 0) + (z % 5 == 0)) == 1;
    printf("d) only 1 of x,y,z divided by 5 = %d\n",help2);
    help3 = (x > 100) || (y > 100) || (z > 100);
    printf("e) At least one of X,Y,Z more than 100 = %d\n\n", help3);
    //3.31
    x = 10;
    help = (x % 5 == 0) || (x % 7 == 0);
    printf("3.31:\na)(N %% 5 == 0) || (N %% 7 == 0) = (%d %% 5 == 0) || (%d %% 7 == 0) = %d\n",x,x,help);
    help = (x % 4 == 0) || (x % 10 != 0);
    printf("b)(x %% 4 == 0) || (x %% 10 != 0) = (%d %% 4 == 0) || (%d %% 10 != 0) = %d\n\n",x,x,help);
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
    c_a = 3; // король
    c_b = 4;
    c_c = 3; // пешка
    c_d = 5;
    help = (abs(c_c - c_a) <= 1) || (abs(c_d - c_b) <= 1);
    printf("v)korol on (%d,%d) and peshka (%d,%d) = %d\n", c_a, c_b, c_c, c_d,help);
    c_a = 5; // Ферзь
    c_b = 4;
    help = ((c_a == c_c) || (c_d == c_b)) || (abs(c_c - c_a) == abs(c_d - c_b));
    printf("g)ferz on (%d,%d) and peshka on(%d,%d) = %d\n",c_a,c_b,c_c,c_d,help);
    //3.35
    printf("3.35\n");
    c_a = 3; // ладья
    c_b = 4;
    c_c = 5; // ферзь
    c_d = 5;
    int c_e = 3; // нужно сюда попасть
    int c_f = 7;
    help = ((c_a == c_e) ^ (c_b == c_f));
    help = help && (((c_e == c_c) || (c_d == c_f)) || (abs(c_c - c_e) == abs(c_d - c_f)));
    printf("b)Rook on %d:%d moves to %d:%d, queen on %d:%d = %d;\n", c_a, c_b, c_e, c_f, c_c, c_d, help);
    c_a = 1; // ферзь
    c_b = 2;
    c_c = 7; // слон
    c_d = 8;
    c_e = 5; // нужно сюда попасть
    c_f = 6;
    help = ((c_e == c_a) || (c_b == c_f)) || (abs(c_a - c_e) == abs(c_b - c_f));
    help = help && (abs(c_c - c_e) == abs(c_d - c_f));
    printf("z)Queen on %d:%d moves to %d:%d, bishop on %d:%d = %d;\n", c_a, c_b, c_e, c_f, c_c, c_d, help);
    c_a = 4; // конь
    c_b = 4;
    c_c = 7; // слон
    c_d = 8;
    c_e = 5; // нужно сюда попасть
    c_f = 6;
    help = (abs(c_a - c_e) == 1 && abs(c_b - c_f) == 2) || (abs(c_a - c_e) == 2 && abs(c_b - c_f) == 1);
    help = help && (abs(c_c - c_e) == abs(c_d - c_f));
    printf("m)Knight on %d:%d moves to %d:%d, bishop on %d:%d = %d;\n\n", c_a, c_b, c_e, c_f, c_c, c_d, help);
}
