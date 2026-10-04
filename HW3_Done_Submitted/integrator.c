/* YOU MUST MODIFY THIS FILE */
// Read "hw3.h" to learn about the two data types: `Range` and `RangeAnswer`

#include "hw3.h"

double integrate1(Range rng)
{
  double step = (rng.upperlimit - rng.lowerlimit) / rng.intervals;
  double sum = 0.0;
  for (int i = 0; i < rng.intervals; i++)
  {
    double x = rng.lowerlimit + i * step;
    sum += func(x);
  }
  return step * sum;
}

void integrate2(RangeAnswer * rngans)
{
  rngans -> answer = integrate1(rngans -> rng);
}
