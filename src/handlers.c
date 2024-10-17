#include "handlers.h"

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
    // todo: call calculation logic
    showString(globalState.inputBuffer, globalState.count);
}