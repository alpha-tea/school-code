#include "global.h"
#include "library.h"

void string_exchange(char** s1, char** s2);
int string_find_sub(char s1[], char s2[]);
void string_clear(char s[], int len);
int string_concat(char src[], char dst[]);
int string_palindrom(char c[]);
int string_char_find(char s[], char c, int direct, int debug);
int string_find_seq(char s[], char c, int start, int length);
int num_radix(char src[], char dst[], int from, int to);
void print_binary_byte(unsigned char byte);
void print_binary_word(unsigned short int word);
unsigned char shift_logical_right(unsigned char dst[], unsigned char counter);
unsigned char add_byte(unsigned char dst[], unsigned char src[]);
unsigned char not_gate(unsigned char bit_1);
unsigned char and_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char or_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char xor_gate(unsigned char bit_1, unsigned char bit_2);
unsigned char nand_gate(unsigned char bit_1, unsigned char bit_2);
int string_xchg_chars(char src[], int table[], int count);
int string_delete(char src[], int start, int length);
void string_rlc(char src[], int counter);
void string_rrc(char src[], int counter);
int int_to_string(char dst[], int num, int base);
void string_reverse(char string[]);
int string_is_symmetrical(char string[]);
int string_checking_brackets(char src[]);
char boolean_calculator(char src[]);
int string_checking_brackets(char src[]);


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

unsigned char not_gate(unsigned char bit_1)
{
    if (bit_1 == 0x01)
        return 0x00;
    else
        return 0x01;
}

unsigned char and_gate(unsigned char bit_1, unsigned char bit_2)
{
    if (bit_1 == 0x01)
        if (bit_2 == 0x01)
            return 0x01;
    return 0x00;
}

unsigned char or_gate(unsigned char bit_1, unsigned char bit_2)
{
    if (bit_1 == 0x01)
        return 0x01;
    else if (bit_2 == 0x01)
        return 0x01;
    return 0x00;
}

unsigned char xor_gate(unsigned char bit_1, unsigned char bit_2)
{
    if (bit_1 == bit_2)
        return 0x00;
    return 0x01;
}

unsigned char nand_gate(unsigned char bit_1, unsigned char bit_2)
{
    if (bit_1 == 1)
        if (bit_2 == 1)
            return 0x00;
    return 0x01;
}

unsigned char add_byte(unsigned char dst[], unsigned char src[])
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

int string_rep_sub(char src[], char find[],char rep[],int all)
{
    int j = 0, src_len = string_length(src), find_len = string_length(find), quantity = 0;
    if (src_len == 0 || find_len == 0 || src_len < find_len || find_len != string_length(rep) ||
            string_is_equal(find, rep) == 0)
        return -1;
    while ((j = string_find_sub(src,find)) >= 0 && all >= 0) {
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

        printf("Parts move %d:%d, chars move:",left_part, right_part);
        for (int k = 0; k < parts_size; ++k) {
            printf("%c:%c ",src[left_part + k], src[right_part + k]);
            char tmp = src[left_part + k];
            src[left_part + k] = src[right_part + k];
            src[right_part + k] = tmp;
        }
    }
    printf("Result = %s;\n",src);
    return 0;
}

static unsigned char bits_nums[BYTE_NUMS][CHAR_BIT];

unsigned char set_register(unsigned char* num, unsigned char byte[])
{
    for (unsigned char ix = 0; ix != CHAR_BIT; ++ix)
        byte[ix] = bits_nums[*num][ix];
    return 0x01;
}

unsigned char get_register(unsigned char* num, unsigned char byte[])
{
    for (unsigned short ix = 0; ix != BYTE_NUMS; ++ix) {
        unsigned char zero_flag = 0x01;
        for (unsigned char iy = 0; iy != CHAR_BIT; ++iy) {
            unsigned char bit_r = not_gate(xor_gate(byte[iy],bits_nums[ix][iy]));
            zero_flag = and_gate(zero_flag,bit_r);
            //if (byte[iy] != bits_nums[ix][iy])
            //  zero_flag = 0x00;
        }
        if (zero_flag == 0x01) {
            *num = (unsigned char)(ix);
            return 0x01;
        }
    }
    return 0x00;
}

int string_to_words(char text[], char words[STRING_MAX][STRING_MAX])    // Fix later...
{
    int idx_word = 0, i, j, words_total = 0;
    for (i = 0, j = 0; text[i] != '\0' || idx_word != i;) {
        if ((text[i] == ' ' || text[i] == '\0') && idx_word < i) {
            string_copy_substr(text,words[j++],idx_word,i - idx_word);
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

unsigned char not_logical (unsigned char dst[])
{
    unsigned char zero_flag = 0x00;
    for (unsigned char ix = 0; ix != CHAR_BIT; ++ix) {
        dst[ix] = not_gate(dst[ix]);
        zero_flag = or_gate(zero_flag,dst[ix]);
    }
    return not_gate(zero_flag);
}

unsigned char and_logical(unsigned char dst[], unsigned char src[]) // возвращает признак нуля.
{
    unsigned char zero_flag = 0x00;
    for (unsigned char ix = 0; ix != CHAR_BIT; ++ix) {
        dst[ix] = and_gate(dst[ix],src[ix]);
        zero_flag = or_gate(zero_flag,dst[ix]);
    }
    return not_gate(zero_flag);
}

unsigned char or_logical(unsigned char dst[], unsigned char src[])
{
    unsigned char zero_flag = 0x00;
    for (unsigned char ix = 0; ix != CHAR_BIT; ++ix) {
        dst[ix] = or_gate(dst[ix],src[ix]);
        zero_flag = or_gate(zero_flag,dst[ix]);
    }
    return not_gate(zero_flag);
}

unsigned char xor_logical(unsigned char dst[], unsigned char src[])
{
    unsigned char zero_flag = 0x00;
    for (unsigned char ix = 0; ix != CHAR_BIT; ++ix) {
        dst[ix] = xor_gate(dst[ix],src[ix]);
        zero_flag = or_gate(zero_flag,dst[ix]);
    }
    return not_gate(zero_flag);
}

int string_to_int(char src[], int base)
{
    const int base_min = 2, base_max = 16;
    char digits[] = "0123456789ABCDEF";
    if (base < base_min || base > base_max)
        return 0;
    int idx = 0, number = 0, sign = 0; // 0 - пока не определили знак.
    while (!sign && src[idx] != '\0') {
        if (src[idx] == '-')
            sign = -1;
        if (src[idx] == '+')
            sign = 1;
        int idx_2 = 0;
        while (src[idx] != digits[idx_2] && idx_2 < base) // Здесь можно использовать if для анализа.
            ++idx_2;
        if (idx_2 != base)
            sign = 1;
        else
            ++idx;
    }
    //printf("Sign = %d\nIdx = %d\n",sign,idx);
    while (src[idx] != '\0') {
        int j = 0; // Здесь тоже можно через if.
        while (src[idx] != digits[j] && j < base)
            ++j;
        if (src[idx] == digits[j] && j != base)
            number = number * base + j;
        //printf("Src = %c, idx = %d, number = %d\n",src[idx],idx,number);
        ++idx;
    }
    return sign * number;
}

unsigned char shift_logical_left(unsigned char dst[], unsigned char counter) // возвращает последний бит, вышедший за пределы.
{
    unsigned char carry_flag = 0x00;
    for (unsigned char ix = 0; ix != counter; ++ix) {
        carry_flag = dst[CHAR_BIT - 1];
        for (unsigned char iy = CHAR_BIT - 1; iy != 0; --iy)
            dst[iy] = dst[iy - 1];
        dst[0] = 0x00;
    }
    return carry_flag;
}


void chapter_9()
{
    int i = 0, j = 0, k = 0;
    //printf("[%ld]%d\n",(long)&i,i);
    printf("Size of char: %u bytes, min = %d, max = %d, bits in char =  %d;\n\n",
           sizeof(char), CHAR_MIN, CHAR_MAX, CHAR_BIT);
    printf("9.1;\nEnter name: ");
    char name[STRING_MAX] = "daniil";
    //scanf("%s", name);
    i = sizeof (name);
    printf("a)%s, size of string = %d;\n",name,i);
    printf("b)Hello! My dear %s!;\n\n",name);
    printf("9.6 - 9.11, two countries;\n");
    char s1[STRING_MAX] = "first";
    char s2[STRING_MAX] = "second";
    printf("s1 = %s;\ns2 = %s;\n",s1,s2);
    char help_char[STRING_MAX];
    for (i = 0; s1[i] != '\0'; ++i)
        help_char[i] = s1[i];
    help_char[i] = '\0';
    printf("temp string = %s;\n", help_char);
    for (i = 0; s2[i] != '\0'; ++i)
        s1[i] = s2[i];
    s1[i] = '\0';
    for (i = 0; help_char[i] != '\0'; ++i)
        s2[i] = help_char[i];
    s2[i] = '\0';
    printf("s1 = %s;\ns2 = %s;\n\n",s1,s2);
    printf("9.7 - 9.10, 9.12;\n");
    char* words[] = {"alpha","beta","gamma"};
    int max = 0, min = STRING_MAX, index_max = 0, index_min = 0;
    for (i = 0; i < 3; ++i) {
        printf("%s,",words[i]);
        for (j = 0; words[i][j] != '\0'; ++j)
            ;
        printf(" size of string: %d(sizeof addr: %d), ",j,sizeof(words[i]));
        if (j > max) {
            max = j;
            index_max = i;
        }
        if (j < min) {
            min = j;
            index_min = i;
        }
        if (j % 2 == 0)
            printf("even;\n");
        else
            printf("odd;\n");
    }
    printf("min = %d, max = %d;\n\n",index_min,index_max);
    char *addr;
    addr = words[1];
    words[1] = words[2];
    words[2] = words[0];
    words[0] = addr;
    printf("a)Words after exchange, a = %s, b = %s, c = %s;\n",words[0],words[1],words[2]);
    string_exchange(&words[1],&words[0]);
    printf("b)Words after exchange, a = %s, b = %s, c = %s;\n\n",words[0],words[1],words[2]);
    k = 3;
    int help = 0;
    char letter[] = "people";
    printf("9.15, find k letter, k = %d\n",k);
    printf("word = %s;\nletter = %c;\n\n",letter,letter[k - 1]);
    printf("9.18, comparison of letters in a words;\n");
    char word_1[] = "Hello";
    char word_2[] = "People"; // must be more than 4 letters and even quantity
    printf("1) %s;\n2) %s;\n",word_1,word_2);
    help = string_length(word_2);
    if (word_1[0] == word_2[help - 1])
        printf("Yes they are the same(%c:%c).\n\n",word_1[0], word_2[help - 1]);
    else
        printf("No, they are different(%c:%c).\n\n",word_1[0], word_2[help - 1]);
    printf("9.21, output part of a word, chars 2,3,4;\n");
    printf("word = %s;\noutput = ",word_2);
    for (k = 1; k <= 3; ++k)
        printf("%c",word_2[k]);
    printf("\n\n9.22, print the first half of a word;\nword = %s;",word_2);
    help /= 2;
    word_2[help] = '\0';
    printf("%s",word_2);
    char color_1[] = "Green", color_2[] = "Black",color_3[] = "White";
    printf("\n\n9.24 - 9.30, word conversion, cut and copy: %s, %s, %s;\n",color_1,color_2,color_3);
    char string_1[STRING_MAX], string_2[STRING_MAX];
    string_clear(string_1,STRING_MAX);
    string_clear(string_2,STRING_MAX);
    string_copy_substr(color_2,string_1,1,1);
    string_copy_substr(color_3,string_2,2,3);
    string_concat(string_2,string_1);
    printf("%s\n",string_1);
    string_copy_substr(color_3,string_1,3,1);
    string_copy_substr(color_1,string_2,2,3);
    string_concat(string_2,string_1);
    printf("%s\n",string_1);
    printf("9.31 - 9.36,find and replace chars in words: %s, %s;\n",color_2, color_3);
    const char tab_replacment[] = "aAeEiIsS";
    for (i = 0; color_3[i] != '\0'; ++i)
        for (k = 0; tab_replacment[k] != '\0'; k += 2)
            if (color_3[i] == tab_replacment[k])
                color_3[i] = tab_replacment[k + 1];
    printf("%s\n", color_3);
    /*
    char even_string[] = {"Programmer"};
    printf("9.37 - 9.40, Replacing halves of a word with each other: %s;\n",even_string);
    string_swap(even_string);
    printf("a)%s\n\n",even_string);
    */
    char* colors[] = {"Red","Orange","Yellow","Blue","Brown"};
    printf("Task from Cefeiko(searching in array of strings, Color: Blue).\n");
    int r1 = 0;
    for (i = 0; i < 5 && r1 == 0; ++i) {
        printf("Color[%d] = %s; ",i,colors[i]);
        r1 = string_is_equal(colors[i],"Blue");
        if (r1 == 0)
            printf("Yes! Color Blue founded;\n");
        else if (r1 == -1)
            printf("No! Color Blue not founded;\n");
        else if (r1 == -2)
            printf("Error, one or both strings are empty;\n");
    }
    char string_3[] = "This is a simple string.";
    char a = 'T';
    printf("\n9.75-9.77, search for a character in a string;\n%s\n",string_3);
    printf("Index(%c) = %d;\n",a,string_char_find(string_3,a,0,1));
    printf("Index(%c) = %d;\n",a,string_char_find(string_3,a,1,1));
    a = '.';
    printf("Index(%c) = %d;\n",a,string_char_find(string_3,a,0,1));
    printf("Index(%c) = %d;\n\n",a,string_char_find(string_3,a,1,1));
    printf("9.78, palindrom, Yes(0),No(-1);\n%s;\n","abab");
    printf("(ab)%d;\n",string_palindrom("ab"));
    printf("(a)%d;\n",string_palindrom("a"));
    printf("(-11-)%d;\n",string_palindrom("-11-"));
    printf("()%d;\n",string_palindrom(""));
    printf("(aba)%d;\n",string_palindrom("aba"));
    printf("(  )%d;\n",string_palindrom("  "));
    a = 'T';
    printf("\n9.79, counter, find char = %c;\n%s\n",a,string_3);
    printf("%d\n",string_char_counter(string_3,a));
    printf("%d\n",string_char_counter(string_3,' '));
    char string_4[] = "adggfds";
    printf("\n9.80, search for a sequence of identical letters(%c) in a string;\n%s;\n",'g',string_4);
    printf("start = %c, length = %c;\n",'2','3');
    printf("%d;\n\n", string_find_seq(string_4,'g',2,3));
    char string_5[] = "abcda", string_6[] = "";
    printf("9.81, string comparison;\n1) %s;\n2) %s;\n", string_5, string_6);
    int result = string_is_equal(string_5,string_6);
    if (result == -1)
        printf("Strings different;\n\n");
    else if (result == 0)
        printf("Strings are equal;\n\n");
    else if (result > 0)
        printf("Strings partly equal: %d;\n\n",result);
    char string_7[] = "dsfabc";
    char string_8[] = "abc", string_9[] = "gda";;
    printf("9.86 - 9.87, search for a substring in a string;\n");
    printf("string = %s;\n",string_7);
    printf("substring = %s;\n",string_8);
    printf("%d;\n",string_find_sub(string_7,string_8));
    printf("Replace substring '%s' with substring '%s' in previous string\n",string_8, string_9);
    result = string_rep_sub(string_7,string_8,string_9,1);
    printf("quantity = %d, result string = %s;\n\n", result, string_7);
    char string_10[] = "color green red blue yellow,";
    printf("9.88, source string '%s', using comma;\n",string_10);
    int x = string_char_find( string_10, ',', 0, 0);
    if (x != -1) {
        int y = string_char_find( &string_10[x + 1], ',', 0, 0);
        if (y == -1)
            y = string_length(string_10);
        else
            y += x + 1;
        char string_11[STRING_MAX];
        string_copy_substr(string_10,string_11, x + 1, y - x - 1);
        printf("Source string first comma %d, second comma %d, word = %s;\n\n",x,y,string_11);
    } else
        printf("No comma found;\n\n");
    char c1 = 'r', c2 = 'y';
    if (string_char_find(string_10,c1,0,0) < string_char_find(string_10,c2,0,0))
        printf("9.89, First char %c, second char %c;\n",c1,c2);
    else
        printf("9.89, First char %c, second char %c;\n",c2,c1);
    printf("\nSpecial task;\n");
    char* string_special[] = {"123","796","60452","101001","32674","306973","2F4B","1C2AB"};
    unsigned int special_size = sizeof (string_special) / sizeof (char*);
    printf("Idx:\tSource:\tBase:\tDecimal:\n");
    for (unsigned int g = 0; g < special_size; ++g) {
        printf("%d)\t%s\t",g,string_special[g]);
        int num_sys = 0, sum = 0, str_len = string_length(string_special[g]);
        char numbers[] = "0123456789ABCDEF";
        int str_number[str_len];
        for (int j = 0; j < str_len; ++j)
            str_number[j] = -1;
        help = 1; max = 0;
        for (i = 0; string_special[g][i] != '\0'; ++i) {
            for (int k = 0; numbers[k] != '\0' && str_number[str_len - i - 1] == -1; ++k)
                if (numbers[k] == string_special[g][i]) {
                    str_number[str_len - i - 1] = k;
                    if (k > max)
                        max = k;
                }
        }
        if (max > 0 && max < string_length(numbers)) {
            num_sys = max + 1;
            printf("%d\t", num_sys);
            if (num_sys != 10) {
                for (int i = 0; i < str_len; ++i) {
                    if (i == 0)
                        sum += str_number[i];
                    else
                        sum += str_number[i] * help;
                    help *= num_sys;
                }
                printf("%d\n",sum);
            } else
                printf("Your number is already in decimal;\n");
        } else
            printf("You entered incorrect number!;\n");
    }
    printf("\nSpecial task 2;\n");
    char string_start[] = "1010101111101111";
    char string_end[STRING_MAX] = "\0";
    int start = 2, end = 10;
    printf("from %d to %d;\nSource string = %s;\n",start,end,string_start);
    result = num_radix(string_start,string_end,start,end);
    printf("Length = %d;\nNumber = %s\n\n",result,string_end);
    /*
        1101 = 13
        1011 = 11
        ----
       11000 = 24
*/
    unsigned char a1 = 157, a2 = 231;
    unsigned short int r = 0;
    printf("Size of char = %d, size of short int = %d;\n",sizeof (unsigned char),sizeof (unsigned short int));
    printf("Multiply numbers %d and %d, without operators '*' and '+'.\n",a1,a2);
    printf("a1:\t");
    print_binary_byte(a1);
    printf("\na2:\t");
    print_binary_byte(a2);
    printf("\n\t--------\n");
    int mask = 0x01;
    for (i = 0; i < CHAR_BIT; ++i, mask <<= 1) {
        unsigned char bit = a2 & mask;
        unsigned char carry_flag = 0x00;
        unsigned short int add = 0x0000;
        int mask_xor = 0x01;
        for (k = 0; k < CHAR_BIT - i; ++k)
            printf(" ");
        if (bit != 0) {
            add = (unsigned short int)(a1) << i;
            print_binary_byte(a1);
        } else
            print_binary_byte(0);
        for (j = 0, mask_xor = 0x01; j < WORD_BITS; ++j, mask_xor <<= 1) {
            unsigned short int bit_a = add & mask_xor, bit_r = r & mask_xor;
            r = r ^ bit_a ^ (unsigned short int)(carry_flag << j);
            carry_flag = ((bit_a != 0 && bit_r != 0) || (carry_flag != 0 && (bit_a != 0 || bit_r != 0)));
        }
        if (i != 0)
            printf("\t");
        printf(":result = ");
        print_binary_word(r);
        printf("\n");
    }
    printf("-----------------\n");
    print_binary_word(r);
    printf("\ndecimal = %d;\n",r);
    unsigned char number_1 = 0;
    int number_2 = 15;
    printf("number_1:= %d;\n",number_1);
    //add_byte(&number_1,number_2);
    printf("number_2:= %d;\nTotal = %d\n\n",number_2,number_1);
    printf("Truth table for logical gates:\n");
    printf("Bit A:\tBit B:\tNot A:\tAnd:\tOr:\tXor:\tNand:\n");
    for (i = 0; i <= 1; ++i) {
        for (j = 0; j <= 1; ++j) {
            printf("%d\t%d\t",i,j);
            printf("%d\t",not_gate(i));
            printf("%d\t",and_gate(i,j));
            printf("%d\t",or_gate(i,j));
            printf("%d\t",xor_gate(i,j));
            printf("%d\t\n",nand_gate(i,j));
        }
    }
    printf("\nMake bits table, size %d bytes;\n",sizeof (bits_nums));
    for (i = 0; i < BYTE_NUMS; ++i) {
        unsigned char n = i;
        for (j = 0; j < CHAR_BIT; ++j) {
            bits_nums[i][j] = n % 2;
            n /= 2;
        }
        //printf("%d: ",i);
        //for (k = CHAR_BIT - 1; k >= 0; --k)
        //printf("%d",bits_nums[i][k]);
        //printf("\n");
    }
    printf("Get and set registers from byte array:\n");
    unsigned char byte_a[CHAR_BIT], byte_b[CHAR_BIT];
    /*
    for (i = 0; i < BYTE_NUMS; ++i) {
        printf("%3d:",i);
        unsigned char num = (unsigned char)(i);
        set_register(&num,byte_a);
        for (j = CHAR_BIT - 1; j >= 0; --j)
            printf("%d",byte_a[j]);
        get_register(&num,byte_a);
        printf(":%3d\n",num);
    }
    */
    unsigned char bytes[] = {0xAA, 0xFF, 0x00, 0xAA, 0xCB, 0x13};
    printf("\nDebug logical operators and shifts:\n");
    printf("Bytes:\t1:\t\t2:\t\t3:\t\tZero and carry flags:\n");
    for (i = 0; i < 2; ++i) {
        if (i == 0)
            printf("Byte A:\t");
        else
            printf("Byte B:\t");
        for (j = 0; j < 3; ++j) {
            print_binary_byte(bytes[j * 2 + i]);
            printf("\t");
        }
        printf("\n");
    }
    char* operators[] = {"NOT","AND","OR","XOR","SHL","SHR"};
    unsigned char carry_flag = 0x00, zero_flag = 0x00, num = 0x00;
    for (i = 0; i < 6; ++i) {
        printf("%s:\t",operators[i]);
        for (j = 0; j < 3; j++) {
            set_register(&bytes[j * 2], byte_a);
            set_register(&bytes[j * 2 + 1], byte_b);
            switch (i) {
            case 0:
                zero_flag = not_logical(byte_a);
                break;
            case 1:
                zero_flag = and_logical(byte_a,byte_b);
                break;
            case 2:
                zero_flag = or_logical(byte_a,byte_b);
                break;
            case 3:
                zero_flag = xor_logical(byte_a,byte_b);
                break;
            case 4:
                carry_flag = shift_logical_left(byte_a,3);
                break;
            case 5:
                carry_flag = shift_logical_right(byte_a,2);
                break;
            default:
                printf("Error! Something went wrong!");
            }
            get_register(&num,byte_a);
            print_binary_byte(num);
            printf(":[%d:%d]\t",zero_flag,carry_flag);
        }
        printf("\n");
    }
    printf("\nTesting byte adder.\n");
    printf("Bytes:\t1:\t\t2:\t\t3:\t\tZero and carry flags:\n");
    for (i = 0; i < 2; ++i) {
        if (i == 0)
            printf("Byte A:\t");
        else
            printf("Byte B:\t");
        for (j = 0; j < 3; ++j) {
            print_binary_byte(bytes[j * 2 + i]);
            printf("(%d)\t",bytes[j * 2 + i]);
        }
        printf("\n");
    }
    printf("Result:\t");
    for (i = 0; i < 3; ++i) {
        set_register(&bytes[i * 2],byte_a);
        set_register(&bytes[i * 2 + 1],byte_b);
        carry_flag = add_byte(byte_a,byte_b);
        get_register(&num,byte_a);
        print_binary_byte(num);
        printf(":%d(%d)\t",carry_flag,num);
    }
    /*
    set_register(&number,mass_1);
    set_register(&number2,mass_2);
    for(i = CHAR_BIT - 1; i >= 0; --i)
        printf("%d",mass_1[i]);
    printf(" - %d\n",number);
    for(i = CHAR_BIT - 1; i >= 0; --i)
        printf("%d",mass_2[i]);
    printf(" - %d\n",number2);
    add_byte(mass_1,mass_2);
    for(i = CHAR_BIT - 1; i >= 0; --i)
        printf("%d",mass_1[i]);
    get_register(&number,mass_1);
    printf(" - %d\n",number);
    */
    printf("\nEnd of Special task.");
    char string[] = "This is text";
    printf("\n\n9.41 - 9.42, given a string, print it in a column and in reverse order;\n");
    printf("string = %s;\n",string);
    help = string_length(string);
    printf("reverse string = ");
    for (i = help - 1; i >= 0; --i)
        printf("%c",string[i]);
    printf("\nstring to column:\n");
    for (i = 0; i < help; ++i)
        printf("%c\n",string[i]);
    printf("\n9.43,The word was given. Get the word formed by the odd letters of the word.\n");
    printf("string = %s;\n",string);
    printf("Odd letters = ");
    for(i = 0; i < help; ++i)
        if (i % 2 != 0)
            printf("%c[%d] ",string[i],i);
    char letter_1 = 'A';
    int n = 5;
    char string2[STRING_MAX];
    printf("\n\n9.47 - 9.49, add a character and their number to a word, set parametrically;\n");
    for (i = 0; i < n; ++i)
        string2[i] = letter_1;
    for (j = 0; j < help; ++i, ++j)
        string2[i] = string[j];
    for (j = 0; j < n; ++i, ++j)
        string2[i] = letter_1;
    string2[i] = '\0';
    int b = 0;
    printf("string_result = %s;\n\n",string2);
    printf("9.50, Replacing characters, a = %d, b = %d, n = %d;\n",a,b,n);
    char mass_1[] = "0123456789";
    char mass_2[] = "0123456789";
    printf("word_1 = %s;\n",mass_1);
    printf("Was:\nword_2 = %s;\n",mass_2);
    int help_1 = string_length(mass_1);
    int help_2 = string_length(mass_2);
    if (b <= help_2 - n && a + b <= help_1 && help_1 > 0 && help_2 > 0)
        for (i = a; i < a + b; ++i, ++n)
            mass_2[n] = mass_1[i];
    else
        printf("error: length does not meet requirements;\n\n");
    printf("Became:\nword_2 = %s;\n\n",mass_2);
    printf("9.51 - 9.65, searching letters\n");
    char array[] = "ooorammggg"; //Pneumonoultramicroscopicsilicovolcanoconiosis
    char search_letters[] = "oma";
    int len_array = string_length(array);
    int len_letters = string_length(search_letters);
    int counters[len_letters], sum = 0, quantity = 0;
    n = 7; a = 2;
    for (i = 0; i < len_letters; ++i)
        counters[i] = 0;
    printf("string = %s;\n\n\t",array);
    for (i = 0; i < len_letters; ++i)
        printf("%c\t",search_letters[i]);
    printf("N(%d)\tSeq(%d).\n",n,a);
    for (i = 0; i < len_array; ++i) {
        printf("%c(%d):\t",array[i],i);
        for (j = 0; j < len_letters; ++j)
            if (array[i] == search_letters[j]) {
                printf("+\t");
                counters[j]++;
                sum++;
            } else
                printf("-\t");
        if (i % n == 0 )
            printf("YES\t");
        else
            printf("NO\t");
        for (k = 0; k < a && k + i < len_array && array[i] == array [i + k]; ++k)
            ;
        if (k == a) {
            printf("+");
            ++quantity;
        }
        printf("\n");
    }
    printf("Total:  ");
    for (j = 0; j < len_letters; ++j)
        printf("%d(%d/%d)\t",counters[j],counters[j],sum);
    printf("\nQuantity = %d;\n\n",quantity);
    n = 10; // ограничитель ширины строки.
    printf("9.66-9.74, line break by word, length = %d;\n",n);
    int is_word = 0, counter = 0, tab_size = 8; // флаг слова и счётчик столбцов.
    //char line[] = "\ta \tbc d efg \tggf   w\n";
    char line[] = "\ta \tbc d efg \tggf   w\tr"; //  several different models or storage classes for storing data in memory. To    understand the options it's helpful to go over a few concepts and terms first.
    printf("Source string = '%s';\n",line);
    printf("0123456789A:\n");
    quantity = 0;
    for (i = 0; line[i] != '\0'; ++i, ++counter) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
            if (is_word == 0) {
                for (j = 0; line[j + i] != ' ' && line[j + i] != '\t' &&
                     line[j + i] != '\n' && line[j + i] != '\0'; ++j)
                    ;
                if (j + counter > n) {
                    printf("\n");
                    counter = 0;
                }
            }
            if (!is_word) {
                ++quantity;
                is_word = 1;
            }
        } else {
            is_word = 0;
            if (line[i] == '\t') {
                help = counter + tab_size - (counter % tab_size);
                if (help > n && i != 0) {
                    printf("\n");
                    counter = tab_size - 1;
                } else
                    counter = help - 1;
            }
            if (line[i] == '\n')
                counter = 0;
        }
        printf("%c",line[i]);
    }
    /*
    for (i = 0; i <= help; ++i) {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\0') {
            if (counter <= n) {
                while (is_word < i)
                    printf("%c",line[is_word++]);
            } else if (counter > n && i - is_word <= n) {
                printf(":\n");
                counter -= n;
                while (is_word < i)
                    printf("%c",line[is_word++]);
            } else {
                counter -= (i - is_word);
                while (is_word < i) {
                    if (counter == n) {
                        printf("+\n");
                        counter = 0;
                    }
                    printf("%c",line[is_word++]);
                    counter++;
                }
            }
            if (line[i] == '\t') {
                counter += tab_size - (counter % tab_size);
                printf("!%d", counter);
            } else if (line[i] == '\n') {
                printf("*%d",counter);
                counter = 0;
            } else if (line[i] == ' ')
                counter++;
            if (counter > n) {
                printf("#%d\n",counter);
                if (line[is_word] == '\t')
                    counter = tab_size;
                else
                    counter = 1;    // Если что это учёт последнего символа!
            }
            if (line[i] != '\0') {
                printf("%c",line[is_word]);
                if (line[is_word] == '\t' && n <= tab_size){
                    printf("@\n");
                    counter = 0;
                }
                is_word++;
            } else {
                printf("[EOF]\n");
            }
        } else
            counter++;
    }
    */
    printf("\nWords = %d;\n\n",quantity);
    char pairs_string[] = "txel";
    char line_1[] = "ee hta tet tt";
    printf("9.90-9.91, replace all characters specified in pairs;\n");
    printf("Pairs of replace: '%s'\n",pairs_string);
    printf("was = '%s'\n",line_1);
    if (string_length(pairs_string) % 2 == 0) {
        for (j = 0; pairs_string[j] != '\0'; j += 2)
            while ((b = string_char_find(line_1,pairs_string[j],0,0)) != -1)
                line_1[b] = pairs_string[j + 1];
        printf("became = '%s'\n\n",line_1);
    } else
        printf("Array of replace table not even!\n\n");
    char line_3[] = "Text po dlinee, long text.";
    b = string_length(line_3);
    char interval[] = {'a',3,'c',2,'f',5,'\0'};
    printf("9.92 - 9.93, replace chars on intervals in string\n");
    printf("source string = '%s', length = %d\n",line_3,b);
    printf("chars and intervals: ");
    for (i = 0; interval[i] != '\0'; i += 2)
        printf("%c:%d ",interval[i], interval[i + 1]);
    printf("\n");
    for (i = 0; interval[i] != '\0'; i += 2)
        for (j = 0; j < b; j += interval[i + 1])
            line_3[j] = interval[i];
    printf("result string = '%s';\n\n",line_3);
    printf("9.94-9.99, substring replacement;\n");
    char line_2[] = "is This is simple textThis";
    char* words_1[] = {"This","Blue","text","word","is","IS"};
    int value_size = (sizeof (words_1) / sizeof (char*)) / 2;
    printf("sourc string = '%s', words to replace: %d\n",line_2,value_size);
    for (i = 0, is_word = 1; i < value_size; ++i) {
        if (string_length(words_1[i * 2]) != string_length(words_1[i * 2 + 1]))
            is_word = 0;
        printf("'%s':'%s' ",words_1[i * 2],words_1[i * 2 + 1]);
    }
    if (is_word == 1) {
        for (i = 0; i < value_size; ++i) {
            help = string_length(words_1[i * 2]);
            while((b = string_find_sub(line_2,words_1[i * 2])) != -1)
                for (j = 0; j < help; ++j)
                    line_2[j + b] = words_1[i * 2 + 1][j];
        }
        printf("\nresult string = '%s'\n\n",line_2);
    } else
        printf("Error: pairs is not match;\n\n");
    char src[] = "123456";
    int table[] = {0,5,1,4,2,3};
    b = (sizeof (table) / sizeof (int)) / 2;
    printf("9.100 - 9.102, swap characters in a string, count = %d;\n",b);
    printf("replace table: ");
    for (i = 0; i < b * 2; ++i)
        printf("%d ",table[i]);
    printf("\nsource string = '%s'\n",src);
    n = string_xchg_chars(src,table,b);
    printf("result string = '%s'\nresult = %d;\n\n",src,n);
    printf("9.103-107, replace chars in text with generators.\n");
    n = 4; // generators
    int b1 = 2, b2 = 10;
    srand(time(NULL));
    char src_1[STRING_MAX];
    int tab_rep[STRING_MAX * 2];
    for (k = 0; k < n; ++k) {
        for (j = 0; j < 15; ++j)
            src_1[j] = 'a' + rand() % 26;
        src_1[15] = '\0';
        switch (k) {
        case 0:
            printf("gen = %d;\nexchange chars in pairs\n",k);
            for (i = 0; i < 15; ++i)
                tab_rep[i] = i;
            counter = 7;
            break;
        case 1:
            printf("gen = %d;\nreverse string\n",k);
            for (i = 0, j = 14; i < j; ++i, --j) {
                tab_rep[i * 2] = i;
                tab_rep[i * 2 + 1] = j;
            }
            counter = 7;
            break;
        case 2:
            printf("gen = %d;\nreverse string from %d to %d\n",k,b1,b2);
            int l = 0;
            for (i = b1 + 1, j = b2 - 1; i < j; ++i, --j, l++) {
                tab_rep[l * 2] = i;
                tab_rep[l * 2 + 1] = j;
            }
            counter = l;
            break;
        case 3:
            printf("gen = %d;\nexchange first 'a' and last 'o'\n",k);
            tab_rep[0] = string_char_find(src_1,'a',0,0);
            tab_rep[1] = string_char_find(src_1,'o',1,0);
            counter = 1;
            break;
        default:
            printf("gen out of range;\n");
        }
        printf("source string = '%s'\n",src_1);
        printf("table replace: ");
        for (i = 0; i < counter; ++i)
            printf("%d:%d ",tab_rep[i * 2],tab_rep[i * 2 + 1]);
        printf("\n");
        b = string_xchg_chars(src_1,tab_rep,counter);
        if (b == 0)
            printf("result string = '%s'\n",src_1);
        else
            printf("error: in generator.\n");
        printf("9.114, removing duplicate letters;\n");
        int length = 40; quantity = 0;
        char src_4[STRING_MAX];
        for (j = 0; j < length; ++j)
            src_4[j] = 'a' + rand() % 26;
        src_4[j] = '\0';
        printf("source string: '%s' %d\n",src_4, string_length(src_4));
        printf("indexes to delete: ");
        for (i = 0; i < length - 1; ++i)
            while ((k = string_char_find(&src_4[i + 1],src_4[i],0,0)) != -1) {
                string_delete(&src_4[i + 1],k,1);
                ++quantity;
                printf("%d ",i + 1 + k);
            }
        printf("\nstring: '%s' %d\nquantity = %d;\n\n",src_4,string_length(src_4),quantity);
        char src_5[STRING_MAX] = "acbdefgh!";
        char word_ins[] = "";
        start = 9;
        printf("string to insert: '%s', '%s', %d\n",src_5,word_ins,start);
        string_insert(src_5,word_ins,start,STRING_MAX);
        printf("result string: '%s';",src_5);
        printf("9.124-9.137, error correction;\n");
        char src_6[] = "JreeH black reT Grobn GRue oPiHE";
        char* vocabulary[] = {"black","brown","olive","green","red","blue"};
        int voc_size = sizeof (vocabulary) / sizeof (char*);
        double correct = 0.5;
        is_word = 0;
        len_array = string_length(src_6);
        printf("source string: '%s', correct = %.2f;\nvocabulary:",src_6,correct);
        for (i = 0; i < voc_size; ++i)
            printf(" %s",vocabulary[i]);
        printf(";\nIndex:\tWord:\tEqual(%%):\tFound:\tCorrected:\n");
        for (i = 0; i < len_array; ++i) {
            if (src_6[i] != ' ' && is_word == 0) {
                char word[STRING_MAX];
                int end = i, voc_pos = -1;
                while (src_6[end] != ' ' && src_6[end] != '\0')
                    ++end;
                double actual = 0.0, current = 0.0;
                string_copy_substr(src_6, word, i, end - i);
                for (j = 0; j < voc_size; ++j) {
                    quantity = 0;
                    for (k = 0; vocabulary[j][k] != '\0'; ++k)
                        if (vocabulary[j][k] == word[k])
                            ++quantity;
                    current = (double)(quantity) / (double)(end - i);
                    if (current > actual) {
                        voc_pos = j;
                        actual = current;
                    }
                }
                printf("%d:\t\t%s:\t%.2f:\t",i,word,actual);
                if (actual < 1 && actual >= correct) {
                    printf("%s:\treplaced\n",vocabulary[voc_pos]);
                    string_rep_sub(src_6, word, vocabulary[voc_pos],1);
                } else if (actual < current)
                    printf("Not found.\n");
                else
                    printf("Word correct.\n");
                is_word = 1;
            }
            if (src_6[i] == ' ')
                is_word = 0;
        }
        printf("result string: '%s';\n\n",src_6);
        counter = 10;
        n = 1;
        printf("9.124-9.137, line shift, counter = %d, type = %d;\n",counter,n);
        char src_7[] = "Hello";
        printf("source string = '%s'\n",src_7);
        if (n == 0)
            string_rrc(src_7,counter);
        else
            string_rlc(src_7,counter);
        printf("result string: '%s';\n\n",src_7);
        printf("9.138-9.141, string to digits;\n");
        quantity = 0;
        int max_digit = 0;
        sum = 0;
        char src_8[] = "5A3B1C02z";
        printf("source string: '%s';\n",src_8);
        printf("Char:\tIsDigit:\tDigit:\n");
        for (i = 0; src_8[i] != '\0'; ++i) { //48 57
            if (src_8[i] >= '0' && src_8[i] <= '9') {
                int digit = src_8[i] - '0';
                ++quantity;
                sum += digit;
                if (digit > max_digit)
                    max_digit = digit;
                printf("%c:\tYES:\t\t%d:\n",src_8[i],digit);
            } else
                printf("%c:\tNO:\t\t-\n",src_8[i]);
        }
        printf("Sum = %d;\nQuantity = %d;\nMax digit = %d;\n\n",sum,quantity,max_digit);
    }
    char* nums_ints[] = {"bin: +10210", "bin: 5-100101017",
                         "oct: R0274AY", "oct: 89-81",
                         "dec: AB9-8F", "3dec: 40+1FA5",
                         "hex: 07F35H-S", "-hex: F"};
    int nums_base[] = {2,2,8,8,10,10,16,16};
    int nums_total = sizeof (nums_base) / sizeof (int);
    printf("9.142 - 9.144, convert strings to integers and reverse, nums = %d;\n",nums_total);
    printf("String:\t\tLength:\tBase:\tNumber:\tString[Length]:\n");
    for (i = 0; i < nums_total; ++i) {
        char num_str[STRING_MAX];
        int str_ln = string_length(nums_ints[i]);
        result = string_to_int(nums_ints[i], nums_base[i]);
        printf("'%s'\t",nums_ints[i]);
        if (str_ln < tab_size - 2) // не забыть учесть кавычки.
            printf("\t");
        printf("%d\t%d\t%d\t",str_ln, nums_base[i],result);
        int_to_string(num_str,result,nums_base[i]);
        printf("'%s'[%d]\n",num_str,string_length(num_str));
    }
    char src_11[] = "1-2+3+15-7+309-216";
    printf("\n\n9.147, calculate string %s;\n",src_11);
    sum = 0;
    printf("integers from text: ");
    for (i = 0; src_11[i] != '\0'; i = j) {
        char num[STRING_MAX];
        j = i + 1;
        while (src_11[j] != '+' && src_11[j] != '-' && src_11[j] != '\0')
            ++j;
        string_copy_substr(src_11, num, i, j - i);
        k = string_to_int(num,10);
        sum += k;
        printf("%d[%d] ",k, sum);
    }
    printf("\nsum = %d;\n\n",sum);
    char text[] = "qqqqqqqqqqwertyppasdfghjjjkkllzxcvbmmmnn";
    printf("9.152-9.153, find longest seq of char in text: '%s'\n",text);
    quantity = 1;
    max = 0;
    j = -1;
    for (i = 0; text[i] != '\0'; ++i) {
        while (text[i] == text[i + 1]) {
            quantity++;
            i++;
        }
        if (max < quantity) {
            j = i;
            max = quantity;
        }
        quantity = 1;
    }
    printf("max seq = %d, char = '%c'\n\n",max,text[j]);
    char src_12[] = "ammferetftu";
    quantity = 0;
    printf("9.154-9.155, search for unique letters;\nsource string = '%s'\nunique: ",src_12);
    for (i = 0; src_12[i] != '\0'; ++i) {
        for (j = 0; src_12[j] != '\0'; ++j)
            if (src_12[i] == src_12[j] && i != j)
                break;
        if (src_12[j] == '\0') {
            printf("%c ",src_12[i]);
            ++quantity;
        }
    }
    printf("\nquantity = %d;\n\n",quantity);
    char* words_2[] = {"green","red"};
    printf("9.156-9.159, search for similar letters;\n");
    printf("word_1: %s\nword_2: %s\n",words_2[0],words_2[1]);
    for (i = 0; i < 2; ++i) {
        int unique = 0, diffs = 0, ix;
        printf("Compare chars in %d word and %d word: \n",i,(i + 1) % 2);
        for (j = 0; words_2[i][j] != '\0'; ++j) {
            k = string_char_find(words_2[(i + 1) % 2],words_2[i][j],0,0);
            for (ix = 0; ix < j && words_2[i][ix] != words_2[i][j]; ++ix)
                ;
            if (k == -1) {
                if (ix == j) {
                    printf("'%c': unique ",words_2[i][j]);
                    ++unique;
                }
            } else
                if (ix == j) {
                    printf("'%c': not unique ",words_2[i][j]);
                    ++diffs;
                }
        }
        printf("Total: unique = %d\ndiffs = %d\n",unique,diffs);
    }
    printf("\n9.160, build word from chars of other word;\n");
    char* word_pairs[] = { "blue", "cyan", "magenta", "tag", "red", "deer", "a", "aa"};
    value_size = sizeof (word_pairs) / sizeof (char*);
    int strict, not_strict;
    for (i = 0; i < value_size; i += 2) {
        strict = 1; not_strict = 1;
        printf("'%s':'%s'\n",word_pairs[i], word_pairs[i + 1]);
        for (j = 0; word_pairs[i + 1][j] != '\0'; ++j) {
            if (string_char_find(word_pairs[i], word_pairs[i + 1][j],0,0) != -1) {
                quantity = string_char_counter(word_pairs[i],word_pairs[i + 1][j]); // В каком ищем.
                counter = string_char_counter(word_pairs[i + 1],word_pairs[i + 1][j]); // Какое ищем.
                printf("%c(%d)(%d): ",word_pairs[i + 1][j],quantity,counter);
                if (counter > quantity)
                    strict = 0;
            } else {
                strict = 0;
                not_strict = 0;
            }
        }
        if (strict == 1)
            printf("strict compliance;\n");
        else if (not_strict == 1)
            printf("not strict compliance;\n");
        else
            printf("no matches;\n");
    }
    char src_9[] = "Red blue green     white  black  brown      yellow magenta";
    printf("\n9.164, working with words from string;\nsource string = '%s'\n",src_9);
    char wrd_colors[STRING_MAX][STRING_MAX];
    int colors_total;
    colors_total = string_to_words(src_9,wrd_colors);
    for (i = 0; i < colors_total; ++i)
        printf("'%s'\n",wrd_colors[i]);
    printf("\n9.171-9.179, working with word strings;\n");
    int idx = 0; int idx_min = 0; int idx_max = 0; min = STRING_MAX; max = 0;
    int wrd_indexes[colors_total]; int unique = 0; int wrd_length[colors_total];
    printf("string[idx]:\tlength:\tunique:\tsymmet:\n");
    for (i = 0; i < colors_total; ++i) {
        wrd_indexes[i] = i;
        unique = 1;
        idx = 1;
        wrd_length[i] = string_length(wrd_colors[i]);
        if (wrd_length[i] < min) {
            min = wrd_length[i];
            idx_min = i;
        }
        if (wrd_length[i] > max) {
            max = wrd_length[i];
            idx_max = i;
        }
        for (j = 0; j < colors_total && (unique != 0 || idx == 1); ++j)
            if (j != i) {
                result = string_is_equal(wrd_colors[i], wrd_colors[j]);
                help = string_is_symmetrical(wrd_colors[i]);
                if (help == 0)
                    idx = 0;
                if (result == 0)
                    unique = 0;
            }
        printf("'%s'[%d]\tlen: %d\t",wrd_colors[i],i,wrd_length[i]);
        if (unique == 1)
            printf(" YES\t");
        else
            printf(" NO\t");
        if (idx == 1)
            printf(" YES\n");
        else
            printf(" NO\n");
    }
    printf("biggest: '%s'[%d], len = %d;\n",wrd_colors[idx_max],idx_max,max);
    printf("smallest: '%s'[%d], len = %d;\n",wrd_colors[idx_min],idx_min,min);
    for (i = 1; i < colors_total; ++i)
        for (j = i; j > 0; --j) {
            if (string_length(wrd_colors[wrd_indexes[j]]) < string_length(wrd_colors[wrd_indexes[j - 1]])) {
                help = wrd_indexes[j - 1];
                wrd_indexes[j - 1] = wrd_indexes[j];
                wrd_indexes[j] = help;
            }
        }
    printf("buble sort, ascending;\n");
    for (i = 0; i < colors_total; ++i)
        printf("'%s'\n",wrd_colors[wrd_indexes[i]]);
    printf("insertion sort, descending\n");
    int wrd_sort[STRING_MAX];
    printf("Word:\tInsert:\tArray:\n");
    for (i = 0; i < colors_total; ++i) {
        for (j = 0; j < i; ++j) {
            if (wrd_length[i] >= wrd_length[wrd_sort[j]])
                break;
        }
        for (k = i; k != j; --k)
            wrd_sort[k] = wrd_sort[k - 1];
        wrd_sort[j] = i;
        printf("%d\t%d\t",wrd_indexes[i],j);
        for (k = 0; k <= i; ++k)
            printf("%d ",wrd_sort[k]);
        printf("\n");
    }
    for (i = 0; i < colors_total; ++i)
        printf("'%s'\n",wrd_colors[wrd_sort[i]]);
    char src_search[] = "red";
    printf("\n9.165-9.167, permutation of words in a line;\n");
    printf("source string: \n");
    for (i = 0; i < colors_total; ++i)
        printf("'%s' ",wrd_colors[i]);
    printf("\n");
    char* wrd_addr[colors_total];
    for (i = 0; i < 3; ++i) {
        switch (i) {
        case 0:
            printf("9.165, reverse string\n");
            for (k = 0; k < colors_total; ++k)
                wrd_addr[k] = wrd_colors[colors_total - k - 1];
            break;
        case 1:
            printf("9.166, exchange first and last word\n");
            for (k = 1; k < colors_total - 1; ++k)
                wrd_addr[k] = wrd_colors[k];
            wrd_addr[0] = wrd_colors[colors_total - 1];
            wrd_addr[colors_total - 1] = wrd_colors[0];
            k = colors_total;
            break;
        case 2:
            printf("9.167, all words except = '%s'\n",src_search);
            for (j = 0, k = 0; j < colors_total; ++j) {
                result = string_is_equal(wrd_colors[j],src_search);
                if (result != 0 && result != -2)
                    wrd_addr[k++] = wrd_colors[j];
            }
            break;
        default:
            printf("error: wrong parametr\n");
        }
        for (j = 0; j < k; ++j)
            printf("'%s' ",wrd_addr[j]);
        printf("\n");
    }
    char src_14[] = "green grey blue black alpha wow magenta yellow win";
    char wrd_text[STRING_MAX][STRING_MAX];
    counter = string_to_words(src_14,wrd_text);
    char rules[] = "SgEnBaBwMa1Ll2Qe1";
    printf("9.168-9.169, searching words, using rules\n");
    printf("Format, command and data. 'S' - start char: char, 'E' - end char: char, "
           "'B' - both start and end char: char, 'M' - more than chars: char + digit, "
           "'L' - less than chars: char + digit, 'Q' - equal chars: char + digit.\n");
    printf("source string: '%s'\nwords = %d:",src_14,counter);
    for (i = 0; i < counter; ++i)
        printf("'%s' ",wrd_text[i]);
    printf("\n");
    printf("Index:\tRule:\tWords:\n");
    int length;
    for (i = 0; rules[i] != '\0'; i += k) {
        printf("%d\t%c:%c", i, rules[i], rules[i + 1]);
        if (rules[i] == 'M' || rules[i] == 'Q' || rules[i] == 'L')
            printf(":%d", rules[i + 2] - '0');
        printf("\t");
        for (j = 0; j < counter; ++j) {
            switch (rules[i]) {
            case 'S':
                if (wrd_text[j][0] == rules[i + 1])
                    printf("%s ",wrd_text[j]);
                k = 2;
                break;
            case 'B':
                length = string_length(wrd_text[j]);
                if (wrd_text[j][0] == rules[i + 1] && wrd_text[j][length - 1] == rules[i + 1])
                    printf("%s ",wrd_text[j]);
                k = 2;
                break;
            case 'E':
                length = string_length(wrd_text[j]);
                if (wrd_text[j][length - 1] == rules[i + 1])
                    printf("%s ",wrd_text[j]);
                k = 2;
                break;
            case 'L':
                quantity = string_char_counter(wrd_text[j],rules[i + 1]);
                if (quantity < rules[i + 2] - '0')
                    printf("%s ",wrd_text[j]);
                k = 3;
                break;
            case 'M':
                quantity = string_char_counter(wrd_text[j],rules[i + 1]);
                if (quantity > rules[i + 2] - '0')
                    printf("%s ",wrd_text[j]);
                k = 3;
                break;
            case 'Q':
                quantity = string_char_counter(wrd_text[j],rules[i + 1]);
                if (quantity == rules[i + 2] - '0')
                    printf("%s ",wrd_text[j]);
                k = 3;
                break;
            default:
                k = 1;
                printf("?");
            }
        }
        printf("\n");
    }
    char src_10[] = "yellow red white purple";
    char wrd_colors_2[STRING_MAX][STRING_MAX];
    int colors_total_2 = string_to_words(src_10,wrd_colors_2);
    printf("\n9.180 - 9.183, searching words in strings\n");
    printf("\nFirst string: '%s'\n",src_9);
    printf("string:\tunique:\tonce in both strings:\n");
    for (i = 0; i < colors_total; ++i) {
        quantity = 0; counter = 0;

        printf("%s",wrd_colors[i]);
        if (string_length(wrd_colors[i]) < 8)
            printf("\t");
        for (k = 0; k < colors_total; ++k)
            if (string_is_equal(wrd_colors[i],wrd_colors[k]) == 0)
                counter++;
        for (k = i - 1; k >= 0 && string_is_equal(wrd_colors[i],wrd_colors[k]) != 0; --k)
            ; //  отслеживаем уникальные.
        if (k == -1) {
            for (j = 0; j < colors_total_2; ++j)
                if (string_is_equal(wrd_colors[i],wrd_colors_2[j]) == 0)
                    quantity++;
            if (quantity > 0)
                printf(" NO\t\t");
            else
                printf(" YES\t\t");
        } else
            printf("recurr.\t\t");
        if (counter == quantity && counter == 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    printf("Second string: '%s'\n",src_10);
    printf("string:\tunique:\n");
    for (i = 0; i < colors_total_2; ++i) {
        printf("%s:\t",wrd_colors_2[i]);
        for (j = 0; j < colors_total && string_is_equal(wrd_colors_2[i],wrd_colors[j]) != 0; ++j)
            ;
        if (j != colors_total)
            printf(" NO\n");
        else
            printf(" YES\n");
    }
    n = 15; // ограничитель ширины строки.
    printf("\n9.186, formating text, width = %d\n",n);
    char src_15[STRING_MAX] = "\na b \n cab   de s\n\n  \nf\n";
    char words_line[STRING_MAX];
    printf("Source string:\n'");
    for (i = 0; src_15[i] != '\0'; ++i) {
        if (src_15[i] == '\n')
            printf("(n)");
        else
            printf("%c",src_15[i]);
    }
    printf("'\n");
    printf("0123456789ABCDEF:\n");
    int mode = 4; //(left edge - 1; centered - 2; right edge - 3; in width - 4)
    for (i = 0; src_15[i] != '\0'; i = k) {
        int words_length = 0;
        for (j = i + 1, k = i; src_15[k] != '\n' && src_15[k] != '\0' && words_length + (j - k) <= n; ++j) {
            if (src_15[k] == ' ')
                k = j;
            if ((k < j) && (src_15[j] == ' ' || src_15[j] == '\n' || src_15[j] == '\0')) {
                string_copy_substr(src_15, &words_line[words_length], k, j - k + 1);
                words_length += j - k + 1;
                k = j;
                words_line[words_length] = '\0';
                //printf("j = %d, k = %d, length = %d, '%s'\n", j, k, words_length, words_line);
            }
        }
        if (words_length == 0) {
            for (;words_length < n && src_15[k] != '\n' && src_15[k] != '\0'; ++words_length)
                words_line[words_length] = src_15[k++];
            if (src_15[k] == '\n')
                ++k;
            words_line[words_length] = '\0';
        } else {
            if (words_line[k] == '\n') {
                words_length -= 2;          // extra paragraph
                words_line[words_length] = '\0';
            } else
                words_line[--words_length] = '\0';      // remove separator
        }
        switch (mode) {
        case 1:
            break;
        case 2:
            for (j = 0; string_length(words_line) < n; ++j) {
                if (j % 2 == 0)
                    string_insert(words_line," ",0,STRING_MAX);
                else
                    string_insert(words_line," ",string_length(words_line),STRING_MAX);
            }
            break;
        case 3:
            length = n - string_length(words_line);
            for (j = 0; j < length; ++j)
                string_insert(words_line," ",0,STRING_MAX);
            break;
        case 4: {
            int sp = 0, sp_idx[STRING_MAX], spaces = 0, offset;
            while ((offset = string_char_find(&words_line[sp],' ',0,0)) != -1) {
                sp_idx[spaces++] = sp + offset;
                sp += offset + 1;
            }
            for (int l = 0; words_length < n && spaces > 0; l = ((l + 1) % spaces)) {
                string_insert(words_line, " ", sp_idx[l], STRING_MAX);
                words_length++;
                for (int m = l + 1; m < spaces; ++m)
                    sp_idx[m]++;
            }
            break;
        }
        default:
            printf("error: wrong mode parametr\n");
        }
        printf("%s\n",words_line);
    }
    char src_13[] = "!(1 | 0) & (!(0 ^ 1))";
    //char src_13[] = "!(!1 ^ 0) & (0 ^ 1 | 1) & 0";
    result = string_checking_brackets(src_13);
    if (result > 0) {
        printf("source string:\n'%s'\n",src_13);
        printf("result = %c\n\n",boolean_calculator(src_13));
    } else
        printf("You entered incorrect string, error at: %d\n\n", result * -1);
}
