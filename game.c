#include "global.h"
#include "library.h"

int uniq_gen(int number[], int length)
{
    if (length < 1 || length > 10)
        return -1;
    int mass[length], tmp = 0;
    for (int i = 0; i < length; ++i) {
        if (i == 0)                         // Чтобы число не начиналось с 0
            tmp = 1 + rand() % 9;
        else
            tmp = rand() % 10;
        number[i] = tmp;
        for (int j = 0; j < i; ++j)
            if (number[i] == mass[j]) {
                tmp = rand() % 10;
                number[i] = tmp;
                j = 0;
            }
        mass[i] = tmp;
    }
    return 0;
}

int uniq_gen_fast(int number[], int length)
{
    const int num_max = 10;
    if (length < 1 || length > num_max)
        return -1;
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, tmp = 0, idx_1 = 0 , idx_2 = 0;
    for (int i = 0; i < length * length && digits[0] == 0; ++i) {   // Не оптимально по производительности.
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
