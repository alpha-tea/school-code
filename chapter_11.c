#include "global.h"
#include "library.h"

enum array_inf_val {inf_info, inf_addr, inf_mem_size, inf_elements, inf_positiv, inf_negativ,
                    inf_zeros, inf_evens, inf_odds, inf_avarage_a, inf_avarage_g, inf_prim,
                    inf_sum, inf_mult, inf_var_sum, inf_sqr_sum, inf_end};

enum array_check_type {chk_info, chk_more, chk_less, chk_equal, chk_div, chk_sqrt,
                       chk_sign, chk_parity, chk_idx_odd, chk_idx_even, chk_end};

enum array_action_type {act_info, act_mov, act_add, act_sub, act_mult, act_div, act_abs, act_sqrt, act_end};

enum array_xchg_type {xchg_forward, xchg_backward, xchg_even_odd};

//static const char* array_xchg_name[] = {"forward", "backward", "even-odd"};

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
    case act_end:
        ;
    default:
        ;//printf("error, info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;\n",
        // data, offset, parameter, array_action_name[type], limit);
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
        //default:
        //printf("error, info: data = %p, offset = %d, parameter = %d, type = '%s', limit = %d;\n",
        //     data, offset, parameter, array_check_name[type], limit);
    case chk_end:
        ;
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

enum array_print_mode {prt_nope = 0x00, prt_element = 0x01, prt_indexes = 0x02, prt_chars = 0x04};

void array_print(int data[], int limit, int mode)   //Вывод масива в заданном режиме, разделитель - пробел.
{
    for (int i = 0; i < limit; ++i) {
        for (enum array_print_mode mask = prt_element; mask <= prt_chars; mask <<= 1) {
            switch ((enum array_print_mode)mode & mask) {
            case prt_nope:
                break;
            case prt_element:
                printf("%d", data[i]);
                break;
            case prt_indexes:
                printf("[%d]", i);
                break;
            case prt_chars:
                if (data[i] >= 0 && data[i] <= 127)
                    printf("'%c'", data[i]);
                else
                    printf("''");
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
        //Подумать над направлением поиска.
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

int array_create_input(int data[], int init[], int direct, int isInput, int limit)
{
    int i = 0;
    if (limit <= 0) {
        printf("empty array, error;");
        return -1;
    }
    switch (isInput) {
    case 0:
        if (direct > 0)
            for (i = 0; i < limit; ++i)
                data[i] = init[i];
        else
            for (i = limit - 1; i >= 0; --i)
                data[limit - 1 - i] = init[i];
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

int array_unique_elements(int data[], int size, int unique_data[])
{           // функция поиска уникальных элементов, возврат из количества.
    if (size <= 0) {
        printf("error: size incorrect;\n");
        return -1;
    }
    int i = 0, j = 0, counter = 0;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size && (i == j || data[i] != data[j]); ++j)
            ;
        if (j == size)
            unique_data[counter++] = data[i];
    }
    return counter;
}

int array_copy_elements(int data[], int size, int copies_data[])
{           //Функция поиска элементов массива, имеющих копии.
    if (size <= 0) {
        printf("error: size incorrect;\n");
        return -1;
    }
    int i = 0, j = 0, k = 0, counter = 0;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size && (i == j || data[i] != data[j]); ++j)
            ;
        if (j != size) {
            for (k = 0; k < counter && data[j] != copies_data[k]; ++k)
                ;
            if (k == counter)
                copies_data[counter++] = data[i];
        }
    }
    return counter;
}

int array_min_max(int data[], int size, int type, int step, int* idx)
{           //Функция поиска максимального и минимального элемента в массива.
    //data - первый элемент массива.
    //size - размер(кол-во элементов) массива.
    //step - шаг.
    //*idx - возврат индекс максимального или минимального элемента
    //type - NULL - min, not NULL - max
    if (size <= 0 || abs(step) == 0) {
        printf("error: size or step incorrect;\n");
        return -1;
    }
    int i = (step > 0) ? 0 : size - 1;
    int max = data[i], min = data[i], idx_max = i, idx_min = i;
    for (; (step > 0 && i < size) || (step < 0 && i >= 0); i += step) {
        if (data[i] > max) {    //не оптимален.
            max = data[i];
            idx_max = i;
        }
        if (data[i] < min) {
            min = data[i];
            idx_min = i;
        }
    }
    //printf("min = %d(%d), max = %d(%d);\n",min,idx_min,max,idx_max);
    if (type != 0) {
        *idx = idx_max;
        return max;
    } else {
        *idx = idx_min;
        return min;
    }
}

int array_xchg_elements(int data[], int size, int idx_a, int idx_b)
{
    if (idx_a == idx_b || idx_a < 0 || idx_a >= size || idx_b < 0 || idx_b >= size) {
        printf("error: in indexes;");
        return -1;
    }
    int tmp = data[idx_a];
    data[idx_a] = data[idx_b];
    data[idx_b] = tmp;
    return 0;
}

int array_xchg_range(int data[], int size, int idx_size_flags[])
{   //idx size flags offsets: 0 - start, 1 - length, 2 - exchange type.
    if (size <= 0) {
        printf("error: size incorrect;\n");
        return -1;
    }
    const int idx_size = 3;
    int i = 0, j = 0, counter = 0;
    while (idx_size_flags[i + 1] > 0) {
        if (idx_size_flags[i] > size)
            printf("warning: start element more than size");
        switch (idx_size_flags[i + 2]) {
        case xchg_forward:
            //printf("forward ");
            for (j = 0; j < idx_size_flags[i + 1] && j < idx_size_flags[i + 4]; ++j)
                array_xchg_elements(data,size,idx_size_flags[i] + j,idx_size_flags[i + 3] + j);
            i += idx_size * 2;
            counter += j;
            break;
        case xchg_backward:
            //printf("backward ");
            for (j = 0; j < idx_size_flags[i + 1] && j < idx_size_flags[i + 4]; ++j)
                array_xchg_elements(data,size,idx_size_flags[i] + j,
                                    idx_size_flags[i + 3] + idx_size_flags[i + 4] - j - 1);
            i += idx_size * 2;
            counter += j;
            break;
        case xchg_even_odd:
            //printf("even-odd ");
            for (j = 0; j < idx_size_flags[i + 1]; j += 2)
                array_xchg_elements(data,size,idx_size_flags[i] + j, idx_size_flags[i] + j + 1);
            i += idx_size;
            counter += j / 2;
            break;
        default:
            printf("error: exchange type not correct;\n");
            ++i;
        }
    }
    return counter;
}

int array_delete_element(int data[], int size, int index)
{
    if (index < 0 || index >= size) {
        printf("error in index;\n");
        return -1;
    }
    int i = 0;
    for (i = index; i < size - 1; ++i)
        data[i] = data[i + 1];
    data[size - 1] = 0;
    return 0;
}

int array_delete_all(int data[], int size, int parameter, enum array_check_type type)
{
    //Удаляет все элементы по условию, возвращает кол-во удаленных элементов.
    if (size < 1 || type < 0 || type >= chk_end) {
        printf("error in size or type;");
        return -1;
    }
    int counter = 0;
    for (int i = 0; i < size;)
        if (array_check_element(data,i,parameter,type,size)) {
            array_delete_element(data,size--,i);
            counter++;
        } else
            ++i;
    return counter;
}

int array_delete_equal(int data[], int size)
{
    //Посмотреть быстрые методы для полностью случайного массива.
    if (size < 2) {
        printf("error in size;/n");
        return -1;
    }
    int i = 0, j = 0, k = 0, number = 0;
    for (i = 0; i < size - 1; ++i) {
        number = data[i];
        for (j = i + 1; j < size - 1;)
            if (data[j] == number) {
                for (k = j; k < size - 1; ++k)
                    data[k] = data[k + 1];
                size--;
            } else
                ++j;
    }
    return size - 1;
}

int array_insert_element(int data[], int size, int element, int index)
{   // Функция вставки элементов, массив расширяется без контроля длинны.
    if (size < 1 || index > size || index < 0) {
        printf("error in size;");
        return -1;
    }
    for (int i = size; i > index; --i)
        data[i] = data[i - 1];
    data[index] = element;
    return 0;
}

int array_insert_all(int data[], int size, int element, int parameter, enum array_check_type type)
{
    if (size < 1 || type < 0 || type >= chk_end) {
        printf("error in size or type;/n");
        return -1;
    }
    int counter = 0;
    for (int i = 0; i < size; ++i)
        if (array_check_element(data, i, parameter, type, size)) {
            array_insert_element(data, size++, element, i++);
            counter++;
        }
    return counter;
}

int digits_mul(int factor_a[], int factor_b[], int result[], int size)
{                   //Дополнить произвольным основанием системы счисления.
    if (size < 1)
        return -1;
    int number_tmp[size], a = 0;
    for (int j = size - 1, counter = 0, k = 0; j >= 0; --j, ++counter, k = 0) {
        if (factor_b[j] != 0) {
            for (int i = 0; i < size; ++i)
                number_tmp[i] = 0;
            for (int i = size - 1; i >= 0; --i) {
                int a = factor_a[i] * factor_b[j];
                number_tmp[i] += ((a % 10) + k) % 10;
                if ((a % 10) + k > 9)
                    k = a / 10 + 1;
                else
                    k = a / 10;
            }
            int b = k;      //Переполнение.
            for (k = size - 1; k >= 0; --k) { // После оформить в функцию если понадобится.
                a = result[k + size - counter] + number_tmp[k];
                result[k + size - counter] = a % 10;
                if (a > 9)
                    result[k + size - counter - 1]++;
                if (k == 0)
                    result[k + size - counter - 1] += b;
            }
        }
    }
    return 0;
}

int digits_add(int add_a[], int add_b[], int result[], int size)
{                     //Дополнить произвольным основанием системы счисления.
    if (size < 1)
        return -1;
    for (int i = size - 1; i >= 0; --i) {
        int a = add_a[i] + add_b[i];
        if (a > 9) {
            if (i > 0)
                result[i - 1]++;
            else
                return -1;
        }
        result[i] = a % 10;
    }
    return 0;
}

int digits_sub(int sub_a[], int sub_b[], int result[], int size)
{                       //Дополнить произвольным основанием системы счисления.
    if (size < 1)
        return -1;
    for (int i = size - 1; i >= 0; --i) {
        int a = sub_a[i] - sub_b[i];
        if (a < 0) {
            if (i != 0) {
                result[i - 1]--;        //Подумать для страховки.
            } else
                return -1;
            result[i] = 10 - abs(sub_b[i] - sub_a[i]);
        } else
            sub_a[i] = a;
    }
    return 0;
}

int digits_div(int div_a[], int div_b[], int result[], int size, int size_result)
{
    int num_2 = 0, num_1 = 0, number = 0;       //Сделать без преобразования в num,
    //можно создавать доп.массивы
    int b = 0, i = 0, j = 0, k = 0, tmp = 0, length = 0, counter = 0;
    for (b = 0; div_b[b] == 0; ++b)          //Напишем вместе, оформить в функцию.
        ;
    for (i = size - 1; i >= 0; --i)
        num_2 += div_b[i] * pow(10,size - i - 1);
    for (b = 0; div_a[b] == 0; ++b)
        ;
    for (i = size - 1; i >= 0; --i)
        num_1 += div_a[i] * pow(10,size - i - 1);
    length = size - b;
    printf("num 1 = %d, num 2 = %d, length = %d, b = %d;\n", num_1, num_2, length, b);
    for (i = b; i < size; ++i) {
        //for (j = b; j <= i; ++j)
        number = number * 10 + div_a[i];
        //printf("!%d ",number);
        if (number >= num_2) {
            for (k = 0, tmp = 0; tmp < number; ++k) {
                tmp += num_2;
            }
            if (tmp != number) {
                tmp -= num_2;
                --k;
            }
            for (j = 0; k != 0 && j < size_result; ++j, ++ counter) {
                result[counter] = k / 10;
                k /= 10;
            }
            number -= tmp;
        }

        if (div_a[i] == 0 && num_1 % tmp == 0) {
            result[counter] = 0;
            ++counter;
        }
    }
    printf("number = %d, tmp = %d", number, tmp);
    result[counter] = -1;
    return 0;
}

int array_add(int data_a[], int data_b[], int data_r[], int size)
{   //Функция сложения двух массивов по элементно и сохранение в третий.
    //Возвращает сумму всех элементов.
    if (size < 1)
        return -1;
    int i = 0, result = 0;
    for (i = 0; i < size; ++i) {
        data_r[i] = data_a[i] + data_b[i];
        result += data_r[i];
    }
    return result;
}

int array_sub(int data_a[], int data_b[], int data_r[], int size)
{   //Функция вычитание двух массивов по элементно и сохранение в третий.
    //Возвращает разность всех элементов.
    if (size < 1)
        return -1;
    int i = 0, result = 0;
    for (i = 0; i < size; ++i) {
        data_r[i] = data_a[i] - data_b[i];
        result -= data_r[i];
    }
    return result;
}

int array_mul(int data_a[], int data_b[], int data_r[], int size)
{   //Функция умножения двух массивов по элементно и сохранение в третий.
    //Возвращает произведение всех элементов.
    if (size < 1)
        return -1;
    int i = 0, result = 1;
    for (i = 0; i < size; ++i) {
        data_r[i] = data_a[i] * data_b[i];
        result *= data_r[i];
    }
    return result;
}

int array_div(int data_a[], int data_b[], int data_r[], int size)
{   //Функция деления двух массивов по элементно и сохранение в третий.
    //Возвращает сред. арифметическое результирующих элементов.
    if (size < 1)
        return -1;
    int i = 0, result = 1;
    for (i = 0; i < size; ++i) {
        data_r[i] = data_a[i] / data_b[i];
        result += data_r[i];
    }
    return result / (i + 1);
}

int array_is_descending(int data[], int size)
{               //Функция определения строго убывающей последовательности.
    if (size < 1)
        return -1;
    int i = 0;
    for (i = 0; i < size - 1 && data[i] > data[i + 1]; ++i)
        ;
    if (i == size - 1)
        return 1;
    return 0;
}

int array_is_ascending(int data[], int size)
{
    //Функция определения строго возврастающей последовательности.
    if (size < 1)
        return -1;
    int i = 0;
    for (i = 0; i < size - 1 && data[i] < data[i + 1]; ++i)
        ;
    if (i == size - 1)
        return 1;
    return 0;
}

int array_is_equal(int data[], int size)
{
    //Функция определения равнойэлементной последовательности.
    if (size < 1)
        return -1;
    int i = 0;
    for (i = 0; i < size - 1 && data[i] == data[i + 1]; ++i)
        ;
    if (i == size - 1)
        return 1;
    return 0;
}

int array_find_if(int data[], int result[], int par, int size, enum array_check_type type)
{
    if (size < 1)
        return -1;
    int i = 0, counter = 0;
    for (i = 0; i < size; ++i)
        if (array_check_element(data,i,par,type,OBJECTS_MAX))
            result[counter++] = data[i];
    return counter;
}

int array_comparison(int data_1[], int data_2[], int data_result[], int par, enum array_check_type type, int length)
{
    if (length < 1)
        return -1;
    for (int i = 0; i < length; ++i) {
        if (array_check_element(data_1,i,par,type,length) == array_check_element(data_2,i,par,type,length))
            data_result[i] = 1;
        else
            data_result[i] = 0;
    }
    return 0;
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
    array_create_input(data, init, 1, 0, length);
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
    /*
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
        for (j = 0; j < string_length(commands[i]); ++j) { // найти функцию.
            printf("%c\n", commands[i][j]);
            if (commands[i][j] == '_')
                commands[i][j] = (char)('0' + (rand() % random_max)); //Разобраться.
            printf("%c\n", commands[i][j]);
        }
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
    */
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
    printf("11.84) average of rains in month = %.2f;\n", (double)result / (double)quantity);
    random_max = 20; quantity = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    for (i = 0; i < quantity; ++i)
        if (data[i] < 0)
            data[i] -= 150;
        else
            data[i] += 150;
    printf("11.87) Height of students: ");
    array_print(data, quantity, prt_element | prt_indexes);
    a = array_sum_elements(data,quantity,0,chk_less);
    b = array_sum_elements(data,quantity,0,chk_more);
    int counter = array_chk_counter(data,quantity,0,chk_less);
    printf("\naverage height of boys = %.2f, average height of girls = %.2f;\n",
           fabs((double)a / (double)counter), (double)b / (double)(quantity - counter));
    printf("11.90) search elements more than sum\n");
    result = a + b; //from previous task;
    array_print(data, quantity, prt_element | prt_indexes);
    counter = array_chk_counter(data,quantity,result,chk_more);
    printf("quantity = %d, sum = %d;\n", counter, result);
    printf("11.93 - 11.96, prices for goods: ");
    random_max = 20; quantity = 10;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    result = array_sum_elements(data,quantity,-1,chk_more);
    result /= quantity;
    counter = array_chk_counter(data,quantity,result,chk_more);
    printf("\naverage of cost = %d,  quantity elements more than average = %d;\n", result, counter);
    printf("diff prices: ");
    for (i = 0; i < quantity; ++i)
        printf("%d ", result - data[i]);
    counter = 5;
    int idx = 0;
    printf("\n\n11.99, source array, size = %d, range = %d: ", quantity, counter);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n");
    for (i = 0, max = 0; i < quantity - counter; ++i) {
        summ = array_sum_elements(&data[i],counter,0,chk_more);
        if (summ > max) {
            max = summ;
            idx = i;
        }
        printf("sum = %d[%d:%d]\n", summ ,i, i + 5);
    }
    printf("max in summs = %d[%d:%d];\n\n", max, idx, idx + 5);
    printf("11.100-11.102, search unique elements and copies;\n");
    random_max = 5; quantity = 3;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\ncopies: ");
    a = array_copy_elements(data,quantity,data_extra);
    array_print(data_extra, a, prt_element | prt_indexes);
    if (a == 1)
        printf("\n11.101 - 11.102 - yes, one copy = %d;\n", data_extra[0]);
    else
        printf("\n11.101 - 11.102 - no, not one copy;\n");
    printf("unique: ");
    b = array_unique_elements(data,quantity,data_extra);
    array_print(data_extra, b, prt_element | prt_indexes);
    if (b > 0)
        printf("\n11.100 - yes, some uniq elements;\n");
    else
        printf("\n11.100 - no, no uniq elements;\n");
    printf("\n11.103*, Changes of signin array: ");
    random_max = 10; quantity = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 1, counter = 0; i < quantity; ++i) {
        if ((data[i] < 0 && data[i - 1] > 0) || (data[i] > 0 && data[i - 1] < 0))
            ++counter;
    }
    printf("\nChanges of sign = %d;\n\n", counter);
    printf("11.104*-11.106*, ascending sequence;\nsource vales: ");
    for (i = 0, a = 0; i < quantity; ++i) {
        data[i] = a;
        a += rand() % 1;
        printf("%d ", data[i]);
    }
    for (i = 0, counter = 0, result = 1, a = 0, length = 0, max = 0; i < quantity - 1; ++i) {
        if (data[i] == data[i + 1] && a == 0) {
            ++counter;
            length = 2;
            a = 1;
        } else if ((data[i] != data[i + 1]) || (a == 1 && i == quantity - 2)) {
            if (max < length) {
                max = length + (i == quantity - 2);
                b = data[i];
            }
            if (data[i] != data[i + 1])
                ++result;
            a = 0;
        } else if (data[i] == data[i + 1] && a == 1)
            ++length;
    }
    printf("\ncounter of sequences = %d, uniq elements = %d, longest element = %d(elem = %d);\n\n",
           counter, result, max, b);
    printf("11.107, search max and min;\nsource array: ");
    random_max = 10; quantity = 5;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    int *ptr_max = &random_max, *ptr_min = &quantity;
    max = array_min_max(data,quantity,1,1,ptr_max);
    min = array_min_max(data,quantity,0,1,ptr_min);
    printf("\nmax = %d\nmin = %d\ndiff(max - min) = %d\nidx max = %d;\nidx min = %d;\n\n",
           max, min, max - min, *ptr_max, *ptr_min);
    printf("11.111, search max;\n");
    result = 0;
    int max_idx = 1, min_idx = 0;
    max = array_min_max(data,quantity,1,1,&max_idx);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("max score = %d, idx = %d\n\n", max, max_idx);
    printf("11.113, search diff max and min;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    max = array_min_max(data,quantity,1,1,&max_idx);
    min = array_min_max(data,quantity,0,1,&min_idx);
    printf("\ndiff = %d;\n\n", max - min);
    printf("11.114, athlete assessment;\n");
    random_max = 10; quantity = 10;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    min = array_min_max(data,quantity,0,1,&min_idx);
    max = array_min_max(data,quantity,1,1,&max_idx);
    data[max_idx] = 0;
    data[min_idx] = 0;
    result = array_information(data,quantity,inf_sum);
    printf("\nmax = %d(%d)\nmin = %d(%d)\nscore = %d / %d = %d;\n\n", max, max_idx, min, min_idx,
           result, quantity, result / quantity);
    printf("11.118, finding the first max and last max;\n");
    quantity = 10;
    array_print(data, quantity, prt_element | prt_indexes);
    max = array_min_max(data,quantity,1,1,&max_idx); // first max
    printf("\nfirst max: %d(%d)\n",max,max_idx);
    max = array_min_max(data,quantity,1,-1,&max_idx); // last max
    printf("last max: %d(%d)\n\n",max,max_idx);
    printf("11.123, how many coldest days;\n");
    random_max = 5; quantity = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    min = array_min_max(data,quantity,0,1,&min_idx);
    result = array_chk_counter(data,quantity,min,chk_equal);
    printf("\ncoldest = %d\nquantity = %d;\n\n", min, result);
    printf("11.124, how many max and min;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    max = array_min_max(data,quantity,1,1,&max_idx);
    min = array_min_max(data,quantity,0,1,&min_idx);
    printf("\nall indexes of max elements(%d): ", max);
    result = -1;
    while ((result = array_scan_element(data,result + 1,quantity,max,chk_equal)) != -1)
        printf("%d ", result);
    printf("\nall indexes of min elements(%d): ", min);
    result = -1;
    while ((result = array_scan_element(data,result + 1,quantity,min,chk_equal)) != -1)
        printf("%d ", result);
    printf("\n\n");
    printf("11.127,;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    max = array_min_max(data,quantity,1,1,&max_idx);
    min = array_min_max(data,quantity,0,1,&min_idx);
    if (max - min == 10)
        printf("\nYes!, more than 10, max = %d, min = %d\n\n",max,min);
    else
        printf("\nNo!, less than 10, max = %d, min = %d\n\n",max,min);
    printf("11.130, first max or first min idx;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    array_min_max(data,quantity,1,1,&max_idx);
    array_min_max(data,quantity,0,1,&min_idx);
    if (max_idx < min_idx)
        printf("\nMax (%d)(%d);\n\n",max_idx, min_idx);
    else
        printf("\nMin (%d)(%d);\n\n",max_idx, min_idx);
    printf("11.132, 11.138, 11.140 - 11.141, finding some highest and lowest values;\n");
    random_max = 20; quantity = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    int idxs_max[OBJECTS_MAX], idxs_min[OBJECTS_MAX], data_max[OBJECTS_MAX], data_min[OBJECTS_MAX];
    counter = 5;
    for (i = 0; i < counter; ++i) {
        data_max[i] = -random_max;
        data_min[i] = random_max;
        idxs_max[i] = 0;
        idxs_min[i] = 0;
    }
    for (i = 0; i < quantity; ++i) {
        for (k = counter - 1; k >= 0; --k) {
            if (data_max[k] <= data[i]) {
                for (j = 0; j < k; ++j) {
                    data_max[j] = data_max[j + 1];
                    idxs_max[j] = idxs_max[j + 1];
                }
                data_max[k] = data[i];
                idxs_max[k] = i;
                break;
            }
        }
        for (k = counter - 1; k >= 0; --k) {
            if (data_min[k] >= data[i]) {
                for (j = 0; j < k; ++j) {
                    data_min[j] = data_min[j + 1];
                    idxs_min[j] = idxs_min[j + 1];
                }
                data_min[k] = data[i];
                idxs_min[k] = i;
                break;
            }
        }
    }
    printf("\nMax:\n");
    for (i = counter - 1; i >= 0; --i)
        printf("%d) %d[%d];\n", i + 1, data_max[i], idxs_max[i]);
    printf("Min:\n");
    for (i = counter - 1; i >= 0; --i)
        printf("%d) %d[%d];\n", i + 1, data_min[i], idxs_min[i]);
    printf("\n11.142, change the sign of the element maximum in absolute value;\n");
    max = data[0];
    for (i = 1; i < quantity; ++i) {
        if ((data[i] > 0 && data[i] > max) || (data[i] < 0 && data[i] * -1 > max)) {
            max = data[i];
            idx = i;
        }
    }
    data[idx] *= -1;
    printf("result = %d;\n\n", data[idx]);
    printf("11.143, bubble sort;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; i < quantity; ++i) {
        for (j = 0; j < quantity - i - 1; ++j)
            if (data[j] > data[j + 1]) {
                result = data[j];
                data[j] = data[j + 1];
                data[j + 1] = result;
                /*
                data[j] ^= data[j + 1];
                data[j] ^= data[j + 1];
                data[j] ^= data[j + 1];
                */
            }
    }
    printf("\nresult: ");
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.144, exchange elements;\nsource array: ");
    random_max = 20; quantity = 10;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = 2; b = 7; array_min_max(data,quantity,1,1,&result);
    array_xchg_elements(data,quantity,a,b);
    printf("\na,b) result(%d,%d): ",a,b);
    array_print(data, quantity, prt_element | prt_indexes);
    array_xchg_elements(data,quantity,3,result);
    printf("\nc) result(%d,%d): ",3,result);
    array_print(data, quantity, prt_element | prt_indexes);
    array_min_max(data,quantity,0,-1,&result);
    array_xchg_elements(data,quantity,0,result);
    printf("\nd) result(%d,%d): ",0,result);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.145, exchange elements;\nsource array: ");
    int ranges[] = {0, 5, xchg_forward, 5, 5, xchg_forward, 0, 0, 0,
                    0, 10, xchg_even_odd, 0, 0, 0, 0, 0, 0,
                    0, 5, xchg_backward, 5, 5, xchg_backward, 0, 0, 0};
    array_print(data, quantity, prt_element | prt_indexes);
    char* info_ranges[] = {"a, forward exchange in half array:",
                           "b, even-odd exchange:",
                           "c, backward exchange in half array:"};
    for (i = 0; i < 3; ++i) {
        printf("\n%s", info_ranges[i]);
        array_xchg_range(data,quantity,&ranges[i * 9]);
        printf("\n");
        array_print(data, quantity, prt_element | prt_indexes);
    }
    printf("\n\n11.147, exchange elements;\nsource array: ");
    array_print(data, quantity, prt_element | prt_indexes);
    array_min_max(data,quantity,1,1,&a);
    array_min_max(data,quantity,0,1,&b);
    if (data[a] > data[b]) {
        max = a;
        min = b;
    } else {
        max = b;
        min = a;
    }
    for (i = 0; i <= (max - min) / 2 + 1 - (max - min) % 2; ++i)
        array_xchg_elements(data,quantity,min + i,max - i);
    printf("\nresult(max = %d, min = %d):\n", max, min);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.149, delete elements;\nsource array: ");
    result = rand() % quantity;
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\nresult(%d) = ", result);
    array_delete_element(data,quantity,result);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.151, delete max and min elements;\n");
    uniq_gen_fast_alt(data,quantity,20);
    array_print(data, quantity, prt_element | prt_indexes);
    array_min_max(data,quantity,1,1,&a);
    array_delete_element(data,quantity,a);
    array_min_max(data,quantity - 1,0,1,&b);
    array_delete_element(data,quantity - 1,b);
    printf("\nresult(max %d, min = %d): ", a, b);
    array_print(data, quantity - 2, prt_element | prt_indexes);
    printf("\n\n11.153, delete first negative and first even elements;\n");
    random_max = 20; quantity = 10; a = -1; b = -1;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = array_scan_element(data,0,quantity,0,chk_less);
    if (a != -1)
        array_delete_element(data,quantity,a);
    for (i = quantity - 1; i >= 0 && data[i] % 2 != 0; --i)     //not use functions
        ;
    if (i != -1)
        array_delete_element(data,quantity,i);
    printf("\nresult(negative = %d, even = %d);\n", a, i);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.156, delete elements;\n");
    quantity = 20;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    quantity -= array_delete_all(data,quantity,0,chk_less);
    printf("\na, negative: ");
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % random_max / 2 + 10;
    quantity -= array_delete_all(data,quantity,a,chk_more);
    printf("\nb, more than a(%d): ",a);
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % quantity;
    b = (a != 0) ? rand() % a: 0;
    for (i = b; i <= a; ++i, quantity--)
        array_delete_element(data,quantity,b);
    printf("\nc, from b(%d) to a(%d): ", b, a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.157, delete elements;\n");
    quantity = 10;
    array_create_sequence(data, 1, 1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 1; i < quantity; i += 2)
        if (array_check_element(data,i,2,chk_div,quantity))
            data[i] = random_max;
    quantity -= array_delete_all(data, quantity, random_max, chk_equal);
    printf("\na: ");
    array_print(data, quantity, prt_element | prt_indexes);
    quantity -= array_delete_all(data, quantity, 3, chk_div);
    quantity -= array_delete_all(data, quantity, 5, chk_div);
    printf("\nb: ");
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.158, delete equal elements;\n");
    random_max = 10; quantity = 30;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = array_delete_equal(data,quantity);
    printf("\nnew size = %d|",a);
    array_print(data, a, prt_element | prt_indexes);
    printf("\n\n11.159, insert element;\n");
    random_max = 20; quantity = 10;
    a = rand() % random_max;
    b = rand() % quantity;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    array_insert_element(data,quantity,a,b);
    printf("\nresult(idx = %d, num = %d): ",b,a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.161, insert element;\n");
    int names[] = {'a', 'f', 'k', 'r', 'x'};
    quantity = 5;
    a = 'a' + rand() % ('z' - 'a');
    printf("\nsource string with peaks: ");
    array_print(names, quantity, prt_chars | prt_indexes);
    b = array_scan_element(names,0,quantity,a,chk_more);    //В упорядоченном массиве можно использовать более быстрый поиск.
    array_insert_element(names,quantity,a,b);
    printf("\nname = %c, height = %d, index = %d;\n", a, b, i);
    array_print(names, quantity + 1, prt_chars | prt_indexes);
    printf("\n\n11.163, insert elements before and after max;\n");
    quantity = 10;
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % random_max;
    b = rand() % random_max;
    array_min_max(data,quantity,1,1,&result);
    array_insert_element(data,quantity++,a,result + 1);
    array_insert_element(data,quantity++,b,result);
    printf("max idx = %d, before = %d, after = %d\n", result, b, a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.164, insert elements before multiples of a and after all negative elements;\n");
    quantity = 10;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % quantity + 1;
    b = rand() % random_max;
    quantity += array_insert_all(data,quantity,b,a,chk_div);
    quantity += array_insert_all(data,quantity,b,0,chk_less);
    printf("a = %d, number = %d;\n", a, b);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.167, insert the number and after the number where there is a digit 5;\n");
    a = rand() % random_max;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; i < quantity; ++i) {
        result = number_to_digits(data[i],data_extra,2);
        while (result > 0)
            if (data_extra[--result] == 5) {
                array_insert_element(data,quantity++,a,i++);
                break;
            }
    }
    printf("a = %d\n",a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.168, insert the number n between numbers with the same sign;\n");
    a = rand() % random_max;
    array_create_sequence(data, -1, -1, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; i < quantity - 1; ++i)
        if (abs(data[i]) / data[i] == abs(data[i + 1]) / data[i + 1])
            array_insert_element(data,quantity++,a,++i);
    printf("a = %d\n",a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.170, rearrange the first element in place of k;\n");
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % quantity;
    b = data[0];
    for (i = 0; i < a; ++i)
        data[i] = data[i + 1];
    data[a] = b;            //Сохраняем элемент в позицию а.
    printf("k = %d;\n", a);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.174, rearrange the last element in place of k;\n");
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % quantity;
    array_insert_element(data,quantity,data[quantity - 1],a);
    printf("k = %d;\n", a);
    array_print(data, ++quantity, prt_element | prt_indexes);
    printf("\n\n11.177, correct sequence order;\n");
    b = rand() % (quantity - 1) + 1;
    for (i = 0, a = 0; i < quantity; ++i) { //Использовать арифметическую последовательность.
        if (i != b) {
            a += rand() % random_max + random_max;
            data[i] = a;
        } else {
            a -= rand() % random_max;
            data[i] = a;
        }
    }
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; i < quantity - 1 && data[i] < data[i + 1]; ++i)
        ;
    if (i + 1 != quantity)
        data[i + 1] = data[i] + rand() % (data[i + 2] - data[i]); // 0-1 не бывает.
    else
        data[i + 1] = data[i] + rand() % random_max;
    printf("error in %d, b = %d;\n",i + 1, b);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n\n11.182, print all elements in array except first and last zero;\n");
    quantity = 10;
    array_create_sequence(data, 0, 0, random_max, 0b00000001, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    printf("\n");
    for (i = 0; data[i] != 0 && i < quantity; ++i)
        printf("%d ", data[i]);
    for (i++; i < quantity; ++i)
        printf("%d ", data[i]);
    printf("\n\n11,183, ascending array with numbers: ");
    quantity = 16;
    array_create_sequence(data, 0, 48, 3, 0b00000010, OBJECTS_MAX);
    array_print(data, quantity, prt_element | prt_indexes);
    a = rand() % 48;
    printf("\na) elements less than %d:\n", a);
    for (i = 0; data[i] < a && i < quantity; ++i)
        printf("%d ", data[i]);
    printf("\nb) fast search forward: ");
    for (i = 0, j = 1, k = 0; i < quantity && data[i] < a; i += j, j++, ++k)
        ;
    if (i > quantity)   //если дошли до конца массива.
        i = quantity - 1;
    printf("element more or equal than %d founded at %d position;\n", a ,i);
    for (; (data[i - 1] >= a || i == 0) && i >= 0; --i, ++k)
        ;
    printf(" element: %d, index: %d, counter: %d;\n", data[i], i, k);
    printf("c) fast search with minimum diff to a = %d;\n", a);
    for (i = quantity / 2, j = quantity / 2, k = 0; data[i] != a && j != 0; j /= 2, ++k) {
        printf("i = %d, j = %d\n", i, j);
        if (data[i] > a)
            i -= j / 2;
        else
            i += j / 2;
    }
    printf("Position: %d, counter = %d", i, k);
    for (i = 1, j = abs(data[0] - a), k = 0; j > abs(data[i] - a); ++i, ++k)
        j = abs(data[i] - a);
    i--;
    printf("\nPosotion with minimum diff is %d, element = %d, counter = %d;\n", i, data[i], k);
    printf("\n11,185, scores of teams in descending order;\n");
    random_max = 50;        //Можно применить быстрый поиск.
    idx = rand() % 16;
    for (i = 0; i < quantity; ++i) {
        data[i] = random_max;
        if (random_max > 5)
            random_max -= 2 + rand() % 4;
        if (idx == i)
            a = data[i];
    }
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; data[i] > a && i < quantity; ++i)
        ;
    printf("\nteam position: %d, score = %d, ", i, data[i]);
    printf("\n\n11,187, scores in class from 5 - 2;\n");
    int score[4] = {4 , 4 , 4, 4};
    for (j = 0; j < quantity; j++) {
        int idx_1 = rand() % 4;
        int idx_2 = rand() % 4;
        if (score[idx_1] > 0) {
            score[idx_1]--;
            score[idx_2]++;
        }
    }
    for (i = 0, k = 0; i < 4; ++i)
        for (j = score[i]; j > 0; --j, ++k)
            data[k] = 5 - i;
    array_print(data, quantity, prt_element | prt_indexes);
    for (i = 0; data[i] == 5; ++i)
        ;
    printf("\nquantity: %d\n\n", i);
    const int d_size = 8;
    int number_1[] = {9,9,9,9,9,9,9,9};
    int number_2[] = {9,9,9,9,9,9,9,9};
    //int number_4[] = {0,0,0,0,0,0,0,0};
    int number_3[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    printf("11.189, digital calculator for arrays");
    printf("\nadd 1:\t");
    array_print(number_1, d_size, prt_element);
    printf("\nadd 2:\t");
    array_print(number_2, d_size, prt_element);
    printf("\nsum:\t");
    digits_add(number_1,number_2,number_1,8);
    array_print(number_1, d_size, prt_element);
    printf("\nsub_2:\t");
    array_print(number_2, d_size, prt_element);
    digits_sub(number_1,number_2,number_1,8);
    printf("\ndiff:\t");
    array_print(number_1, d_size, prt_element);
    printf("\nmul_2:\t");
    array_print(number_2, d_size, prt_element);
    printf("\n");
    digits_mul(number_1,number_2,number_3,8);
    printf("mul:\t");
    array_print(number_3, d_size * 2, prt_element);
    printf("\ndiv1:\t");
    array_print(number_1, d_size, prt_element);
    printf("\ndiv2:\t");
    array_print(number_2, d_size, prt_element);
    printf("\nprivat:\t\n");
    a = 123545;
    return;
    printf("\n11.191, search uniq. digits in number %d\n", a);
    int array_digit[6];
    int uniq_array_digit[6];
    number_to_digits(a,array_digit,6);
    array_print(array_digit,6,prt_element | prt_indexes);
    result = array_unique_elements(array_digit,6,uniq_array_digit);
    printf("\nresult = %d\n\n", result);
    printf("*11,193, 2^100 digits: ");
    printf("\nMethod #1: factorization of size int, 2^100 = 2^25 * 2^25 * 2^25 * 2^25(in binary);\n");
    for (i = 0; i < 4; ++i) {
        unsigned int number = 1;
        for (j = 0; j < 25; ++j)
            number <<= 1;
        //print_binary_dword(number);
    }
    printf("\nMethod #2: factorization of size int, 2^100 = 2^25 * 2^25 * 2^25 * 2^25(in dec);\n");
    int data_nums[] = {5,2,3,1 << 25}; // 128 bits total.
    char hex_num[OBJECTS_MAX];
    hex_num[16] = '\0';     //Вывод в 16-ой системе счисления.
    for (i = 0; i < 4; ++i) {
        int_to_string(&hex_num[i * 4],data_nums[i],16);
        printf("%s:",hex_num);
    }
    printf("\nmethod #3: binary data 128 bit to 32 bit data * 4, convert to array of digits:\n");
    int array_result[128];
    int array_number[8];
    for (i = 0; i < 8; ++i)
        array_number[i] = 0;
    for (i = 0; i < 128; ++i)
        array_result[i] = 0;
    number_to_digits(data_nums[3],&array_result[119],8);
    number_to_digits(data_nums[3],array_number,8);
    array_print(array_number,8,prt_element);
    printf("\n");
    array_print(array_result,128,prt_element);
    printf("\nmethod #4: using arrays:\n");
    int num_a[OBJECTS_MAX];
    int num_b[OBJECTS_MAX];
    int num_r[OBJECTS_MAX];
    int num_s[OBJECTS_MAX]; // слогаемое при умножении на num_r.
    int n_digits = 32, carry = 0, g = 0;
    num_a[n_digits - 1] = 1;
    num_a[n_digits - 2] = 0;
    num_b[n_digits - 1] = 2;
    num_b[n_digits - 2] = 3;
    for (i = 0; i < OBJECTS_MAX; ++i) {
        if (i < n_digits - 2)
            num_a[i] = num_b[i] = 0;
        num_r[i] = num_s[i] = 0;
    }
    array_print(num_a,n_digits,prt_element);
    printf("\n");
    array_print(num_b,n_digits,prt_element);
    printf("\n");
    array_print(num_r,n_digits,prt_element);
    printf("\n");
    array_print(num_s,n_digits,prt_element);
    printf("\n");
    time_t t1 = time(NULL);
    for (i = 0; i < 20; ++i) { //main cycle.
        for (j = n_digits - 1, carry = 0; j >= 0; --j) {
            for (k = n_digits - 1; k >= 0 || carry > 0; --k) {
                num_s[k] = (num_a[k] * num_b[j] + carry) % 10;
                carry = (num_a[k] * num_b[j] + carry) / 10;
                //printf("n_a = %d, n_b = %d, n_s = %d, carry = %d;\n", num_a[k], num_b[j], num_s[k], carry);
            }
            for (g = n_digits - 1, b = j; g != k; --g, --b) {
                int digit = num_r[b] + num_s[g];
                num_r[b] = (digit + carry) % 10;
                carry = (digit + carry) / 10;
                //printf("n_s = %d, n_r = %d, carry = %d, g = %d;\n", num_s[g], num_r[b], carry, g);
            }
        }
        for (g = 0; g < n_digits; ++g) {
            num_a[g] = num_r[g];
            num_r[g] = 0;
        }
    }
    time_t t2 = time(NULL);
    array_print(num_a,n_digits,prt_element);
    printf("\n%s", asctime(gmtime(&t1)));
    printf("\n%s", asctime(gmtime(&t2)));
    /*
    int numerator[] = {0,0,0,0,1,0,2,4};
    int denominator[] = {0,0,0,0,0,5,1,2};
    int result_array[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    digits_div(numerator,denominator,result_array,8, 16);
    printf("\n");
    array_print(result_array,16,prt_element);
    */
    printf("\n\n11.210 - 11.212, func fir check sequence;\n");
    quantity = 15;
    array_create_sequence(data,0,quantity,1,0b00000010,OBJECTS_MAX);
    array_print(data,quantity,prt_element);
    printf("\nis ascending:\t%d\n", array_is_ascending(data,quantity));
    printf("is descending:\t%d\n", array_is_descending(data,quantity));
    printf("is equals:\t%d\n", array_is_equal(data,quantity));
    printf("\n11.214, costs of goods in first and second months;\n");
    int data_1[OBJECTS_MAX] = {1,2,3,4,5}, data_2[OBJECTS_MAX] = {5,4,3,2,1}, data_result[OBJECTS_MAX];
    printf("1)");
    array_print(data_1,5,prt_element);
    printf("\n2)");
    array_print(data_2,5,prt_element);
    array_add(data_1,data_2,data_result,5);
    printf("\nresult: ");
    array_print(data_result,5,prt_element);
    printf("\n\n11.217, total harvest from areas;\n");
    int areas[OBJECTS_MAX] = {1,2,3,4,5}, yield[OBJECTS_MAX] = {6,3,8,4,0}, harvest[OBJECTS_MAX];
    printf("1)");
    array_print(areas,5,prt_element);
    printf("\n2)");
    array_print(yield,5,prt_element);
    result = array_mul(areas,yield,harvest,5);
    result = array_information(harvest,5,inf_sum);
    printf("\nharvest(three arrays): ");
    array_print(harvest,5,prt_element);
    array_mul(areas,yield,areas,5);
    printf("\nharvest(two arrays): ");
    array_print(areas,5,prt_element);
    printf("\ntotal: %d;\n\n",result);
    printf("11.218, parallelepiped with sizes and volumes;\n");
    int parall[] = {2,3,8,6,5,3,5,7,4,2,1,6};
    for (i = 0; i < 12; i += 3) {
        int v = parall[i] * parall[i + 1] * parall[i + 2];
        printf("%d * %d * %d = %d;\n",parall[i], parall[i + 1], parall[i + 2], v);
    }
    printf("\n11.219, search 10 motores with 80 hourse power;\n");
    int car_cost[] = {100,500,230,125,549};
    int car_power[] = {100,70,130,125,49};
    result = array_find_if(car_power,data_result,80,5,chk_less);
    printf("cars cost: ");
    array_print(car_cost, 5, prt_element);
    printf("\ncars power: ");
    array_print(car_power, 5, prt_element);
    printf("\nresult: ");
    array_print(data_result, result, prt_element);
    printf("\n\n11.223, football, goals and loses;\nPlus: ");
    int s_plus[5] = {1,4,3,5,2};  //Забитые.
    int s_minus[5] = {4,5,2,1,2}; //Пропущенные.
    char* result_in_game[] = {"Lose!", "Draw!", "Win!"};
    array_print(s_plus, 5, prt_element);
    printf("\nMinus: ");
    array_print(s_minus, 5, prt_element);
    printf("\na) ");
    for (i = 0; i < 5; ++i) {
        if (s_plus[i] > s_minus[i])
            printf("%d: %s, ", i + 1, result_in_game[2]);
        else if (s_plus[i] < s_minus[i])
            printf("%d: %s, ", i + 1, result_in_game[0]);
        else
            printf("%d: %s, ", i + 1, result_in_game[1]);
    }
    summ = 0;
    array_sub(s_plus,s_minus,data,5);
    result = array_information(data,5,inf_negativ);
    summ += result * 3;
    printf("\nb) %d - wins;", result);
    array_sub(s_plus,s_minus,data,5);
    result = array_information(data,5,inf_positiv);
    summ += result * 0;
    printf("\nc) %d - loses;", result);
    array_sub(s_plus,s_minus,data,5);
    result = array_chk_counter(data,5,0,chk_equal);
    summ += result;
    printf("\nd) %d - draws;\n", result);
    printf("e) %d - scores;\n\n", summ);
    printf("11,232, distants and time, speed: \n");
    int dist[] = {80,72,108,94,96};
    int timer[] = {2,1,3,2,2};
    int speed[5];
    array_div(dist,timer,speed,5);
    array_print(speed,5,prt_element);
    array_min_max(speed,5,1,1,&result);
    printf("\nMax in idx = %d(%d);\n", result, speed[result]);
    printf("\n11.234, find min square of rectangle;\n");
    int points[] = {0,9, 9,0, 6,1, 7,4, 1,9, 9,1};
    min = 81;
    for (i = 0; i < 12; i += 4) {
        int tmp = abs((points[i] - points[i + 2]) * (points[i + 1] - points[i + 3]));
        printf("Square #%d: %d:%d %d:%d, S = %d;\n",
               i + 1, points[i], points[i + 1],  points[i + 2],  points[i + 3], tmp);
        if (tmp < min)
            min = tmp;
    }
    printf("Min size = %d;\n\n", min);
    printf("11.235, copying array elements in different order;\nsource: \n");
    int mass_1[] = {0,1,2,3,4};
    int mass_2[5];
    array_print(mass_1,5,prt_element);
    printf("\n");
    array_create_input(mass_2,mass_1,1,0,5);
    printf("\n");
    array_print(mass_2,5,prt_element);
    array_create_input(mass_2,mass_1,0,0,5);
    printf("\n");
    array_print(mass_2,5,prt_element);
    printf("\n\n11.236, copying array elements according to the rules;\nsource: \n");
    array_print(mass_1,5,prt_element);
    printf("\n");
    for (i = 0; i < 5; ++i)
        if (mass_1[i] % 2 == 0)
            mass_2[i] = pow(mass_1[i],2);
        else
            mass_2[i] = 2 * mass_1[i];
    array_print(mass_2,5,prt_element);
    printf("\n\n11.239, copying array elements according to the rules;\nsource: \n");
    array_print(mass_2,5,prt_element);
    printf("\n");
    for (i = 0; i < 5; ++i)
        if (mass_2[i] % 2 == 0)
            mass_2[i] = mass_2[i] * 2;
    array_print(mass_2,5,prt_element);
    printf("\n\n11.242, copying array elements according to the rules;\nsource: \n");
    array_print(mass_1,5,prt_element);
    printf("\n");
    for (i = 0; i < 5; ++i)
        if (mass_1[i] % 2 != 0)
            mass_2[i] = mass_1[i];
    array_print(mass_2,5,prt_element);
    printf("\n");
    counter = 0;
    for (i = 0; i < 5; ++i)
        if (mass_1[i] % 2 != 0)
            mass_2[counter++] = mass_1[i];
    array_print(mass_2,5,prt_element);
    printf("\n\n11.245, first negative then positive;\nsource: \n");
    quantity = 10;
    srand(time(NULL));
    array_create_sequence(data,-1,-1,random_max,0b00000001,quantity);
    array_print(data,10,prt_element);
    printf("\n");
    int count_neg = 0, count_pos = quantity - 1;
    for (i = 0; i < quantity; ++i)
        if (data[i] < 0)
            data_extra[count_neg++] = data[i];
        else
            data_extra[count_pos--] = data[i];
    array_print(data_extra,10,prt_element);
    printf("\n\n11.247, comparison of signs of arrays if equal then 1 else 0;\nsource: \n");
    array_print(data,quantity,prt_element);
    array_create_sequence(data_extra,-1,-1,random_max,0b00000001,quantity);
    printf("\n");
    array_print(data_extra,quantity,prt_element);
    printf("\n");
    array_comparison(data,data_extra,data_result,0,chk_less,quantity);
    array_print(data_result,quantity,prt_element);
    printf("\n\n11.248, mountain plateau wind data;\n");
    random_max = 8;
    int n = 9; //кол-во исследователей.
    int data_scient[n][quantity];
    for (i = 0; i < n; ++i)
        array_create_sequence(data_scient[i],1,1,random_max,0b00000001,quantity);
    printf("+ ");
    for (i = 0; i < quantity; ++i)
        printf("%d ", i + 1);
    for (i = 0; i < n; ++i) {
        printf("\n%d:",i + 1);
        for (j = 0; j < quantity; ++j)
            printf("%d ", data_scient[i][j]);
    }
}




