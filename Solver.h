/*
 * Solver.h
 *
 *  Created on: Dec 24, 2019
 *      Author: afeka
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "AllEquations.h"



typedef struct
{
	int count;
	float** A_Mat;
	float*  B_VEC;
	float   Detrmin;
	float*  X_Vec;
}Solver;




int initSolver(Solver* sol);
int initMatrix(float** mat,AllEquation* allEq);
float det(float **mat, int rows, int cols);
void initB(Solver* sol,AllEquation* allEq );
void printMatrix(const float** mat,int rows, int cols);
int solve(Solver* sol,float **a, float originalDet, int rows, int cols);
void freeSol(Solver* sol);
#endif /* SOLVER_H_ */
