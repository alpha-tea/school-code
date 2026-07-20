#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "library.h"
#define SIZE 10

/*
 *  Глава 7. Сочетание оператора цикла и условного оператора.
 */

void ScriptedEngeneer_1()
{
    int count = 0;
    unsigned char n = 0;
    printf("Task from ScriptedEngeneer 1:\n");
    printf("Size of unsigned char: %d bytes and bits in char: %d;\n", (int)sizeof(n), CHAR_BIT);
    printf("Size of unsigned short int: %u;\n", (unsigned int)sizeof(unsigned short int));
    char binary[CHAR_BIT + 1];
    for (int i = 0; i <= CHAR_BIT; ++i)
        binary[i] = 0;
    for (unsigned short int j = 0x0000; j < 0x100; ++j) {
        n = j & 0x00ff;
        byte_to_binary_str(n, binary);
        int size = string_length(binary);
        int i;
        for (i = 0; i < size && binary[i] == binary[size - i - 1]; ++i)
            ;
        if (i == size) {
            printf("%d\t%s\n", n, binary);
            ++count;
        }
    }
    printf("Total palindromes [0..255]: %d", count);
}

void chapter_7()
{
    printf("Chapter 7. Generated sequences computations, simple search and numbers;\n\n");
    int a = 10, b = 20, c = 5, temp = 0;
    printf("7.2(7.4), a = %d, b = %d, c = %d\n", a, b, c);
    if (b > a) {
        temp = a;
        a = b;
        b = temp;
    }
    printf("All numbers divisible by %d or 4: ", c);
    for (; a >= b; a--) {
        if (a % c == 0)
            printf("%d(%d) ", a, c);
        if (a % 4 == 0)
            printf("%d(4) ", a);
    }
    printf("\n\n");
    printf("7.6, searching numbers from 1000 to 9999, divisible by 133 and 134.\n");
    for (int i = 1000; i <= 9999; ++i)
        if (i % 133 == 125 && i % 134 == 111)
            printf("%d ", i);
    int n = 6;
    printf("\n\n7.8, In range [100..999], Sum of digits, n = %d\n", n);
    int sum = 0;
    b = 0;
    c = 0;
    if (n <= 27 && n > 0) {
        for (int i = 100; i <= 999; ++i, sum = 0, c = i) {
            while (c > 0) {
                a = c % 10;
                c /= 10;
                sum += a;
            }
            if (sum == n) {
                ++b;
                printf("%d ", i);
            }
        }
        printf("\nQuantity: %d", b);
    } else
        printf("You entered incorrect value!\n\n");
    n = 7;
    printf("\n\n7.10. in range [10..99], divisible by n (or digit n), n = %d\n", n);
    for (int i = 10; i <= 99; ++i) {
        a = i % 10;
        b = i / 10;
        if (i % n == 0 || (a == n || b == n))
            printf("%d ", i);
    }
    printf("\n\n7.12. in range [30..100], divisible by 3 and tail 2,4,8;\n");
    sum = 0;
    for (int i = 30; i <= 100; ++i)
        if (i % 3 == 0 && (i % 10 == 2 || i % 10 == 8 || i % 10 == 4)) {
            printf("%d ", i);
            sum += i;
        }
    printf("\nsum = %d;\n\n", sum);
    printf("7.14(7.16)\n");
    srand(0);
    double double_array[8];
    double sum_d = 0;
    sum = 0;
    for (int i = 0; i < 8; ++i) {
        double_array[i] = (double)(rand() % 100) / (double)(1 + rand() % 7);
        if (double_array[i] < 10.5)
            sum_d += double_array[i];
        printf("double(%.2f)\n", double_array[i]);
        a = rand() % 11;
        if (a % 2 == 0) {
            sum += a;
            printf("int(%d)\n", a);
        }
    }
    printf("\nSum(< 10.75) = %.2f", sum_d);
    printf("\nSum(%% 2 == 0) = %d\n\n", sum);
    printf("7.20, sequence A, n = %d\n", SIZE);
    int mass[SIZE];
    a = 0;
    b = 1;
    for (int i = 0; i < SIZE; ++i) {
        mass[i] = rand() % 21;
        printf("%d ", mass[i]);
        a += mass[i] * b;
        b *= -1;
    }
    c = mass[0] + mass[SIZE - 1];
    temp = mass[0] - mass[1];
    printf("\na(a1 - a2 + a3 ...)) %d\n", a);
    printf("b(a1 + A)) %d\n", c);
    printf("c(a1 - a2)) %d\n\n", temp);
    printf("7.24, students in classes, sum of odd;\n");
    srand(1);
    int student_counts[11];
    sum = 0;
    for (int i = 0; i < 11; ++i) {
        student_counts[i] = 1 + rand() % 35;
        printf("class(%d): %d students\n", i + 1, student_counts[i]);
        if ((i + 1) % 2 != 0)
            sum += student_counts[i];
    }
    printf("Sum of students: %d\n\n", sum);
    printf("7.27. Doubles less than 100;\n");
    srand(1);
    a = 0;
    for (int i = 0; i < 8; ++i) {
        double_array[i] = (double)(rand() % 1001) / (double)(1 + rand() % 8);
        printf("%.2f ", double_array[i]);
        if (double_array[i] < 100)
            ++a;
    }
    printf("\nQuantity: %d\n\n", a);
    printf("7.32. students and exams;\n");
    int undergrad_grades[15][2];
    temp = 0;
    srand(1);
    for (a = 0; a < 15; ++a) {
        undergrad_grades[a][0] = 1 + rand() % 5;
        undergrad_grades[a][1] = 1 + rand() % 5;
        if (undergrad_grades[a][1] == 2 || undergrad_grades[a][0] == 2)
            ++temp;
        printf("student #%d received %d and %d;\n", a + 1, undergrad_grades[a][1], undergrad_grades[a][0]);
    }
    printf("Number of students who received 2: %d\n\n", temp);
    printf("7.33 - 7.37. Sequence of digits;\n");
    srand(1);
    temp = 0;
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
        printf("%d ", mass[i]);
    }
    for (int i = 0; i < SIZE; ++i) {
        if (mass[i] < 0)
            ++temp;
        if (mass[i] % 3 == 0)
            ++multiple_three;
        if (mass[i] % 7 == 0)
            ++multiple_seven;
        if (i < SIZE - 1 && mass[i] == mass[i + 1]) {
            if (mass[i] == 0 && mass[i + 1] == 0)
                ++zero_couples;
            if (mass[i] % 2 == 0 && mass[i + 1] % 2 == 0)
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
    printf("\n7.33) Number of negative numbers and number of positive numbers: %d:%d;\n", temp, SIZE - temp);
    printf("7.34) The number of multiples of three, and the number of multiples of seven: %d:%d;\n", multiple_three, multiple_seven);
    printf("7.35(a)) The number of pairs of adjacent numbers equal to each other: %d;\n", identical_couples);
    printf("7.35(b)) The number of pairs of adjacent numbers equal to zero: %d;\n", zero_couples);
    printf("7.35(v)) The number of pairs of adjacent numbers that are even numbers: %d;\n", even_couples);
    printf("7.35(g)) The number of pairs of adjacent numbers ending in digit 5: %d;\n", couples_five);
    printf("7.36) The number of real numbers that are larger than their neighbors: %d;\n", c);
    printf("7.37) How many signs in the sequence change: %d;\n", difference);
    printf("7.39\n");
    n = 5;
    const double g_const = 9.8;
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
        printf("%d) alpha = %d;\nstart speed = %d;\n\n", i, alpha, start_speed);
        t = R / (cos(alpha) * start_speed);
        y = start_speed * t * sin(alpha) - (g_const * pow(t, 2)) / 2;
        if (y <= P + H && y >= H)
            ++a;
        else
            ++b;
    }
    c = (100 / (b + a)) * a;
    printf("Hit percentage: %d; a(%d), b(%d)\n\n", c, a, b);
    printf("7.42. Score of football team.\n");
    b = 0;
    c = 0;
    temp = 0;
    int score_table[3] = {0, 1, 3};
    for (int i = 0; i < 5; ++i) {
        a = rand() % 3;
        if (score_table[a] == 1)
            ++temp;
        if (score_table[a] == 0)
            ++c;
        if (score_table[a] == 3)
            ++b;
        printf("%d[%d] ", score_table[a], a);
    }
    printf("\nWin = %d;\nLose = %d;\nDraw = %d;\n\n", b, c, temp);
    srand(1);
    n = 8;
    c = 5;
    a = 10;
    sum = 0;
    temp = 0;
    int sum1 = 0, temp1 = 0, rand_1 = 2, rand_2 = 2;
    printf("7.44, 7.46. Average, n = %d, a = %d\n", n, a);
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
            ++temp;
        }
        if (b % c == 0) {
            sum1 += b;
            ++temp1;
        }
        printf("%d ", b);
    }
    printf("\n7.44. More than n) %d;\n", sum / temp);
    printf("7.46. Which are multiples of n) %d, sum = %d, quantity = %d\n\n", sum1 / temp1, sum1, temp1);
    printf("7.51. Find the number of the last negative number, temp = %d;\n", temp);
    srand(1);
    b = 0;
    int index = 0;
    int a1 = 0, b1 = 0;
    for (index = 1; index <= a; ++index) {
        if (b1 < temp) {
            a1 = rand() % 6;
            c = 1 + rand() % 9;
            if (a1 == 0) {
                c *= -1;
                b = index;
            }
            if (c > 0)
                ++b1;
        } else {
            if (c > 0) {
                c = -c;
                b1 = 0;
                b = index;
            }
        }
        printf("%d ", c);
    }
    printf("\nNumber of the last negative number: %d\n\n", b);
    printf("7.52, 7.54, Finding the minimum and maximum value\n");
    srand(1);
    n = 10;
    t = 0;
    temp1 = 0;
    temp = 0;
    double min_x = 100;
    for (index = 0; index < n; ++index) {
        y = (double)(rand() % 100) / (double)(1 + rand() % 100);
        if (y >= t) {
            temp = index;
            t = y;
        }
        if (y <= min_x) {
            temp1 = index;
            min_x = y;
        }
        printf("%.2f ", y);
    }
    printf("\nMin(%d) = %.2f;\nMax(%d) = %.2f;\n\n", temp1, min_x, temp, t);
    printf("7.56, The longest path:\n");
    int city = 0;
    n = 5;
    a = 0;
    for (int i = 0; i < n; ++i) {
        city = rand() % 9001;
        if (city > a)
            a = city;
        printf("%d)%d;\n", i + 1, city);
    }
    printf("The most remote: %d;\n\n", a);
    printf("7.59, Finding the diagonal of a square:\n");
    double S = 0, diagonal = 0, side = 0;
    min_x = 0;
    for (index = 0; index <= 5; ++index) {
        S = 1 + rand() % 100;
        side = sqrt(S);
        diagonal = sqrt(pow(side, 2) * 2);
        if (diagonal > min_x)
            min_x = diagonal;
        printf("S = %.0f, diagonal = %.2f, side = %.2f;\n", S, diagonal, side);
    }
    printf("Max diagonal = %.2f;\n\n", min_x);
    printf("7.63, precipitation:\n");
    a = 0;
    for (index = 1; index <= 31; ++index) {
        b = rand() % 15;
        if (b >= a) {
            a = b;
            temp = index;
        }
        printf("%d ", b);
    }
    printf("\nThe largest amount of precipitation was equal to %d, day = %d;\n\n", a, temp);
    printf("7.66, biggest class:\n");
    a = 0;
    b = 30;
    c = b;
    for (index = 1; index <= 20; ++index) {
        temp = 1 + rand() % c;
        if (temp > a)
            a = temp;
        if (temp < b)
            b = temp;
        printf("%d ", temp);
    }
    printf("\nmax = %d, min = %d;\nexcess - %d;\n\n", a, b, a - b);
    printf("7.67, pairs of numbers:\n");
    n = 10;
    sum = 0;
    int product = n * n;
    for (index = 0; index < n; ++index) {
        a = rand() % n;
        b = rand() % n;
        if (sum < a + b)
            sum = a + b;
        if (product > a * b)
            product = a * b;
        printf("%d:%d(sum = %d)(prod = %d)\n", a, b, a + b, a * b);
    }
    printf("\nMax sum = %d;\nMin product = %d;\n\n", sum, product);
    printf("7.70, Minimum population density:\n");
    for (index = 0; index < 5; ++index) {
        a = 1 + rand() % 1000;
        b = 1 + rand() % 1000;
        y = (double)b / (double)a;
        if (index == 0)
            t = y;
        if (y < t)
            t = y;
        printf("%d:%d(%.2f), ", b, a, y);
    }
    printf("\nMinimum population density: %.2f;\n\n", t);
    printf("7.76, Minimum temperature:\n");
    temp = 0;
    for (index = 1; index <= 31; ++index) {
        a = rand() % 15;
        if (index == 1)
            b = a;
        if (a < b) {
            b = a;
            temp = 0;
        }
        if (a == b)
            ++temp;
        printf("%d ", a);
    }
    printf("\nMinimum temperature = %d, quantity = %d;\n\n", b, temp);
    printf("7.79\n");
    b = rand() % 256;
    printf("%d;\n", b);
    int bin_array[CHAR_BIT] = {0, 0, 0, 0, 0, 0, 0, 0};
    index = CHAR_BIT - 1;
    while (b > 0) {
        int bit = b % 2;
        bin_array[index--] = bit;
        b /= 2;
    }
    printf("binary = ");
    int bits_len[2] = {CHAR_BIT, CHAR_BIT};
    int bits_type = bin_array[0], bits = 1;
    printf("%d", bits_type);
    for (index = 1; index < CHAR_BIT; ++index) {
        if (bin_array[index] == bits_type) {
            bits++;
            printf(".");
        } else {
            if (bits_len[bits_type] > bits)
                bits_len[bits_type] = bits;
            bits = 1;
            bits_type = bin_array[index];
            printf("-");
        }
        printf("%d", bin_array[index]);
    }
    if (bits_len[bits_type] > bits)
        bits_len[bits_type] = bits;
    printf("\nMin bits(zero) = %d, min bits(one) = %d;\n", bits_len[0], bits_len[1]);
    if (bits_len[0] > bits_len[1])
        printf("bits(1) more than bits(0);\n\n");
    else
        printf("bits(0) less or equal than bits(1);\n\n");
    printf("7.80, customer service:\n");
    n = 10;
    int service_time = 0;
    a = 0;
    int people_1[n];
    for (index = 0; index < n; ++index) {
        service_time = 1 + rand() % 10;
        if (index == 0)
            a = service_time;
        if (service_time < a)
            a = service_time;
        people_1[index] = service_time;
        printf("buyer: #%d, time = %d;\n", index, service_time);
    }
    printf("Fastest customer numbers: ");
    for (index = 0; index < n; ++index)
        if (people_1[index] == a)
            printf("%d; ", index);
    printf("\n\n");
    printf("7.81, min and max sum of pairs:\n");
    n = 20;
    a = -1;
    b = 0;
    c = 0;
    int min_sum = -1, max_sum = -1;
    if (n >= 3) {
        int mass_1[n];
        for (index = 0; index < n; ++index) {
            mass_1[index] = rand() % 10;
            printf("%d ", mass_1[index]);
        }
        for (index = 0; index < n - 1; ++index) {
            sum = mass_1[index] + mass_1[index + 1];
            if (a == -1) {
                max_sum = sum;
                min_sum = sum;
                a = 0;
            }
            if (sum > max_sum) {
                max_sum = sum;
                b = index;
            }
            if (sum < min_sum) {
                min_sum = sum;
                c = index;
            }
        }
        if (max_sum != -1 && min_sum != -1)
            printf("\nmax sum(%d,%d) = %d;\nmin sum(%d,%d) = %d;\n\n", b, b + 1, max_sum, c, c + 1, min_sum);
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
    int b2 = 0, c1 = 0, c2 = 0;
    int football[n], max_scores[amount], min_scores[amount];
    for (index = 0; index < amount; ++index) {
        max_scores[index] = -1;
        min_scores[index] = 11;
    }
    for (index = 0; index < n; ++index) {
        football[index] = rand() % 11;
        printf("%d ", football[index]);
        if (football[index] > a)
            a = football[index];
    }
    for (index = 0; index < n; ++index) {
        b1 = 0;
        b2 = 0;
        c2 = min_scores[b2];
        c1 = max_scores[b1];
        for (int j = 1; j < amount; ++j) {
            if (max_scores[j] < c1) {
                c1 = max_scores[j];
                b1 = j;
            }
            if (min_scores[j] > c2) {
                c2 = min_scores[j];
                b2 = j;
            }
        }
        if (football[index] > max_scores[b1])
            max_scores[b1] = football[index];
        if (football[index] < min_scores[b2])
            min_scores[b2] = football[index];
    }
    printf("\nMax scores: ");
    for (int j = 0; j < amount; ++j) {
        sum += max_scores[j];
        printf("%d ", max_scores[j]);
    }
    printf("\nMin scores: ");
    for (int j = 0; j < amount; ++j) {
        sum1 += min_scores[j];
        printf("%d ", min_scores[j]);
    }
    printf("\nSum of winners: max = %d, min = %d;\n\n", sum, sum1);
    printf("7.86 - 7.89;\n");
    b = 50;
    c = 2;
    sum = 0;
    for (index = 0; index < 10; ++index) {
        a = rand() % 15;
        sum += a;
        printf("%d ", a);
    }
    printf("\nSum = %d", sum);
    printf("\n1) Amount is more than(100,78): ");
    if (sum > 78)
        printf("78");
    else
        printf("-");
    if (sum > 100)
        printf("100");
    printf("\n2) Is it true that the sum numbers less than b(%d)? - ", b);
    if (sum > b)
        printf("Yes!\n");
    else
        printf("No!\n");
    printf("3) Sum is even number? - ");
    if (sum % 2 == 0)
        printf("Yes!\n");
    else
        printf("No!\n");
    printf("4) It is true that the sum is a multiple of c(%d)? - ", c);
    if (sum % c == 0)
        printf("Yes!\n\n");
    else
        printf("No!\n\n");
    printf("7.93, the cheapest item:\n");
    c = 100;
    for (index = 0; index < 8; ++index) {
        a = rand() % 100;
        b = rand() % 100;
        printf("%d) 1(%d),2(%d);\n", index, a, b);
        if (a < c) {
            c = a;
            temp = 1;
            temp1 = index;
        }
        if (b < c) {
            c = b;
            temp = 2;
            temp1 = index;
        }
    }
    printf("Product number: ");
    if (temp == 1)
        printf("%d(1)\n\n", temp1);
    else
        printf("%d(2)\n\n", temp1);
    printf("7.95\n");
    n = 50;
    product = 1;
    for (index = 0; index < 5; ++index) {
        a = rand() % 10;
        product *= a;
        printf("%d ", a);
    }
    if (product > n)
        printf("\nYes, product(%d) > n(%d)", product, n);
    else
        printf("\nNo, product(%d) > n(%d)", product, n);
    a = 5;
    b = 2;
    printf("7.100, 7.106, 7.108, checking the multiplicity of the sum, m = %d, p = %d:\n", a, b);
    n = 10;
    sum = 0;
    sum1 = 0;
    printf("numbers: ");
    for (index = 0; index < n; ++index) {
        c = rand() % 10;
        if (c > a)
            sum += c;
        printf("%d ", c);
        if (c % 2 == 0)
            sum1 += c;
    }
    if (sum % b == 0)
        printf("\nsum = %d, p = %d, YES! The sum is a multiple of p\n", sum, b);
    else
        printf("\nsum = %d, p = %d? NO! The sum is not a multiple of p\n", sum, b);
    if (sum1 % 3 == 0)
        printf("the sum of positive numbers is a multiple of 3;\n\n");
    else
        printf("the sum of positive numbers is not a multiple of 3;\n\n");
    printf("7.102, street:\n");
    sum = 0;
    sum1 = 0;
    printf("Number of residents: ");
    for (index = 1; index <= 10; ++index) {
        a = rand() % 10;
        if (index % 2 == 0)
            sum += a;
        else
            sum1 += a;
        printf("%d ", a);
    }
    if (sum > sum1)
        printf("\nMost residents live in houses with even numbers: even = %d, odd = %d;\n\n", sum, sum1);
    else if (sum1 > sum)
        printf("\nMost residents live in houses with odd numbers: even = %d, odd = %d;\n\n", sum, sum1);
    else
        printf("\nThe even and odd sides have the same number of people: even = %d, odd = %d;\n\n", sum, sum1);
    printf("7.112, average height of students:\n");
    n = 15;
    sum = 0;
    sum1 = 0;
    for (index = 0; index < n; ++index) {
        a = -1 * ((rand() % 51) + 150);
        b = 150 + rand() % 27;
        sum += abs(a);
        sum1 += b;
        printf("boy = %d, girl = %d;\n", a, b);
    }
    if ((sum / n) - (sum1 / n) > 10)
        printf("The average height of boys is 10 cm more than girls: boy = %d, girl = %d\n\n", sum / n, sum1 / n);
    else
        printf("The average height of boys is 10 cm smaller than girls: boy = %d, girl = %d\n\n", sum / n, sum1 / n);
    c = rand() % 3;
    printf("7.115, average:, c = %d\n", c);
    temp = 0;
    sum = 0;
    printf("numbers: ");
    for (index = 0; index < 12; ++index) {
        if (c == 0) {
            a = rand() % 9;
            if (a % 2 == 0)
                ++a;
        } else {
            a = rand() % 10;
            if (a % 2 == 0) {
                sum += a;
                ++temp;
            }
        }
        printf("%d ", a);
    }
    if (temp > 0)
        printf("\nAverage = %d;\n\n", sum / temp);
    else
        printf("\nThere are no even numbers in the sequence;\n\n");
    b = rand() % 3;
    printf("7.118, Find number by the last negative number, b = %d\n", b);
    n = 10;
    temp = 0;
    printf("numbers: ");
    for (index = 1; index <= n; ++index) {
        if (b == 0)
            c = rand() % 10;
        else {
            a = rand() % 3;
            c = 1 + rand() % 9;
            if (a == 0)
                c *= -1;
        }
        if (c < 0)
            temp = index;
        printf("%d ", c);
    }
    if (temp == 0) {
        printf("\nThere are no negative numbers in the sequence;\n\n");
    } else
        printf("\nNumber of the last negative number: %d\n\n", temp);
    printf("7.122, determining the minimum and maximum age among a group of people:\n");
    n = 10;
    int min_age = 100, max_age = 0;
    printf("Age: ");
    for (index = 0; index < n; ++index) {
        a = 1 + rand() % 100;
        if (max_age < a) {
            max_age = a;
            temp = index;
        }
        if (min_age > a) {
            min_age = a;
            temp1 = index;
        }
        printf("%d ", a);
    }
    if (temp > temp1)
        printf("\nThe person with the minimum age appeared in the sequence earlier \n"
               "than the person with the maximum age: min = %d, max = %d,"
               " min and max pos: %d:%d;\n\n", min_age, max_age, temp1, temp);
    else
        printf("\nThe person with the maximum age appeared in the sequence earlier \n"
               "than the person with the minimum age: min = %d, max = %d,"
               " min and max pos: %d:%d;\n\n", min_age, max_age, temp1, temp);
    printf("7.124 - 7.125, sequence of not descending numbers:\n");
    int numbers[10];
    a = 0;
    temp = 0;
    temp1 = 1;
    numbers[0] = rand() % 10;
    for (index = 1; index < 10; ++index)
        numbers[index] = numbers[index - 1] + rand() % 3;
    for (index = 0; index < 9; ++index) {
        if (numbers[index] == numbers[index + 1] && a == 0) {
            ++temp;
            a = 1;
        } else if (numbers[index] != numbers[index + 1]) {
            ++temp1;
            a = 0;
        }
    }
    for (index = 0; index < 10; ++index)
        printf("%d ", numbers[index]);
    printf("\nSequences = %d, different numbers = %d;\n\n", temp, temp1);
    a = 6;
    printf("7.128, number = %d:\n", a);
    int is_perfect = is_perfect_number(a);
    if (is_perfect != 0)
        printf("Number is perfect\n\n");
    else
        printf("Number is not perfect\n\n");
    ScriptedEngeneer_1();
}