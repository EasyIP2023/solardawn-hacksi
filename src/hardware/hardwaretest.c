/*
 * Copyright (c) 2017, Vincent Davis
 *
 *----------------------------------------------------------------------
 * This file is part of project solardawn.
 *
 *  solardawn is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  solardawn is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with solardawn; if not, write to the Free Software
 *  Foundation, Inc.:
 *      59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *----------------------------------------------------------------------
 */

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
