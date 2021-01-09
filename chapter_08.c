#include "global.h"
#include "library.h"

int prime_number(int number)
{
    int i = 2;
    for (i = 2; i < number && number % i != 0; ++i)
        ;
    return (i == number);
}

int digital_root(int n)
{
    int a = 0, sum = 0;
    printf("Digital root: n = %d;",n);
    while (n > 0) {
        a = n % 10;
        sum += a;
        printf("%d ",a);
        n /= 10;
    }
    printf(": sum = %d\n",sum);
    if (sum > 9)
        sum = digital_root(sum);
    return sum;
}

void chapter_8()
{
    printf("8.3\na)\n");
    //a
    int i = 1, j = 0;
    for (i = 1; i <= 5; ++i) {
        for (j = 0; j < i; ++j)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nb)\n");
    //b
    int k = 1;
    j = 5;
    for (i = 5; i <= 9; ++i){
        for (j = 1;j <= 10 - i; ++j)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nc)\n");
    //c
    j = 1;
    for (i = 10; i <= 50;i += 10, ++j) {
        for (k = 1; k <= j; ++k)
            printf("%d ",i);
        printf("\n");
    }
    printf("\nd)\n");
    //d
    k = 1, j = 5;
    for (i = 5; i <= 25; i += 5, --j){
        for (k = 1;k <= j; ++k)
            printf("%-3d",i);
        printf("\n");
    }
    printf("\n");
    printf("8.7, Multiplication table:\n");
    j = 1;
    for (i = 1; i <= 9; ++i) {
        for (j = 1; j <= 9; ++j)
            printf("%d x %d = %2d; ", i, j, i * j);
        printf("\n");
    }
    int n = 5, a = 3;
    printf("\n8.9, scores of students:, exams = %d, students = %d;\n",a,n);
    srand(time(NULL));
    printf("\t1\t2\t3, - lessons:\n\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t",i);
        for (j = 0; j < a; ++j)
            printf("%d\t", 1 + rand() % 5);
        printf("\n");
    }
    printf("\nB)\t");
    for (i = 1; i <= n; ++i)
        printf("%d\t",i);
    printf("\n\n");
    for (k = 0; k < a; ++k) {
        printf("%d)\t",k);
        for (j = 1; j <= n; ++j)
            printf("%d\t", 1 + rand() % 5);
        printf("\n");
    }
    a = 3;
    n = 5;
    int sum = 0, sum1 = 0, salary = 0;
    int salary_mass[a];
    for (i = 0; i < a; ++i)
        salary_mass[i] = 0;
    printf("\n8.11,salary for workers, workers = %d, months = %d;\n",n,a);
    printf("Worker:\\Month:\t");
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Total:\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t\t",i);
        sum1 = 0;
        for (j = 0; j < a; ++j) {
            salary = 10 + rand() % 90;
            sum1 += salary;
            sum += salary;
            salary_mass[j] += salary;
            printf("%d\t",salary);
        }
        printf("%d\n",sum1);
    }
    printf("Total:\t\t");
    for (i = 0; i < a ; ++i)
        printf("%d\t",salary_mass[i]);
    printf("%d\n\n",sum);
    n = 5;
    a = 3;
    int c = 1, help = 1;
    printf("8.14, scores of students, students = %d, lessons = %d;\n",n,a);
    sum = 0;      // Количество студентов, сдавшие экзамены без двоек.
    sum1 = 0;     // Количество предметов, по которым были получены только оценки "5" и "4".
    int scores_mass[a], scores_mass1[a];
    printf("Students:\\Lessons:\t");
    for (i = 0; i < a; ++i) {
        scores_mass[i] = 0;
        scores_mass1[i] = 0;
    }
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("\n");
    for (i = 0; i < n; ++i, c = 1, help = 1) {
        printf("%d)\t\t\t",i);
        for (j = 0; j < a; ++j) {
            int score = 1 + rand() % 5;
            if (score < 3)
                scores_mass[j]++;
            if (score < 2 && c == 1)
                c = 0;
            if (score < 2)
                scores_mass1[j]++;
            printf("%d\t",score);
        }
        if (c == 1) {
            sum++;
            printf("Passed without negative scores.");
        } else
            printf("Passed with negative scores.");
        printf("\n");
        if (help == 0)
            sum1++;
    }
    printf("Total negatives:\t");
    for (i = 0; i < a; ++i)
        printf("%d\t",scores_mass[i]);
    printf("\nLucky students: %d;\n",sum);
    printf("Positive lessons:\t");
    for (i = 0; i < a; ++i)
        if (scores_mass1[i] == 0)
            printf("Yes\t");
        else
            printf("No\t");
    printf("\n\n");
    n = 5; // кол-во работников.
    a = 3; // кол-во месяцев.
    printf("8.17, salary for workers, workers = %d, months = %d;\n",n,a);
    int salary_month[a];// для каждого месяца.(б)
    int salary_workers[a];
    printf("Worker:\\Month:\t");
    for (k = 0; k < a; ++k) {
        salary_workers[k] = 0;
        salary_month[k] = 0;
    }
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Max salary on month:\n");
    for (i = 0; i < n; ++i) {
        int max_salary = 0;
        printf("%d)\t\t",i);
        for (j = 0; j < a; ++j) {
            salary = 1 + rand() % 100;
            printf("%d\t",salary);
            if (salary > max_salary)
                max_salary = salary;
            if (i == 0) {
                salary_workers[j] = i;
                salary_month[j] = salary;
            } else if (salary > salary_month[j]) {
                salary_month[j] = salary;
                salary_workers[j] = i;
            }
        }
        printf("%d\n",max_salary);
    }
    printf("Max salary:\t");
    for (i = 0; i < a; ++i)
        printf("%d\t",salary_workers[i]);
    n = 3;  // магазины.
    a = 5;  // дни.
    printf("\n\n8.20, Shop revenue;\n");
    int income_days[a], income_shops[n];
    int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    int max_income = 0,x = 0, y = 0; // номер дня и магазина с максимальным доходом.
    printf("Shops:\\Days:\t");
    for (k = 0; k < a; ++k)
        income_days[k] = 0;
    for (k = 0; k < n; ++k)
        income_shops[k] = 0;
    for (i = 1; i <= a; ++i)
        printf("%d:\t",i);
    printf("Sum of income:\n");
    for (i = 0; i < n; ++i) {
        printf("%d)\t\t",i);
        for (j = 0; j < a; ++j) {
            int income = 1 + rand() % 100;
            income_shops[i] += income;
            income_days[j] += income;
            printf("%d\t",income);
            if (income > max_income) {
                max_income = income;
                x = j;
                y = i;
            }
        }
        printf("%d\n",income_shops[i]);
    }
    printf("Sum of shops:\t");
    for (i = 0; i < n; ++i)
        if (income_shops[i] > r1) {
            r1 = income_shops[i];
            r3 = i;
        }
    for (i = 0; i < a; ++i) {
        printf("%d\t",income_days[i]);
        if (income_days[i] > r2) {
            r2 = income_days[i];
            r4 = i;
        }
    }
    printf("\na)Max sum of days: %d;\n",r3);
    printf("b)Max sum of shops: %d;\n",r4 + 1);
    printf("c)Shop = %d, Day = %d, Max income = %d;\n\n",y,x + 1, max_income);
    n = 5;
    a = 5;
    printf("8.23,goods and sales in days, goods = %d, sales = %d\n",n,a);
    int prices[n], sum_days[a];
    printf("Goods(prices):\\Sales(cost):\t");
    for (i = 0; i < a; ++i) {
        printf("%d:\t", i + 1);
        sum_days[i] = 0;
    }
    printf("Total:\n");
    int all_sum = 0, max_cost = 0, pos_cost= 0, max_day_cost = 0, pos_day_cost = 0;
    for (i = 0; i < n; ++i) {
        prices[i] = 1 + rand() % 9;
        int sum = 0;
        printf("%d(%d):\t\t\t\t",i,prices[i]);
        for (j = 0; j < a; ++j) {
            int quantity = 1 + rand() % 9;
            printf("%d(%d)\t",quantity,prices[i] * quantity);
            sum += quantity * prices[i];
            sum_days[j] += quantity * prices[i];
        }
        printf("%d\n",sum);
        if (sum > max_cost) {
            max_cost = sum;
            pos_cost = i;
        }
        all_sum += sum;
    }
    printf("B) Sum of days:\t\t\t");
    const int limit = 150;
    for (i = 0, n = 0; i < a; ++i) {
        if (sum_days[i] > max_day_cost) {
            max_day_cost = sum_days[i];
            pos_day_cost = i + 1;
        }
        if (sum_days[i] > limit)
            ++n;
        printf("%d\t",sum_days[i]);
    }
    printf("\nV) Total sales for all days: %d;\n",all_sum);
    printf("G) Max cost is: %d and good: %d;\n",max_cost,pos_cost);
    printf("D) Max cost is: %d and day: %d;\n",max_day_cost, pos_day_cost);
    printf("E) Days bigger than limit(%d): %d;\n\n",limit,n);
    n = 20;
    int divs_sum[n], max_divisor = 0, min_divisor = n, m = 2;
    c = 3; //k.
    int max_sum = 0, min_sum = 0, quantity = 0;
    const char* answ[] = {"NO","YES"};
    printf("8.25 - 8.38, Finding divisors, N = %d, C = %d, M = %d:\n",n,c,m);
    printf("T - total, Q - quantity;\n");
    printf("Number:\tDividers(T,Q):\tDivs=C:\tSum %% M:Prime:\tIdeal:\tPairs:\t\n");
    for (i = 0; i < n; ++i) {
        divs_sum[i] = 1;
        printf("%d:\t%d ",i + 1,divs_sum[i]);
        a = i + 1; k = 2; quantity = 1;
        int num = a;
        while (a > 1) {
            while (a % k == 0 && a > 1) {
                printf("%d ",k);
                divs_sum[i] += k;
                ++quantity;
                a /= k;
            }
            ++k;
        }
        printf("(%d,%d)",divs_sum[i],quantity);
        if (quantity == 1)
            printf("\t");
        printf("\t%s\t%s",answ[quantity == c],answ[divs_sum[i] % m == 0]);
        printf("\t%s\t%s\t",answ[prime_number(num)], answ[ideal_number(num)]);
        if (quantity > max_divisor) {
            max_divisor = quantity;
            r1 = num;
        }
        if (quantity < min_divisor) {
            min_divisor = quantity;
            r2 = num;
        }
        if (i == 0) {
            min_sum = divs_sum[i];
            r3 = num;
        }
        if (divs_sum[i] > max_sum) {
            max_sum = divs_sum[i];
            r4 = num;
        }
        if (divs_sum[i] < min_sum) {
            min_sum = divs_sum[i];
            r3 = num;
        }
        for (j = i - 1;j > 0; --j)
            if (divs_sum[j] == divs_sum[i])
                printf("%d:%d ",j + 1,i + 1);
        printf("\n");
    }
    printf("Number with min divisors: %d, divisors = %d;\n",r2,min_divisor);
    printf("Number with max divisors: %d, divisors = %d;\n",r1,max_divisor);
    printf("Number with max sum: %d, max sum = %d;\n",r4,max_sum);
    printf("Number with min sum: %d, min sum = %d;\n",r3,min_sum);
    /*
 *
        printf("%d:",i);
        a = i;
        if (prime_number(a) == 1)
            printf(" prime number;");
        if (ideal_number(a) == 1)
            printf(" ideal number;");
        printf("\ndivisors: ");
        for (j = 1; j <= a; ++j) {
            if (i % j == 0) {
                printf(" %d",j);
                sum += j;
                ++mults;
                if (j % m == 0)
                    printf("+");
            }
        }
        printf("\nTotal = %d, Sum = %d;\n\n",b,sum);
*/
    //Complex code!!
    int s = 48;
    printf("\n8.39.Find the dimensions of all rectangles, S = %d;\n",s);
    for (i = 1; i <= s; ++i)
        for (j = 1; j <= s; ++j) {
            if (j * i == s && j >= i)
                printf("b)a = %d, b = %d;\n",i,j);
            if (j * i == s)
                printf("a)a = %d, b = %d;\n",i,j);
        }
    a = 10;
    printf("\n8.41.Find all natural solutions x and y, k = %d, X^2 + Y^2 = K^2;\n", a);
    for (k = 1;k <= a; ++k) {
        printf("%d(%d): ",k, k * k);
        for (i = 1; i <= k; ++i)
            for (j = i; j <= k; ++j)
                if (pow(j,2) + pow(i,2) == pow(k,2))
                    printf("x = %d, y = %d, ",j * j,i * i);
        printf("\n");
    }
    n = 5;
    sum = 0;
    printf("\n8.43.Calculate: 1^1 + 2^2 ... + n^n, n = %d;\n",n);
    for (i = 1; i <= n; ++i) {
        a = i;
        for (j = 1; j < i; ++j)
            a *= i;
        sum += a;
        printf("%d ",a);
        if (i != n)
            printf("+ ");
    }
    printf("\nSum = %d;\n\n",sum);
    n = 3;
    if (n > 27 || n < 1)
        printf("You entered incorrect value!\n\n");
    else {
        printf("8.44, sum of digits of a three-digit number, n = %d;\n",n);
        for (i = 1; i <= 9; ++i)
            for (j = 0; j <= 9; ++j)
                for (k = 0;k <= 9; ++k)
                    if (i + j + k == n)
                        printf("%d%d%d, %d + %d + %d = %d;\n",i,j,k,i,j,k,n);
    }
    n = 10;
    quantity = 0;
    printf("\n8.48, banknotes = 1,2,5,10 and sum = %d;\n", n);
    const int cost[] = {1, 2, 5, 10};
    for (i = 0; i <= n; ++i)
        for (j = 0; j <= n / 2; ++j)
            for (k = 0; k <= n / 5; ++k)
                for (int l = 0; l <= n / 10; ++l)
                    if (cost[0] * i + cost[1] * j + cost[2] * k + cost[3] * l == n) {
                        printf("1: %d, 2: %d, 5: %d, 10: %d;\n",i,j,k,l);
                        ++quantity;
                    }
    printf("Quantity of variants: %d;\n\n",quantity);
    n = 20;
    m = 10;
    printf("8.49, sum of digits n = %d, if n^2 < m = %d;\n",n,m);
    for (i = 1; i <= n; ++i) {
        a = i; sum = 0;
        printf("n = %d; ",i);
        while (a > 0) {
            k = a % 10;
            printf("%d ",k);
            sum += k;
            a /= 10;
        }
        printf("sum = %d, ",sum);
        if (sum * sum < m)
            printf("%d < m;\n",sum * sum);
        else
            printf("%d > m;\n", sum * sum);
    }
    printf("\n8.50, banknotes = 1, 2, 4, 8, 16, 32, 64; n = %d; n, n + 1...n + 10\n",n);
    printf("Money:\\Banknote:\t64\t32\t16\t8\t4\t2\t1\n");
    for (i = 0; i <= 10; ++i) {
        a = i + n;
        printf("%d:\t\t\t",a);
        for (j = 64; j >= 1; a %= j, j = j >> 1)
            printf("%d\t", a / j);
        printf("\n");
    }
    n = 2147483647;
    printf("\n8.51, digital root of the number, n = %d;\n",n);
    a = digital_root(n);
    printf("Digital root of the number n = %d;\n\n",a);
    n = 46;
    i = 2;
    printf("8.53 - 8.54, Simple divisors, n = %d;\n",n);
    while (n > 1) {
        while (n % i == 0 && prime_number(i) == 1) {
            printf("%d ", i);
            n /= i;
        }
        ++i;
    }
    n = 176; // q
    a = 8;  // p
    printf("\n\n8.55 - 8.57, divisors of q(%d) coprime to p(%d);\n",n,a);
    i = 2;
    while (n > 1) {
        while (n % i == 0) {
            printf("%d", i);
            if (evklid_first_step(i,a) == 1)
                printf("!");
            n /= i;
            printf(":%d ",n);
        }
        ++i;
    }
    n = 72;
    printf("\n\n8.58,sum of cubes, n = %d;\n",n);
    for (i = 1; i <= 5; ++i)
        for (j = i; j <= 5; ++j) {
            if ((j * j * j + i * i * i) <= n)
                printf("%d:%d ",i,j);
        }
    n = 1; // числитель
    a = 1; // знаменатель
    c = 10; // ограничитель
    printf("\n\n8.59, irreducible fractions, c = %d;\n",c);
    for (; a <= c; ++a) {
        for (n = 1; n < a; ++n)
            if (evklid_first_step(n,a) == 1)
                printf("%d/%d ",n,a);
        printf("\n");
    }
}
