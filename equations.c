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

void setXYZ(Equation *eq, int number, char prom,int minus) {
//10*x-3*y-3*z=3
	if (prom == 'f') {
        if(minus == 1)
        	number*=-1;
		    eq->B = number;
	} else {
		int index = findProm(prom);
		eq->count++;
		if(minus == 1)
			number*=(-1);
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
	eq->count = 0;
	str = createDynStr("Equation");
	char neg = '-';
	int minus = 0;
	if (!str)
		return 0;
	// 10*x-3*y-3*z=3;
	eq->A = (float*) malloc(sizeof(float) * 3);
	for(int i = 0 ; i < strlen(str) ; i ++)
	{
		int counter = 1;
		int number = 0;
		char prom = 'f';
	   	minus = 0;
	   	if(str[i] == neg) {
	   		minus = 1;
	   		i++;
	   	}
	   	while(isdigit(str[i]))
	   	{
	   		float temp = str[i] - '0';
	   		number = number*counter + temp;
	   		counter*=10;
	   		i++;
	   	}
	 	if(str[i] == neg) {
		   		minus = 1;
		   		i++;
		   	}
	   	if(str[i] == '*') {
	   		i++;
	   		prom = str[i];
	   	}
        if(str[i] == '=' || str[i] == '+')
        	continue;

	   	setXYZ(eq,number,prom,minus);

	}
	if(eq->B !=0 && eq->count == 0)
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
		if (!allEq->eqArr[i])
			return 0;
		if (initEq(allEq->eqArr[i]) == 0) {
			printf("Invalid equation");
			free(allEq->eqArr[i]);
			return 0;
		}

	}
	for (int i = 0; i < numEq; i++)
		printEq(allEq->eqArr[i]);
	return 1;
}

int initMatrix(float **mat, AllEquation *allEq) {
	int cols;
	cols = allEq->eqArr[0]->count;
	for (int i = 0; i < allEq->count; i++) {
		mat[i] = (float*)malloc(sizeof(float)*allEq->eqArr[i]->count);
		for (int j = 0; j < allEq->eqArr[i]->count; j++) {

            mat[i][j] = allEq->eqArr[i]->A[j];
		}
		free(allEq->eqArr[i]->A);
		free(allEq->eqArr[i]);
	}
	return cols;
}

void printMatrix(const float** mat,int rows, int cols) {
	printf("-----------printing matrix------\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			printf(" %0.3f ", mat[i][j]);
		printf("\n");
	}
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


	int cols = initMatrix(sol->A_Mat,allEq);
	printMatrix(sol->A_Mat, sol->count,cols);
	return 1;
}


