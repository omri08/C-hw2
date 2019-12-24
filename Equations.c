/*
 * equations.c
 *
 *  Created on: 14 Dec 2019
 *      Author: omri
 */
#include "Equations.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringsFuncs.h"

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
	//1*x+1*y+1*z=6
	//0*x+2*y+5*z=-4
	//2*x+5*y-1*z=27
	eq->A = (float*) malloc(sizeof(float) * 3);
	for (int i = 0; i < eq->count; i++)
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
			if (str[i] == '.') {
				position++;
				i++;
			} else {
				if (position > 0)
					position++;
				float temp = str[i] - '0';
				number = number * 10 + temp;
				i++;
			}

		}
		while (position - 1 > 0) {
			number /= 10;
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













