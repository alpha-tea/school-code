#include "global.h"
#include "library.h"

//static int wrong_path[100000000];
//static int path_sizes = ;

int f(int s, int n, int k)
{
    if (s == n) {
        if (k <= 3)
            return 1;
        else
            return 0;
    } else if (s > n || k > 3)
        return 0;
    else {
        if (s % 6 == 0 && s != 6 && (s + 2 <= 300 || s * 3 <= 300 || s * 2 <= 300))
            ++k;
        //printf("s = %d n = %d k = %d;\n", s, n, k);
        return f(s + 2, n, k) + f(s * 2, n, k) + f(s * 3, n, k);
    }
}

int main()
{
    /*
     * Логическая функция F задаётся выражением ((a ∧ b) ≡ ¬c) ∧ (b → d).
     *  На рисунке приведён частично заполненный фрагмент таблицы истинности функции F,
     *  содержащий неповторяющиеся наборы аргументов, при которых функция F истинна.
     *  Определите, какому столбцу таблицы истинности функции F соответствует каждая из переменных
     *   a, b, c, d.
    Теоретическое решение по таблице:
         * 1 0 0 0 = 1
         * 1 0 1 0 = 1
         * 1 0 1 1 = 1 abcd, cadb
         * 1 1 0 0 = 1
#define TAB_MAX 4
    const int data_size = (int)pow(TAB_MAX, TAB_MAX);
    printf("All combination not only uniq = %d;\n", data_size);
    int data[TAB_MAX][TAB_MAX] = {{1,0,0,0}, {1,0,1,0}, {1,0,1,1}, {1,1,0,0}};
    int comb[TAB_MAX] = {0,0,0,0};
    for (int i = 0, j = 0, k = 0; i < data_size; ++i) {
        //printf("\n");
        int is_uniq = 1;        //Другой алгоритм перестановки.
        for (j = 0; j < TAB_MAX - 1 && is_uniq; ++j)
            for (k = j + 1; k < TAB_MAX && is_uniq; ++k)
                if (comb[j] == comb[k])
                    is_uniq = 0;
        if (is_uniq) {
            printf("uniq combination;\n");
            for (int j = 0; j < TAB_MAX; ++j)
                printf("%c ", 'A' + comb[j]);
            int is_correct = 1;
            for (int j = 0; j < TAB_MAX && is_correct; ++j) {
                int vals[TAB_MAX];
                printf("source table: ");
                for (k = 0; k < TAB_MAX; ++k) {
                    vals[comb[k]] = data[j][k];
                    printf("%c[%d] ", comb[k] + 'A', vals[comb[k]]);
                }
                printf("\ndata values: ");
                for (k = 0; k < TAB_MAX; ++k)
                    printf("%c:%d ", 'A' + k, vals[k]);
                if (!(((vals[0] && vals[1]) == !vals[2]) && (!vals[1] || vals[3])))
                    is_correct = 0;
            }
            if (is_correct)
                printf("Yes, correct founded;\n\n");
            else
                printf("No, table data incorrect;\n\n");
        } //else
            //printf("not uniq combination;\n");
        j = 0;
        while (++comb[j] == TAB_MAX)
            comb[j++] = 0;
        //printf("\n");
    }
    */
    task_15();
    return 0;
}





