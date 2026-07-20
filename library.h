#ifndef LIBRARY_H
#define LIBRARY_H

#define STRING_MAX 256
#define BYTE_NUMS 256

// Общая библиотека универсальных функций для всех глав задачника.

int string_length(char s[]);

int string_char_counter(char s[], char c);

int is_perfect_number(int a);

int gcd(int a, int b);

int count_digits(int number);

int string_copy_substr(char src[], char dst[], int start, int length);

int string_is_equal(char string_1[], char string_2[]);

int string_insert(char dst[], char ins[], int start, int limit);

int factorial(int n);

int is_prime_number(int number);

int string_char_find(char s[], char c, int direct, int debug);

int array_rotate_range(int data[], int size, int start, int length, int direct);

int int_to_digits_array(int number, int data[], int size);

int find_max_recursive(int numbers[], int length, int* idx, int max);

int hex_char_to_int(char c);

int generate_shuffled_array(int number[], int length, int limit);

void string_reverse(char string[]);

int int_to_string(char dst[], int num, int base);

int generate_shuffled_range(int number[], int start, int limit);

void print_binary_byte(unsigned char byte);

void swap_ints(int *a, int *b);

double power_int_exp(double base, unsigned int exp);

void string_print_reversed(const char s[]);

int sum_digits_base(int num, int base);

int lcm(int a, int b);

int is_fibonacci_number(int n);

void byte_to_binary_str(unsigned char byte, char string[]);

int digital_root(int n);

int string_length_brackets(char src[], int start);

int string_checking_brackets(char src[]);

int string_delete(char src[], int start, int length);

int string_is_symmetrical(char string[]);

void string_rrc(char src[], int counter);

void string_rlc(char src[], int counter);

int string_xchg_chars(char src[], int table[], int count);

int num_radix(char src[], char dst[], int from, int to);

int string_find_seq(char s[], char c, int start, int length);

int string_palindrom(char c[]);

int string_concat(char src[], char dst[]);

void string_clear(char s[], int len);

void string_exchange(char** s1, char** s2);

int string_find_sub(char s1[], char s2[]);

int string_rep_sub(char src[], char find[], char rep[], int all);

int string_swap_parts(char src[], int parts, int mode);

int string_to_words(char text[], char words[STRING_MAX][STRING_MAX]);

int string_to_int(char src[], int base);

int uniq_gen_fast(int number[], int length, int limit);

int uniq_gen_fast_symbols(char string[], int length);

int string_rand_change(char string[], int level_change);
#endif
