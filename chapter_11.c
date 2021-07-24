#include "global.h"
#include "library.h"

enum array_inf_val {inf_info, inf_addr, inf_mem_size, inf_elements, inf_positiv, inf_negativ,
                    inf_zeros, inf_evens, inf_odds, inf_avarage_a, inf_avarage_g, inf_prim,
                    inf_sum, inf_mult, inf_var_sum, inf_sqr_sum, inf_end};

enum array_check_type {chk_info, chk_more, chk_less, chk_equal, chk_div, chk_sqrt,
                       chk_sign, chk_parity, chk_idx_odd, chk_idx_even, chk_end};

enum array_action_type {act_info, act_mov, act_add, act_sub, act_mult, act_div, act_abs, act_sqrt, act_end};

static const char* array_action_name[] = {"info", "mov", "add", "sub", "mult", "div", "abs", "sqrt"};

static const char* array_check_name[] = {"info", "is more than", "is less than", "is equal", "is devided by",
                                         "is sqrt of", "sign", "parity", "index odd", "index even"};
static const char* array_info_names[] = { "Array information, 32-bit compile with integers other may be incorrect.", "Address of array", "Size in memory, bytes",
                                          "Elements in array", "Positive numbers", "Negative numbers", "Zeros numbers", "Even numbers", "Odd numbers", "Avarage ariphmetic",
                                          "Avarage geometric", "Primary numbers", "Sum of all elements", "Multiply of all elements", "Variable sum, all elements", "Reverse sum" };

static char comm_chk_name[] = "IMLEDRSP";
static char comm_act_name[] = "IMASUDBR";

int array_modify_element(int data[], int offset, enum array_action_type type, int parameter, int limit)
{
    if (offset >= limit || offset < 0) {
        printf("error, offset or limit incorrect;\n");
        return -1;
    }
    switch (type) {
    case act_info:
        printf("info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;",
               data, offset, parameter, array_action_name[type], limit);
        break;
    case act_mov:
        data[offset] = parameter;
        break;
    case act_add:
        data[offset] += parameter;
        break;
    case act_sub:
        data[offset] -= parameter;
        break;
    case act_mult:
        data[offset] *= parameter;
        break;
    case act_div:
        if (parameter != 0)
            data[offset] /= parameter;
        else
            printf("error: divided by 0!");
        break;
    case act_abs:
        data[offset] = abs(data[offset]);
        break;
    case act_sqrt:
        data[offset] = (int)(sqrt((double)data[offset])); //Лучше так не делать!
        break;
    default:
        printf("error, info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;\n",
               data, offset, parameter, array_action_name[type], limit);
    }
    return 0;     //data[offset];
}

int array_check_element(int data[], int offset, int parameter, enum array_check_type type, int limit)
{
    if (offset > limit || limit < 0) {
        printf("error, offset or limit incorrect;\n");
        return -1;
    }
    switch (type) {
    case chk_info:
        printf("info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;",
               data, offset, parameter, array_check_name[type], limit);
        break;
    case chk_more:
        if (data[offset] > parameter)
            return 1;
        break;
    case chk_less:
        if (data[offset] < parameter)
            return 1;
        break;
    case chk_equal:
        if (data[offset] == parameter)
            return 1;
        break;
    case chk_div:
        if (parameter != 0) {
            if (data[offset] % parameter == 0)
                return 1;
        } else
            printf("error, division by zero parameter;\n");
        break;
    case chk_sqrt:
        if (data[offset] == parameter * parameter) // fix exchange.....
            return 1;
        break;
    case chk_sign:
        return data[offset] / abs(data[offset]);
    case chk_parity:
        if (data[offset] % 2 == 0)
            return 1;
        break;
    case chk_idx_odd:           // move later
        if (offset % 2 != 0)
            return 1;
        break;
    case chk_idx_even:
        if (offset % 2 == 0)
            return 1;
        break;
    default:
        printf("error, info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;\n",
               data, offset, parameter, array_check_name[type], limit);
    }
    return 0;
}

int array_information(int data[], int size, enum array_inf_val ret)
{               // Функция для целочисленного массива, но платформозависимая.
    // Коректно работает при сборке под 32 бита, иначе информация может быть искажена.
    if (!size) {
        printf("array empty, nothing to do.");
        return -1;
    }
    int sign = 1;
    const int enum_size = inf_sqr_sum + 1;
    int data_int[enum_size];   //15 - enum length.
    for (int i = 0; i < enum_size; ++i)
        data_int[i] = 0;
    data_int[inf_avarage_g] = 1;
    data_int[inf_mult] = 1;
    data_int[inf_addr] = (int)data; //32-bit only, sorry(
    data_int[inf_mem_size] = sizeof(int) * size;
    data_int[inf_elements] = size;
    for (int i = 0; i < size; ++i, sign *= -1) {
        if (array_check_element(data, i, 0, chk_more, size))
            ++data_int[inf_positiv];
        else if (array_check_element(data, i, 0, chk_less, size))
            ++data_int[inf_negativ];
        else
            ++data_int[inf_zeros];
        if (array_check_element(data, i, 2, chk_parity, size))
            ++data_int[inf_evens];
        else
            ++data_int[inf_odds];
        data_int[inf_avarage_a] += data[i];
        data_int[inf_avarage_g] *= data[i];
        if (prime_number(data[i]))
            ++data_int[inf_prim];

        data_int[inf_var_sum] += data[i] * sign;
        data_int[inf_mult] *= data[i];
        data_int[inf_sum] += data[i];
        data_int[inf_sqr_sum] += data[i] * data[i];
    }
    data_int[inf_avarage_a] /= size;
    data_int[inf_avarage_g] /= size; //Не та интерпритация.
    if (ret == inf_info) {
        for (int i = 0; i < enum_size; ++i) {
            printf("'%s': ", array_info_names[i]);
            if (i == enum_size - 1)
                printf("1 / %d or %.10f.", data_int[inf_sum], 1.0 / (double)data_int[inf_sum]);
            else if (i > 0)
                printf("%d;", data_int[i]);
            printf("\n");
        }
        return 0;
    } else
        return data_int[ret];
}

enum array_print_mode {prt_nope = 0x00, prt_element = 0x01, prt_indexes = 0x02};

void array_print(int data[], int limit, int mode)   //Вывод масива в заданном режиме, разделитель - пробел.
{
    for (int i = 0; i < limit; ++i) {
        for (enum array_print_mode mask = prt_element; mask <= prt_indexes; mask <<= 1) {
            switch ((enum array_print_mode)mode & mask) {
            case prt_nope:
                break;
            case prt_element:
                printf("%d", data[i]);
                break;
            case prt_indexes:
                printf("[%d]", i);
                break;
            default:
                printf("error, data = %p, limit = %d, mode = %d;\n", data, limit, mode);
            }
        }
        printf(" ");
    }
}

int array_scan_element(int data[], int offset, int size, int parameter, enum array_check_type type)
{       //Линейный поиск элемента в масиве с учётом типа проверки и параметров.
    if (size <= 0 || type < chk_info || type >= chk_end) {
        printf("error, size or type incorrect;\n");
        return -1;
    }
    int i = 0;
    for (i = offset; i < size; ++i)
        if (array_check_element(data,i,parameter,type,size))
            return i;
    return -1;
}

int array_modify_action(int data[], int size, int parameter, enum array_action_type type)
{       //модификация маcсива с заданный действием
    // вернуть кол-во изменённых элементов.
    if (size <= 0 || type < act_info || type >= act_end) {
        printf("error, size or type incorrect;\n");
        return -1;
    }
    int i = 0, result;
    for (i = 0; i < size; ++i)
        result = array_modify_element(data,i,type,parameter,size);
    return result;
}

int array_create_input(int data[], int init[], int isInput, int limit)
{
    int i = 0;
    if (limit <= 0) {
        printf("empty array, error;");
        return -1;
    }
    switch (isInput) {
    case 0:
        for (i = 0; i < limit; ++i)
            data[i] = init[i];
        break;
    default:
        for (i = 0; i < limit; ++i)
            scanf("%d",&data[i]);
        break;
    }
    return i;
}

int is_Fibonacci(int n)
{   //Является ли число элементом последовательности Фибоначчи. Числа Фибоначчи могут быть отрицательными. Знакопеременная последовательность.
    int f1 = 1, f2 = 1, f3 = 0;
    while ((f3 = f1 + 2) < n) {
        f1 = f2;
        f2 = f3;
    }
    if (f3 == n || (n >= 0 && n <= 1))
        return 1;
    else
        return 0;
}

int array_create_sequence(int data[], int first, int last, int par, int flags, int limit)
{//Инициализация массива данных последовательности, заданный по правилам, и с учётом элементов.
    if (limit <= 0) {
        printf("error, empty array;\n");
        return -1;
    }
    int elements = 0;
    switch (flags) {
    case 0b00000001://Random values.
        if (par > 0)
            for (int i = 0; i < limit; ++i) {
                data[i] = rand() % par;
                if ((first < 0 || last < 0) && rand() % 2)
                    data[i] *= -1;
            }
        else
            printf("error generate random;\n");
        break;
    case 0b00000010: {//arif_progres.
        int i = 0;
        for (i = 0; elements < limit && first != last; ++i, first += par, elements++)
            data[i] = first;
        if (first == last)
            data[i] = last;
        else
            printf("warning: sequence doesn't reach last element.\n");
    } break;
    case 0b00000100: { //geomet_progres.
        int i = 0;
        for (i = 0; elements <= limit && first != last; ++i, first *= par, elements++)
            data[i] = first;
        if (first == last)
            data[i] = last;
        else
            printf("warning: sequence doesn't reach last element.\n");
    }  break;
    case 0b00001000: {// fibonachi, проверить на полный крадрат по совету Андрея.
        if (is_Fibonacci(first)) {
            if (!is_Fibonacci(last))
                printf("warning: last element is not fibonacci;\n");
            for (int i = 0, f1 = 0, f2 = 1, f3 = 1; elements < limit && f3 != last; ++i) {
                f3 = f1 + f2;
                if (f3 >= first)
                    data[elements++] = f3;
                f1 = f2;
                f2 = f3;
            }
        } else
            printf("error: first element is not fibonacci;\n");
    }   break;
    case 0b00010000: {// Все числа уникальные.
        if (abs(last) - abs(first) <= par && par > 0) {
            for (int i = 0; i < par && i < limit; ++i, first++, elements++)
                data[i] = first;
            int tmp = 0, idx_1 = 0 , idx_2 = 0;
            for (int i = 0; i < limit * limit; ++i) {
                idx_1 = rand() % par;
                idx_2 = rand() % par;
                tmp = data[idx_1];
                data[idx_1] = data[idx_2];
                data[idx_2] = tmp;
            }
        } else
            printf("error: elements more than delta from first to last;\n");
    } break;
    default:
        printf("error in flags!;\n\n");
        break;
    };
    return 0;
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}
//Максимальный вывод в случае ошибки.
// Функция изменения элементов массива парами команд условие-действие и каждое состоит из двух символов, можно между командами добавить пробел.
// Для ограничений использовать максимум одну букву для команды и одну цифру для параметра.
// Пример: char commands[] = "L0A0 V4D2" - первая пара: все отрицательные элементы взять по модулю;
// вторая пара: все элементы которые делятся на 4, разделить на 2.

int array_update_commands(int data[], char commands[], int limit) {
    const int min_command_size = 4;
    if (limit <= 0 && string_length(commands) < min_command_size) {
        printf("error, size array or commands incorrect;\n");
        return -1;
    }
    int i = 0, j = 0, result_chk = 0, result_act = 0, number_chk = 0, number_act = 0,
            counter = 0, length = string_length(commands);
    printf("data size %d, commands %s;\n", limit, commands);
    for (i = 0; i < length; ++i) { // Главный цикл.
        printf("Check: %c ", commands[i]);
        if ((result_chk = string_char_find(comm_chk_name, commands[i], 0, 0)) != -1 &&
                (is_digit(commands[i + 1]) || commands[i + 1] == '_')) {
            printf("'%s' ", array_check_name[result_chk]);
            if ((result_act = string_char_find(comm_act_name, commands[i + 2], 0, 0)) != -1 &&
                    (is_digit(commands[i + 3]) || commands[i + 3] == '_')) {
                printf("command: %c '%s' ", commands[i + 2] ,array_action_name[result_act]);
                number_chk = char_to_hex(commands[i + 1]);
                number_act = char_to_hex(commands[i + 3]);
                printf("digits: chk = %d, act = %d ", number_chk, number_act);
                j = 0;
                while ((j = array_scan_element(data, j, limit, number_chk, result_chk)) != -1) {
                    printf("modify: element[position] = %d[%d] ", data[j], j);
                    array_modify_action(&data[j], 1, number_act, result_act);
                    counter++;
                    ++j;
                }
                i += min_command_size;
                //array_modify_element(data, j, result_act, number_act, limit);
            } else
                printf("error: unknown command to change elements or wrong digit;\n"
                "idx = %d, element = %c;\n\n", i, commands[i + 2]);
        } else
            printf("error: unknown command to check elements or wrong digit;\n"
            "idx = %d, element = %c;\n\n", i, commands[i]);
        //while (commands[i] == ' ')
        //  ++i;  add later
        printf("\n");
    }
    return counter;
}

int array_sum_elements(int data[], int size, int parameter, enum array_check_type type)
{          //Функция расчёта суммы элементов массива с выводом или без, с возвратом результата(суммы).
    if (size <= 0) {
        printf("error, size incorrect;\n");
        return -1;
    }
    int i = 0, sum = 0;
    for (i = 0; i < size; ++i)
        if (array_check_element(data,i,parameter,type,size))
            sum += data[i];
    return sum;
}

int array_chk_counter(int data[], int size, int parameter, enum array_check_type type)
{   //Функция подсчёта количества элементов, удовлетворяющих условию.
    if (size <= 0 || type < chk_info || type >= chk_end) {
        printf("error, size or type incorrect;\n");
        return -1;
    }
    int i = 0, counter = 0;
    for (i = 0; i < size && type != chk_info; ++i)
        if (array_check_element(data,i,parameter,type,size))
            ++counter;
    if (type == chk_info)
        printf("info: data = %p, parameter = %d, type = '%s', limit = %d;\n",
               data, parameter, array_check_name[type], size);
    return counter;
}

void chapter_11()
{
    printf("11.1 - 11.2, moving data across arrays;\n");
    int i = 0;
    int length = 10, random_max = 10;
    int data[OBJECTS_MAX];
    int init[OBJECTS_MAX];
    srand(time(NULL));
    for (i = 0; i < length; ++i)
        init[i] = rand() % random_max;
    printf("source elements: ");
    array_print(init,length,prt_element);
    array_create_input(data, init, 0, length);
    printf("output: ");
    for (i = 0; i < length; ++i)
        printf("%d ",data[i]);
    printf(";\n\n");
    printf("11.3 - 11.9, filling the array elements with integer elements of sequence, length = %d\n", length);
    printf("random sequence with random_max = %d: ", random_max);
    int first = 0, last = 9, par = random_max, flags = 0b00000001;   //warning: binary integer literals are a GNU extension
    array_create_sequence(data, first, last, par,flags, length);
    array_print(init,length,prt_element);
    first = 3, last = 15, par = 3, flags = 0b00000010;
    printf("\narif. sequence from %d to %d, step = %d: ", first, last, par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(init,length,prt_element);
    first = 2, last = 32, par = 2, flags = 0b0000100;
    printf("\ngeometr. sequence from %d to %d, step = %d: ", first, last, par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(init,length,prt_element);
    first = 21, last = 89, par = 5, flags = 0b0001000;
    printf("\nFibonacci sequence from %d to %d: ", first, last);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(init,length,prt_element);
    first = 0, last = 9, par = 10, flags = 0b0010000;
    printf("\nunique sequence with parameter = %d: ", par);
    array_create_sequence(data, first, last, par,flags, length);
    array_print(init,length,prt_element);
    printf("\n11.12, filling an array with prime and natural numbers;\n");
    int quantity = 0;
    printf("A(natural, divisible by 13 or 17 and more than 299):\n");
    for (i = 300; quantity < 20; ++i) {
        if (i % 13 == 0 || i % 17 == 0) {
            data[quantity] = i;
            ++quantity;
        }
    }
    array_print(init,length,prt_element);
    printf("\nB(first 30 primes numbers):\n");
    for (i = 2, quantity = 0; quantity < 30; ++i) {
        if (prime_number(i) == 1) {
            data[quantity] = i;
            ++quantity;
        }
    }
    array_print(init,length,prt_element);


    printf("\n\n11.13 - 11.14, outputting array values;\n");
    for (i = 0; i < length; ++i)
        data[i] = rand() % random_max;
    printf("output: ");
    array_print(init,length,prt_element | prt_indexes);
    int parameter = 0, type = 0, result = 0;
    length = 10;
    printf("\n\n11.15 - 11.16, checking elements with various modes, size = %d\nelements: ", length);
    array_print(data, length, prt_indexes | prt_element);
    for (enum array_check_type mode = chk_info;mode <= chk_parity; ++mode){
        parameter = rand() % random_max;
        int offset = rand() % length;
        printf("\ncheck if element with offset = %d:'%s', parameter = %d, ", offset,
               array_check_name[mode], parameter);
        result = array_check_element(data, offset, parameter, mode, length);
        printf("result = %d", result);
    }
    printf("\n\n");
    srand(time(NULL));
    parameter = 5, type = 1, length = 10, random_max = 20;
    printf("11.17 - 11.18, changing all elements of the array to a parameter = %d, type = %d;\n", parameter, type);
    for (i = 0; i < length; ++i)
        data[i] = rand() % random_max;
    printf("source values: ");
    array_print(data, length, prt_indexes | prt_element);
    for (enum array_action_type mode = act_info;mode <= act_div; ++mode){
        parameter = rand() % random_max;
        int offset = rand() % length;
        printf("\nchanging element on parameters = %d[%d]:'%s', parameter = %d, ", data[offset], offset,
               array_action_name[mode], parameter);
        result = array_modify_element(data, offset, mode, parameter, length);
        printf("result = %d", result);
    }
    printf("\nresult array: ");
    array_print(data, length, prt_indexes | prt_element);
    printf("\n\n");
    printf("11.19, output of array characteristics;\n");
    quantity = 10;
    int info_array[] = {0, 167, -13, 5,-7,-4, 3, 5, 17, -11};
    printf("source values: ");
    array_print(info_array, length, prt_indexes | prt_element);
    printf("\n");
    array_information(info_array, quantity, result);
    printf("\n11.21, determine the total rainfall for January;\n");
    quantity = 5; // Кол-во дней.
    array_create_sequence(data,0,quantity - 1,10,1,OBJECTS_MAX);
    int summ = array_information(data,quantity,inf_sum);
    array_print(data,quantity,prt_element | prt_indexes);
    printf("Total: %d mm, elements = %d;\n\n", summ, quantity);
    printf("11.23, determine the total resistance of the circuit when connected in series;\n");
    quantity = 5; //Кол-во элементов.
    array_create_sequence(data,0,quantity - 1,10,1,OBJECTS_MAX);
    summ = array_information(data,quantity,inf_sum);
    array_print(data,quantity,prt_element | prt_indexes);
    printf("Total: %d Om, elements = %d;\n\n", summ, quantity);
    printf("11.25, determine the total amount of precipitation for eachten days of June.;\n");
    quantity = 15;
    int j = 0, dec = 5; //Декада
    array_create_sequence(data,0,quantity - 1,quantity,1,quantity);
    for (i = 0, j = -1; i < quantity; ++i)
        if ((i + 1) % dec == 0) {
            summ = array_information(&data[j],i - j,inf_sum);
            array_print(&data[j],i - j,prt_element);
            printf("\tsum = %d\n",summ);
            j = i;
        }
    printf("\n11.27, how much precipitation fell on average in one day in the first, second and third decades of September.;\n");
    for (i = 0, j = 0; i < quantity; ++i)
        if ((i + 1) % dec == 0) {
            summ = array_information(&data[j],i - j,inf_sum);
            array_print(&data[j],i - j,prt_element);
            printf("\tsum = %d, average = %d\n",summ, summ / dec);
            j = i;
        }
    printf("\n11.29, is it true that the sum of the array elements is an even number and that the sum of the squares of the array elements is a three-digit number;\n");
    int min = 99, max = 999;
    array_create_sequence(data,0,quantity - 1,10,0x01,OBJECTS_MAX);
    array_print(data,quantity,prt_element | prt_indexes);
    result = array_information(data,quantity,inf_sum);
    if (result % 2 == 0)
        printf("\na) Yes, sum is even (%d);\n", result);
    else
        printf("\na) No, sum is odd (%d);\n", result);
    summ = array_information(data,quantity,inf_sqr_sum);
    if (summ > min && summ < max)
        printf("b) Yes, sum of power 2 is three-digits (%d);\n", summ);
    else
        printf("b) No, sum of power 2 isn't three-digits (%d);\n", summ);
    printf("\n11.31, is it true that the total number of books in the library there is a three-digit number.;\n");
    quantity = 10;
    array_create_sequence(data,0,quantity - 1,20,1,OBJECTS_MAX);
    array_print(data,quantity,prt_element | prt_indexes);
    summ = array_information(data,quantity,inf_sum);
    min = 99, max = 999;
    if (summ > min && summ < max)
        printf("\nYes (%d);\n", summ);
    else
        printf("\nNo (%d);\n", summ);
    printf("\n11.33, determine if the athlete has advanced to the nextstage of the competition.;\n");
    quantity = 10;
    array_create_sequence(data,0,quantity - 1,20,1,OBJECTS_MAX);
    array_print(data,quantity,prt_element | prt_indexes);
    summ = array_information(data,quantity,inf_sum);
    if (summ > min)
        printf("\nYes (%d);\n", summ);
    else
        printf("\nNo (%d);\n", summ);
    printf("\n11.35, find out which type of program the athlete showed the best result.;\n");
    quantity = 18;
    int scores[3], k = 0, programm_size = 6;
    array_create_sequence(data,0,quantity - 1,10,1,OBJECTS_MAX);
    printf("elements:\n");
    for (i = 0, j = 0, k = 0; i < quantity; ++i) {
        if ((i + 1) % programm_size == 0) {
            array_print(&data[k],i - k + 1,prt_element);
            summ = array_information(&data[k],i - k + 1,inf_sum);
            scores[j] = summ;
            printf("\t| idx = %d, sum = %d\n", j, summ);
            ++j;
            k = i + 1;
        }
    }
    find_max_recur(scores,3,&result,0);
    printf("max score idx = %d, sum = %d;\n\n",result, scores[result]);
    printf("11.36 - 11.39, checking elements for conditions;\n");
    quantity = 10; max = 100;
    array_create_sequence(data,0,quantity - 1,max * 2,1,OBJECTS_MAX);
    printf("element: less than %d: n %% 10 == 0: three-digits: idx %% 3 == 0:\n", max);
    char sign[] = "-+";
    for (i = 0; i < quantity; ++i) {
        printf("%d\t\t",data[i]);
        result = array_check_element(data,i,max,chk_less,OBJECTS_MAX);
        printf("%c\t    ", sign[result]);
        result = array_check_element(data,i,10,chk_div,OBJECTS_MAX);
        printf("%c\t\t    ", sign[result]);
        result = (array_check_element(data,i,1000,chk_less,OBJECTS_MAX)
                  && array_check_element(data,i,99,chk_more,OBJECTS_MAX));
        printf("%c\t\t", sign[result]);;
        result = array_check_element(data,i,3,chk_div,OBJECTS_MAX);
        printf("%c\n", sign[result]);
    }
    printf("\n11.41 - 11.45, print first even and then odd elements;\n");
    quantity = 10; max = 10;
    array_create_sequence(data,0,quantity - 1,max,1,OBJECTS_MAX);
    printf("source values: ");
    array_print(data,quantity,prt_element);
    printf("\nelement:\teven-odd:\tis zero:\teven idx:\todd idx:\n");
    for (i = 0; i < quantity; ++i) {
        printf("%d\t\t",data[i]);
        result = array_check_element(data,i,2,chk_parity,OBJECTS_MAX);
        if (result)
            printf("even\t\t");
        else
            printf("odd\t\t");
        result = array_check_element(data,i,0,chk_equal,OBJECTS_MAX);
        printf("%c\t",sign[result]);
        if (i % 2 == 0)
            printf("\t%d[%d]", data[i],i);
        else
            printf("\t\t\t%d[%d]", data[i],i);
        printf("\n");
    }
    printf("11.46 - 11.51, using string of commands;\n");
    quantity = 10; random_max = 10;
    printf("all posible checks, command letter:\n");
    for (enum array_check_type i = chk_info; i != chk_end; ++i)
        printf("%c:\t %s\n", comm_chk_name[i], array_check_name[i]);
    printf("all posible actions, command letter:\n");
    for (enum array_action_type i = act_info; i != act_end; ++i)
        printf("%c:\t %s\n", comm_act_name[i], array_action_name[i]);
    char* commands[] = {"L9U2","L9U2","L9U2","L9U2","L9U2","L9U2"};
    char* tasks[] = {"11.46, all negative numbers became absolute",
                     "11.47, all elements more than 3 to square root",
                     "11.48, all positive minus k1, other minus k2",
                     "11.49, all negative add m1, other add m2",
                     "11.50, all positive sub k1, all negative sub n",
                     "11.51, all negative add a1, all zeroes sub b"};
    printf("!\n");
    for (i = 0; i < 6; ++i) {
        /*
        for (j = 0; j < string_length(commands[i]); ++j) { // найти функцию.
            printf("%c\n", commands[i][j]);
            if (commands[i][j] == '_')
                commands[i][j] = (char)('0' + (rand() % random_max)); //Разобраться.
            printf("%c\n", commands[i][j]);
        }
        */
        printf("\n\n%s, command = %s;\nsource array: ", tasks[i], commands[i]);
        for (j = 0; j < quantity; ++j) {
            data[j] = rand() % random_max - 5;
            printf("%d ",data[j]);
        }
        printf("\n");
        array_update_commands(data,commands[i],quantity);
        printf("result array: ");
        array_print(data, quantity, prt_element);
    }
    printf("\n\n11.55, calculation of the sum of elements matching the condition;\n");
    quantity = 10;
    int a = 3, b = 5;
    array_create_sequence(data,0,quantity - 1,10,0b00000001,OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    result = array_sum_elements(data,quantity,0,chk_idx_odd);
    printf("\nsum of odd elements: %d;\n", result);
    result = array_sum_elements(data,quantity,a,chk_div);
    printf("sum of elements that are multiples of a given number(%d): %d;\n", a, result);
    result += array_sum_elements(data,quantity,b,chk_div);
    printf("sum of array elements that are multiples of a(%d) or b(%d): %d;\n", a, b, result);
    printf("\n11.57, find the total amount of precipitation on even days in February\n");
    quantity = 10;
    array_create_sequence(data, 0, quantity - 1, 10, 0b00000001, OBJECTS_MAX);
    result = array_sum_elements(data, quantity, 0, chk_idx_even);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("sum of precipitation: %d;\n\n", result);
    printf("11.59, quotient of dividing the sum of positive elements by the modulus of the sum of negative elements;\n");
    quantity = 10; random_max = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = array_sum_elements(data,quantity,0,chk_more);
    b = array_sum_elements(data,quantity,0,chk_less);
    if (b != 0)
        printf("\n(%d) / (%d) = %.2f;\n\n", a, abs(b), (double)a / (double)abs(b));
    else
        printf("\n(%d) / (%d) = error;\n\n", a,abs(b));
    printf("\n11.61, Is it true that more precipitation fell on even numbers than on odd numbers?\n");
    quantity = 10;
    srand(time(NULL));
    array_create_sequence(data, 0, quantity - 1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = array_sum_elements(data,quantity,0,chk_idx_even);
    b = array_sum_elements(data,quantity,0,chk_idx_odd);
    if (a < b)
        printf("precipitation on even days is more than on odd days: %d:%d;\n\n", a, b);
    else if (a > b)
        printf("precipitation on odd days is more than on even days: %d:%d;\n\n", a, b);
    else
        printf("precipitation on even days is the same as on odd days: %d:%d;\n\n", a, b);
    printf("11.63 - 11.75;\nsource array: ");
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    result = array_chk_counter(data,quantity,-1,chk_more);
    printf("\n11.63) counter of non-negative elements = %d;", result);
    result = array_chk_counter(data,quantity,0,chk_less);
    printf("\n11.66) counter of negative students scores = %d;", result);
    int data_extra[OBJECTS_MAX];
    a = 2; b = 7; result = 0;
    for (i = 0; i < quantity; ++i)
        if (data[i] >= a && data[i] <= b)
            ++result;
    printf("\n11.69) counter of elements in [%d:%d] = %d;\n", a, b, result);
    result = array_chk_counter(data,quantity,0,chk_less);
    printf("11.72) counter of negative = %d, counter of positive = %d;\n", result, quantity - result);
    result = array_chk_counter(data,quantity,5,chk_more);
    printf("11.75) counter of elements in [5:9] = %d;\n", result);
    for (i = 1, result = 0; i < quantity - 1; ++i)
        if (data[i] > data[i - 1] && data[i] > data[i + 1])
            ++result;
    printf("11.78, counter of elements more than near = %d;\n", result);
    printf("\n11.80 - 11.97;\nsource array: ");
    random_max = 10; quantity = 16;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    result = array_chk_counter(data,quantity,0,chk_equal);
    printf("\n11.81) is no rain in 5 days(%d) - ", result);
    if (result == 5)
        printf("true;\n");
    else
        printf("false;\n");
    result = array_sum_elements(data,quantity,0,chk_more);
    printf("11.83) average of rains in month = %.2f;\n", (double)result / (double)quantity);
}










