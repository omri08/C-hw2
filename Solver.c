/*
 * Solver.c
 *
 *  Created on: Dec 24, 2019
 *      Author: afeka
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Solver.h"



//1*x+1*y+1*z=6
//Enter Equation
//5*z+2*y=-4
//Enter Equation
//2*x-1*z+5*y=27
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

	float det = 0;
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
			for(int k = 0 ; k < rows ; k ++ ){
				temp[k][i] = a[k][i];
			}


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
