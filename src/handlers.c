#include "handlers.h"

struct {
    char inputBuffer[SCREEN_CAPACITY_SYMBOLS];
    int count;
} globalState = {.count = 0};

void appendCharHandler(struct HandlerParameters params) {
    globalState.inputBuffer[globalState.count] = params.symbol;
    globalState.count++;
}

void equalsHandler(struct HandlerParameters params) {
    // todo: call calculation logic
    showString(globalState.inputBuffer, globalState.count);
}