#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "library.h"

#define OBJ_MAX 256

void bulls_and_cows() {
    int i = 0, j = 0, k = 0, counter = 0, quantity = 0, positions = 0;
    const int number_length = 4;
    int number[number_length], entered_number[number_length], is_equal = 0;

    uniq_gen_fast(number, number_length, 9);
    printf("\nBULLS AND COWS\n");
    printf("Hack the terminal, guess the number of length %d.\n", number_length);
    printf("The number consists of unique digits and does not start with zero!\n");
    printf("Enter '0' to exit the game.\n\n");
    printf("Guess:\t\tCorrect(Cows):\tPositions(Bulls):\n");

    while (is_equal == 0) {
        scanf("%d", &k);
        if (k == 0) return;

        if (count_digits(k) == number_length) {
            for (i = number_length - 1; i >= 0 && k != 0; --i) {
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
            printf("%d\t\t%d\t\t%d\n", quantity, counter, positions);
        } else {
            printf("You entered a number of the wrong length!\n");
        }
    }
    printf("Hooray, you won! Number of attempts: %d\n\n", quantity);
}

void hack_the_terminal(int length, int quantity, int attempts) {
    if (length < 1 || quantity < 2 || length > 26) {
        printf("Error in parameters!\n\n");
        return;
    }
    srand(time(NULL));
    int correct_variant = rand() % quantity, i = 0, j = 0, k = 0, is_equal = 0, idx = 0, likeness = 0;
    char passwords[quantity][length + 1];
    uniq_gen_fast_symbols(passwords[correct_variant], length);
    printf("Game: Hack The Terminal\n");
    printf("Rules:  You must enter the index of the assumed password\n\tand guess it in a limited number of attempts.\n\n");
    printf("idx:    password:   addr:\n");
    for (i = 0; i < quantity; ++i) {
        if (i != correct_variant) {
            string_copy_substr(passwords[correct_variant], passwords[i], 0, length);
            passwords[i][length] = '\0';
            string_rand_change(passwords[i], 1 + rand() % length);
        }
        printf("%2d\t |%s|%11p\n", i, passwords[i], (void*)passwords[i]);
    }
    while (is_equal != 1 && attempts > 0) {
        printf("Attempts Remaining: ");
        for (j = attempts; j > 0; --j) {
            printf("■ ");
        }
        printf("\nPlease enter idx: ");
        scanf("%d", &idx);

        if (idx >= 0 && idx < quantity) {
            likeness = 0;
            for (k = 0; k < length; ++k) {
                if (passwords[correct_variant][k] == passwords[idx][k]) {
                    likeness++;
                }
            }
            if (likeness == length) {
                is_equal = 1;
                printf("Terminal Hacked!\nWelcome!\n");
            } else {
                printf("Likeness: %d\n\n", likeness);
            }
        } else {
            printf("Index is incorrect!\n\n");
        }
        attempts--;
    }
    if (is_equal == 0) {
        printf("Terminal Is Locked!\n\n");
    }
}

void play_hack_the_terminal() {
    int length, quantity, attempts;
    printf("\nTERMINAL HACK (Fallout)\n");
    printf("Enter password length (e.g., 5): ");
    scanf("%d", &length);
    printf("Enter the number of words on the screen (e.g., 7): ");
    scanf("%d", &quantity);
    printf("Enter the number of attempts (e.g., 4): ");
    scanf("%d", &attempts);
    hack_the_terminal(length, quantity, attempts);
}

int stalker_evaluation_function(int properties[]) {
    const int properties_quantity = 14;
    double properties_point[14] = {16,32,120,4.7,8,80.1,50,32,50,32,32,32,28,0.01};
    if (properties[0] < 0)
        return INT_MIN;
    double points = 0;
    for (int i = 0; i < properties_quantity; ++i)
        points += properties[i] * properties_point[i];
    return (int)(points);
}

void stalker_best_combination_of_artifacts() {
    const int artifacts_quantity = 15;
    const int properties_quantity = 14;
    const char* artifacts[15] = {"Spring","Flash","Raven Eye","Soul","Wrenched","Slime","Slug","Stone Blood",
                                 "Stone Flower","Porcupine","Drops","Sea Urchin","Thorn","Meat Chunk","Jellyfish"};
    const int artifacts_properties[15][14] =
        {{0,0,0,0,0,0,0,0,10,0,0,0,0,0},{0,-10,0,0,0,6,0,0,0,-10,0,0,0,0},{-10,0,-7,0,0,0,0,0,0,15,20,10,-10,0},
         {10,10,0,0,60,0,-7,0,-7,0,0,0,0,0},{-3,0,0,0,0,0,2,0,2,0,0,0,0,0},{0,0,0,67,0,0,0,0,0,0,-20,-10,0,0},
         {0,0,0,133,0,0,0,0,0,0,-10,-10,0,0},{3,3,0,0,20,0,-3,0,-3,0,0,0,0,0},{-5,0,4,0,0,0,0,0,0,0,0,0,0,0},
         {40,0,0,0,0,-2,0,0,0,0,0,0,0,0},{5,0,0,0,0,-7,0,0,0,0,0,0,0,0},{20,0,0,-100,0,0,0,0,0,0,0,0,0,0},
         {5,0,0,-100,0,0,0,0,0,0,0,0,0,0},{5,5,0,0,40,0,-5,0,-5,0,0,0,0,0},{0,-3,2,0,0,0,0,0,0,0,0,0,0,0}};
    int artifacts_counter[15] = {0};
    int properties[14] = {0};
    int i, j, k, tmp = 0, properties_max;
    int a_c[15] = {0};
    int a_p[14] = {0};

    printf("Enter the number of artifacts you have (for each type):\n");
    for (i = 0; i < artifacts_quantity; ++i) {
        printf("%s: ", artifacts[i]);
        scanf("%d", &artifacts_counter[i]);
    }

    for (i = 0; i < artifacts_quantity; ++i) {
        for (j = 0; j < artifacts_counter[i]; ++j) {
            for (k = 0; k < properties_quantity; ++k) {
                properties[k] += artifacts_properties[i][k];
            }
        }
    }
    properties_max = stalker_evaluation_function(properties);

    printf("\nSearching for optimal combination (brute force)...\n");

    for (a_c[0]=0; a_c[0]<=artifacts_counter[0]; ++a_c[0])
        for (a_c[1]=0; a_c[1]<=artifacts_counter[1]; ++a_c[1])
            for (a_c[2]=0; a_c[2]<=artifacts_counter[2]; ++a_c[2])
                for (a_c[3]=0; a_c[3]<=artifacts_counter[3]; ++a_c[3])
                    for (a_c[4]=0; a_c[4]<=artifacts_counter[4]; ++a_c[4])
                        for (a_c[5]=0; a_c[5]<=artifacts_counter[5]; ++a_c[5])
                            for (a_c[6]=0; a_c[6]<=artifacts_counter[6]; ++a_c[6])
                                for (a_c[7]=0; a_c[7]<=artifacts_counter[7]; ++a_c[7])
                                    for (a_c[8]=0; a_c[8]<=artifacts_counter[8]; ++a_c[8])
                                        for (a_c[9]=0; a_c[9]<=artifacts_counter[9]; ++a_c[9])
                                            for (a_c[10]=0; a_c[10]<=artifacts_counter[10]; ++a_c[10])
                                                for (a_c[11]=0; a_c[11]<=artifacts_counter[11]; ++a_c[11])
                                                    for (a_c[12]=0; a_c[12]<=artifacts_counter[12]; ++a_c[12])
                                                        for (a_c[13]=0; a_c[13]<=artifacts_counter[13]; ++a_c[13])
                                                            for (a_c[14]=0; a_c[14]<=artifacts_counter[14]; ++a_c[14]) {
                                                                for (i = 0; i < artifacts_quantity; ++i) {
                                                                    for (j = 0; j < a_c[i]; ++j) {
                                                                        for (k = 0; k < properties_quantity; ++k) {
                                                                            a_p[k] += artifacts_properties[i][k];
                                                                        }
                                                                    }
                                                                }
                                                                tmp = stalker_evaluation_function(a_p);
                                                                if (tmp > properties_max) {
                                                                    properties_max = tmp;
                                                                    printf("\nBetter combination found! Score: %d\n", tmp);
                                                                    for (int idx = 0; idx < 15; ++idx) {
                                                                        printf("%d ", a_c[idx]);
                                                                    }
                                                                    printf("\n");
                                                                }
                                                                for (i = 0; i < 14; ++i) {
                                                                    a_p[i] = 0;
                                                                }
                                                            }
    printf("Done.\n\n");
}

int checking_nearby_paths(int size, int place[size][size], int x, int y) {
    int sum = 0;
    if (x < size - 1 && place[x + 1][y] == '*') ++sum;
    if (y < size - 1 && place[x][y + 1] == '*') ++sum;
    if (x > 0 && place[x - 1][y] == '*') ++sum;
    if (y > 0 && place[x][y - 1] == '*') ++sum;

    return (sum > 1) ? 0 : 1;
}

void labyrinth_direction_create(int size, int place[size][size], int *x, int *y, int *branches_counter, char empty) {
    int way = 0, flag = 0, result = 0;
    int directions[][2] = { {-1, 0}, {0, +1}, {+1, 0}, {0, -1}};

    while (flag == 0) {
        way = rand() % 4;
        int tmp_x = *x + directions[way][0], tmp_y = *y + directions[way][1];
        if (tmp_x >= 0 && tmp_x < size && tmp_y >= 0 && tmp_y < size &&
            place[tmp_x][tmp_y] == empty) {
            result = checking_nearby_paths(size, place, tmp_x, tmp_y);
            if (result) {
                flag = 1;
                *x = tmp_x;
                *y = tmp_y;
            }
        }
    }
    place[*x][*y] = '*';
    *branches_counter += 1;

    if (!(rand() % 4)) {
        labyrinth_direction_create(size, place, x, y, branches_counter, empty);
        *branches_counter += 1;
    }
}

void labyrinth_basic_create(int size, int place[size][size], int branches, char empty) {
    int x = 0, y = 0, branches_counter = 0;
    while (branches_counter < branches && x < size && y < size) {
        labyrinth_direction_create(size, place, &x, &y, &branches_counter, empty);
    }

    printf("\nGenerated labyrinth:\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c ", place[i][j]);
        }
        printf("\n");
    }
}

void labyrinth(int size, int branches) {
    int place[size][size];
    char empty = '.';

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            place[i][j] = empty;
        }
    }

    place[0][0] = '*';
    labyrinth_basic_create(size, place, branches, empty);
}

void play_labyrinth() {
    int size, branches;
    printf("\nLABYRINTH GENERATOR\n");
    printf("Enter field size (e.g., 15): ");
    scanf("%d", &size);
    printf("Enter the number of branches (e.g., 50): ");
    scanf("%d", &branches);

    if (size > 0 && size < 100)
        labyrinth(size, branches);
    else
        printf("Invalid field size.\n");
}

void chapter_16() {
    int choice = -1;
    srand(time(NULL));

    do {
        printf("1. Bulls and cows (Logic game)\n");
        printf("2. Fallout terminal hack (Algorithm)\n");
        printf("3. S.T.A.L.K.E.R. (Artifact calculator)\n");
        printf("4. Labyrinth generator\n");
        printf("0. Exit\n");
        printf("----------------------------------\n");
        printf("Select menu item: ");

        if (scanf("%d", &choice) != 1) {
            printf("Input error. A number is expected.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            bulls_and_cows();
            break;
        case 2:
            play_hack_the_terminal();
            break;
        case 3:
            stalker_best_combination_of_artifacts();
            break;
        case 4:
            play_labyrinth();
            break;
        case 0:
            printf("Exiting the menu...\n");
            break;
        default:
            printf("Invalid menu item, try again.\n");
        }
    } while (choice != 0);
}