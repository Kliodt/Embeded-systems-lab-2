#include "../include/rpn_math.h"
#include <stdio.h>

#define STACK_MAX_SIZE 30
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101

typedef struct Stack_tag {
    struct expression_token data[STACK_MAX_SIZE];
    size_t size;
} Stack;

int push(Stack *s, const struct expression_token exp_t){
    if(s->size >= STACK_MAX_SIZE) return STACK_OVERFLOW;
    s->data[s->size] = exp_t;
    s->size++;
    return 0;
}

int pop(Stack *s, struct expression_token* exp_t){
    if(s->size == 0) return STACK_UNDERFLOW;
    s->size--;
    *exp_t = s->data[s->size];
    return 0;
}

int peek(Stack *s, struct expression_token* exp_t){
    if(s->size == 0) return STACK_UNDERFLOW;
    *exp_t = s->data[s->size - 1];
    return 0;
}

double apply_operation(double l, double r, enum math_operation op){
    switch (op)
    {
    case ADDITION:
        return l + r;
    case SUBSTRUCTION:
        return l - r;
    case MULTIPLICATION:
        return l * r;
    case DIVISION:
        return l / r;
    default:
        return 0;
    }
}

int is_float_part(char current_symbol){
    return current_symbol >= '0' && current_symbol <= '9' || current_symbol == '.';
}

int is_defined_operation(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'; 
}

enum math_operation get_operation(char c){
    switch (c)
    {
    case '+':
        return ADDITION;
    case '-':
        return SUBSTRUCTION;
    case '/':
        return DIVISION;
    case '*':
        return MULTIPLICATION;
    case '(':
        return LEFT_BR;
    case ')':
        return RIGHT_BR;
    default:
        return NO_OP;
    }
}

void copy_string(char* from_buffer, char* to_buffer, int size){
    for(size_t i = 0; i < size; i++){
        to_buffer[i] = from_buffer[i];
    }
}

double get_double_from_string(char* buffer, int size){
    double r=0;
    double after_coma_r = 0;
    size_t current_c;
    size_t after_coma = 0;
    int after_coma_flag = 0;
    for(current_c = 0; current_c < size; current_c++){
        if(buffer[current_c] == '.'){
            after_coma_flag = 1;
            continue;
        }
        if(!after_coma_flag){
            r = r * 10 + (buffer[current_c] - 48);
        } else {
            after_coma++;
            after_coma_r = after_coma_r * 10 + (buffer[current_c] - 48);
        }
    }
    while(after_coma > 0){
        after_coma_r /= 10;
        after_coma -= 1;
    }
    return r + after_coma_r;
}

size_t split_equaition_into_tokens(char* expression, size_t expression_size, struct expression_token* token_buffer){
    size_t current_token_buffer_size = 0;
    char current_symbol;
    double current_number = 0.0;
    char number_buffer[100] = "";
    int number_start = -1;
    size_t i = 0;
    while(i < expression_size){
        current_symbol = expression[i];
        if(is_defined_operation(current_symbol)){
            if(number_start != -1){
                //strncpy_s(number_buffer, 99, expression + number_start, i - number_start);
                copy_string(expression + number_start, number_buffer, i - number_start);
                number_buffer[i - number_start + 1] = '\0';
                //sscanf_s(number_buffer, "%lf", &current_number);
                current_number = get_double_from_string(number_buffer, i - number_start);

                struct expression_token cur_t;
                cur_t.operation = NO_OP;
                cur_t.number = current_number;
                token_buffer[current_token_buffer_size++] = cur_t;

                number_buffer[0] = '\0';
            }
            number_start = -1;
            struct expression_token cur_t;
            cur_t.operation = get_operation(current_symbol);
            token_buffer[current_token_buffer_size++] = cur_t;
        }
        else if(is_float_part(current_symbol)){
            if(current_symbol == '.' && number_start == -1) return -1;
            if(number_start == -1) number_start = i;
            if(i == expression_size - 1){
                //strncpy_s(number_buffer, 99, expression + number_start, i - number_start + 1);
                copy_string(expression + number_start, number_buffer, i - number_start + 1);

                number_buffer[i - number_start + 1] = '\0'; // +2
                //sscanf_s(number_buffer, "%lf", &current_number);
                current_number = get_double_from_string(number_buffer, i - number_start);
                struct expression_token cur_t;
                cur_t.operation = NO_OP;
                cur_t.number = current_number;
                token_buffer[current_token_buffer_size++] = cur_t;

                number_buffer[0] = '\0';
            }
        } else {
            return -1;
        }
        i++;
    }
    return current_token_buffer_size;
}

int get_operation_priority(enum math_operation op){
    switch (op)
    {
    case ADDITION:
        return 1;
    case SUBSTRUCTION:
        return 1;
    case MULTIPLICATION:
        return 2;
    case DIVISION:
        return 2;
    case LEFT_BR:
        return -1;
    case RIGHT_BR:
        return 0;
    default:
        return -2;
    }
}

int reorder_in_rpn(struct expression_token *token_buffer, size_t token_buffer_size, struct expression_token *rpn_buffer){
    Stack stack;
    stack.size = 0;
    struct expression_token current_token = {0};
    struct expression_token buffer_token = {0};
    
    size_t rpn_buffer_size = 0;
    size_t i = 0;
    for(i = 0; i < token_buffer_size; i++){
        current_token = token_buffer[i];
        if(current_token.operation != NO_OP){
            if(current_token.operation == LEFT_BR){
                if(push(&stack, current_token) != 0) return -1;
            } else {
                if(stack.size > 0){
                    if(peek(&stack, &buffer_token) != 0) return -1;
                }
                while(stack.size > 0 && get_operation_priority(buffer_token.operation) >= get_operation_priority(current_token.operation)){
                    if(pop(&stack, &buffer_token) != 0) return -1;
                    rpn_buffer[rpn_buffer_size++] = buffer_token;
                    if(stack.size > 0){
                        if(peek(&stack, &buffer_token) != 0) return -1;
                    }
                }
                if (current_token.operation == RIGHT_BR){
                    if(pop(&stack, &buffer_token) != 0) return -1;
                } else {
                    if(push(&stack, current_token) != 0) return -1;
                }
            }
        } else {
            rpn_buffer[rpn_buffer_size++] = current_token;
        }
    }
    while(stack.size > 0){
        if(pop(&stack, &buffer_token) != 0) return -1;
        rpn_buffer[rpn_buffer_size++] = buffer_token;
    }

    return (int) rpn_buffer_size;

}

enum resolve_expression_code compute_rpn(struct expression_token * rpn_buffer, size_t rpn_buffer_size, double *result){
    Stack stack;
    stack.size = 0;
    struct expression_token current_token;
    struct expression_token l;
    struct expression_token r;

    for(size_t i = 0; i < rpn_buffer_size; i++){
        current_token = rpn_buffer[i];
        if(current_token.operation == NO_OP){
            if(push(&stack, current_token) != 0) return -1;
        } else {
            if(stack.size < 2) return NOT_VALID;
            if(pop(&stack, &r) != 0) return -1;
            if(pop(&stack, &l) != 0) return -1;
            if(current_token.operation == DIVISION && r.number < 0.00001) return ERROR;
            l.number = apply_operation(l.number, r.number, current_token.operation);
            if(push(&stack, l) != 0) return -1;
        }
    }
    if(stack.size != 1) return NOT_VALID;
    *result = stack.data[0].number;
    return OK;
}
/**
 * Итак, эта функция принимает:
 *      expression - строка математического выражения без пробелов
 *      expression_size - длина данной строки
 *      result - ссылка на число-результат
 * 
 * Эта функция отдает:
 *      enum resolve_expression_code:
 * OK - если все ок и можно забирать результат
 * NOT_VALID - если выражение не валидно
 * ERROR - если произошло деление на 0
 * 
 * P.S. Надо бы сделать тесты конечно
 * 
 * **/
int check_brackets(char* expression, size_t expression_size){
    size_t count = 0;
    for(size_t i = 0; i < expression_size; i++){
        if (expression[i] == '(') count++;
        if (expression[i] == ')') count--;
        if(count < 0) return 0;
    }
    if(count == 0) return 1;
    return 0;
}

enum resolve_expression_code resolve_expression(char* expression, size_t expression_size, double* result){
    if(expression_size <= 0) return NOT_VALID;
    struct expression_token token_buffer[1024] = {0};
    struct expression_token rpn_buffer[1024] = {0};
    if(!check_brackets(expression, expression_size)) return NOT_VALID;

    size_t current_token_buffer_size = split_equaition_into_tokens(expression, expression_size, token_buffer);
    if(current_token_buffer_size == -1) return NOT_VALID;

    size_t rpn_buffer_size = reorder_in_rpn(token_buffer, current_token_buffer_size, rpn_buffer);
    if(rpn_buffer_size == -1) return NOT_VALID;

    /*
        Отладочный принты
    */
    /*
    for(size_t i = 0; i < current_token_buffer_size; i++){
        printf("{%f, %d}\n", token_buffer[i].number, (int)token_buffer[i].operation);
    }
    printf("\n");
    for(size_t i = 0; i < rpn_buffer_size; i++){
        printf("{%f, %d}\n", rpn_buffer[i].number, (int)rpn_buffer[i].operation);
    }
    printf("\n");
    */

    return compute_rpn(rpn_buffer, rpn_buffer_size, result);
}



int main(){
    char* s = "3*(1.1-2)";
    double r;
    enum resolve_expression_code result = resolve_expression(s, 9, &r);
    if(result == OK){
        printf("%f\n", r);
    } else if (result == NOT_VALID){
        printf("Not valid expression");
    } else{
        printf("Eror during computation");
    }
    return 0;
}