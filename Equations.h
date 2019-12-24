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



int initEq(Equation* eq);
void setXYZ(Equation* eq, float number, char prom,int minus);
void printEq(const Equation* eq);
int findProm(char prom);



#endif /* EQUATIONS_H_ */
