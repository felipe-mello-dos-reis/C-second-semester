#include <stdio.h>

#include "expression.h"

int main() {
  EXPRESSION *e = expression_read();

  expression_print(e);
  printf(" = %d\n", expression_evaluate(e));

  expression_destroy(e);
}
