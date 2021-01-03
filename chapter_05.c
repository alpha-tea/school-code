#include "global.h"

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

int cubing(int n)
{
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

void invert_1(const char s[], int len)
{
    if (len <= 0) {
        printf("You entered incorrect lenth\n");
        return;
    }
    while (--len >= 0)
        printf("%c",s[len]);
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

int factorial(int n)
{
    int result = 1;
    for (; n > 0; --n) {
        result = result * n;
    }
    return result;
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

double summary(int n)
{
    if (n <= 1 || n > 10) {
        printf("You entered incorrect value!!!!\n");
        return -1;
    }
    double result = 1;
    for (int i = 1; i <= n; ++i)
        result += 1.0 / (double)factorial(i);
    return result;
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
