#include "expr.h"
#include "variables.h"
#include <math.h>
#include <stdlib.h>

double evaluate(expr *ex, double x) {
  double *stack = malloc(sizeof(double) * STACK_MAX);
  int sp = 0;

  stack[sp++] = x;

  for (int i = 0; i < EXPR_LEN; ++i) {
    element e = ex->elts[i];
    switch (e.typ) {
    case ELT_NUMBER: {
      stack[sp++] = e.value;
      break;
    }
    case ELT_ABS: {
      double x = stack[--sp];
      stack[sp++] = fabs(e.value);
      break;
    }
    case ELT_SQ: {
      double x = stack[--sp];
      stack[sp++] = e.value * e.value;
      break;
    }
    case ELT_ADD: {
      double rhs = stack[--sp];
      double lhs = stack[--sp];
      stack[sp++] = lhs + rhs;
      break;
    }
    case ELT_SUB: {
      double rhs = stack[--sp];
      double lhs = stack[--sp];
      stack[sp++] = lhs - rhs;
      break;
    }
    case ELT_MUL: {
      double rhs = stack[--sp];
      double lhs = stack[--sp];
      stack[sp++] = lhs * rhs;
      break;
    }
      //  case ELT_DIV: {
      //  double rhs = stack[--sp];
      //  double lhs = stack[--sp];
      //  stack[sp++] = lhs / rhs;
      //  break;
      //}
    case ELT_DUP: {
      double x = stack[--sp];
      stack[sp++] = x;
      stack[sp++] = x;
      break;
    }
    case ELT_SWAP: {
      double x = stack[--sp];
      double y = stack[--sp];
      stack[sp++] = x;
      stack[sp++] = y;
      break;
    }
    }
  }
  free(stack);
  return stack[--sp];
}
