#include "global.h"
#include "library.h"

int evklid_many_numbers(int mass[], int size)
{
    int i = 0;
    int previous = mass[i];
    for (i = 1; i < size; ++i)
        previous = evklid(previous, mass[i]);
    return previous;
}

int reduction_of_fractions(int numerator, int denominator, int debug)
{
    if (numerator < 1 || denominator < 1)
        return -1;
    int result = evklid(numerator,denominator);
    if (debug == 1)
        printf("Sourse:\nnum = %d, denum = %d;\n",numerator,denominator);
    numerator /= result;
    denominator /= result;
    if (debug == 1)
        printf("Result(/%d):\nnum = %d, denum = %d;\n",result,numerator,denominator);
    return 0;
}

int days_in_month(int month, int year)
{
    const int months_in_year = 12;
    if (month < 1 || month > months_in_year)
        return -1;
    int days_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        days_months[1]++; // В феврале может быть на один день больше.
    return days_months[month - 1];
}

void print_date(int day, int month, int year, char* format) // Улучшать по мере продвижения заданий.
{
    const int date_size = 4, base = 10;
    const char fill = '0';
    int fields[date_size], digits[date_size];
    int dates[date_size];
    dates[0] = day;
    dates[1] = month;
    dates[2] = year;
    int divs[date_size];
    for (int i = 0; i < date_size; ++i) {
        fields[i] = 0;
        digits[i] = 0;
        if (i < date_size - 1)
            divs[i] = 1;
        else
            divs[i] = 0;
    }
    const char* epoch[] = {"B.C.","A.D"};
    char format_chars[] = "DMYE";
    //printf("digits in dates:");
    for (int i = 0; i < date_size ; ++i) {
        int number = abs(dates[i]);
        while (number) {
            if (number >= base)
                divs[i] *= base;
            number /= base;
            digits[i]++;
        }
        //printf(" %d",digits[i]);
    }
    //printf("\nfields size(digits): divs of chars: ");
    for (int i = 0; format_chars[i] != '\0'; ++i) {
        for (int j = 0; format[j] != '\0'; ++j)
            if (format[j] == format_chars[i])
                fields[i]++;
        //printf("%d(%d):%d ",fields[i],digits[i],divs[i]);
    }
    //printf("\nresult: ");
    for (int i = 0, j = 0; format[i] != '\0'; ++i) {
        for (j = 0; j < date_size && format[i] != format_chars[j]; ++j)
            ;
        if (j != date_size && divs[j] > 0) {
            if (digits[j] >= fields[j] && j != date_size - 1) { // Последняя буква в таблице - это эпоха.
                printf("%d",abs(dates[j] / divs[j]) % base);
                divs[j] /= base;
                digits[j]--;
                fields[j]--;
            } else {
                printf("%c",fill);
                fields[j]--;
            }
        } else if (j == date_size - 1) {
            printf("%s",epoch[(year > 0)]);
        } else
            printf("%c",format[i]);
    }
}

int date_next_day(int* day, int* month, int* year)
{
    const int months_in_year = 12;
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // days in month
    int leap = 0;
    if ((*year % 4 == 0 && *year % 100 != 0) || *year % 400 == 0)
        leap = 1;
    months[1] += leap;  // хитрый трюк)
    if (*day < 1 || *day > months[*month - 1] || *month > months_in_year || *month < 1)
        return -1;
    if (*day + 1 > months[*month - 1]) {
        if (*month == months_in_year) {
            *month = 1;
            if (++(*year) == 0)
                *year = 1;
        } else
            ++(*month);
        *day = 1;
    } else
        *day += 1;
    return 0;
}

int date_prev_day(int* day, int* month, int* year)
{
    const int months_in_year = 12;
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // days in month
    int leap = 0;
    if ((*year % 4 == 0 && *year % 100 != 0) || *year % 400 == 0)
        leap = 1;
    months[1] += leap;  // хитрый трюк)
    if (*day < 1 || *day > months[*month - 1] || *month > months_in_year || *month < 1)
        return -1;
    if (*day - 1 < 1) {
        if (*month - 1 < 1) {
            *month = months_in_year;
            if (*year - 1 == 0) // B.C.
                *year = -1;
            else
                --(*year);
        } else
            --(*month);
        *day = months[*month - 1];
    } else
        --(*day);
    return 0;
}

int degree_check(int value, int base)
{                   // Возвращает число, степенью которого является value.
    if (base <= 0)
        return 0;
    if (base == 1)
        return value;
    for (int i = 2; i * i <= value; ++i) {
        int factor = i, power = 1;
        while (factor < value && power < base) {
            factor *= i;
            power++;
        }
        if (factor == value && power == base)
            return i;
    }
    return 0;
}

int max_int_pair(int a, int b)
{
    return ((a > b) ? a : b);
}

int digits_in_num(int num, int start, int len, int* sum)
{
    *sum = 0;
    int k = num, quantity = 0;
    quantity = length_number(k);
    if ((start + len > quantity || start < 0 || len < 0) && (start == 0 && len == 0))
        return -1;
    k = pow(10,quantity - 1);
    int limit = 0;
    if (start == 0 && len == 0)
        limit = quantity;
    else
        limit = start + len;
    for (int i = 0; i < limit; ++i) {
        int digit = num / k;
        if (i >= start && i < limit)
            *sum += digit;
        num %= k;
        k /= 10;
    }
    return quantity;
}

double fraction_calculator_with_factorials(int numbers[], int is_factorial[])
{
    int numerator = 0, denominator = 0;
    printf("Values: ");
    for (int i = 0; i < NUMBERS_QUANTITY; ++i)
        if (is_factorial[i] == 1) {
            printf("%d!",numbers[i]);
            numbers[i] = factorial(numbers[i]);
            printf("(%d), ",numbers[i]);
        } else
            printf("%d, ",numbers[i]);
    return numerator / denominator;
}

double calc_exp_10_1(int numbers[], int is_sqrt[], int exp_size, int terms)
{
    int i = 0, num_den_size = exp_size / terms / 2;
    double num = 0.0, denum = 0.0, result = 0.0, value = 0.0, lim = 0.000000000000001;
    if ((exp_size <= 0 || terms < 1) && exp_size % terms == 0)
        return -1.0;
    printf("(");
    for (i = 0; i <= exp_size; ++i) {
        if (i > 0 && i % num_den_size == 0) {
            printf(")");
            if (i % (exp_size / terms) == 0) {
                if (i != exp_size)
                    printf(" + (");
                if (denum > lim) {
                    result += num / denum;
                } else {
                    printf("error: %d - %0.2f\n", i, denum);
                }
                num = 0.0;
                denum = 0.0;
            } else
                printf(" / (");
        }
        if (i != exp_size) {
            value = numbers[i];
            if (is_sqrt[i] == 1) {
                value = sqrt(value);
                printf("sqrt(%d)", numbers[i]);
            } else
                printf("%d", numbers[i]);
            if (i % (exp_size / terms) < num_den_size)
                num += value;
            else
                denum += value;
            if (i % num_den_size == 0)      // add terms
                printf(" + ");
        }
    }
    printf(" = %.5f\n", result);
    return result;
}

int sign(int number)
{
    if (number > 0)
        return 1;
    else if (number < 0)
        return -1;
    else
        return 0;
}

double hypotenuse(double a, double b)
{
    return sqrt(pow(a,2) + pow(b,2));
}

double perimeter(double a, double b, double c)
{
    return a + b + c;
}

double perimeter_isosceles_trapezoid(double bases_1, double bases_2, double height) // использовать как можно больше вызовов из предыдуших заданий.
{
    return hypotenuse(height,(bases_2 - bases_1) / 2) * 2 + bases_1 + bases_2;
}

int quadratic_equations(int a, int b , int c)
{
    double disc = 0, x1 = 0, x2 = 0;
    disc = (b * b) - (4 * a * c);
    if (disc < 0)
        return -1;
    else if (disc == 0)
        x1 = (-b + sqrt(disc)) / (2 * a);
    else {
        x1 = (-b + sqrt(disc)) / (2 * a);
        x2 = (-b - sqrt(disc)) / (2 * a);
    }
    return (x1 != ceil(x1) || x2 != ceil(x1)) ? 1 : 0; // ceil - dangerous code!!!
}

double line_vertex(double vertex[])
{
    double a, b;
    a = fabs(vertex[0] - vertex[1]);
    b = fabs(vertex[2] - vertex[3]);
    return hypotenuse(a,b);
}

int check_even_or_odd(int mode, int value)
{
    if (mode == 0) {
        if (value % 2 == 0)
            return 1;
    } else if (value % 2 != 0)
        return 1;
    return 0;
}

double triangle_heron(double a, double b, double c)
{
    double half_per = perimeter(a,b,c) / 2.0;
    return sqrt(half_per * (half_per - a) * (half_per - b) * (half_per - c));
}

int char_to_hex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

char hex_to_char(int c)
{
    if (c >= 0 && c <= 9)
        return c + '0';
    else if (c >= 10 && c <= 15)
        return c - 10 + 'A';
    return -1;
}

void exchange_of_values(int *a, int *b)
{
    *a -= *b;
    *b += *a;
    *a = *b - *a;
}

int pair_max(int a, int b)
{
    return (a > b) ? a : b;
}

int pair_min(int a, int b)
{
    return (a < b) ? a : b;
}

void output_screen(char* buffer, int size_x, int size_y)
{
    if (size_x < 1 || size_y < 1)
        return;
    printf(" ");
    for (int i = 0; i < size_x; ++i) {
        if (i >= 0 && i <= 9)
            printf(" %c",'0' + i);
        else
            printf(" %c", 'A' + i - 10);
    }
    printf("\n");
    for (int i = 0;i < size_y; ++i) {
        if (i >= 0 && i <= 9)
            printf("%c ",i + '0');
        else
            printf("%c ", 'A' + i - 10);
        for (int j = 0; j < size_x; ++j)
            printf("%c ", buffer[i * size_y + j]);
        printf("\n");
    }
}

void clear_screen(char* buffer, int size_x, int size_y, char fill)
{
    for (int i = 0; i < size_y; ++i)
        for (int j = 0; j < size_x; ++j)
            buffer[i * size_y + j] = fill;
}

int is_command_correct(char command[], int idx, int pars, int src_size)
{
    if (pars >= OBJECTS_MAX || pars < 0 || src_size < 0 || src_size > OBJECTS_MAX)
        return 0;
    for (int i = 1; i <= pars; ++i)
        if (char_to_hex(command[idx + i]) == -1)
            return 0;
    return 1;
}

int factorial_recur(int number)
{
    //printf("factorial = %d\n",number);
    if (number < 2)
        return 1;
    return (factorial_recur(number - 1) * number);
}

int exp_recur(int power, int base)
{
    //printf("power = %d\n", power);
    if (power < 2)
        return base;
    return (exp_recur(power - 1, base) * base);
}

int expt (int base, int power) {    // От Андрея
    printf("exp = %d:%d\n", base, power);
    if (power == 0) {return 1; }
    int quot = power / 2;
    int rem = power % 2;
    if (rem == 0) {
        int half = expt(base, quot);
        return half * half  ;
    } else {
        int half = expt(base, quot);
        return half * half * base ;
    }
}

int sum_of_digits_recur(int number)
{
    printf("sum = %d\n", number);
    if (number < 1)
        return 0;
    return (sum_of_digits_recur(number / 10) + number % 10);
}

int number_of_digits_recur(int number)
{
    printf("quantity = %d\n", number);
    if (number < 1)
        return 0;
    return (number_of_digits_recur(number / 10) + 1);
}

int digital_root_recur(int number)
{
    printf("root = %d\n", number);
    if (number < 10)
        return number;
    return (digital_root_recur(sum_of_digits_recur(number)));
}

int value_arith_progres(int d, int n, int a1)
{
    printf("arif = %d:%d:%d\n",d,n,a1);
    if (n <= 1)
        return a1;
    int r = value_arith_progres(d,n - 1, a1) + d;
    printf("r = %d\n", r);
    return r;
}

int sum_arith_progres(int d, int n, int a1)
{
    printf("arif = %d:%d:%d\n",d,n,a1);
    if (n <= 1)
        return a1;
    int r = a1, next = a1 + d;
    r += sum_arith_progres(d, n - 1, next);
    printf("r = %d\n", r);
    return r;
}

int arif_recur(int a1, int d, int n, int* sum)
{
    printf("element = %d, sum = %d;\n", a1, *sum);
    *sum += a1;
    n--;
    if (n > 0) {
        a1 += d;
        a1 = arif_recur(a1, d, n, sum);
    }
    return a1;
}

int fibonacci_recur(int n)
{
    if (n <= 1)
        return n;
    return fibonacci_recur(n - 1) + fibonacci_recur(n - 2);
}

int find_max_recur(int numbers[], int length, int* idx, int max)
{
    if (length < 0)                             // Реализовать функцию только с адресной арифметикой.
        return max;
    if (numbers[length] > max) {
        max = numbers[length];
        *idx = length;
    }
    return find_max_recur(numbers,--length,idx,max);
}

int flip_number(int n)
{
    const int base = 10;
    if (n == 0)
        return 0;
    printf("%d", n % base);
    return flip_number(n / base);
}

int reverse_number(int n, int result)
{
    const int base = 10;                    // Улучшить функцию...
    result = result * base + n % base;
    if (n > base) {
        printf("\nrevers, n = %d, result before = %d\n", n, result);
        result = reverse_number(n / base, result);
        printf("\nrevers, n = %d, result after = %d\n", n, result);
    }
    return result;
}

void print_integer_recur(int number, int base)
{
    char digits_for_translation[] = "0123456789ABCDEF";
    if (number <= 0 || base < 2 || base > 16)
        return;
    if (number >= base)
        print_integer_recur(number / base,base);
    printf("%c",digits_for_translation[number % base]);
}

int prime_check_recur(int number, int* num_ptr)
{                                      // Кто придумает более красививое решение, тот молодец!
    if (number < 1 || *num_ptr < 1)
        return -1;
    if (number == 1)
        return 1;
    if (number == *num_ptr)
        number--;
    if ((*num_ptr % number) == 0)
        return 0;
    return prime_check_recur(--number, num_ptr);
}

int symmetric_check_recur(char string[], int start, int end, int limit)
{
    if (string_length(string) > limit || end >= string_length(string) || start > end)
        return -1;
    if (string[start] != string[end])
        return 0;
    else if (end - start <= 1)
        return 1;
    return symmetric_check_recur(string, ++start, --end, limit);
}

int ackermann(int m, int n)
{
    if (m < 0 || n < 0)
        return -1;
    int result = 0;
    if (m == 0)
        return n + 1;
    else
        if (n == 0)
            result = ackermann(m - 1, 1);
        else
            result = ackermann(m - 1, ackermann(m, n - 1));
    return result;
}

void chapter_10()
{
    int i = 0, j = 0, k = 0;
    double result_double;
    const int variants = 4, exp_size = 12;
    printf("10.1, calculate X, all variants.\n");
    //int data_1[exp_size * variants], is_sqrt[exp_size * variants];
    srand(time(NULL));
    for (i = 0; i < variants; ++i) {
        for (j = 0; j < exp_size; ++j) {;
            //data_1[i * exp_size + j] = 1 + rand() % 100;
            //is_sqrt[i * exp_size + j] = rand() % 2;
        }
    }
    for (k = 0; k < variants; ++k)
        printf("Variant %d:\n",k);
    int x = 2, y = -15, z = 0, s1 = 0, s2 = 0;
    printf("\n10.5, determine the value of z = sign x(%d) + sign y(%d), using in line code and function \n",x,y);
    // 1
    z = sign(x) + sign(y);
    printf("1) z = %d;\n",z);
    // 2
    if (x > 0)
        s1 =  1;
    else if (x < 0)
        s1 = -1;
    if (y > 0)
        s2 =  1;
    else if (y < 0)
        s2 =  -1;
    z = s1 + s2;
    printf("2) z = %d;\n\n",z);
    double AC = 12, AB = 10, DC = 15, P = 0;
    printf("10.6, hypotenuse calculation and find perimeter, AC = %.2f, AB = %.2f, DC = %.2f\n",AC,AB,DC);
    result_double = hypotenuse(AB,AC);
    result_double = hypotenuse(result_double,DC);
    P = AC + AB + DC + result_double;
    printf("P = %.2f\n\n",P);
    printf("10.7, calculation of the perimeter of an isosceles trapezoid by its bases and height\n");
    const int trapezoids = 2, trapez_param = 3;
    double trapez[trapezoids * trapez_param];
    printf("Bases and heights: ");
    for (i = 0; i < trapez_param * trapezoids; ++i) {
        trapez[i] = 1 + rand() % 10;
        printf("%.1f ",trapez[i]);
    }
    printf("\n");
    double sum_double = 0;
    for (j = 0; j < trapezoids; ++j)
        sum_double += perimeter_isosceles_trapezoid
                (trapez[j * trapez_param],trapez[j * trapez_param + 1],trapez[j * trapez_param + 2]);
    printf("Sum = %.2f;\n\n",sum_double);
    int a = 1, b = -4, c = -21, result;
    printf("10.8, determine the presence of real roots of equation, a = %d, b = %d, c = %d\n",a,b,c);
    result = quadratic_equations(a,b,c);
    printf("1)result = %d\n",result);
    result = quadratic_equations(b,a,c);
    printf("2)result = %d\n",result);
    result = quadratic_equations(c,a,b);
    printf("3)result = %d\n\n",result);
    printf("10.9, calculating the perimeter of a triangle by the coordinates of its vertices\n");
    const int parties = 3, coordinates = 2;
    double vertex[STRING_MAX];
    P = 0;
    printf("vertex: ");
    for (i = 0; i < parties; ++i) {
        for (j = 0; j < coordinates; ++j) {
            vertex[i * coordinates + j] = 1 + rand() % 10;
            printf("%.1f ",vertex[i * coordinates + j]);
        }
        P += line_vertex(vertex);
    }
    printf("\np = %.2f;\n\n",P);
    double side_a = 3.0, side_b = 4.0, side_c = 5.0;
    printf("10.10 - 10.11, square of triangle, using sides and coordinates, fig. 10.2, page 113;\n");
    printf("side_a = %.1f, side_b = %.1f, side_c = %.1f;\n", side_a, side_b, side_c);
    printf("Size of triangle using Heron's formula = %.2f;\n", triangle_heron(side_a, side_b, side_c));
    // скопируем координаты первой точки, в хвост трёх вершин массива vertex.
    vertex[6] = vertex[0];
    vertex[7] = vertex[1];
    double lines[STRING_MAX];
    printf("Sides of triangle: ");
    for (i = 0; i < parties && i < STRING_MAX; ++i)  {
        lines[i] = line_vertex(&vertex[i * coordinates]);
        printf("%.1f ",lines[i]);
    }
    printf("\nSize of triangle, using coordinates = %.2f;\n\n", triangle_heron(lines[0],lines[1],lines[2]));
    printf("10.12, parity check;\n");
    int sequence_1[SEQUENCE_LENGTH];
    int sequence_2[SEQUENCE_LENGTH];
    printf("sequence_1: ");
    for (i = 0; i < SEQUENCE_LENGTH; ++i) {
        sequence_1[i] = rand() % 10;
        sequence_2[i] = rand() % 10;
        printf("%d ",sequence_1[i]);
    }
    printf(":(even): ");
    for (i = 0; i < SEQUENCE_LENGTH; ++i)
        printf("%d ", check_even_or_odd(0, sequence_1[i])); // mode == 0 - even, else - odd;
    printf("\nsequence_2: ");
    for (i = 0; i < SEQUENCE_LENGTH; ++i)
        printf("%d ", sequence_2[i]);
    printf(":(odd): ");
    for (i = 0; i < SEQUENCE_LENGTH; ++i)
        printf("%d ", check_even_or_odd(1, sequence_2[i]));
    int base = 5;
    int sequence_3[SEQUENCE_LENGTH] = {0,32,10,14,16,40,125,81,512,243,16807};
    printf("\n\n10.13 - 10.14, degree check, base = %d\n",base);
    printf("sequence: ");
    for (i = 0; i < SEQUENCE_LENGTH; ++i)
        printf("%d ", sequence_3[i]);
    printf("\n");
    for (i = 1; i <= base; ++i) {
        printf("all numbers in power: %d:",i);
        for (j = 0; j < SEQUENCE_LENGTH; ++j) {
            result = degree_check(sequence_3[j],i);
            if (result > 0)
                printf("%d[num = %d] ", sequence_3[j], result);
        }
        printf("\n");
    }
    int last_number = -1, pairs = 0, diff = 2, limit = 100;
    printf("\n10.15 - 10.16, search for primes and adjacent primes, limit = %d, diff = %d\n", limit, diff);
    for (int i = 1; i <= limit; ++i)
        if (prime_number(i)) {
            if (i - last_number == diff) {
                ++pairs;
                printf("%d:%d ",i - 2, i);
            } else
                printf("%d ",i);
            last_number = i;
        }
    printf("\nTotal pairs = %d;", pairs);
    printf("\n\n10.17, determine factorial, (2 * 5!) + (3 * 8!) / (6! + 4!);\n");
    double num_d = (2 * factorial(5)) + (3 * factorial(8));
    double denom_d = factorial(6) + factorial(4);
    printf("Result = %.2f\n\n", num_d / denom_d);
    int number[2] = {1236, 82601}, start = 2, length = 2;
    int quant[2], sums[2];
    printf("10.18-10.19, calculating the sum and digits in pair, start = %d, length = %d, %d:%d\n",
           start, length, number[0], number[1]);
    for (i = 0; i < 2; ++i) {
        quant[i] = digits_in_num(number[i], start, length, &sums[i]);
        printf("quantity = %d, sum = %d\n", quant[i], sums[i]);
    }
    printf("Max digits in num = %d\n", pair_max(quant[0], quant[1]));
    printf("Max sum of digits in num = %d\n", pair_max(sums[0], sums[1]));
    printf("\n10.20, finding lucky numbers;\n");
    int left = 0, right = 0, counter = 0;
    length = 2;
    if (length % 2 == 0 && length >= 2 && length < 9) {
        int min = pow(10, length - 1), max = pow(10 ,length);
        for (int i = min; i < max; ++i, left = 0, right = 0) {
            digits_in_num(i, 0, length / 2, &left);
            digits_in_num(i, length / 2, length / 2, &right);
            if (left == right) {
                printf("%d ",i);
                ++counter;
            }
        }
    } else
        printf("error in parameters and of lucky numbers;\n");
    printf("\nTotal: %d;\n\n",counter);                                              // Убрать
    int data_int[OBJECTS_MAX] = {123456, 415362, 516243, 243651, 654321};
    int data_size = 5;
    printf("10.22, find max number in vector\n");
    printf("numbers: ");
    int max = data_int[0];
    for (i = 0; i < data_size; ++i) {
        printf("%d ",data_int[i]);
        max = max_int_pair(data_int[i], max);
    }
    printf("\nmax number = %d;\n\n", max);
    int month = 2, year = 2020, day = 28;
    char format[STRING_MAX] = "DD-MM-YYYY";
    printf("10.23, define next day, previous day and days in month;\n");
    printf("date:\t\tprevious:\tnext:\t\tdays in month:\n");
    int data_dates[] = {1,1,1, 31,12,-1, 28,2,1900, 1,3,1900, 29,2,2000, 1,3,2000, 28,2,2020, 1,3,2020, 16,1,2021};
    for (i = 0; i < 9; ++i) {
        day = data_dates[i * 3];
        month = data_dates[i * 3 + 1];
        year = data_dates[i * 3 + 2];
        print_date(day, month, year, format);
        printf("\t");
        date_prev_day(&day, &month, &year);
        print_date(day, month, year, format);
        printf("\t");
        day = data_dates[i * 3];
        month = data_dates[i * 3 + 1];
        year = data_dates[i * 3 + 2];
        date_next_day(&day, &month, &year);
        print_date(day, month, year, format);
        printf("\n");
        month = data_dates[i * 3 + 1];
        year = data_dates[i * 3 + 2];
        printf("%d\n",days_in_month(month, year));
    }
    int numerator = 75, denominator = 125;
    int mass_2[] = {25,25,125,625,725};
    int mass_int_size = sizeof (mass_2) / sizeof(int);
    printf("\n10.24 - 10.27, NOD and reduction of fractions;\n");
    printf("Reduction of fractions:\n");
    result = reduction_of_fractions(numerator,denominator,1);
    printf("return = %d\n\n",result);
    printf("NOD for many numbers, using Evklid:\n");
    printf("numbers: ");
    for (i = 0; i < mass_int_size; ++i)
        printf("%d ",mass_2[i]);
    result = evklid_many_numbers(mass_2,mass_int_size);
    printf("\n\nsize of array: %d, NOD = %d\n\n",mass_int_size,result);
    char symbol = 'a';
    int total_symb = 0, total_len = 0;
    const int texts_quant = 3;
    double percent;
    char* texts[] = {"Subscribe to channel", "8 bit tea party", "This is simple text"};
    int first = 0;
    int idx = 0;
    printf("10.28 - 10.31, counting the number of characters (%c) in a sentence\n", symbol);
    for (i = 0; i < texts_quant; ++i) {
        printf("'%s': ",texts[i]);
        int quantity = string_char_counter(texts[i],symbol);
        total_symb += quantity;
        int length = string_length(texts[i]);
        total_len += length;
        percent = (double)(quantity) / (double)(length) * 100;
        if (i != 0 && string_char_find(texts[i],symbol,0,0) < first)
            idx = i;
        first = string_char_find(texts[i],symbol,0,0);
        printf("ratio: %d/%d, in percentages: %.2f%%, ",quantity,length, percent);
        printf("first symbol idx: %d\n", first);
    }
    percent = (double)total_symb / (double)total_len * 100;
    printf("total symbols: %d; total length: %d, percent = %.2f;\n", total_symb, total_len, percent);
    printf("First symbol in all texts: %d\n", idx);
    char commands[OBJECTS_MAX][STRING_MAX] = {"V0102"};  //C422CC22C822C652CA52;P00DP34DPF0DPFFDP0FD;P00RFFP22R66PD2RA6P2DR6APDDRAA;P77B80P77B8FP77B05P77B09P77BF5P77BF9
    const int commands_size = 1;
    char screen[OBJECTS_MAX * OBJECTS_MAX];
    const int screen_size = 16;
    char paper = '.';
    char ink = 'O';
    clear_screen(screen,screen_size,screen_size,paper);
    printf("\n10.33 - 10.37, drawing figuries with command:\n"); // Чуть больше строк с описанием команды.
    printf("P## - set position to coordinaties x:y\n");
    printf("D - set point to current position\n");
    printf("H# - draw a horizontal line to x\n");
    printf("V# - draw a vertical line to y\n");
    printf("R## - draw a rectangle to x:y\n");
    printf("B## - draw a line to x:y\n");
    printf("T#### - draw a triangle with vertexes x1:y1 to x2:y2\n");
    printf("C# - draw a circle with radius R\n");
    int curr_y = 0, curr_x = 0;
    int delta_x = 0, delta_y = 0;
    int radius = 5;
    for (k = 0;k < commands_size; ++k) {
        for (i = 0; commands[k][i] != '\0'; ++i) {  // подумать потом более над безопасным решением...
            switch (commands[k][i]) {
            case 'P':
                if (is_command_correct(commands[k], i, 2, screen_size) == 1) {
                    curr_x = char_to_hex(commands[k][i + 1]);
                    curr_y = char_to_hex(commands[k][i + 2]);
                    printf("Set active position to (%d:%d)\n", curr_x, curr_y);
                    i += 2;
                } else
                    printf("error at %d, parameters '%c' and '%c'\n",
                           i, commands[k][i + 1], commands[k][i + 2]);
                break;
            case 'D':
                screen[curr_y * screen_size + curr_x] = ink;
                printf("draw a point at current position (%d:%d)\n", curr_x, curr_y);
                break;
            case 'H':
                if (is_command_correct(commands[k], i, 1, screen_size)) {
                    int to_x = char_to_hex(commands[k][i + 1]);
                    int sign = (to_x < curr_x) ? -1 : 1;
                    printf("draw horizontal line from %d to %d\n",curr_x,to_x);
                    i += 1;
                    screen[curr_y * screen_size + to_x] = ink;
                    for (; to_x != curr_x; curr_x += sign)
                        screen[curr_y * screen_size + curr_x] = ink;
                } else
                    printf("error at %d, parameter '%c'\n", i, commands[k][i + 1]);
                break;
            case 'V':
                if (is_command_correct(commands[k], i, 1, screen_size)) {
                    int to_y = char_to_hex(commands[k][i + 1]);
                    int sign = (to_y  < curr_y) ? -1 : 1;
                    printf("draw vertical line from %d to %d\n",curr_y,to_y);
                    i += 1;
                    screen[curr_y * screen_size + to_y] = ink;
                    for (; to_y != curr_y; curr_y += sign)
                        screen[curr_y * screen_size + curr_x] = ink;
                } else
                    printf("error at %d, parameter '%c'\n", i, commands[k][i + 1]);
                break;
            case 'R':
                if (is_command_correct(commands[k],i,2,screen_size)) {
                    char rect_commands[] = "H_V_H_V_";
                    rect_commands[1] = commands[k][i + 1];
                    rect_commands[3] = commands[k][i + 2];
                    rect_commands[5] = hex_to_char(curr_x);
                    rect_commands[7] = hex_to_char(curr_y);
                    string_insert(commands[k],rect_commands,i + 3, STRING_MAX);
                    printf("draw rectangle to (%c:%c), with commands '%s', result = '%s'\n",
                           rect_commands[1], rect_commands[3], rect_commands, commands[k]);
                    i += 2;
                } else
                    printf("error at %d, parameters '%c' and '%c'\n",
                           i, commands[k][i + 1], commands[k][i + 2]);
                break;
            case 'B':
                if (is_command_correct(commands[k], i, 2, screen_size)) {
                    int to_x = char_to_hex(commands[k][i + 1]);
                    int to_y = char_to_hex(commands[k][i + 2]);
                    delta_x = abs(to_x - curr_x);
                    delta_y = abs(to_y - curr_y);
                    int sign_x = (to_x > curr_x) ? 1 : -1;
                    int sign_y = (to_y > curr_y) ? 1 : -1;
                    int offset = delta_x - delta_y;
                    screen[to_y * screen_size + to_x] = ink;
                    printf("draw a line from (%d:%d) to (%d:%d)\n",curr_x, curr_y, to_x, to_y);
                    printf("d_x = %d, d_y = %d, sign_x_y = %d:%d, offset = %d\n",
                           delta_x, delta_y, sign_x, sign_y, offset);
                    while (curr_x != to_x || curr_y != to_y) {
                        screen[curr_y * screen_size + curr_x] = ink;
                        int carry_flag = offset * 2;
                        if (carry_flag > (-1 * delta_y)) {
                            curr_x += sign_x;
                            offset -= delta_y;
                        }
                        if (carry_flag < delta_x) {
                            curr_y += sign_y;
                            offset += delta_x;
                        }
                    }
                    i += 2;
                } else
                    printf("error at %d, parameters '%c' and '%c'\n",
                           i, commands[k][i + 1], commands[k][i + 2]);
                break;
            case 'T':
                if (is_command_correct(commands[k],i,4,screen_size)) {
                    char trian_commands[] = "B__B__B__";
                    trian_commands[1] = commands[k][i + 1];
                    trian_commands[2] = commands[k][i + 2];
                    trian_commands[4] = commands[k][i + 3];
                    trian_commands[5] = commands[k][i + 4];
                    trian_commands[7] = hex_to_char(curr_x);
                    trian_commands[8] = hex_to_char(curr_y);
                    string_insert(commands[k],trian_commands,i + 5, STRING_MAX);
                    printf("draw triangle vertexes, with commands '%s', result = '%s'\n",
                           trian_commands, commands[k]);
                    i += 4;
                } else {
                    printf("error at %d, parameters vertexes: ", i);
                    for (j = 0; j < 4; ++j)
                        printf("%c ",commands[k][i + j]);
                    printf("\n");
                }
                break;
            case 'C':
                if (is_command_correct(commands[k], i, 1, screen_size)) {
                    radius = char_to_hex(commands[k][i + 1]);
                    printf("draw a circle, radius = %d; curr_x = %d, curr_y = %d)\n", radius, curr_x, curr_y);
                    int delta = 1 - (2 * radius);
                    int pos_x = 0, pos_y = radius, offset = 0;
                    while (pos_y >= 0) {
                        screen[(curr_y + pos_y) * screen_size + curr_x + pos_x] = ink;
                        screen[(curr_y - pos_y) * screen_size + curr_x + pos_x] = ink;
                        screen[(curr_y + pos_y) * screen_size + curr_x - pos_x] = ink;
                        screen[(curr_y - pos_y) * screen_size + curr_x - pos_x] = ink;
                        offset = 2 * (delta + pos_y) - 1;
                        if (delta < 0 && offset < 0) {
                            pos_x++;
                            delta += 2 * pos_x + 1;
                        } else {
                            offset = 2 * (delta - pos_x) - 1;
                            if (delta > 0 && offset > 0) {
                                pos_y--;
                                delta = 1 - 2 * pos_y;
                            } else {
                                pos_y--;
                                pos_x++;
                                delta += 2 * (pos_x - pos_y);
                            }
                        }
                    }
                    i += 1;
                }
                break;
            default:
                printf("ERROR: unknown command - '%c'!\n",commands[k][i]);
            }
            printf("\n");
            output_screen(screen, screen_size, screen_size);
            printf("\n");
        }
        printf("result commands string: '%s'",commands[k]);
    }
    int a1 = 1, b1 = 2, c1 = 3 , d1 = 4;
    printf("\n10.38, exchange of values, a = %d, b = %d, c = %d, d = %d;\n", a1, b1, c1, d1);
    exchange_of_values(&a1,&b1);
    exchange_of_values(&c1,&d1);
    printf("result = a = %d, b = %d, c = %d, d = %d;\n", a1, b1, c1, d1);
    day = 2;
    year = -2021;
    month = 9;
    int date_quantity = 10;
    char* date_formats[] = {"DD-MM-YYYY E", "E DDD-M-YYY", "EDMY-DMY-E", "D-M-Y", "Y-Y-Y"
                            , "DDDMMM", "E", "Y___Y__M_", "__E__DD_", "___YYYYY___"};
    printf("date: %d:%d:%d;\n",day,month,year);
    printf("source format:\tresult format:\n");
    for (i = 0; i < date_quantity; ++i) {
        printf("'%s'\t", date_formats[i]);
        if (string_length(date_formats[i]) < 6)
            printf("\t");
        print_date(day,month,year,date_formats[i]);
        printf("\n");
    }
    a = 9;
    printf("\n10.41, recursive factorial of %d;\n", a);
    result = factorial_recur(a);
    printf("result = %d;\n\n",result);
    int power = 5;
    base = 2;
    printf("10.42, recursive exponentiation, power = %d, base = %d;\n", power, base);
    result = expt(base,power);
    printf("result = %d;\n\n", result);
    int value = 123;
    printf("10.43, sum of digits and their number, recursively, number = %d\n", value);
    printf("sum of digits = %d;\n", sum_of_digits_recur(value));
    printf("quantity of digits = %d;\n\n", number_of_digits_recur(value));
    value = 15478;
    printf("10.44, digital root of a number, recursively, number = %d;\n",value);
    printf("digital root = %d;\n\n",digital_root_recur(value));
    int d = 3, n = 3, sum = 0;
    a1 = 1;
    printf("10.45, arithmetic progression, recursive, a1 = %d, n = %d, d = %d;\n", a1, n, d);
    printf("n value of arithmetic progression = %d\n",value_arith_progres(d,n,a1));
    printf("sum of arithmetic progression = %d\n\n", sum_arith_progres(d,n,a1));
    printf("n of value = %d;\n", arif_recur(a1,d,n,&sum));
    printf("sum = %d;\n\n", sum);
    n = 16;
    printf("10.47, recursive fibonacci, n = %d;\n", n);
    result = fibonacci_recur(n);
    printf("result = %d;\n\n",result);
    int numbers[] = {1,4,-7,12,81,-41,513,-1024};
    n = (sizeof (numbers) / sizeof (int)) - 1;
    idx = 0;
    max = numbers[n];
    printf("10.48 - 10.49, find the maximum number and its index, length = %d;\n", n);
    printf("value:\n");
    for (i = 0; i <= n; ++i)
        printf("%d ",numbers[i]);
    printf("\nmax = %d, ", find_max_recur(numbers,n,&idx, max));
    printf("idx = %d;\n\n",idx);
    a1 = 0;
    int a2 = 3, a3 = 0, a4 = 3;
    printf("10.50, funcion Ackermann, A(m,n), m = %d, n = %d;\n", a2, a4);
    printf("n / m:\t0:\t1:\t2:\t3:\n");
    for (;a3 <= a4; ++a3) {
        printf("%d\t", a3);
        for(a1 = 0; a1 <= a2; ++a1)
            printf("%d\t", ackermann(a1,a3));
        printf("\n");
    }
    n = 12345;
    result = 0;
    printf("10.52, flip the number, number = %d;\n", n);
    printf("result = %d;\n\n", reverse_number(n,result));
    const int bases[] = {2,4,8,16,10};
    const int tab_size = 5;
    for (i = 0; i < tab_size; ++i)
        data_int[i] = rand() % 128;
    printf("10.54 - 10.55, translation;\n");
    printf("number:\t2:\t4:\t8:\t16:\t10:\n");
    for (i = 0; i < tab_size; ++i) {
        printf("%d\t", data_int[i]);
        for (j = 0;j < tab_size; ++j) {
            print_integer_recur(data_int[i], bases[j]);
            printf("\t");
        }
        printf("\n");
    }
    n = 17;
    printf("\n10.56, recursively checking if a number is prime, number = %d;\n", n);
    result = prime_check_recur(n,&n);
    printf("result = %d;\n\n",result);
    char src[] = "adeqweewqsde";
    start = 5;
    int end = 6;
    printf("10.57, is the string symmetric, start = %d, end = %d;\n", start, end);
    printf("source string: '%s'\n",src);
    result = symmetric_check_recur(src, start, end, STRING_MAX);
    printf("result = %d;\n\n", result);
}
