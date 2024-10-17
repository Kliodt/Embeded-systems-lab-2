#include <inttypes.h>
#include <stdint.h>

#include "controller.h"
#include "fonts.h"
#include "kb.h"
#include "oled.h"

int KB_LAYOUT = 0;

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};

bool initController() { return true; }

void showString(char str[], int count) {
    oled_Reset();
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

    struct HandlerInfo *handlerInfo = &allHandlers[buttonCode];
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

void changeLayout() {
    if (KB_LAYOUT == 12) {
        KB_LAYOUT = 0;
    } else if (KB_LAYOUT == 0) {
        KB_LAYOUT = 12;
    }
}

void KB_Test(void) {
    UART_Transmit((uint8_t *)"KB test start\n");
    uint8_t Row[4] = {ROW1, ROW2, ROW3, ROW4}, Key;
    oled_Reset();
    oled_WriteString("From bottom to top", Font_7x10, White);
    OLED_KB(OLED_Keys);
    oled_UpdateScreen();
    while (1) {
        int row_number = 0;
        for (row_number; row_number < 4; row_number++) {
            Key = Check_Row(Row[row_number]);
            if (Key == 0x01) {
                tryCallHandler(3 * row_number + KB_LAYOUT);
                // UART_Transmit ((uint8_t *)"Left pressed\n");
                // L = 1;
                // OLED_Keys[3 * i] = 0x31;
                // OLED_KB (OLED_Keys);
            } else if (Key == 0x02) {
                tryCallHandler(3 * row_number + 1 + KB_LAYOUT);
                // UART_Transmit ((uint8_t *)"Center pressed\n");
                // C = 1;
                // OLED_Keys[1 + 3 * i] = 0x31;
                // OLED_KB (OLED_Keys);
            } else if (Key == 0x04) {
                tryCallHandler(3 * row_number + 2 + KB_LAYOUT);
                // UART_Transmit( (uint8_t*)"Right pressed\n" );
                // R = 1;
                // OLED_Keys[2+3*i] = 0x31;
                // OLED_KB(OLED_Keys);
            }
            // UART_Transmit ((uint8_t *)"Row complete\n");
            // R = C = L = 0;
            // HAL_Delay (25);
        }
        row_number = 0;
    }

    // UART_Transmit ((uint8_t *)"KB test complete\n");
}

// UART_Transmit( (uint8_t*)"Right pressed\n" );
// R = 1;
// OLED_Keys[2+3*i] = 0x31;
// OLED_KB(OLED_Keys);