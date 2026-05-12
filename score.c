#include "data.h"
#include "evaluate.h"
#include <stdio.h>

double score(expr *ex, datapoint *dataset, int datacount) {
  double loss = 0.0;
  for (int i = 0; i < datacount; ++i) {
    double appx = evaluate(ex, dataset[i].x);
    double corr = dataset[i].y;
    double err = appx - corr;
    loss += (err + 0.1) * err;
  }

  return loss;
}
