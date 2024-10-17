#include "controller.h"
#include "handlers.h"

int
main ()
{
  initController ();

    struct HandlerInfo btnSym0 = {appendCharHandler, {.symbol = '0'}};
    struct HandlerInfo btnSym1 = {appendCharHandler, {.symbol = '1'}};
    struct HandlerInfo btnSym2 = {appendCharHandler, {.symbol = '2'}};
    struct HandlerInfo btnSym3 = {appendCharHandler, {.symbol = '3'}};
    struct HandlerInfo btnSym4 = {appendCharHandler, {.symbol = '4'}};
    struct HandlerInfo btnSym5 = {appendCharHandler, {.symbol = '5'}};
    struct HandlerInfo btnSym6 = {appendCharHandler, {.symbol = '6'}};
    struct HandlerInfo btnSym7 = {appendCharHandler, {.symbol = '7'}};
    struct HandlerInfo btnSym8 = {appendCharHandler, {.symbol = '8'}};
    struct HandlerInfo btnSym9 = {appendCharHandler, {.symbol = '9'}};
    
    struct HandlerInfo btnSymPlus = {appendCharHandler, {.symbol = '+'}};
    struct HandlerInfo btnSymMinus = {appendCharHandler, {.symbol = '-'}};
    struct HandlerInfo btnSymMultiply = {appendCharHandler, {.symbol = '*'}};
    struct HandlerInfo btnSymDivide = {appendCharHandler, {.symbol = '/'}};

    struct HandlerInfo btnSymPoint = {appendCharHandler, {.symbol = '.'}};
    struct HandlerInfo btnSymBracketLeft = {appendCharHandler, {.symbol = '('}};
    struct HandlerInfo btnSymBracketRight = {appendCharHandler, {.symbol = ')'}};

    struct HandlerInfo btnEquals = {equalsHandler};
    struct HandlerInfo btnClearOne = {clearOneHandler};
    struct HandlerInfo btnClearAll = {clearAllHandler};

    struct HandlerInfo btnSwitchLayout = {switchLayout};

    // layout 1
    setHandler(BUTTON_SYMBOL_0, btnSym0);
    setHandler(BUTTON_SYMBOL_1, btnSym1);
    setHandler(BUTTON_SYMBOL_2, btnSym2);
    setHandler(BUTTON_SYMBOL_3, btnSym3);
    setHandler(BUTTON_SYMBOL_4, btnSym4);
    setHandler(BUTTON_SYMBOL_5, btnSym5);
    setHandler(BUTTON_SYMBOL_6, btnSym6);
    setHandler(BUTTON_SYMBOL_7, btnSym7);
    setHandler(BUTTON_SYMBOL_8, btnSym8);
    setHandler(BUTTON_SYMBOL_9, btnSym9);
    setHandler(BUTTON_POINT, btnSymPoint);
    setHandler(BUTTON_SWITCH_LAYOUT_1, btnSwitchLayout);
    
    // layout 2
    setHandler(BUTTON_PLUS, btnSymPlus);
    setHandler(BUTTON_MINUS, btnSymMinus);
    setHandler(BUTTON_MULTIPLY, btnSymMultiply);
    setHandler(BUTTON_DIVIDE, btnSymDivide);
    setHandler(BUTTON_LEFT_BRACKET, btnSymBracketLeft);
    setHandler(BUTTON_RIGHT_BRACKET, btnSymBracketRight);

    setHandler(BUTTON_EQUALS, btnEquals);
    setHandler(BUTTON_CLEAR_ONE, btnClearOne);
    setHandler(BUTTON_CLEAR_ALL, btnClearAll);
    setHandler(BUTTON_SWITCH_LAYOUT_2, btnSwitchLayout);

  startListening ();
}