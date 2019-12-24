/*
 * AllEquations.h
 *
 *  Created on: Dec 24, 2019
 *      Author: afeka
 */

#ifndef ALLEQUATIONS_H_
#define ALLEQUATIONS_H_
#include "Equations.h"


typedef struct
{
	int count; // number of equations
	Equation** eqArr; // all equations

}AllEquation;



int initAll(AllEquation* allEq);

#endif /* ALLEQUATIONS_H_ */
