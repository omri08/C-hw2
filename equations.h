/*
 * equations.h
 *
 *  Created on: 14 Dec 2019
 *      Author: Omri
 */

#ifndef EQUATIONS_H_
#define EQUATIONS_H_

typedef struct
{
	int count;
	float* A; // coefficients of x,y,z (int that order)
    float B; // the free number on the right side
}Equation;


typedef struct
{
	int count; // number of equations
	Equation** eqArr; // all equations

}AllEquation;

typedef struct
{
	int count;
	float** A_Mat;
	float*  B_VEC;
	float   Detrmin;
	float*  X_Vec;
}Solver;

//single equation
int initEq(Equation* eq);
void setXYZ(Equation* eq,char* number, char* prom);
void printEq(const Equation* eq);

// all equation
int findProm(char* prom);
int initAll(AllEquation* allEq);

// solver/matrix
int initSolver(Solver* sol);
void initMatrix(float** mat,AllEquation* allEq);
void printMatrix(const float** mat, int size);

#endif /* EQUATIONS_H_ */
