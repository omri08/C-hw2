/*
 * equations.c
 *
 *  Created on: 14 Dec 2019
 *      Author: omri
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringsFuncs.h"
#include "equations.h"

void setXYZ(Equation *eq, float number, char prom, int minus) {
//10*x-3*y-3*z=3
	if (prom == 'f') {
		if (minus == 1)
			number *= -1;
		eq->B = number;
	} else {
		int index = findProm(prom);
		if (minus == 1)
			number *= (-1);
		eq->A[index] = number;

	}

}

int findProm(char prom) {

	if (prom == 'x')
		return 0;
	else if (prom == 'y')
		return 1;
	else
		return 2;
}

int initEq(Equation *eq) {
	char *str;
	str = createDynStr("Equation");
	char neg = '-';
	int minus = 0;
	if (!str)
		return 0;
	//-1.2*x+95.85*y-123.456*z=3
	//Enter Equation
	//-1.1*x+2.2*y-3.3*z=3
	//Enter Equation
	//95.85*x-1.23*y+78*z=3
	eq->A = (float*) malloc(sizeof(float) * 3);
	for(int i = 0 ; i < eq->count ; i ++)
		eq->A[i] = 0;
	for (int i = 0; i < strlen(str); i++) {

		float number = 0;
		char prom = 'f';
		int position = 0;
		minus = 0;
		if (str[i] == neg) {
			minus = 1;
			i++;
		}
		while (isdigit(str[i]) || str[i] == '.') {
			if(str[i] == '.')
			{
			 position++;
			 i++;
			} else {
			if(position >0)
             position++;
			float temp = str[i] - '0';
			number = number * 10 + temp;
			i++;
			}

		}
		while(position-1 > 0) {
			number/=10;
			position--;
		}
		if (str[i] == neg) {
			minus = 1;
			i++;
		}
		if (str[i] == '*') {
			i++;
			prom = str[i];
		}
		if (str[i] == '=' || str[i] == '+')
			continue;

		setXYZ(eq, number, prom, minus);

	}
	if (eq->B != 0 && eq->count == 0)
		return 0;

	return 1;
}

void printEq(const Equation *eq) {
	for (int i = 0; i < eq->count; i++) {
		printf("%0.3f ", eq->A[i]);
	}
	printf("\n");
}

int initAll(AllEquation *allEq) {
	int numEq;
	printf("Enter number of equations(1-3)\n");
	scanf("%d", &numEq);
	allEq->count = numEq;
	while ((getchar()) != '\n')
		; // to clean the buffer

	allEq->eqArr = (Equation**) malloc(numEq * sizeof(Equation*));
	for (int i = 0; i < numEq; i++) {
		allEq->eqArr[i] = (Equation*) malloc(sizeof(Equation));
		allEq->eqArr[i]->count = numEq;
		if (!allEq->eqArr[i])
			return 0;
		if (initEq(allEq->eqArr[i]) == 0) {
			printf("Invalid equation");
			free(allEq->eqArr[i]);
			return 0;
		}

	}

	return 1;
}

int initMatrix(float **mat, AllEquation *allEq) {
	int cols;
	cols = allEq->eqArr[0]->count;
	for (int i = 0; i < allEq->count; i++) {
		mat[i] = (float*) malloc(sizeof(float) * allEq->eqArr[i]->count);
		for (int j = 0; j < allEq->eqArr[i]->count; j++) {

			mat[i][j] = allEq->eqArr[i]->A[j];
		}
		free(allEq->eqArr[i]->A);
		free(allEq->eqArr[i]);
	}
	return cols;
}

void printMatrix(const float **mat, int rows, int cols) {
	printf("-----------printing matrix------\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			printf(" %0.3f ", mat[i][j]);
		printf("\n");
	}
}

int det(Solver *sol, int rows, int cols) {
	float temp;
	float **a = sol->A_Mat;
	if (rows != cols)
		return -1;
	if (rows == 1 && cols == 1) {
		sol->Detrmin = sol->A_Mat[0][0];
		return 1;
	}
	if (rows == 2 && cols == 2) {
		sol->Detrmin = sol->A_Mat[0][0] * sol->A_Mat[1][1]
				- sol->A_Mat[1][0] * sol->A_Mat[0][1];
		return 1;
	}
	if (rows == 3 && cols == 3) {
		float  r1 = a[0][0] * ((a[1][1] * a[2][2])
		    - (a[2][1] * a[1][2]));

		   float r2 = a[0][1] * ((a[1][0] * a[2][2])
		    - (a[2][0] * a[1][2]));

		    float r3 = a[0][2] * ((a[1][0] * a[2][1])
		    - (a[2][0] * a[1][1]));

		 float    detval= r1 - r2 + r3;

		sol->Detrmin = detval;
		return 1;
	}
	return -1;

}

int initSolver(Solver *sol) {
	AllEquation *allEq;
	allEq = (AllEquation*) malloc(sizeof(AllEquation));

	if (!allEq)
		return 0;

	if (initAll(allEq) == 0) {
		free(allEq);
		return 0;
	}

	sol->count = allEq->count;
	sol->A_Mat = (float**) malloc(sol->count * sizeof(float*));
	if (!sol->A_Mat) {
		free(allEq);
		return 0;
	}

	int cols = initMatrix(sol->A_Mat, allEq);
	printMatrix(sol->A_Mat, sol->count, cols);
	if(det(sol,sol->count,cols) == 1)
		printf("The det is: %0.3f",sol->Detrmin);

	return 1;
}

