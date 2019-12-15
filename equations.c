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

void setXYZ(char* number, char* prom)
{
	printf("%s - %s \n", number,prom);
	int len = strlen(number);



}



int initEq()
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
	setXYZ(number,prom);
	while(number)
	{


		number = strtok(NULL,token);
		prom = strtok(NULL,token);
		if(number);
		setXYZ(number,prom);

	}



}
