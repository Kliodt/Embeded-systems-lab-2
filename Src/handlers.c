#include "handlers.h"
#include "rpn_math.h"
#include "stringUtils.h"
#include <stdio.h>

struct
{
  char inputBuffer[SCREEN_CAPACITY_SYMBOLS];
  int count;
} globalState = { .count = 0 };

void appendCharHandler(struct HandlerParameters params) {
    if (globalState.count >= SCREEN_CAPACITY_SYMBOLS) return;
    globalState.inputBuffer[globalState.count] = params.symbol;
    globalState.count++;
    showString(globalState.inputBuffer, globalState.count);
}

void clearOneHandler(struct HandlerParameters params) {
    if (globalState.count > 0) {
        globalState.count--;
    }
    showString(globalState.inputBuffer, globalState.count);
}

void clearAllHandler(struct HandlerParameters params) {
    globalState.count = 0;
    showString(globalState.inputBuffer, globalState.count);
}

void switchLayout(struct HandlerParameters params) {
    changeLayout();
}

int trackingZeroesCount(char buf[], int count);

void equalsHandler(struct HandlerParameters params) {
    double result = 0;
    enum resolve_expression_code resultCode = 
        resolve_expression(globalState.inputBuffer, globalState.count, &result);

    switch (resultCode) {
        case OK:
            // globalState.count = snprintf(globalState.inputBuffer, SCREEN_CAPACITY_SYMBOLS, "%lf", result);
            double_to_string(result, globalState.inputBuffer);
            globalState.count = strLen(globalState.inputBuffer);
            globalState.count -= trackingZeroesCount(globalState.inputBuffer, globalState.count);
            showString(globalState.inputBuffer, globalState.count);
            break;
        case ERROR:
            showString("Error", 5);
            break;
        case NOT_VALID:
            showString("Invalid expression", 18);
            break;
        default: break;
    }
}

// returns the number of zeroes at the end of the string after the point
int trackingZeroesCount(char buf[], int count) {
    int zeroesCount = 0;
    bool keepCount = true; 
    for (unsigned i = count - 1; i >= 0; i--) {
        if (keepCount && buf[i] == '0') zeroesCount++;
        else {
            if (buf[i] == '.') {
                return keepCount ? zeroesCount + 1 : zeroesCount;
            }; 
            keepCount = false;
        }
    }
    return 0;
}

typedef unsigned long rsize_t;
typedef int errno_t;

#define EOK       0     /* Операция успешна */
#define ESNULLP   1     /* Нулевой указатель */
#define ESZEROL   2     /* Длина равна нулю */
#define ESLEMAX   3     /* Длина превышает максимум */
#define ESNOSPC   4     /* Недостаточно места */

#define RSIZE_MAX_STR  (4UL << 10)  /* Максимальный размер строки 4KB */

errno_t strCopy(char *dest, int destsz, const char *src) {
    int i;

    /* Проверка на нулевые указатели */
    if (dest == 0) {
        return ESNULLP;
    }
    if (src == 0) {
        dest[0] = '\0';
        return ESNULLP;
    }

    /* Проверка на корректность размера */
    if (destsz == 0) {
        return ESZEROL;
    }
    if (destsz > RSIZE_MAX_STR) {
        return ESLEMAX;
    }

    /* Копирование строки */
    for (i = 0; i < destsz; i++) {
        dest[i] = src[i];
        if (src[i] == '\0') {
            /* Успешное копирование */
            return EOK;
        }
    }

    /* Недостаточно места в dest */
    dest[0] = '\0';  /* Обнуляем dest */
    return ESNOSPC;
}

