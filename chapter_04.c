#include "global.h"

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
