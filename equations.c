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

void setXYZ(Equation *eq, char *stringNumber, char *prom) {
	float fNumber;
	float freeNumber;
	if (prom == NULL) {
		freeNumber = atof(stringNumber);
		eq->B = freeNumber;
	} else {
		int index = findProm(prom);
		eq->count++;
		fNumber = atof(stringNumber);
		eq->A[index] = fNumber;

	}

}

int findProm(char *prom) {
	char x[2];
	x[0] = 'x';
	x[1] = '\0';
	char y[2];
	y[0] = 'y';
	y[1] = '\0';

	int checkX = strcmp(prom, x);
	int checkY = strcmp(prom, y);

	if (checkX == 0)
		return 0;
	else if (checkY == 0)
		return 1;
	else
		return 2;
}

int initEq(Equation *eq) {
	char *str;
	eq->count = 0;
	str = createDynStr("Equation");
	if (!str)
		return 0;

	eq->A = (float*) malloc(sizeof(float) * 3);

	char *token = "*+=";
	char *neg = "-";
	char *number;
	char *prom;
	int skip = 0;
	number = strtok(str, token);
	prom = strtok(NULL, token);
	int checkNeg;

	while (number) {

		if (skip != 1)
			setXYZ(eq, number, prom);
		skip = 0;
		number = strtok(NULL, token);
		if (number != NULL)
			checkNeg = strcmp(number, neg);

		if (checkNeg == 0) {
			char temp[50] = "";
			number = strtok(NULL, token);
			strcat(temp, neg);
			strcat(temp, number);
			prom = strtok(NULL, token);
			skip = 1;
			setXYZ(eq, temp, prom);
		}
		if (skip != 1)
			prom = strtok(NULL, token);

	}

	if (eq->count == 0 && eq->B != 0) // invalid equation
		return 0;
	else
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

void initMatrix(float **mat, AllEquation *allEq) {
	for (int i = 0; i < allEq->count; i++) {
		for (int j = 0; j < allEq->count; j++) {
			mat[i][j] = allEq->eqArr[i]->A[j];

		}
		free(allEq->eqArr[i]->A);
		free(allEq->eqArr[i]);
	}
}

void printMatrix(const float **mat, int size) {
	printf("-----------printing matrix------\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
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

	for (int i = 0; i < sol->count; i++)
		sol->A_Mat[i] = (float*) malloc(sol->count * sizeof(float));

	printMatrix(sol->A_Mat, sol->count);
	return 1;
}


