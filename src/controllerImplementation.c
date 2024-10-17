#include "controller.h"

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};

bool initController() { return true; }

void showString(char str[], int count) {
    str[count] = '\0';  // bad
    printf(str);
    printf("\n");
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

bool changeLayout() {return 1;};

void startListening() {
    while (true) {
        // break;  // listen here
        printf("-------------\n");
        printf("Input: ");
        char word[256];
        scanf_s("%s" , word, sizeof(word));
        int i = 0;
        while (word[i++]) {
            char ch = word[i-1];
            int btnIndex;
            switch (ch) {
                case '1': btnIndex = 0; break;
                case '2': btnIndex = 1; break; 
                case '3': btnIndex = 2; break; 
                case '4': btnIndex = 3; break; 
                case '5': btnIndex = 4; break; 
                case '6': btnIndex = 5; break; 
                case '7': btnIndex = 6; break; 
                case '8': btnIndex = 7; break; 
                case '9': btnIndex = 8; break; 
                case '.': btnIndex = 9; break; 
                case '0': btnIndex = 10; break; 
                case '+': btnIndex = 12; break; 
                case '(': btnIndex = 13; break; 
                case ')': btnIndex = 14; break; 
                case '-': btnIndex = 15; break; 
                case '<': btnIndex = 16; break; 
                case 'C': btnIndex = 17; break; 
                case '*': btnIndex = 18; break; 
                case '=': btnIndex = 19; break; 
                case '/': btnIndex = 21; break;
                default: printf("error in your input"); return;
            }
            tryCallHandler(btnIndex);
        }
    }

   
}
