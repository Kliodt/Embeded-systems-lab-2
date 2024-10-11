#pragma once

#include <stdbool.h>
#include <stdio.h>

// calculator button codes
#define BUTTON_SYMBOL_0 0
#define BUTTON_SYMBOL_1 1
#define BUTTON_SYMBOL_2 2
#define BUTTON_SYMBOL_3 3
#define BUTTON_SYMBOL_4 4
#define BUTTON_SYMBOL_5 5
#define BUTTON_SYMBOL_6 6
#define BUTTON_SYMBOL_7 7
#define BUTTON_SYMBOL_8 8
#define BUTTON_SYMBOL_9 9
#define BUTTON_EQUALS 10

#define BUTTONS_TOTAL \
    11  // ! dont forget to change this after adding new button code

// screen parameters
#define SCREEN_CAPACITY_SYMBOLS 100  // ? change it to real one

/**
 * Параметры функции-обработчика
 */
struct HandlerParameters {
    char symbol;
    // maybe add more parameters here
};

/**
 * Содержит информацию о функции-обработчике и параметрах,
 * с которыми она вызывается
 */
struct HandlerInfo {
    void (*handlerFunction)(struct HandlerParameters);
    struct HandlerParameters parameters;
};

/**
 * Начальная инициализация требуемых внутренних параметров контроллера
 */
bool initController();

/**
 * Вывести переданную строку
 */
void showString(char str[], int count);

/**
 * Добавить обработчик на нажатие кнопки
 * @param buttonCode код кнопки (определены в controller.h)
 * @param handlerConfig обработчик
 */
bool setHandler(int buttonCode, struct HandlerInfo handlerConfig);

/**
 * Начать прослушивать события нажатий на кнопки
 */
void startListening();
