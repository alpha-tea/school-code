#include "global.h"
#include "library.h"

#define Y CHAR_MAX
#define Z CHAR_MIN
#define DIGIT 5
#define SEQUENCE_LENGTH 11
#define NUMBERS_QUANTITY 6

int find_max_ints(int mass[], int size)
{
    if (size < 1)
        return -1;
    int max = mass[0];
    for (int i = 1; i < size; ++i)
        if (mass[i] > max)
            max = mass[i];
    return max;
}

int pair_max(int a, int b)
{
    return (a > b) ? a : b;
}

int pair_min(int a, int b)
{
    return (a < b) ? a : b;
}

int length_number(int number)
{
    int i = 0;
    while (number > 0) {
        number /= 10;
        ++i;
    }
    return i;
}

int digits_in_num(int num, int start, int len, int* sum)
{
    *sum = 0;
    int k = num, quantity = 0;
    quantity = length_number(k);
    if (start + len > quantity || start < 0 || len <= 0)
        return -1;
    k = pow(10,quantity - 1);
    for (int i = 0; i < start + len; ++i) {
        int digit = num / k;
        if (i >= start && i < start + len)
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

int search_prime_number(int number)
{
    int i = 2;
    for (i = 2; i < number && number % i != 0; ++i)
        ;
    return (i == number);
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


void print_binary_byte(unsigned char byte)
{
    for (int i = CHAR_BIT - 1; i >= 0; --i)
        printf("%d", (byte >> i) & 0x01);
}

void print_binary_word(unsigned short int word)
{
    print_binary_byte((unsigned char)(word >> CHAR_BIT));
    print_binary_byte((unsigned char)(word & 0xFF));
}

int evklid(int a, int b)
{
    //int c = 0, d = 0;
    //int i = 0;
    //printf("Algoritm Evklida\n");
    while (a != 0 && b != 0) {
        if (a > b) {
            //c = a;
            a %= b;
            //++i;
            //printf("%d)a(%d) > b(%d);\nTotal: a = %d;\n\n",i,c,b,a);
        } else {
            //d = b;
            b %= a;
            //++i;
            //printf("%d)b(%d) > a(%d)\nTotal: b = %d;\n\n",i,d,a,b);
        }
    }
    return a + b;
}

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

int string_find_sub(char s1[], char s2[])
{
    int j = 0, src_1 = string_length(s1), src_2 = string_length(s2);
    if (src_1 == 0 || src_2 == 0 || src_1 < src_2)
        return -2;
    for (int i = 0; i < src_1; ++i) {
        if (s1[i] == s2[j])
            ++j;
        else
            j = 0;
        if (j == src_2)
            return i - j + 1;
    }
    return -1;
}

int num_radix(char src[], char dst[], int from, int to)
{
    int src_len = string_length(src), quantity = 0, sum = 0, number = 0, help1 = 0;
    int help = 1;
    char numbers[] = "0123456789ABCDEF";
    if (to == from || from < 1 || from > 16 || to < 1 || to > 16) {
        printf("Error in parameters.\n");
        return -1;
    }
    for (int i = src_len - 1; i >= 0; --i) {
        for (int k = 0; numbers[k] != '\0' && k <= from; ++k)
            if (numbers[k] == src[i]) {
                if (k >= from)
                    return -1;
                number = k;
            }
        sum += number * help;
        help *= from;
    }
    help = sum;
    while (help > 0) {
        help /= to;
        ++help1;
    }
    for (int l = help1 - 1; l >= 0; --l) {
        number = sum % to;
        sum /= to;
        dst[l] = numbers[number];
        ++quantity;
    }
    return quantity;
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

int string_palindrom(char c[])
{
    int i = 0, src_len = string_length(c);
    if (src_len == 0)
        return -1;
    for (i = 0; i < src_len && c[i] == c[src_len - i - 1]; ++i)
        ;
    if (i == src_len)
        return 0;
    return -1;
}

int string_char_find(char s[], char c, int direct, int debug)
{
    int index = string_length(s);
    if (index == 0) {
        if (debug == 1)
            printf("No chars in string;\n");
        return -1;
    }
    if (debug == 1)
        printf("Char before find: ");
    if (direct == 0) {
        index = 0;
        while (s[index] != c && s[index] != '\0') {
            if (debug == 1)
                printf("%c",s[index]);
            index++;
        }
    } else {
        index--;
        while (s[index] != c && index >= 0) {
            if (debug == 1)
                printf("%c",s[index]);
            index--;
        }
    }
    if (debug == 1)
        printf("\n");
    if (s[index] == c)
        return index;
    else
        return -1;
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
    return (x1 != (int)(x1) || x2 != (int)(x2)) ? 1 : 0; // исправить позже...
}

int string_is_equal(char string_1[], char string_2[])
{
    int help = 0;
    if (string_length(string_1) == 0 || string_length(string_2) == 0) {
        printf("String or substring are empty;\n");
        return -2;
    }
    for (int i = 0; string_1[i] != '\0' &&  string_2[i] != '\0'; ++i)
        if (string_1[i] == string_2[i])
            ++help;
    if (help > 0 && help < string_length(string_1))
        return help;
    else if (help == string_length(string_1))
        return 0;
    else
        return -1;
}

void string_clear(char s[], int len)
{
    for (int i = 0; i < len; ++i)
        s[i] = '\0';
}

void string_exchange(char** s1, char** s2)
{
    char *addr;
    addr = *s1;
    *s1 = *s2;
    *s2 = addr;
}

int string_copy_substr(char src[], char dst[], int start, int length)
{
    if (string_length(src) < length + start)
        return -1;
    int i = 0;
    for (i = 0; i < length; ++i)
        dst[i] = src[i + start];
    dst[i] = '\0';
    return i;
}

int string_concat(char src[], char dst[])
{
    int src_len = string_length(src), dst_length = string_length(dst);
    int i = 0;
    for (i = 0; i < src_len; ++i)
        dst[i + dst_length] = src[i];
    dst[i + dst_length] = '\0';
    return i;
}

int string_find_char(char s[],  char c)
{
    int index = 0;
    while (s[index] != '\0'){
        if (s[index] == c)
            return index;
        index++;
    }
    return -1;
}

double perimeter(double a, double b, double c)
{
    return a + b + c;
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

double line_vertex(double vertex[])
{
    double a, b;
    a = fabs(vertex[0] - vertex[1]);
    b = fabs(vertex[2] - vertex[3]);
    return hypotenuse(a,b);
}

void string_reverse(char string[])
{
    int size = string_length(string);
    for (int j = 0; j < size / 2; ++j) {
        char c = string[j];
        string[j] = string[size - 1 - j];
        string[size - 1 - j] = c;
    }
}

unsigned char shift_logical_right(unsigned char dst[], unsigned char counter)
{
    unsigned char carry_flag = 0x00;
    for (unsigned char ix = 0; ix != counter; ++ix) {
        carry_flag = dst[0];
        for (unsigned char iy = 0; iy != CHAR_BIT - 1; ++iy)
            dst[iy] = dst[iy + 1];
        dst[CHAR_BIT - 1] = 0x00;
    }
    return carry_flag;
}

int string_find_seq(char s[], char c, int start, int length)
{
    int src_len = string_length(s), index = 0;
    if (src_len < start + length) {
        printf("Sequence length more than string length.\n");
        return -1;
    }
    for (index = start; index < start + length && s[index] == c; ++index)
        ;
    return (index == start + length);
}

int string_is_symmetrical(char string[])
{
    int help = 0, len_1 = string_length(string) - 1;
    if (len_1 < 1) {
        printf("error, string is empty;\n");
        return -1;
    }
    while (help < len_1 && string[help] == string[len_1]) {
        ++help;
        --len_1;
    }
    return (help >= len_1);
}

int int_to_string(char dst[], int num, int base)
{
    const int base_min = 2, base_max = 16;
    char digits[] = "0123456789ABCDEF";
    int i = 0;
    if (base < base_min || base > base_max)
        return -1;
    if (num < 0) {
        dst[i++] = '-';
        num *= -1;
    }
    for (;num > 0; ++i) {
        dst[i] = digits[num % base];
        num /= base;
    }
    dst[i] = '\0';
    if (dst[0] == '-')
        string_reverse(&dst[1]);
    else
        string_reverse(dst);
    return 0;
}

char uppercase(char c)
{
    return (c >= 'a' && c <= 'z') ? c -= ('a' - 'A') : c;
}

unsigned char add_byte(unsigned char dst[], unsigned char src[]) // возвращает признак нуля.
{
    int i, help = 0, help2 = 0;
    for (i = 0; i < CHAR_BIT; ++i) {
        help2 = dst[i];
        dst[i] = xor_gate(xor_gate(dst[i],src[i]),help);
        if (and_gate(help2,src[i]) == 1)
            help = 1;
        else if (xor_gate(help2,src[i]) != 1)
            help = 0;
    }
    return help;
}

int number_system_check(int system,int char_in_int[],int len)
{
    for (int i = 0; i < len; ++i)
        if (char_in_int[i] >= system)
            return 1;
    return 0;
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

int string_delete(char src[], int start, int length)
{
    int help = string_length(src), i;
    if (start < 0 || start + length > help || length <= 0)
        return -1;
    for (i = start; i + length < help; ++i)
        src[i] = src[i + length];
    src[i] = '\0';
    return 0;
}

int max_int_pair(int a, int b)
{
    return ((a > b) ? a : b);
}

int string_checking_brackets(char src[])
{
    int i = 0, counter = 0;
    for (i = 0; src[i] != '\0' && counter >= 0; ++i) {
        if (src[i] == '(')
            counter++;
        if (src[i] == ')')
            counter--;
    }
    if (counter == 0)
        return i;
    else
        return -1 * (i - 1);
}

double triangle_heron (double a, double b, double c)
{
    double half_per = perimeter(a,b,c) / 2.0;
    return sqrt(half_per * (half_per - a) * (half_per - b) * (half_per - c));
}

int string_length_brackets(char src[], int start)
{
    int i = 0, counter = 1;
    if (src[start] != '(')
        return -1;
    for (i = start + 1; src[i] != '\0' && counter > 0; ++i) {
        if (src[i] == '(')
            counter++;
        if (src[i] == ')')
            counter--;
    }
    return i - 1;
}

char boolean_calculator(char src[])
{
    int i = 0, counter = 0, idx = 0, operand_a = 0, operand_b = 0;
    char result_string[STRING_MAX];
    char sub_string[STRING_MAX];
    char signs[] = "!&^|";      // Идут в порядке уменьшения приоритета си.
    printf("Starting calculator:\n");
    for (i = 0; src[i] != '\0'; ++i) {
        if (src[i] != ' ') {
            if (src[i] == '(') {
                idx = string_length_brackets(src,i);
                string_copy_substr(src,sub_string, i + 1, idx - i - 1);
                printf("index of brackets: [%d:%d], sub_string = '%s'\n", i, idx, sub_string);
                result_string[counter++] = boolean_calculator(sub_string); // Рекурсия
                i = idx;
            } else
                result_string[counter++] = src[i];
        }
    }
    result_string[counter] = '\0';
    printf("Calculate string: '%s'\n", result_string);
    printf("Source string: '%s'\n", src);
    for (i = 0; signs[i] != '\0' && result_string[1] != '\0'; ++i) {
        while ((idx = string_char_find(result_string,signs[i],0,0)) != -1) {
            switch (signs[i]) {
            case '!':
                if (result_string[idx + 1] == '1' || result_string[idx + 1] == '0') {
                    operand_a = result_string[idx + 1] - '0';
                    result_string[idx] = !(operand_a) + '0';
                    string_delete(result_string,idx + 1,1);
                } else
                    printf("error: not expect 0 or 1, idx = %d;\n", idx);
                break;
            case '&':
                if ((result_string[idx + 1] == '1' || result_string[idx + 1] == '0')
                        && (result_string[idx - 1] == '1' || result_string[idx - 1] == '0')) {
                    operand_a = result_string[idx - 1] - '0';
                    operand_b = result_string[idx + 1] - '0';
                    result_string[idx - 1] = (operand_a & operand_b) + '0';
                    string_delete(result_string,idx,2);
                } else
                    printf("error: and expect 0 or 1, to left and right, idx = %d;\n", idx);
                break;
            case '^':
                if ((result_string[idx + 1] == '1' || result_string[idx + 1] == '0')
                        && (result_string[idx - 1] == '1' || result_string[idx - 1] == '0')) {
                    operand_a = result_string[idx - 1] - '0';
                    operand_b = result_string[idx + 1] - '0';
                    result_string[idx - 1] = (operand_a ^ operand_b) + '0';
                    string_delete(result_string,idx,2);
                } else
                    printf("error: xor expect 0 or 1, to left and right, idx = %d;\n", idx);
                break;
            case '|':
                if ((result_string[idx + 1] == '1' || result_string[idx + 1] == '0')
                        && (result_string[idx - 1] == '1' || result_string[idx - 1] == '0')) {
                    operand_a = result_string[idx - 1] - '0';
                    operand_b = result_string[idx + 1] - '0';
                    result_string[idx - 1] = (operand_a | operand_b) + '0';
                    string_delete(result_string,idx,2);
                } else
                    printf("error: or expect 0 or 1, to left and right, idx = %d;\n", idx);
                break;
            default:
                printf("error:");
            }
        }
        printf("\t:'%c': '%s'\n",signs[i], result_string);
    }
    return result_string[0];
}

int string_xchg_chars(char src[], int table[], int count)
{
    char help1 = string_length(src), help;
    if (count == 0 || help1 == 0)
        return -2;
    for (int i = 0; i < count * 2; i += 2) {
        if (table[i] < help1 && table[i] >= 0 && table[i + 1] < help1 && table[i + 1] >= 0) {
            help = src[table[i]];
            src[table[i]] = src[table[i + 1]];
            src[table[i + 1]] = help;
        } else
            return -1;
    }
    return 0;
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

double perimeter_isosceles_trapezoid(double bases_1, double bases_2, double height) // использовать как можно больше вызовов из предыдуших заданий.
{
    return hypotenuse(height,(bases_2 - bases_1) / 2) * 2 + bases_1 + bases_2;
}

int length(char s[])
{
    int len = 0;                //Длинна строки.
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

int string_insert( char dst[], char ins[], int start, int limit)
{
    int ins_len = string_length(ins), dst_len = string_length(dst), i;
    if (ins_len == 0 || ins_len + start >= limit)
        return -1;
    for (i = ins_len + dst_len; i >= start + ins_len; --i)
        dst[i] = dst[i - ins_len];
    for (int j = start, i = 0; j < ins_len + start; ++j, ++i)
        dst[j] = ins[i];
    return 0;
}

void string_rrc(char src[], int counter)
{
    int help = string_length(src), j;
    char help_2;
    for (int i = 0; i < counter; ++i) {
        help_2 = src[help - 1];
        for (j = help - 1; j > 0; --j)
            src[j] = src[j - 1];
        src[j] = help_2;
    }
}

void string_rlc(char src[], int counter)
{
    int help = string_length(src),j;
    char help_2;
    for (int i = 0; i < counter; ++i) {
        help_2 = src[0];
        for (j = 0; j < help - 1; ++j)
            src[j] = src[j + 1];
        src[help - 1] = help_2;
    }
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

void chapter_10()
{
    int i = 0, j = 0, k = 0;
    double result_double;
    const int variants = 4, terms = 3, exp_size = 12;
    printf("10.1, calculate X, all variants.\n");
    int data_1[exp_size * variants], is_sqrt[exp_size * variants];
    srand(time(NULL));
    for (i = 0; i < variants; ++i) {
        for (j = 0; j < exp_size; ++j) {
            data_1[i * exp_size + j] = 1 + rand() % 100;
            is_sqrt[i * exp_size + j] = rand() % 2;
        }
    }
    for (k = 0; k < variants; ++k) {
        printf("Variant %d:\n",k);
        result_double = calc_exp_10_1(&data_1[k * exp_size], is_sqrt, exp_size, terms);
    }
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
    double vertex[OBJECTS_MAX];
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
    // скопируем координаты первой точки, в хвост трёх вершин ммасива vertex.
    vertex[6] = vertex[0];
    vertex[7] = vertex[1];
    double lines[OBJECTS_MAX];
    printf("Sides of triangle: ");
    for (i = 0; i < parties && i < OBJECTS_MAX; ++i)  {
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
        if (search_prime_number(i)) {
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
    printf("\nTotal: %d;\n\n",counter);
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
    printf("10.23, define next day, previous day and days in month;\n");
    printf("date:\t\tprevious:\tnext:\t\tdays in month:\n");
    int data_dates[] = {1,1,1, 31,12,-1, 28,2,1900, 1,3,1900, 29,2,2000, 1,3,2000, 28,2,2020, 1,3,2020, 16,1,2021};
    for (i = 0; i < 9; ++i) {
        day = data_dates[i * 3];
        month = data_dates[i * 3 + 1];
        year = data_dates[i * 3 + 2];
        printf("%2d/%2d/%4d\t", day, month, year);
        date_prev_day(&day, &month, &year);
        printf("%2d/%2d/%4d\t", day, month, year);
        day = data_dates[i * 3];
        month = data_dates[i * 3 + 1];
        year = data_dates[i * 3 + 2];
        date_next_day(&day, &month, &year);
        printf("%2d/%2d/%4d\t", day, month, year);
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
    char commands[OBJECTS_MAX][STRING_MAX] = {"P00RFFP22R66PD2RA6P2DR6APDDRAA"};  //C422CC22C822C652CA52;P00DP34DPF0DPFFDP0FD
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
    printf("C### - draw a circle with radius R to x:y\n");
    int x_pos = 0, y_pos = 0, curr_y = 0, curr_x = 0;
    int delta_x = 0, delta_y = 0, delta_max = 0;
    int err_y = 0, err_x = 0, del_y = 0, del_x = 0;
    int radius = 5, err_rad = 0;
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
                /*
            case 'B':
                start_x_pos = x_pos;
                start_y_pos = y_pos;
                string_find_char_variant_2(digits,command[i + 1],&x_pos);
                string_find_char_variant_2(digits,command[i + 2],&y_pos);
                delta_x = abs(x_pos - start_x_pos);
                delta_y = abs(y_pos - start_y_pos);
                delta_max = delta_x;
                if (delta_y > delta_x)
                    delta_max = delta_y;
                del_y = 1;
                del_x = 1;
                if (y_pos - start_y_pos < 0)
                    del_y = -1;
                if (x_pos - start_x_pos < 0)
                    del_x = -1;
                err_y = delta_x / 2;
                err_x = delta_y / 2;
                for (int x = start_x_pos; x != x_pos + 1;) {
                    field[start_y_pos][x] = 'O';
                    err_y += delta_y;
                    err_x += delta_x;
                    if (err_y >= delta_max) {
                        start_y_pos += del_y;
                        err_y -= delta_max;
                    }
                    if (err_x >= delta_max) {
                        x += del_x;
                        err_x -= delta_max;
                    }
                }
                i += 2;
                break;
            case 'C':
                string_find_char_variant_2(digits,command[i + 1],&start_x_pos);
                string_find_char_variant_2(digits,command[i + 2],&start_y_pos);
                string_find_char_variant_2(digits,command[i + 3],&radius);
                printf("Command: C(rad = %d; x = %d:y = %d)\n",radius,start_x_pos,start_y_pos);
                err_rad = 1 - radius;
                y_pos = 0;
                while (radius >= y_pos) {
                    field[radius + start_y_pos][y_pos + start_x_pos] = 'O';
                    field[y_pos + start_y_pos][radius + start_x_pos] = 'O';
                    field[-radius + start_y_pos][y_pos + start_x_pos] = 'O';
                    field[-y_pos + start_y_pos][radius + start_x_pos] = 'O';
                    field[-radius + start_y_pos][-y_pos + start_x_pos] = 'O';
                    field[-y_pos + start_y_pos][-radius + start_x_pos] = 'O';
                    field[radius + start_y_pos][-y_pos + start_x_pos] = 'O';
                    field[y_pos + start_y_pos][-radius + start_x_pos] = 'O';
                    y_pos++;
                    if (err_rad < 0)
                        err_rad += 2 * y_pos + 1;
                    else {
                        --radius;
                        err_rad += 2 * (y_pos - radius + 1);
                    }
                }
                i += 3;
                break;
                */
            default:
                printf("ERROR: unknown command - '%c'!\n",commands[k][i]);
            }
            printf("\n");
            output_screen(screen, screen_size, screen_size);
            printf("\n");
        }
        printf("result commands string: '%s'",commands[k]);
    }
}


int main()
{
    chapter_8();
    //getchar(); - не снимать, кусается...
    return 0;
}
