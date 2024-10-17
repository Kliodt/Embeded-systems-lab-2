#include "controller.h"
#include "handlers.h"

int
main ()
{
  initController ();

  struct HandlerInfo btnSym0 = { appendCharHandler, { .symbol = '0' } };
  struct HandlerInfo btnSym1 = { appendCharHandler, { .symbol = '1' } };
  struct HandlerInfo btnSym2 = { appendCharHandler, { .symbol = '2' } };
  struct HandlerInfo btnSym3 = { appendCharHandler, { .symbol = '3' } };
  struct HandlerInfo btnSym4 = { appendCharHandler, { .symbol = '4' } };
  struct HandlerInfo btnSym5 = { appendCharHandler, { .symbol = '5' } };
  struct HandlerInfo btnSym6 = { appendCharHandler, { .symbol = '6' } };
  struct HandlerInfo btnSym7 = { appendCharHandler, { .symbol = '7' } };
  struct HandlerInfo btnSym8 = { appendCharHandler, { .symbol = '8' } };
  struct HandlerInfo btnSym9 = { appendCharHandler, { .symbol = '9' } };

  struct HandlerInfo btnEquals = { equalsHandler };

  setHandler (BUTTON_SYMBOL_0, btnSym0);
  setHandler (BUTTON_SYMBOL_1, btnSym1);
  setHandler (BUTTON_SYMBOL_2, btnSym2);
  setHandler (BUTTON_SYMBOL_3, btnSym3);
  setHandler (BUTTON_SYMBOL_4, btnSym4);
  setHandler (BUTTON_SYMBOL_5, btnSym5);
  setHandler (BUTTON_SYMBOL_6, btnSym6);
  setHandler (BUTTON_SYMBOL_7, btnSym7);
  setHandler (BUTTON_SYMBOL_8, btnSym8);
  setHandler (BUTTON_SYMBOL_9, btnSym9);

  setHandler (BUTTON_EQUALS, btnEquals);

  startListening ();
}