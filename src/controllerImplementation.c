#include "controller.h"

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};

bool initController() { return true; }

void showString(char str[], int count) {
    str[count] = '\0';  // bad
    printf(str);
}

bool setHandler(int buttonCode, struct HandlerInfo handlerConfig) {
    if (buttonCode >= BUTTONS_TOTAL) return false;
    allHandlers[buttonCode] = handlerConfig;
    return true;
}

bool tryCallHandler(int buttonCode) {
    if (buttonCode >= BUTTONS_TOTAL) return false;

    struct HandlerInfo* handlerInfo = &allHandlers[buttonCode];
    if (handlerInfo->handlerFunction) {  // check if we have this handler
        handlerInfo->handlerFunction(handlerInfo->parameters);  // call handler
        return true;
    } else {
        return false;
    }
}

void startListening() {
    while (true) {
        break;  // listen here
    }

    // (temporal) simulate listening FOR TESTING
    tryCallHandler(BUTTON_SYMBOL_1);
    tryCallHandler(BUTTON_SYMBOL_2);
    tryCallHandler(BUTTON_SYMBOL_3);
    tryCallHandler(BUTTON_SYMBOL_4);
    tryCallHandler(BUTTON_SYMBOL_5);
    tryCallHandler(BUTTON_SYMBOL_6);
    tryCallHandler(BUTTON_SYMBOL_7);
    tryCallHandler(BUTTON_SYMBOL_8);
    tryCallHandler(BUTTON_SYMBOL_9);
    tryCallHandler(BUTTON_SYMBOL_1);
    tryCallHandler(BUTTON_SYMBOL_0);

    tryCallHandler(BUTTON_EQUALS);
}
