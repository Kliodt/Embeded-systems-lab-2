#include "handlers.h"
#include "rpn_math.h"
#include <stdio.h>

struct {
    char inputBuffer[SCREEN_CAPACITY_SYMBOLS];
    int count;
} globalState = {.count = 0};

void appendCharHandler(struct HandlerParameters params) {
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
    // todo: call switch layout from controller
}

void equalsHandler(struct HandlerParameters params) {
    double result = 0;
    enum resolve_expression_code resultCode = 
        resolve_expression("3*(1.1-2)", 9, &result);

    switch (resultCode) {
        case OK:
            snprintf(globalState.inputBuffer, SCREEN_CAPACITY_SYMBOLS, "%lf", result);
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