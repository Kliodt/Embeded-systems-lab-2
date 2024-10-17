#include "controller.h"
#include "oled.h"
#include "fonts.h"
#include <stdint.h>

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};

bool initController() { return true; }

void showString(char str[], int count) {
    FontDef defaultFont = Font_7x10;
    uint8_t widthInSymbols = OLED_WIDTH / defaultFont.FontWidth;
    uint8_t heightInSymbols = OLED_HEIGHT / defaultFont.FontHeight;
    uint16_t maxSymbolsCount = widthInSymbols * heightInSymbols;
    if (count <= maxSymbolsCount) {
        uint8_t fullSubstringCount = count / widthInSymbols;
        uint8_t lastSubstringLen = count % widthInSymbols;
        for (int i = 0; i < fullSubstringCount; i++) {
            oled_SetCursor(0, i * heightInSymbols);
            char substring[widthInSymbols + 1];
            for (int j = 0; j < widthInSymbols; j++) {
                substring[j] = str[j + i * widthInSymbols];
            }
            substring[widthInSymbols] = '\0';
            oled_WriteString(substring, defaultFont, White);
        }
        oled_SetCursor(0, fullSubstringCount * heightInSymbols);
        char lastSubstring[lastSubstringLen + 1];
        for (int j = 0; j < lastSubstringLen; j++) {
            lastSubstring[j] = str[j + fullSubstringCount * widthInSymbols];
        }
        lastSubstring[lastSubstringLen] = '\0';
        oled_WriteString(lastSubstring, defaultFont, White);
    }
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
