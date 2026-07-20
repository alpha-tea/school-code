#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "library.h"

/*
 *  Глава 5. Оператор цикла с параметром.
 */

int task_5_94_print_and_sum_digits(int a, int n, int base)
{
    if (n <= 0 && a <= 0) {
        printf("You entered incorrect value!!\n");
        return -1;
    }
    printf("Binary: ");
    int temp = a;
    for (int i = 1; i <= n && temp > 0; ++i) {
        printf("%d", temp % base);
        temp /= base;
    }
    printf("\n");
    return sum_digits_base(a, base);
}

int task_5_92_nested_sqrt()
{
    double current_sqrt = 0, prev_sqrt = sqrtf(50);
    for (int i = 49; i > 0; --i) {
        current_sqrt = sqrtf(i) + prev_sqrt;
        prev_sqrt = current_sqrt;
    }
    printf("%.5f\n\n", current_sqrt);
    return 0;
}

int task_5_88_cubing(int n)
{
    int val_accum = 1;
    int val_step = 2;
    int val_temp = 1;
    int k = 1;
    printf("Making cube of %d; ", n);
    for (int i = 1; i < n; ++i) {
        val_accum += val_step;
        val_step += 2;
        val_temp = val_accum;
        printf(" i = %d: value = %d;", i, val_accum);
        for (k = 1; k <= i; ++k) {
            val_temp += val_accum + (2 * k);
            printf("r = %d; ", val_temp);
        }
    }
    printf("\n");
    return val_temp;
}

int task_5_86_squaring(int n)
{
    int val_accum = 1;
    int val_step = 2;
    for (int i = 1; i <= n; ++i) {
        printf("%d ^ 2 = %d;\n", i, val_accum);
        val_accum += val_step + 1;
        val_step += 2;
    }
    return 0;
}

int task_5_84_group_values(int n, int g)
{
    if (n % g != 0) {
        printf("Numbers are not divisible into groups.\n");
        return -1;
    }
    int diff_1 = 0, diff_2 = 0;
    for (int i = n; i > 0; i -= g) {
        diff_2 = i * i;
        for (int j = 1; j < g; ++j) {
            int m = (i - j) * (i - j);
            diff_2 -= m;
            printf("r2 = %d\n", diff_2);
        }
        diff_2 *= diff_2;
        printf("r2 ^ 2 = %d\n", diff_2);
        if (diff_1 == 0)
            diff_1 = diff_2;
        else
            diff_1 -= diff_2;
        printf("r1 = %d\n", diff_1);
    }
    return diff_1;
}

int loop_multiply(int x, int y)
{
    int result = 0;
    for (int i = 0; i < y; ++i) {
        result += x;
    }
    return result;
}

int task_5_39_generate_and_sum()
{
    srand(0);
    int i = 1, a = 0, sum = 0;
    while (i <= 10) {
        a = rand() % 10;
        sum += a;
        printf("%d ", a);
        ++i;
    }
    printf("\n");
    return sum;
}

double task_5_90_sum_inverse_factorials(int n)
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
    printf("Chapter 5. Operators FOR and WHILE. Formatted output ints and input and recursive statements;\n\n");
    printf("5.3\n\n");
    int i = 0, a = 20, b = 15, i1 = 10, a1 = 7, result = 0;
    printf("Numbers\tSquare\tDegree(3)\n\n");
    while (i <= 5) {
        printf("a) %3d %3d\n", i, a + i);
        if (i1 + i <= b) {
            result = pow(i1 + i, 2);
            printf("b) %3d %3d\n", i1 + i, result);
        } else
            printf("b) --\n");
        if (a1 + i <= 50) {
            result = pow(a1 + i, 3);
            printf("c) %3d %3d\n", a1 + i, result);
        } else
            printf("c) Value is greater than 50!\n");
        if (i >= 1 && i <= 4) {
            printf("d) %3d\n", i);
        }
        ++i;
    }
    printf("\n");
    printf("5.8. Pounds to kilograms table\n");
    double pound = 1, kilograms = 0;
    const double grams_in_pound = 453.0;
    while (pound <= 10) {
        kilograms = pound * grams_in_pound / 1000;
        printf("%2.0f lb = %2.3f kg\n", pound, kilograms);
        ++pound;
    }
    printf("\n5.9. Inches to centimeters\n");
    double inch = 10, cm = 0;
    const double cm_per_inch = 2.54;
    while (inch <= 22) {
        cm = inch * cm_per_inch;
        printf("%2.0f inch = %2.2f cm\n", inch, cm);
        ++inch;
    }
    printf("\n5.10. Converter: dollars to rubles\n");
    const double usd = 68.78;
    int temp = 1;
    while (temp <= 20) {
        printf("%d usd = %0.2f rub\n", temp, temp * usd);
        ++temp;
    }
    printf("\n5.11. Distance to the horizon line\n");
    int R = 6350, h = 1, horizon = 0;
    while (h <= 10) {
        horizon = pow(R + h, 2) - pow(R, 2);
        printf("length = %0.f km\n", sqrt(horizon));
        ++h;
    }
    printf("\n5.15. Multiplication table\n");
    int n = 7;
    temp = 1;
    while (temp <= 10) {
        printf("%d * %d = %d;\n", n, temp, n * temp);
        ++temp;
    }
    i = 3;
    printf("\n5.16. Sine table.\n");
    while (i <= 20) {
        printf("sin(%d) = %0.6f\n", i, sin(i));
        ++i;
    }
    printf("\n5.18. Calculation of z by formula.\n");
    a = 2;
    double t = 0, z = 0;
    while (a <= 17) {
        t = 4 * a;
        z = (3.5 * pow(t, 2)) - (7 * t) + 16;
        printf("z = %.f, a = %d\n", z, a);
        ++a;
    }
    printf("\n5.20. Roots table.\n");
    i = 1;
    double temp1 = 0.1;
    while (i <= 9) {
        printf("sqrt(%.1f) = %.5f\n", temp1, sqrt(temp1));
        temp1 += 0.1;
        ++i;
    }
    printf("\n5.22. Candy cost calculation.\n");
    double cost = 289.45;
    double mass = 0.1;
    i = 1;
    while (i <= 20) {
        printf("cost(%.1f kg) = %.2f rub\n", mass, cost * mass);
        mass += 0.1;
        ++i;
    }
    printf("\n5.24. Number sequence.\n");
    i = 1;
    temp1 = 3.2;
    while (i <= 8) {
        printf("%.1f\n%.1f\n", temp1, temp1);
        ++i;
        temp1 += 0.1;
    }
    printf("\n5.26. Number sequence.\n");
    i = 1;
    temp1 = 4.4;
    while (i <= 11) {
        printf("%.1f\n", temp1);
        ++i;
        temp1 += 0.2;
    }
    printf("\n5.30\n");
    i = 20;
    int sum = 0;
    while (i <= 40) {
        sum += pow(i, 3);
        ++i;
    }
    printf("c) Sum of cubes = %d\n", sum);
    sum = 0;
    a = 1;
    n = 5;
    while (a <= n) {
        sum += a * a;
        ++a;
    }
    printf("d) Sum of squares = %d\n\n", sum);
    n = 10;
    printf("5.31 - 5.35. n = %d\n", n);
    printf("idx\t5.31:\t5.32:\t5.33:\t5.34:\t5.35:\n");
    double s = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, p3 = 1, p4 = 1;
    for (i = 0; i < n; ++i) {
        double e1 = (n + i) * (n + i);
        double e2 = 1.0 / (i + 1);
        double e3 = (double)(2 + i) / (double)(3 + i);
        double e4 = 1.0 / p3;
        p3 *= 3;
        double e5 = 1.0 / (i + 1) * p4;
        p4 *= -1;
        s += e1;
        s1 += e2;
        s2 += e3;
        s3 += e4;
        s4 += e5;
        printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", i, e1, e2, e3, e4, e5);
    }
    printf("sum:\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n\n", s, s1, s2, s3, s4);
    printf("5.39: Sum of the sequence\n");
    srand(0);
    sum = 0;
    sum += task_5_39_generate_and_sum();
    printf("Sum = %d\n\n", sum);
    printf("5.42: Exam grades\n");
    i = 1;
    sum = 0;
    while (i <= 4) {
        a = 1 + rand() % 5;
        sum += a;
        printf("%d ", a);
        ++i;
    }
    printf("\n");
    printf("Points = %d\n\n", sum);
    printf("5.45: Total resistance of elements\n");
    i = 0;
    sum = 0;
    a = 1 + rand() % 10;
    while (i <= a) {
        a = 1 + rand() % 10;
        sum += a;
        printf("%d ", a);
        ++i;
    }
    printf("\n");
    printf("Sum = %d\n\n", sum);
    printf("5.48: Sum of squares of numbers\n");
    i = 0;
    sum = 0;
    a = 1 + rand() % 10;
    while (i <= a) {
        a = 1 + rand() % 10;
        sum += a * a;
        printf("%d ", a);
        ++i;
    }
    printf("\n\n");
    printf("Sum of squares = %d\n\n", sum);
    printf("5.51\n");
    srand(1);
    n = 3;
    s = 0;
    for (i = 0; i < 3; ++i) {
        double e = (double)(rand() % 10) / (double)(1 + rand() % 10);
        s += e;
        printf("%.1f ", e);
    }
    printf("AVERAGE = %.2f\n\n", s / n);
    printf("5.54\n");
    n = 10;
    srand(1);
    s = 0;
    for (i = 0; i < n; ++i) {
        a = 1 + rand() % 5;
        s += a;
        printf("%d ", a);
    }
    printf("AVERAGE GRADE = %.0f\n\n", s / n);
    printf("5.56\n");
    n = 1 + rand() % 5;
    i = 1;
    sum = 0;
    while (i <= n) {
        a = rand() % 10;
        sum += abs(a);
        printf("%d ", a);
        ++i;
    }
    printf("\n");
    printf("a) Sum = %d\n\n", sum);
    n = 1 + rand() % 5;
    i = 1;
    sum = 1;
    while (i <= n) {
        a = 1 + rand() % 10;
        sum *= abs(a);
        printf("%d ", a);
        ++i;
    }
    printf("\n");
    printf("b) Product = %d\n\n", sum);
    sum = 0;
    n = 1 + rand() % 8;
    i = 1;
    printf("c)\n");
    a = 1 + rand() % 10;
    while (i <= n) {
        b = 1 + rand() % 10;
        sum += a + b;
        printf("%d + %d = %d\n", a, b, sum);
        ++i;
        a = b;
    }
    printf("Sum = %d\n", sum);
    n = 1 + rand() % 5;
    i = 1;
    sum = 0;
    b = 1;
    while (i <= n) {
        a = rand() % 10;
        sum += a * b;
        printf("%d ", a * b);
        ++i;
        b *= -1;
    }
    printf("\n");
    printf("d) Sum = %d\n\n", sum);
    printf("\n5.57\n");
    int sum1 = 0;
    i = 1;
    sum = 0;
    printf("Two students: ");
    while (i <= 4) {
        a = 1 + rand() % 5;
        b = 1 + rand() % 5;
        sum += a;
        sum1 += b;
        printf("%d - %d; ", a, b);
        ++i;
    }
    printf("\nTotal: %d - %d; \n\n", sum, sum1);
    printf("5.60\n");
    int january = 0, march = 0;
    i = 1;
    printf("January\t\tMarch\n");
    while (i <= 31) {
        a = 1 + rand() % 40;
        january += a;
        b = 1 + rand() % 15;
        march += b;
        printf("%4d\t\t%4d\n", a, b);
        ++i;
    }
    printf("\nTotal:\n%4d\t\t%4d\n\n", january / 31, march / 31);
    printf("5.63\n");
    srand(1);
    sum = 0;
    for (i = 1; i <= 10; ++i) {
        a = 1 + rand() % 7;
        b = 1 + rand() % 5;
        printf("%d - %d; ", a, b);
        sum += a * b;
    }
    printf("TOTAL HARVEST = %d\n", sum);
    printf("AVERAGE YIELD = %.2f\n\n", (double)sum / 10.0);
    printf("5.66. Sequence: ");
    n = 5;
    double a2 = 0, a3 = 0;
    for (int k = 1; k <= n; ++k) {
        a3 = k * (a2) + 1.0 / k;
        printf("a%d = %.2f; ", k, a3);
        a2 = a3;
    }
    printf("\n5.67\n");
    int k = 7;
    n = 10;
    a = 1;
    a1 = 1;
    sum = 2;
    printf("Fibonacci: %d %d ", a, a1);
    for (i = 3; i <= n; ++i) {
        b = a1 + a;
        a = a1;
        a1 = b;
        sum += b;
        printf("%d(%d) ", b, sum);
        if (i == k) {
            printf("Element k found; ");
        }
    }
    if (sum % 2 == 0)
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
    printf("a) k = %d; k / p = %.f / %.f = %.3f\n", k1, (double)k, p, (double)k / p);
    p = 1;
    k = 1;
    n = 6;
    a = 7;
    s = 0;
    printf("b) ");
    for (i = 1; i <= n; ++i) {
        printf("%d) %.3f; ", i, (double)k / p);
        s += (double)k / p;
        p1 = k;
        k += p;
        p = p1;
    }
    if (s > a)
        printf("\nc) Yes, sum > A; %.3f > %d;\n\n", s, a);
    else
        printf("\nc) No, sum < A; %.3f < %d;\n\n", s, a);
    printf("5.69\n");
    double v1 = 0, v2 = 0, v3 = 1.5, v4 = 0;
    n = 7;
    printf("Sequence: ");
    for (i = 4; i < n; ++i) {
        v4 = ((i - 1.0) / (pow(i, 2) + 1)) * v3 - v2 + v1;
        printf("%.2f; ", v4);
    }
    printf("\n\n5.70\n");
    a = 1;
    for (i = 1; i <= 24 / 3; ++i) {
        a *= 2;
        printf("%d hours = %d amoebas\n", i * 3, a);
    }
    printf("\n5.71\n");
    double score = 1000, profit = 0, sum_score = 0;
    const double percent = 2;
    for (i = 1; i <= 5; ++i) {
        if (i >= 3 && i <= 5)
            printf("%d) %.2f\t%.2f\n", i, score, profit);
        else
            printf("%d) %.2f\t-\n", i, score);
        sum_score = score + (score / 100 * percent);
        profit = sum_score - score;
        score = sum_score;
    }
    printf("\n5.72\n");
    printf("a)\n");
    double way = 10, sum_way = 0;
    for (i = 1; i <= 10; ++i) {
        way += way / 10;
        if (i <= 7)
            sum_way += way;
        printf("Way = %.2f km\n", way);
    }
    printf("b) sum = %.2f\n\n", sum_way);
    printf("5.73\n");
    v1 = 100.0; v2 = 20; v3 = 0.05; v4 = 0.02;
    s = 0;
    printf("Year:\tArea:\tYield:\tHarvest:\tSum:\n");
    for (i = 1; i < 8; ++i) {
        double v5 = v1 * v2;
        s += v5;
        printf("%d\t", i);
        if (i <= 7 && i >= 4)
            printf("%.f\t\t", v1);
        else
            printf("-\t\t");
        if (i >= 2)
            printf("%.2f\t\t", v2);
        else
            printf("-\t\t");
        if (i <= 6)
            printf("%.f\t\t%.f", v5, s);
        else
            printf("-\t\t-");
        printf("\n");
        v1 = v1 + (v1 * v3);
        v2 = v2 + (v2 * v4);
    }
    printf("\n5.74\n");
    v1 = 10; v2 = 10; v3 = 0.5; v4 = acos(-1.0) / 6 * v1 * v1 * v1; s = v4;
    n = 12;
    printf("Sequence: ");
    for (i = 1; i < n; ++i) {
        v2 += v1 + v3;
        double v5 = acos(-1.0) / 6 * v2 * v2 * v2;
        s += v5 - v4;
        v1 = v2;
        v4 = acos(-1.0) / 6 * v1 * v1 * v1;
        printf("%3.1f - %3.1f: %3.1f - %3.1f; ", v1, v4, v2, v5);
    }
    printf("\n\n5.75\n");
    sum = 0;
    temp = 2 * 2;
    for (i = 1; i <= 10; ++i) {
        sum += temp;
        temp *= 2;
    }
    printf("%d\n\n", sum);
    printf("5.76\n");
    a2 = 2.2;
    temp1 = a2;
    n = 5;
    for (i = 1; i <= n; ++i) {
        temp1 *= a2;
        printf("%.2f\n", temp1);
    }
    printf("\n5.77\n");
    b = -1;
    sum = 0;
    for (i = 1; i <= 10; ++i) {
        sum += i * i * b;
        b *= -1;
        printf("i = %d;  sum = %d; sign = (%d)\n", i, sum, b);
    }
    printf("\n5.78\n");
    double x1 = 2, x2 = -1, S_sin = 0;
    if (x2 >= x1 && x1 >= 0 && x2 <= acos(-1.0)) {
        S_sin = cos(x1) - cos(x2);
        printf("Area of the sinusoid arch = %.5f\n\n", S_sin);
    } else {
        printf("Incorrect value\n\n");
    }
    printf("5.81\n");
    int x = 5, y = 7;
    result = loop_multiply(x, y);
    printf("x * y = %d * %d = %d\n\n", x, y, result);
    printf("5.82\n");
    n = 1;
    result = factorial(n);
    printf("n = %d; n! = %d;\n\n", n, result);
    printf("5.83\n");
    a = 3;
    p3 = 3;
    printf("a ^ n = %.f ^ %d = %.f\n", p3, a, power_int_exp(p3, a));
    printf("5.84\n");
    task_5_84_group_values(9, 3);
    printf("5.85\n");
    const char s_str[] = "12345";
    printf("Inverted value = ");
    string_print_reversed(s_str);
    printf(";\n\n");
    printf("5.86. n^2 = 1 + 3 + 5 + 7 + ... 2n + 1\n");
    n = 4;
    task_5_86_squaring(n);
    printf("\n5.88. Cubing\n");
    for (i = 1; i <= 5; ++i) {
        result = task_5_88_cubing(i);
        printf("%d ^ 3 = %d;\n", i, result);
    }
    printf("\n5.90\n");
    n = 5;
    double result_1 = 0;
    result_1 = task_5_90_sum_inverse_factorials(n);
    printf("result = %.2f;\n", result_1);
    printf("\n5.92\n");
    task_5_92_nested_sqrt();
    printf("\n5.94\n");
    n = 178;
    result = task_5_94_print_and_sum_digits(n, 8, 2);
    printf("Sum of digits of a six-digit number %d = %d\n\n", n, result);
}