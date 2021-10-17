#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#define IN 1 /* внутри слова */
#define OUT 0 /* снаружи слова */
#define MAXLINE 1000

// Решение задач из книги "Язык программирования Си" (Деннис Ритчи, Брайан Керниган)

int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    /*
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    */
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

float celsius_in_fahr(int celsius)
{
    return (celsius * 5.0 / 9.0) + 32.0;
}

void detab(char source[], int tab)
{
    char line[MAXLINE];
    int i = 0, j = 0, k = 0, counter = 0;
    for (i = 0; source[i] != '\0'; ++i) {
        if (source[i] == '\t') {
            for (j = 1; j <= i; j += tab)
                ;
            for (k = i; k < j - 1; ++k)
                line[counter++] = ' ';
        } else
            line[counter++] = source[i];
    }
    line[counter] = '\0';
    copy(source,line);
    source[counter] = '\0';
}

void entab(char source[], int tab)
{
    char line[MAXLINE];
    int i = 0, j = 0, counter = 1;
    for (i = 0; source[i] != '\0'; ++i, ++counter)
        if (counter % tab == 0) {
            line[j++] = '\t';
            counter = 0;
        }
    for (;counter > 0; --counter)
        line[j++] = ' ';
    line[--j] = '\0';
    copy(source,line);
    source[j] = '\0';
}

void carryover(char source[], int limit)
{
    char line[MAXLINE];
    int i = 0, j = 0, lim = 1, counter = 0;
    for (i = 0; source[i] != '\0'; ++i) {
        if (source[i] == '\t') {
            for (j = lim; j % 8 != 0; ++j, ++lim)
                ;
        }
        if (lim > limit || source[i] == '\n') {
            line[counter++] = '\n';
            if (source[i] != '\t')
                lim = 0;
            else
                lim = 8;
        }
        line[counter++] = source[i];
        lim++;
    }
    line[counter] = '\0';
    copy(source,line);
    source[counter] = '\0';
}

void KernighanRitchie_1()
{
    printf("1.1 - 1.2;\n");
    printf("hello, world!\n");
    printf("\n1.3;\nFahrenheit:\tCelsius:\n");
    float fahr, celsius;
    int lower, upper, step;
    lower = 0;   // нижняя граница температур в таблице
    upper = 100; // верхняя граница
    step = 20;   // величина шага
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%6.0f %15.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    printf("\n1.4;\nCelsius:\tFahrenheit:\n");
    lower = 0;
    upper = 100;
    step = 20;
    celsius = lower;
    while (celsius <= upper) {
        fahr = (celsius * 5/9) + 32;
        printf("%6.0f %15.1f\n", celsius, fahr);
        celsius += step;
    }
    printf("\n1.5;\nFahrenheit:\tCelsius:\n");
    for (fahr = 100; fahr >= 0; fahr -= 20)
        printf("%6.0f %15.1f\n", fahr, (5.0/9.0)*(fahr-32));
    printf("\n1.6;\n");
    printf("result = %d;\n", getchar() != EOF);
    printf("\n1.7;\n");
    printf("EOF = %d\n", EOF);
    printf("\n1.8;\n");
    int c = 0, counter = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n' || c == '\t' || c == ' ')
            ++counter;
    printf("counter = %d\n", counter);
    printf("\n1.9;\n");
    int flag = 0;
    while ((c = getchar()) != EOF) {
        if (flag == 0 || c != ' ')
            putchar(c);
        if (c == ' ')
            flag = 1;
        else
            flag = 0;
    }
    printf("\n\n1.10;\n");
    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\");
        else
            putchar(c);
    }
    printf("\n\n1.11;\n");
    //w\nww\twn\t\tw\nw\tn
    //\nwwwwwwwwwwwwww\n
    //\n\n\nw\t\t\t
    int nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' '|| c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc) ;
    printf("\n\n1.12;\n");
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\n' || c == '\t')
            putchar('\n');
        else
            putchar(c);
    printf("\n\n1.13;\n");
    int i, j, max = 0;
    int ndigit[10];
    counter = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\n' || c == '\t') {
            ++ndigit[counter];
            if (ndigit[counter] > max)
                ++max;
            counter = 0;
        } else
            ++counter;
    for (i = max; i > 0; --i) {
        for (j = 1; j < 10; ++j)
            if (ndigit[j] >= i)
                printf("| ");
            else
                printf("  ");
        printf("\n");
    }
    for (i = 1; i < 10; ++i)
        printf("%d ", i);
    printf("\n\n1.14;\n");
    counter = 0;
    int other = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    for (i = 0; (c = getchar()) != EOF; ++i) {
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0'];
        else
            ++other;
    }
    if (i != 0) {
        printf("i = %d\n",i);
        for (j = 0; j < 10; ++j)
            printf("%d: 1:%d;\n", j, i / ndigit[j]);
        printf("other: 1:%d;\n", i / other);
    }
    printf("\n1.15;\nCelsius:\tFahrenheit:\n");
    lower = 0;
    upper = 100;
    step = 20;
    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius_in_fahr(celsius);
        printf("%6.0f %15.1f\n", celsius, fahr);
        celsius += step;
    }
    printf("\n1.16;\n");
    int len, total = 0;
    max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    while ((len = getline(line, MAXLINE)) > 0) {
        total += len;
        if (len != MAXLINE - 1)
            if (total > max) {
                max = total;
                copy(longest,line);
                total = 0;
            }
    }
    if (max > 0)
        printf("max = %d, '%s'", max, longest);
    printf("\n\n1.17;\n");
    len = 10; //от какой длинны выводить.
    while ((c = getline(line, len)) > 0) {
        printf("!%d!",c);
        if (c == len) {
            printf("%s", line);
            flag = 1;
        } else if (flag == 1) {
            printf("%s", line);
            if (line[c - 1] == '\n')
                flag = 0;
        }
    }
    printf("\n\n1.18\n");
    flag = 0;
    char line_2[MAXLINE];
    counter = 0;
    while ((c = getline(line, len)) > 0) {
        counter = 0;
        if (c > 1) {
            for (i = 0; i < c; ++i) {
                if (line[i] != '\t' && line[i] != ' ') {
                    line_2[counter++] = line[i];
                    flag = 0;
                } else if (flag == 0) {
                    line_2[counter++] = ' ';
                    flag = 1;
                }
            }
            for (i = 0; i < counter; ++i)
                printf("%c", line_2[i]);
        }
    }
    printf("\n\n1.19;\n");
    while ((len = getline(line, MAXLINE)) > 0) {
        //string_reverse(line);
        printf("%s\n",line);
    }
    printf("\n1.20;\n");
    while ((c = getline(line, MAXLINE)) > 0) {
        detab(line,8);
        for (i = 0; line[i] != '\0'; ++i)
            printf("'%c'; ", line[i]);
        printf("\n");
    }
    printf("\n1.21\n");
    while ((c = getline(line, MAXLINE)) > 0) {
        entab(line,8);
        for (i = 0; line[i] != '\0'; ++i)
            if (line[i] != '\t')
                printf("'%c'; ", line[i]);
            else
                printf("'\\t'; ");
        printf("\n");
    }
    printf("\n1.22\n");
    while ((c = getline(line, MAXLINE)) > 0) {
        carryover(line,10);
        printf("0123456789ABCDEF:\n");
        for (i = 0; line[i] != '\0'; ++i)
            printf("%c", line[i]);
        printf("\n");
    }
}

int htoi(char s[])
{
    int i = 0, j = 0, result = 0;
    for (i = 0; s[i] != '\0' && s[j] != '\0';) {
        for (j = i; s[j] != '0' && s[j] != '\0'; ++j)
            ;
        if (s[++j] == 'x' || s[++j] == 'X')
            break;
        else
            i = j;
    }
    for (i = j; s[i + 1] != '\0'; ++i)
        ;
    int length = i;
    while (i > j) {
        if (s[i] >= '0' && s[i] <= '9')
            result += (s[i] - '0') * pow(16,length - i);
        else if (s[i] >= 'A' && s[i] <= 'F')
            result += (s[i] - 'A' + 10) * pow(16,length - i);
        else
            break;
        --i;
    }
    return result;
}

void squeeze(char s1[], char s2[])
{
    int i = 0, counter = 0, j = 0;
    for (i = 0; s1[i] != '\0'; ++i) {
        for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; ++j)
            ;
        if (s2[j] == '\0')
            s1[counter++] = s1[i];
    }
    s1[counter] = '\0';
}

int any(char s1[], char s2[])
{
    int i = 0, j = 0;
    for (i = 0; s1[i] != '\0'; ++i) {
        for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; ++j)
            ;
        if (s2[j] != '\0')
            return i;
    }
    return -1;
}

void print_byte(unsigned char byte)
{
    for (int i = 0; i < CHAR_BIT; ++i)
        printf("%d", (byte & (0x80 >> i)) >> (CHAR_BIT - i - 1));
}

int set_bits(unsigned char x, unsigned char p, unsigned char n, unsigned char y)
{
    unsigned char mask = 0x00;
    for (int i = 0; i < n; ++i)
        mask = (mask << 0x01) | 0x01;
    printf("set right bits from y = %x, to left x = %x, pos = %d, counter = %d;\n", y, x, p, n);
    printf("x:\t\t");
    print_byte(x);
    printf("\ny:\t\t");
    print_byte(y);
    printf("\nmask for y:\t");
    print_byte(mask);
    y = y & mask;
    printf("\ny with mask:\t");
    print_byte(y);
    y = y << (p - n + 1);
    printf("\ny shift left:\t");
    print_byte(y);
    mask = mask << (p - n + 1);
    printf("\nmask shift left:");
    print_byte(mask);
    mask = ~mask;
    printf("\nmask for x:\t");
    print_byte(mask);
    x = x & mask;
    printf("\nx & mask:\t");
    print_byte(x);
    x = x | y;
    printf("\nx | y:\t\t");
    print_byte(x);
    return x;
}

int invert_bits(unsigned char x, unsigned char p, unsigned char n)
{
    unsigned char mask = 0x00;
    for (int i = 0; i < n; ++i)
        mask = (mask << 0x01) | 0x01;
    printf("invert right bits of x = %X, pos = %d, counter = %d;\n", x, p, n);
    printf("x:\t\t");
    print_byte(x);
    printf("\nmask for x:\t");
    print_byte(mask);
    mask = mask << (p - n + 1);
    printf("\nmask shift left:");
    print_byte(mask);
    x = x ^ mask;
    printf("\nx ^ mask:\t");
    print_byte(x);
    return x;
}

int rightrot(unsigned char x, unsigned char n)
{
    printf("rrl bits of x = %X, counter = %d;\n", x, n);
    printf("x:\t\t");
    print_byte(x);
    for (int i = 0; i < n; ++i) {
        unsigned char mask = 0x01;
        mask = x & mask;
        mask <<= CHAR_BIT - 1;
        x >>= 1;
        x |= mask;
    }
    printf("\nres:\t\t");
    print_byte(x);
    return x;
}

void KernighanRitchie_2()
{
    printf("INT:\n");
    printf(" max:\n");
    printf("  signed = %d;\n", INT_MAX);
    printf("  unsigned = %u;\n", UINT_MAX);
    printf(" min:\n");
    printf("  signed = %d;\n", INT_MIN);
    printf("  unsigned = 0;\n\n");
    printf("SHORT:\n");
    printf(" max:\n");
    printf("  signed = %d;\n", SHRT_MAX);
    printf("  unsigned = %u;\n", USHRT_MAX);
    printf(" min:\n");
    printf("  signed = %d;\n", SHRT_MIN);
    printf("  unsigned = 0;\n\n");
    printf("CHAR:\n");
    printf(" max:\n");
    printf("  signed = %d;\n", CHAR_MAX);
    printf("  unsigned = %u;\n", UCHAR_MAX);
    printf(" min:\n");
    printf("  signed = %d;\n", CHAR_MIN);
    printf("  unsigned = 0;\n\n");
    printf("LONG:\n");
    printf(" max:\n");
    printf("  signed = %ld;\n", LONG_MAX);
    printf("  unsigned = %lu;\n", ULONG_MAX);
    printf(" min:\n");
    printf("  signed = %ld;\n", LONG_MIN);
    printf("  unsigned = 0;\n\n");
    printf("FLOAT:\n");
    printf(" max: = %e\n", FLT_MAX);
    printf(" min: = %e\n\n", FLT_MIN);
    printf("DOUBLE:\n");
    printf(" max: = %e\n", DBL_MAX);
    printf(" min: = %e\n\n", DBL_MIN);
    printf("2.2;\n");
    //for (i=0; i<lim-l && (c=getchar()) != '\n' && с != EOF; ++i)
    //s[i] = c;
    int i = 0, lim = MAXLINE, l = 10, c = 0;
    char s[MAXLINE];
    /*
    for (i = 0; i < lim - l; ++i) {
        if ((c = getchar()) == '\n')
            break;
        else if (c == EOF)
            break;
        s[i] = c;
    }
    if (i != 0)
       printf("%s",s);
    */
    printf("\n\n2.3\n");
    char str_1[] = "  0xA12BC5D";
    int result = htoi(str_1);
    printf("%d\n\n",result);
    printf("2.4\n");
    char str_2[] = "h53Rdx38K-joBnifMMt O21TceSfa wVPLkaQrtyqcS!3";
    char str_3[] = "QkLVwfSc12OMn ojK3xdqR5h";
    squeeze(str_2,str_3);
    printf("%s\n\n",str_2);
    printf("2.5\n");
    char str_4[] = "12345";
    char str_5[] = "4";
    result = any(str_4,str_5);
    printf("result = %d;\n\n",result);
    printf("2.6\n");
    set_bits(42,5,3,~42);
    printf("\n\n2.7;\n");
    invert_bits(0xAA,7,8);
    printf("\n\n2.8;\n");
    rightrot(28,4);
}
