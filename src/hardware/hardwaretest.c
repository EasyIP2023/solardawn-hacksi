#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "hardwaretest.h"

double return_watts () {
  double value = rand() / (double)RAND_MAX;
  return value;
}

double return_amount_used () {
  double value = rand() / (double)RAND_MAX;
  return value;
}

double return_amount_produced () {
  double value = rand() / (double)RAND_MAX;
  return value;
}

double return_total_power () {
  double value = rand() / (double)RAND_MAX;
  return value;
}

double return_watt_hours () {
  double value = rand() / (double)RAND_MAX;
  return value;
}
