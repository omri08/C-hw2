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

float det(float **mat, int rows, int cols) {

	float det;
	if (rows != cols)
		return -1;
	if (rows == 1 && cols == 1) {
		det = mat[0][0];
		return det;
	}
	if (rows == 2 && cols == 2) {
		det = mat[0][0] * mat[1][1]- mat[1][0] * mat[0][1];
		return det;
	}
	if (rows == 3 && cols == 3) {

		for (int i = 0; i < 3; i++)
			det = det
					+ (mat[0][i]
							* (mat[1][(i + 1) % 3]
									* mat[2][(i + 2) % 3]
									- mat[1][(i + 2) % 3]
											* mat[2][(i + 1) % 3]));


		return det;
	}
	return -1;

}

int solve(Solver *sol, float **a, float originalDet, int rows, int cols) {

		float **temp;
		temp = (float**) malloc(sizeof(float*) * rows);
	    // coping by value
		for(int i = 0 ; i < rows ; i ++){
			temp[i] = (float*)malloc(sizeof(float)*rows);
			for(int j = 0 ; j < rows ; j ++) {
				temp[i][j] = a[i][j];
			}
		}

		sol->X_Vec = (float*)malloc(sizeof(float)*rows);
		// using cramer
		for(int i = 0 ; i < rows ; i ++) {
			for(int j = 0 ; j < rows ; j++){
				temp[j][i] = sol->B_VEC[j];
			}
			float tempD = det(temp,rows,cols);
			sol->X_Vec[i] = tempD  / originalDet;

			// go back to the original
			for(int k = 0 ; k < rows ; k ++ )
				temp[k][i] = a[k][i];


		}


      // relase all
		for(int i = 0; i < rows ; i ++){
		   free(temp[i]);
		}
		free(temp);


	return 1;
}

void initB(Solver *sol, AllEquation *allEq) {
	sol->B_VEC = (float*) malloc(allEq->count * sizeof(float));
	for (int i = 0; i < allEq->count; i++) {
		sol->B_VEC[i] = allEq->eqArr[i]->B;
	}
}


void freeSol(Solver* sol){
	free(sol->B_VEC);
	free(sol->X_Vec);
	for(int i = 0 ; i < sol->count ; i ++) {
		free(sol->A_Mat[i]);
	}
	free(sol->A_Mat);
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
	initB(sol, allEq);


	int cols = initMatrix(sol->A_Mat, allEq);

	printMatrix(sol->A_Mat, sol->count, cols);

	printf("\nB vector is:\n");
    for(int i = 0 ; i < cols ; i ++)
    	printf("%0.3f\n",sol->B_VEC[i]);

	sol->Detrmin = det(sol->A_Mat,sol->count,cols);
    printf("The detrmin is: %0.3f\n",sol->Detrmin);
	// solve the equation
	if(sol->Detrmin != 0 && sol->Detrmin != -1 ) {
		solve(sol, sol->A_Mat, sol->Detrmin, sol->count, cols);

		// print the equation
      for(int i = 0 ; i < cols ; i ++) {
    	  if(i == 0)
    		  printf("X = %0.3f\n",sol->X_Vec[i]);
    	  if(i == 1)
    		  printf("Y = %0.3f\n",sol->X_Vec[i]);
    	  if(i == 2)
    	  printf("Z = %0.3f\n",sol->X_Vec[i]);

      }
	} else {
     printf("Sorry, det is 0");
     return -1;
	}

   freeSol(sol);
	return 1;
}

