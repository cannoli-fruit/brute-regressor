#include "expr.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>

int iscompliant(expr *e) {
  int total = 1;
  for (int i = 0; i < EXPR_LEN; ++i) {
    switch (e->elts[i].typ) {
    case ELT_NUMBER: {
      total++;
      break;
    }
    case ELT_ADD: {
      if (total < 2)
        return false;
      total--;
      break;
    }
    case ELT_SUB: {
      if (total < 2)
        return false;
      total--;
      break;
    }
    case ELT_MUL: {
      if (total < 2)
        return false;
      total--;
      break;
    }
    case ELT_ABS: {
      if (total == 0)
        return false;
      break;
    }
    case ELT_SQ: {
      if (total == 0)
        return false;
      break;
    }
    case ELT_DUP: {
      if (total == 0)
        return false;
      total++;
      break;
    }
    case ELT_SWAP: {
      if (total < 2)
        return false;
      break;
    }
    default: {
      printf("validator.c line 52\n");
      exit(1);
    }
    }
  }
}
