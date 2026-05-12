#include "variables.h"

enum elt_type {
  ELT_NUMBER,
  ELT_ADD,
  ELT_SUB,
  ELT_MUL,
  // ELT_DIV,
  ELT_ABS,
  ELT_SQ,
  ELT_DUP,
  ELT_SWAP,
  ELT_TYP_COUNT
};

typedef struct {
  enum elt_type typ;
  double value;
} element;

typedef struct {
  element elts[EXPR_LEN];
} expr;
