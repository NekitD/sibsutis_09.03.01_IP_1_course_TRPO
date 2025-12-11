#include "ctest.h"

// Глобальные переменные для хранения списка тестов
static ctest_t* ctest_head = NULL;
static ctest_t* ctest_tail = NULL;

// Переменная для отслеживания текущего состояния теста
static int current_test_failed = 0;
static int test_counter = 0;

// Переменная для хранения информации об ошибке
static char error_message[256];

// Функция для добавления теста в список
void ctest_add(const char* suite, const char* test, void (*func)()) {
    ctest_t* new_test = (ctest_t*)malloc(sizeof(ctest_t));
    new_test->suite = suite;
    new_test->test = test;
    new_test->func = func;
    new_test->next = NULL;
    if (ctest_tail) {
        ctest_tail->next = new_test;
        ctest_tail = new_test;
    } else {
        ctest_head = ctest_tail = new_test;
    }
}

// Функция для регистрации неудачного теста и сохранения сообщения об ошибке
void ctest_fail(const char* message) {
    current_test_failed = 1;
    snprintf(error_message, sizeof(error_message), "%s", message);
}

// Функция для запуска всех тестов
int ctest_main(int argc, const char** argv) {
    (void)argc;
    (void)argv;
    int tests_run = 0;
    int tests_failed = 0;
    int tests_passed = 0;
    ctest_t* t;
    clock_t start_time, end_time;

    start_time = clock();

    // Обратный порядок запуска тестов
    ctest_t* reversed_head = NULL;
    ctest_t* current = ctest_head;
    while (current) {
        ctest_t* next = current->next;
        current->next = reversed_head;
        reversed_head = current;
        current = next;
    }

    // Запуск каждого теста в обратном порядке
    for (t = reversed_head; t; t = t->next) {
        test_counter++;
        printf("TEST %d/%d %s:%s... ", test_counter, tests_run + 1, t->suite, t->test);
        fflush(stdout); // Немедленно выводим сообщение о запуске теста

        current_test_failed = 0;
        t->func();
        
        if (current_test_failed) {
            printf(CTEST_COLOR_RED "[FAIL]" CTEST_COLOR_RESET "\n");
            printf(CTEST_COLOR_YELLOW "%s" CTEST_COLOR_RESET "\n", error_message);
            tests_failed++;
        } else {
            printf(CTEST_COLOR_GREEN "[OK]" CTEST_COLOR_RESET "\n");
            tests_passed++;
        }

        tests_run++;
    }

    end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;

    // Вывод итоговой информации
    printf("\nRESULTS: %d tests (%s%d ok%s, %s%d failed%s, %s%d skipped%s) ran in %.1f ms\n",
           tests_run,
           CTEST_COLOR_GREEN, tests_passed, CTEST_COLOR_RESET,
           CTEST_COLOR_RED, tests_failed, CTEST_COLOR_RESET,
           CTEST_COLOR_YELLOW, 0, CTEST_COLOR_RESET,
           time_spent);

    return tests_failed;
}
