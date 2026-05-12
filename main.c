#include "optimizer.h"
#include "validator.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double evaluate(expr *ex, double x);

typedef struct {
  double bestScore;
  int datacount;
  datapoint *dataset;
} checkData;

typedef void (*emitfn)(expr *e, void *userdata);

static void rec_fill(int pos, int n, int m, expr *cur, emitfn emit,
                     void *userdata) {
  if (pos == n) {
    emit(cur, userdata);
    return;
  }
  for (int digit = 0; digit < m; ++digit) {
    cur->elts[pos].typ = (enum elt_type)digit;
    cur->elts[pos].value = 0.0;
    rec_fill(pos + 1, n, m, cur, emit, userdata);
  }
}

void generate_exprs(emitfn emit, void *userdata) {
  expr cur;
  printf("Generating\n");
  rec_fill(0, EXPR_LEN, ELT_TYP_COUNT, &cur, emit, userdata);
}

void checkfn(expr *e, void *data) {
  checkData *d = data;
  if (!iscompliant(e))
    return;
  for (int i = 0; i < 1; ++i) {
    opt(e, d->dataset, d->datacount);
  }
  double ev = opt(e, d->dataset, d->datacount);
  if (ev == 0.0) {
    for (int i = 0; i < EXPR_LEN; ++i) {
      printf("Typ: %d Val: %f\n", e->elts[i].typ, e->elts[i].value);
    }
    exit(1);
  }
  if (ev < d->bestScore) {
    d->bestScore = ev;
    for (int i = 0; i < EXPR_LEN; ++i) {
      printf("Typ: %d Val: %f\n", e->elts[i].typ, e->elts[i].value);
    }
    printf("Has loss of %f\n", ev);
  }
}

int main() {
  datapoint dataset[256];
  for (int i = 0; i < 256; ++i) {
    double x = ((double)i / 128.0 - 1.0) * M_PI;
    double y = sin(x);
    datapoint d;
    d.x = x;
    d.y = y;
    dataset[i] = d;
  }

  double bestScore = 999.0;

  checkData d;
  d.bestScore = bestScore;
  d.datacount = 256;
  d.dataset = dataset;

  generate_exprs(checkfn, &d);

  return 0;
}
