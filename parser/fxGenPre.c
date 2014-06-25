#include "fxGenPre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* int2bin(int bitLength, uint64_t num1){
	int temp;
	uint64_t temp2;
	char* num2;
	//need to set to zeros before strcat
	num2 = calloc(1, sizeof(char)*(bitLength*2 + 2));	//count in , and \0
	for (temp = bitLength; temp >= 0; temp --) {
		temp2 = num1 >> temp;
		if (temp2 & 1){
			if(!temp){
				strcat(num2, "1");
			}else{
				strcat(num2, "1,");
			}
		}else{
			if(!temp){
				strcat(num2, "0");
			}else{
				strcat(num2, "0,");
			}		
		}
	}
	return num2;
}


//todo:  -) cheer up!

//print function->need to redirect. Printf for now

// int NumDigits(int n); ref:http://stackoverflow.com/questions/1696086/whats-the-best-way-to-get-the-length-of-the-decimal-representation-of-an-int-in
int NumDigits(int n) {
    int digits = 0;
    if (n <= 0) {
        n = -n;
        ++digits;
    }
    while (n) {
        n /= 10;
        ++digits;
    }
    return digits;
}

void setVarName(int bitLength, char** leftVars, char** rightVars, char** argList){
	int temp;
	int argListLength = 0;
	int argListLengthTemp = 0;
	
	for(temp = bitLength; temp >= 0; temp--){
		leftVars[temp] = calloc(1, sizeof(char)*(argListLengthTemp=(4+NumDigits(bitLength)+1)));
		argListLength += argListLengthTemp;	//+1 for ';', -1 for removing space for '\0'
		sprintf(leftVars[temp], "left%d", temp);
		rightVars[temp] = calloc(1, sizeof(char)*(argListLengthTemp=(5+NumDigits(bitLength)+1)));
		argListLength += argListLengthTemp;
		sprintf(rightVars[temp], "right%d", temp);
	}
	argListLength --;	//remove last ';'
	
	//construct the args list string
	argList[0] = calloc(1, sizeof(char)*(argListLength + 1));
	for(temp = bitLength; temp >= 0; temp--){
		strcat(argList[0], leftVars[temp]);
		strcat(argList[0], ",");
	}
	for(temp = bitLength; temp >= 0; temp--){
		strcat(argList[0], rightVars[temp]);
		if(temp){
			strcat(argList[0], ",");
		}
	}
}

void freeVarName(int bitLength, char** leftVars, char** rightVars, char** argList){
	int temp;
	
	for(temp = bitLength; temp >= 0; temp--){
		free(leftVars[temp]);
		free(rightVars[temp]);
	}
	free(argList[0]);
	//this is causing something
	free(argList);
	free(leftVars);
	free(rightVars);
}

void setHalfVarName(int bitLength, char** vars, char** argList, const char* prefix){
	int temp;
	int argListLength = 0;
	int argListLengthTemp = 0;
	int prefixLength = strlen(prefix);
	
	for(temp = bitLength; temp >= 0; temp--){
		vars[temp] = calloc(1, sizeof(char)*(argListLengthTemp=(prefixLength+NumDigits(bitLength)+1)));
		argListLength += argListLengthTemp;	//+1 for ';', -1 for removing space for '\0'
		sprintf(vars[temp], "%s%d", prefix, temp);
	}
	argListLength --;	//remove last ';'
	
	//construct the args list string
	argList[0] = calloc(1, sizeof(char)*(argListLength + 1));
	
	for(temp = bitLength; temp >= 0; temp--){
		strcat(argList[0], vars[temp]);
		if(temp){
			strcat(argList[0], ",");
		}
	}
}

void freeHalfVarName(int bitLength, char** vars, char** argList){
	int temp;
	
	for(temp = bitLength; temp >= 0; temp--){
		free(vars[temp]);
	}
	free(argList[0]);
	free(argList);
	free(vars);
}
