#pragma once
#include <stddef.h>

enum resolve_expression_code {
    OK = 1,
    ERROR,
    NOT_VALID
};

enum math_operation {
    ADDITION = 1,
    SUBSTRUCTION,
    MULTIPLICATION,
    DIVISION,
    LEFT_BR,
    RIGHT_BR,
    NO_OP
};

struct expression_token{
    enum math_operation operation;
    double number;
};

enum resolve_expression_code resolve_expression(char* expression, size_t expression_size, double* result);

// #endif //RPN_MATH_H
