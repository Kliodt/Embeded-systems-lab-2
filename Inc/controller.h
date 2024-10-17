#pragma once

#include <stdbool.h>
#include <stdio.h>

// calculator button codes
#define BUTTON_SYMBOL_1 0
#define BUTTON_SYMBOL_2 1
#define BUTTON_SYMBOL_3 2

#define BUTTON_SYMBOL_4 3
#define BUTTON_SYMBOL_5 4
#define BUTTON_SYMBOL_6 5

#define BUTTON_SYMBOL_7 6
#define BUTTON_SYMBOL_8 7
#define BUTTON_SYMBOL_9 8

#define BUTTON_POINT 9
#define BUTTON_SYMBOL_0 10
#define BUTTON_SWITCH_LAYOUT_1 11

#define BUTTON_PLUS 12
#define BUTTON_LEFT_BRACKET 13
#define BUTTON_RIGHT_BRACKET 14

#define BUTTON_MINUS 15
#define BUTTON_CLEAR_ONE 16
#define BUTTON_CLEAR_ALL 17

#define BUTTON_MULTIPLY 18
#define BUTTON_EQUALS 19
// #define _ 20 // SKIP

#define BUTTON_DIVIDE 21
// #define _ 22 // SKIP
#define BUTTON_SWITCH_LAYOUT_2 23

#define BUTTONS_TOTAL 24

// screen parameters
#define SCREEN_CAPACITY_SYMBOLS 100 // ! change it to real one

/**
 * Параметры функции-обработчика
 */
struct HandlerParameters
{
  char symbol;
  // maybe add more parameters here
};

/**
 * Содержит информацию о функции-обработчике и параметрах,
 * с которыми она вызывается
 */
struct HandlerInfo
{
  void (*handlerFunction) (struct HandlerParameters);
  struct HandlerParameters parameters;
};

/**
 * Начальная инициализация требуемых внутренних параметров контроллера
 */
bool initController ();

/**
 * Вывести переданную строку
 */
void showString (char str[], int count);

/**
 * Добавить обработчик на нажатие кнопки
 * @param buttonCode код кнопки (определены в controller.h)
 * @param handlerConfig обработчик
 */
bool setHandler (int buttonCode, struct HandlerInfo handlerConfig);

/**
 * Начать прослушивать события нажатий на кнопки
 */
void startListening ();

bool changeLayout ();
