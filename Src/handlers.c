#include "handlers.h"
#include "rpn_math.h"
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
            globalState.count = snprintf(globalState.inputBuffer, SCREEN_CAPACITY_SYMBOLS, "%lf", result);
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
