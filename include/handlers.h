#pragma once

#include "controller.h"

/**
 * Добавить один символ в конец строки ввода
 */
void appendCharHandler (struct HandlerParameters params);

/**
 * Удалить последний символ
 */
void clearOneHandler(struct HandlerParameters params);

/**
 * Очистить экран
 */
void clearAllHandler(struct HandlerParameters params);

/**
 * Переключить раскладку
 */
void switchLayout(struct HandlerParameters params);

/**
 * Отобразить результат на экране
 */
void equalsHandler (struct HandlerParameters params);

// todo: more handlers
