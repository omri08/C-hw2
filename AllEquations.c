/*
 * AllEquations.c
 *
 *  Created on: Dec 24, 2019
 *      Author: afeka
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AllEquations.h"

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
