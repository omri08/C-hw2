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

		fNumber = atof(stringNumber);
		eq->A[index] = fNumber;

	}

}

int findProm(char *prom) {
	char *x;
	x = (char*) malloc(2 * sizeof(char));
	char *y;
	y = (char*) malloc(2 * sizeof(char));
	*x = 'x';
	*y = 'y';
	int checkX = strcmp(prom, x);
	int checkY = strcmp(prom, y);
	free(x);
	free(y);
	if (checkX == 0)
		return 0;
	else if (checkY == 0)
		return 1;
	else
		return 2;
}

int initEq(Equation *eq) {
	char *str;

	str = createDynStr("Equation");
	if (!str)
		return 0;

	eq->A = (float*) malloc(sizeof(float) * 3);

	char *token = "* +=";
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

	printf(" X  : %0.3f \n Y  : %0.3f \n Z  : %0.3f \n B  : %0.3f \n", eq->A[0],
			eq->A[1], eq->A[2], eq->B);

	return 1;

}
