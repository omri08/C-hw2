/*
 * main.c
 *
 *  Created on: 14 Dec 2019
 *      Author: omri
 */
#include <stdlib.h>

#include "Solver.h"


int main()
{
 Solver* eq;
  eq = (Solver*)malloc(sizeof(Solver));
  initSolver(eq);

}
