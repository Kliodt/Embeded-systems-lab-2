#include "stringUtils.h"

void double_to_string(double num, char *str) {
    int idx = 0;

    // Обработка отрицательных чисел
    if (num < 0.0) {
        str[idx++] = '-';
        num = -num;
    }

    // Выделение целой части
    int integer_part = (int)num;

    // Выделение дробной части
    double frac_part = num - (double)integer_part;

    // Установка точности
    int precision = 6;

    // Вычисление множителя для дробной части
    double frac_multiplier = 1.0;
    for (int i = 0; i < precision; i++) {
        frac_multiplier *= 10.0;
    }

    // Вычисление дробной части как целого числа с учетом округления
    double fractional_part = frac_part * frac_multiplier + 0.5;
    int fractional_int = (int)fractional_part;

    // Обработка ситуации, когда округление дробной части увеличивает целую часть
    if (fractional_int >= (int)frac_multiplier) {
        fractional_int = 0;
        integer_part += 1;
    }

    // Преобразование целой части в строку
    if (integer_part == 0) {
        str[idx++] = '0';
    } else {
        int digits[10];
        int i = 0;
        int temp_int = integer_part;
        while (temp_int > 0) {
            digits[i++] = temp_int % 10;
            temp_int /= 10;
        }
        for (int j = i - 1; j >= 0; j--) {
            str[idx++] = digits[j] + '0';
        }
    }

    // Добавление десятичной точки
    str[idx++] = '.';

    // Преобразование дробной части в строку с ведущими нулями
    int temp_frac = fractional_int;
    int frac_digits[6];
    for (int i = precision - 1; i >= 0; i--) {
        frac_digits[i] = temp_frac % 10;
        temp_frac /= 10;
    }
    for (int i = 0; i < precision; i++) {
        str[idx++] = frac_digits[i] + '0';
    }

    // Завершение строки нулевым символом
    str[idx] = '\0';
}

int strLen(char* buf) {
    int count = 0;
    while(buf[count++]) {};
    return count-1;
}

double string_to_double(const char *str) {
    int idx = 0;
    int sign = 1;
    double result = 0.0;
    double divisor = 10.0;
    int has_digits = 0;

    // Пропуск ведущих пробелов и табуляций
    while (str[idx] == ' ' || str[idx] == '\t') {
        idx++;
    }

    // Обработка знака числа
    if (str[idx] == '+') {
        idx++;
    } else if (str[idx] == '-') {
        sign = -1;
        idx++;
    }

    // Обработка цифр до десятичной точки
    while (str[idx] >= '0' && str[idx] <= '9') {
        result = result * 10.0 + (str[idx] - '0');
        idx++;
        has_digits = 1;
    }

    // Обработка десятичной точки и дробной части
    if (str[idx] == '.') {
        idx++;
        while (str[idx] >= '0' && str[idx] <= '9') {
            result = result + (str[idx] - '0') / divisor;
            divisor *= 10.0;
            idx++;
            has_digits = 1;
        }
    }

    // Проверка наличия цифр в строке
    if (!has_digits) {
        // Нет цифр для обработки, возвращаем 0.0 или обрабатываем ошибку
        return 0.0;
    }

    // Применение знака к результату
    result *= sign;

    return result;
}

#define EOK       0     /* Операция успешна */
#define ESNULLP   1     /* Нулевой указатель */
#define ESZEROL   2     /* Длина равна нулю */
#define ESLEMAX   3     /* Длина превышает максимум */
#define ESNOSPC   4     /* Недостаточно места */

#define RSIZE_MAX_STR  (4UL << 10)  /* Максимальный размер строки 4KB */

int strCopy(char *dest, int destsz, const char *src) {
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

