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

void setXYZ(Equation* eq,char* number, char* prom)
{
	if(prom == NULL)
		printf("Free number is: %s", number);
	else
	{
	int temp = findProm(prom);
	printf("%s-%s-%d\n", number,prom,temp);

	}


}

int findProm(char* prom)
{
	char x[2];
	char y[2];
	*x = 'x';
	*y = 'y';
    printf("\n%s\n",prom);

    printf("\n%s\n",x);
	int checkX = strcmp(prom,x);
	int checkY = strcmp(prom,y);
	if(checkX == 0)
		return 0;
	else if (checkY == 0)
		return 1;
	else
		return 2;
}

int initEq(Equation* eq)
{
	char* str;
	str = createDynStr("Equation");
	if(!str)
		return 0;
	char* token = "* +  = ";
	char* number;
	char* prom;
	number = strtok(str,token);
	prom = strtok(NULL,token);

	while(number)
	{

		setXYZ(eq,number,prom);
		number = strtok(NULL,token);
		prom = strtok(NULL,token);

	}



}
