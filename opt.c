#include "data.h"
#include "expr.h"
#include "score.h"
#include <stdio.h>

double opt(expr *e, datapoint *dataset, int datacount) {
  double lr = 0.01;
  double lv = score(e, dataset, datacount);
  for (int i = 0; i < EXPR_LEN; ++i) {
    if (e->elts[i].typ != ELT_NUMBER)
      continue;
    double pre = e->elts[i].value;
    double preeval = score(e, dataset, datacount);
    double nudge = pre + 0.0001;
    double nudgeeval = score(e, dataset, datacount);
    double dedx = (nudgeeval - preeval) / 0.0001;
    lv = nudgeeval;
    e->elts[i].value -= lr * dedx;
  }
  return lv;
}
