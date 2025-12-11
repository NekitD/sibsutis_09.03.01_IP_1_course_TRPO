#ifndef CTEST_H
#define CTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Определение цветов для вывода в терминал
#define CTEST_COLOR_RED     "\x1b[31m"
#define CTEST_COLOR_GREEN   "\x1b[32m"
#define CTEST_COLOR_YELLOW  "\x1b[33m"
#define CTEST_COLOR_RESET   "\x1b[0m"

// Макрос для создания тестов
#define CTEST(suite, test) \
    static void test_##suite##_##test(); \
    static void __attribute__((constructor)) add_test_##suite##_##test() { \
        ctest_add(#suite, #test, test_##suite##_##test); \
    } \
    static void test_##suite##_##test()

// Макрос для проверки равенства значений
#define ASSERT_EQUAL(expected, result) \
    if ((expected) != (result)) { \
        char message[256]; \
        snprintf(message, sizeof(message), "ERR: %s:%d expected %d, got %d", __FILE__, __LINE__, (expected), (result)); \
        ctest_fail(message); \
        return; \
    }

// Макрос для проверки неравенства значений
#define ASSERT_NOT_EQUAL(unexpected, result) \
    if ((unexpected) == (result)) { \
        char message[256]; \
        snprintf(message, sizeof(message), "ERR: %s:%d did not expect %d, but got %d", __FILE__, __LINE__, (unexpected), (result)); \
        ctest_fail(message); \
        return; \
    }

// Структура для хранения информации о тестах
typedef struct ctest_t {
    const char* suite;
    const char* test;
    void (*func)();
    struct ctest_t* next;
} ctest_t;

void ctest_add(const char* suite, const char* test, void (*func)());
int ctest_main(int argc, const char** argv);
void ctest_fail(const char* message);

#ifdef __cplusplus
}
#endif

#endif // CTEST_H
