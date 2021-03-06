#include "global.h"
#include "library.h"

int string_rand_change(char string[], int level_change) {
    int length = string_length(string), idx = 0;
    char tmp = 0;
    if (length == 0 || level_change < 1)
        return -1;
    for (int i = 0; i < level_change; ++i) {
        tmp = 'A' + rand() % 26;
        idx = rand() % length;
        while (tmp == string[idx])
            tmp = 'A' + rand() % 26;
        string[rand() % length] = tmp;
    }
    return 0;
}

int uniq_gen_fast(int number[], int length)
{
    const int num_max = 10;
    if (length < 1 || length > num_max)
        return -1;
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < length * length && digits[0] == 0; ++i) {
        idx_1 = rand() % num_max;
        idx_2 = rand() % num_max;
        tmp = digits[idx_1];
        digits[idx_1] = digits[idx_2];
        digits[idx_2] = tmp;
    }
    // Подставить частный случай нуля.
    for (int i = 0; i < length; ++i)
        number[i] = digits[i];
    return 0;
}

int uniq_gen_fast_symbols(char string[], int length)
{
    const int symbol_max = 26;
    if (length < 1 || length > symbol_max)
        return -1;
    char symbols[symbol_max];
    for (int j = 0; j < 26; ++j)
        symbols[j] = 'A' + j;
    char tmp;
    int idx_1 = 0 , idx_2 = 0, i = 0;
    for (i = 0; i < length * length; ++i) {
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

void bulls_and_cows()
{
    int i = 0, j = 0, k = 0, counter = 0, quantity = 0, positions = 0;
    const int number_length = 4;
    int number[number_length], entered_number[number_length], is_equal = 0;
    srand(time(NULL));
    uniq_gen_fast(number,number_length);
    printf("Hack the terminal, guess the number size %d, with using digits.\n",number_length);
    printf("Number with all unique digits and not statring with zero!\n");
    //printf("Debug number: ");
    //for (i = 0; i < number_length; ++i) {
    //   printf("%d", number[i]);
    //}
    printf("\n");
    printf("Guess:\tCorrect:\tPositions:\n");
    while (is_equal == 0) {
        scanf("%d",&k);
        if (length_number(k) == number_length) {
            for (i = number_length - 1; i >= 0 && k != 0; --i) {    // Можно написать доп. функцию.
                entered_number[i] = k % 10;
                k /= 10;
            }
            for (j = 0, counter = 0, positions = 0; j < number_length; ++j) {
                for (k = 0; k < number_length; ++k) {
                    if (number[k] == entered_number[j]) {
                        counter++;
                        if (j == k)
                            positions++;
                    }
                }
            }
            if (positions == number_length)
                is_equal = 1;
            quantity++;
            printf("%d\t%d\t\t%d\n", quantity, counter, positions);
        } else
            printf("You entered a number with the wrong length!;\n");
    }
    printf("Hooray, you won!\nNumber of attempts = %d;\n\n",quantity);
}

void hack_the_terminal(int length, int quantity, int attempts)
{
    if (length < 1 || quantity < 2 || length > 26) {
        printf("error in parameters;\n\n");
        return;
    }
    srand(time(NULL));
    int correct_variant = rand() % quantity, i = 0, j = 0, is_equal = 0, idx = 0, result = 0;
    char passwords[quantity][length + 1];
    uniq_gen_fast_symbols(passwords[correct_variant],length);
    //printf("%s\n", passwords[correct_variant]);
    printf("Game: Hack The Terminal\n");
    printf("Rules:  You must enter the index of the assumed password\n\tand guess it in a limited number of attempts.\n\n");
    printf("idx:    password:   addr:\n");
    for (i = 0; i < quantity; ++i) {    // Подумать над равномерным распределением похожести букв.
        if (i != correct_variant) {
            string_copy_substr(passwords[correct_variant],passwords[i],0,length);
            string_rand_change(passwords[i], length * (1 + rand() % 2)); // контроль длинны отностительно распределения.
            passwords[i][length] = '\0';
        }
        printf("%2d\t |%s|%11p\n", i, passwords[i],passwords[i]);
    }
    while (is_equal != 1 && attempts > 0) {
        printf("Attempts Remaining: ");
        for (j = attempts; j > 0; --j)
            printf("%c ",' ' + 222);
        printf("\nPlease entered idx: ");
        scanf("%d",&idx);
        if (idx >= 0  && idx < quantity) {
            result = string_is_equal(passwords[correct_variant], passwords[idx]);
            if (result == 0) {
                is_equal = 1;
                printf("Terminal Hacked!\nWelcome!\n");
            } else
                printf("Likeness: %d;\n\n",result);
        } else
            printf("Index Is incorrect!\n\n");
        attempts--;
    }
    if (attempts == 0)
        printf("Terminal Is Locked!\n\n");
}
