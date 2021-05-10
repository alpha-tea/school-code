#include "global.h"
#include "library.h"

int uniq_gen_fast(int number[], int length, int limit)
{
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

void bulls_and_cows()
{
    int i = 0, j = 0, k = 0, counter = 0, quantity = 0, positions = 0;
    const int number_length = 4;
    int number[number_length], entered_number[number_length], is_equal = 0;
    srand(time(NULL));
    uniq_gen_fast(number,number_length,9);
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
    int likeness_idx[OBJECTS_MAX];
    int likeness = 0, div = 0, rem = 0;
    printf("length = %d, quantity = %d;\n", length, quantity);
    if (quantity > length) {
        rem = (quantity - 1) % length;
        div = (quantity - 1) / length;
    } else {
        rem = (quantity - 1) % length;
        div = length % (quantity - 1); // Поменять на другую переменную.
    }
    printf("div = %d;\nrem = %d;\n", div, rem);
    likeness_idx[quantity - 1] = length;
    for (int i = 0; i < quantity - 1;) {
        if (quantity > length)
            for (int j = 0; j < div; ++j)
                likeness_idx[i++] = likeness;
        if (rem > 0) {                              // Заполняем массив, если пароль длиннее чем кол-во вариантов...
            likeness_idx[i++] = likeness;
            rem--;
        }
        if (quantity > length)
            likeness++;
        else {
            likeness += length / (quantity - 1);
            if (div > 0) {
                likeness++;
                div--;
            }
        }

    }
    printf("Variants likeness: \n");
    for (int i = 0; i < quantity; ++i)
        printf("%d ", likeness_idx[i]);
    return;
}
