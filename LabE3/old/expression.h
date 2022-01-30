#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdbool.h>

typedef struct expression EXPRESSION;

EXPRESSION *expression_read();

void expression_destroy(EXPRESSION *expression);

void expression_print(const EXPRESSION *expression);

int expression_evaluate(EXPRESSION *expression);

#endif // EXPRESSION_H
