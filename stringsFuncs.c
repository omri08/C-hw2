/*
 * stringsFuncs.c
 *
 *  Created on: 14 Dec 2019
 *      Author: omri
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stringsFuncs.h"

char* createDynStr(const char *msg) {
	char temp[80];
	char *str;

	printf("Enter %s\n", msg);

    if(fgets(temp, sizeof(temp), stdin))
    {
	temp[strcspn(temp, "\n")] = '\0';
	str = (char*) malloc(strlen(temp) + 1 * sizeof(char));
	strcpy(str, temp);
	return str;
    }
    return NULL;

}

