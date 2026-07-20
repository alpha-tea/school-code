#include <stdio.h>
#include <stdlib.h>
#include "library.h"

#undef SIZE

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
                printf("%c", s[index]);
            index++;
        }
    } else {
        index--;
        while (s[index] != c && index >= 0) {
            if (debug == 1)
                printf("%c", s[index]);
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

int string_length(char s[])
{
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

int string_is_equal(char string_1[], char string_2[])
{
    int match_count = 0;
    if (string_length(string_1) == 0 || string_length(string_2) == 0) {
        printf("String or substring are empty;\n");
        return -2;
    }
    for (int i = 0; string_1[i] != '\0' && string_2[i] != '\0'; ++i)
        if (string_1[i] == string_2[i])
            ++match_count;
    if (match_count > 0 && match_count < string_length(string_1))
        return match_count;
    else if (match_count == string_length(string_1))
        return 0;
    else
        return -1;
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

int string_char_counter(char s[], char c)
{
    int count = 0, src_len = string_length(s);
    for (int i = 0; i < src_len; ++i)
        if (s[i] == c)
            ++count;
    return count;
}

int is_perfect_number(int a)
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

int gcd(int a, int b)
{
    while (a != 0 && b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a + b;
}

int count_digits(int number)
{
    int count = 0;
    do {
        number /= 10;
        ++count;
    } while (number > 0);
    return count;
}

int factorial(int n)
{
    int result = 1;
    for (; n > 0; --n)
        result *= n;
    return result;
}

int is_prime_number(int number)
{
    int i = 2;
    for (i = 2; i < number && number % i != 0; ++i)
        ;
    return (i == number);
}

int string_insert(char dst[], char ins[], int start, int limit)
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

int array_rotate_range(int data[], int size, int start, int length, int direct)
{
    if (size < 2 || start + length > size || length <= 1) {
        printf("error: in size or start or length;\n");
        return -1;
    }
    if (direct == 0) {
        int element = data[start];
        for (int i = start; i < start + length; ++i)
            data[i] = data[i + 1];
        data[start + length - 1] = element;
    } else {
        int element = data[start + length - 1];
        for (int i = start + length - 1; i > start; --i)
            data[i] = data[i - 1];
        data[start] = element;
    }
    return 0;
}

int int_to_digits_array(int number, int data[], int size)
{
    if (size < 1) {
        printf("error: in size or number;\n");
        return -1;
    }
    int counter = 0;
    do {
        data[counter] = number % 10;
        number /= 10;
        counter++;
    } while (number != 0 && counter < size);
    for (int i = 0; i < counter / 2; ++i) {
        int temp = data[i];
        data[i] = data[counter - i - 1];
        data[counter - i - 1] = temp;
    }
    return counter;
}

int find_max_recursive(int numbers[], int length, int* idx, int max)
{
    if (length < 0)
        return max;
    if (numbers[length] > max) {
        max = numbers[length];
        *idx = length;
    }
    return find_max_recursive(numbers, --length, idx, max);
}

int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

int generate_shuffled_array(int number[], int length, int limit)
{
    if (length < 1 || length > limit)
        return -1;
    for (int i = 0; i < limit; ++i)
        number[i] = i;
    int temp = 0, idx_1 = 0, idx_2 = 0;
    for (int i = 0; i < length * length; ++i) {
        idx_1 = rand() % limit;
        idx_2 = rand() % limit;
        temp = number[idx_1];
        number[idx_1] = number[idx_2];
        number[idx_2] = temp;
    }
    return 0;
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
    for (; num > 0; ++i) {
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

int generate_shuffled_range(int number[], int start, int limit)
{
    if (limit < 1)
        return -1;
    for (int i = 0; i < limit; ++i)
        number[i] = start + i;
    int temp = 0, idx_1 = 0, idx_2 = 0;
    for (int i = 0; i < limit * limit; ++i) {
        idx_1 = rand() % limit;
        idx_2 = rand() % limit;
        temp = number[idx_1];
        number[idx_1] = number[idx_2];
        number[idx_2] = temp;
    }
    return 0;
}

void print_binary_byte(unsigned char byte)
{
    for (int i = CHAR_BIT - 1; i >= 0; --i)
        printf("%d", (byte >> i) & 0x01);
}

void swap_ints(int *a, int *b)
{
    *a -= *b;
    *b += *a;
    *a = *b - *a;
}

double power_int_exp(double base, unsigned int exp)
{
    double result = 1.0;
    for (unsigned int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

void string_print_reversed(const char s[])
{
    int len = string_length((char*)s);
    while (--len >= 0) {
        printf("%c", s[len]);
    }
}

int sum_digits_base(int num, int base)
{
    if (num <= 0 || base < 2) {
        return -1;
    }
    int sum = 0;
    while (num > 0) {
        sum += num % base;
        num /= base;
    }
    return sum;
}

int lcm(int a, int b)
{
    if (a == 0 || b == 0) return 0;
    return (abs(a * b) / gcd(a, b));
}

int is_fibonacci_number(int n)
{
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    int a = 0, b = 1, c = 0;
    while (c < n) {
        c = a + b;
        a = b;
        b = c;
    }
    return (c == n);
}

void byte_to_binary_str(unsigned char byte, char string[])
{
    int i = 0;
    while (i < CHAR_BIT && byte > 0) {
        string[i] = (byte % 2) + '0';
        byte >>= 1;
        i++;
    }
    string[i] = '\0';
    string_reverse(string);
}

int digital_root(int n)
{
    int sum = 0;
    n = abs(n);
    if (n == 0) return 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    if (sum > 9)
        return digital_root(sum);
    return sum;
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

int string_delete(char src[], int start, int length)
{
    int src_len = string_length(src), i;
    if (start < 0 || start + length > src_len || length <= 0)
        return -1;
    for (i = start; i + length < src_len; ++i)
        src[i] = src[i + length];
    src[i] = '\0';
    return 0;
}

int string_is_symmetrical(char string[])
{
    int i = 0, len_1 = string_length(string) - 1;
    if (len_1 < 1) {
        printf("error, string is empty;\n");
        return -1;
    }
    while (i < len_1 && string[i] == string[len_1]) {
        ++i;
        --len_1;
    }
    return (i >= len_1);
}

void string_rrc(char src[], int counter)
{
    int src_len = string_length(src), j;
    char temp;
    for (int i = 0; i < counter; ++i) {
        temp = src[src_len - 1];
        for (j = src_len - 1; j > 0; --j)
            src[j] = src[j - 1];
        src[j] = temp;
    }
}

void string_rlc(char src[], int counter)
{
    int src_len = string_length(src), j;
    char temp;
    for (int i = 0; i < counter; ++i) {
        temp = src[0];
        for (j = 0; j < src_len - 1; ++j)
            src[j] = src[j + 1];
        src[src_len - 1] = temp;
    }
}

int string_xchg_chars(char src[], int table[], int count)
{
    int src_len = string_length(src);
    char temp;
    if (count == 0 || src_len == 0)
        return -2;
    for (int i = 0; i < count * 2; i += 2) {
        if (table[i] < src_len && table[i] >= 0 && table[i + 1] < src_len && table[i + 1] >= 0) {
            temp = src[table[i]];
            src[table[i]] = src[table[i + 1]];
            src[table[i + 1]] = temp;
        } else
            return -1;
    }
    return 0;
}

int num_radix(char src[], char dst[], int from, int to)
{
    int src_len = string_length(src), quantity = 0, sum = 0, number = 0, temp_len = 0;
    int step = 1;
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
        sum += number * step;
        step *= from;
    }
    step = sum;
    while (step > 0) {
        step /= to;
        ++temp_len;
    }
    for (int l = temp_len - 1; l >= 0; --l) {
        number = sum % to;
        sum /= to;
        dst[l] = numbers[number];
        ++quantity;
    }
    return quantity;
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

int string_concat(char src[], char dst[])
{
    int src_len = string_length(src), dst_length = string_length(dst);
    int i = 0;
    for (i = 0; i < src_len; ++i)
        dst[i + dst_length] = src[i];
    dst[i + dst_length] = '\0';
    return i;
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

int string_rep_sub(char src[], char find[], char rep[], int all)
{
    int j = 0, src_len = string_length(src), find_len = string_length(find), quantity = 0;
    if (src_len == 0 || find_len == 0 || src_len < find_len || find_len != string_length(rep) ||
        string_is_equal(find, rep) == 0)
        return -1;
    while ((j = string_find_sub(src, find)) >= 0 && all >= 0) {
        for (int k = 0; k < find_len; ++k)
            src[j + k] = rep[k];
        if (all == 0)
            --all;
        ++quantity;
    }
    return quantity;
}

int string_swap_parts(char src[], int parts, int mode)
{
    int src_len = string_length(src), parts_size = src_len / parts;
    if ((mode < 1 || mode > 2) && (src_len == 0 || src_len % parts != 0)) {
        printf("String is empty or parts not fit or mode error;\n");
        return -1;
    }
    printf("Exchange %d parts in string %s, parts size = %d;\n", parts, src, parts_size);
    if (mode == 1)
        printf("Swap parts in string in reverse mode;\n");
    else
        printf("Swap parts in string in pairs mode;\n");
    for (int i = 0; i < parts / 2; ++i) {
        int left_part, right_part;
        switch (mode) {
        case 1:
            left_part = i * parts_size;
            right_part = (parts - i - 1) * parts_size;
            break;
        case 2:
            left_part = i * 2 * parts_size;
            right_part = (i * 2 + 1) * parts_size;
            break;
        default:
            printf("Error in mode return;\n");
            return -1;
        }
        printf("Parts move %d:%d, chars move:", left_part, right_part);
        for (int k = 0; k < parts_size; ++k) {
            printf("%c:%c ", src[left_part + k], src[right_part + k]);
            char tmp = src[left_part + k];
            src[left_part + k] = src[right_part + k];
            src[right_part + k] = tmp;
        }
    }
    printf("Result = %s;\n", src);
    return 0;
}

int string_to_words(char text[], char words[STRING_MAX][STRING_MAX])
{
    int idx_word = 0, i, j, words_total = 0;
    for (i = 0, j = 0; text[i] != '\0' || idx_word != i;) {
        if ((text[i] == ' ' || text[i] == '\0') && idx_word < i) {
            string_copy_substr(text, words[j++], idx_word, i - idx_word);
            idx_word = i;
            words_total++;
        } else {
            ++i;
            if (text[idx_word] == ' ')
                idx_word = i;
        }
    }
    return words_total;
}

int string_to_int(char src[], int base)
{
    const int base_min = 2, base_max = 16;
    char digits[] = "0123456789ABCDEF";
    if (base < base_min || base > base_max)
        return 0;
    int idx = 0, number = 0, sign = 0;
    while (!sign && src[idx] != '\0') {
        if (src[idx] == '-')
            sign = -1;
        if (src[idx] == '+')
            sign = 1;
        int idx_2 = 0;
        while (src[idx] != digits[idx_2] && idx_2 < base)
            ++idx_2;
        if (idx_2 != base)
            sign = 1;
        else
            ++idx;
    }
    while (src[idx] != '\0') {
        int j = 0;
        while (src[idx] != digits[j] && j < base)
            ++j;
        if (src[idx] == digits[j] && j != base)
            number = number * base + j;
        ++idx;
    }
    return sign * number;
}

int uniq_gen_fast(int number[], int length, int limit) {
    const int num_max = limit;
    if (length < 1 || length > num_max)
        return -1;
    int digits[limit];
    for (int i = 0; i < limit; ++i)
        digits[i] = i;
    int tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < length * length * length && digits[0] == 0; ++i) {
        idx_1 = rand() % num_max;
        idx_2 = rand() % num_max;
        tmp = digits[idx_1];
        digits[idx_1] = digits[idx_2];
        digits[idx_2] = tmp;
    }
    for (int i = 0; i < length; ++i)
        number[i] = digits[i];
    return 0;
}

int uniq_gen_fast_symbols(char string[], int length) {
    const int symbol_max = 26;
    if (length < 1 || length > symbol_max)
        return -1;
    char symbols[symbol_max];
    for (int j = 0; j < 26; ++j)
        symbols[j] = 'A' + j;
    char tmp;
    int idx_1 = 0 , idx_2 = 0, i = 0;
    for (i = 0; i < length * length * length; ++i) {
        idx_1 = rand() % symbol_max;
        idx_2 = rand() % symbol_max;
        tmp = symbols[idx_1];
        symbols[idx_1] = symbols[idx_2];
        symbols[idx_2] = tmp;
    }
    for (i = 0; i < length; ++i)
        string[i] = symbols[i];
    string[length] = '\0';
    return 0;
}

int string_rand_change(char string[], int level_change) {
    int length = string_length(string);
    if (length == 0 || level_change < 1)
        return -1;
    int mass_idx[level_change];
    char mass_symbol[level_change];
    uniq_gen_fast(mass_idx, level_change, length);
    uniq_gen_fast_symbols(mass_symbol, level_change);
    for (int i = 0; i < level_change; ++i)
        string[mass_idx[i]] = mass_symbol[i];
    return 0;
}