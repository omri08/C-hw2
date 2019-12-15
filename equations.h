/*
 * equations.h
 *
 *  Created on: 14 Dec 2019
 *      Author: omri
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

}AllEuations;

typedef struct
{
	int count;
	float** A_Mat;
	float*  B_VEC;
	float   Detrmin;
	float*  X_Vec;
};

int initEq(Equation* eq);
void setXYZ(Equation* eq,char* number, char* prom);
int findProm(char* prom);
#endif /* EQUATIONS_H_ */
