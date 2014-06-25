#include "fxGenPre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//you can do it!!
//sure~~~


//version 2 using inc and while loop
void printPlus(int bitLength){
	char* tempChar;
	char* tempArg;
	struct stmt* currStmt;
	//stmt location for return
	struct stmt* nextStmt;
	
	//leftX + rightX
	
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");
	
	struct fx* plus = calloc(1, sizeof(struct fx));
	plus->returnType = FX_RETURN_MULTBOOL;
	plus->returnCount = bitLength + 1;
	plus->name = strdup("plus");
	plus->params = strdup(argList[0]);
	
	//while loop
	//argListRight != 0
	plus->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt = plus->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	tempChar = int2bin(bitLength, 0);
	tempArg = strdup(argListRight[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListRight[0])+strlen(tempChar)+2));	//add , plus \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);

	//while loop
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_WHILE;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	
	//left = left << 1; // left shift one bit
	currStmt->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	nextStmt = currStmt->nextStmt;
	currStmt = currStmt->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("inc");
	currStmt->exp2->rightString = strdup(argListLeft[0]);
	
	//right = right - 1
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListRight[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("dec");
	currStmt->exp2->rightString = strdup(argListRight[0]);
	
	//repeat while loop condition
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	currStmt->exp2->rightString = strdup(tempArg);

	free(tempArg);
	free(tempChar);
	
	nextStmt->type = STMT_RETURN;
	nextStmt->exp1 = calloc(1, sizeof(struct exp));
	nextStmt->exp1->type = EXP_ID;
	nextStmt->exp1->leftString = strdup(argListLeft[0]);
	
	printFX(plus);
	
	freeFx(plus);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}

//version 2 using inc and while loop
void printMinus(int bitLength){
	char* tempChar;
	char* tempArg;
	struct stmt* currStmt;
	//stmt location for return
	struct stmt* nextStmt;
	
	//leftX + rightX
	
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");
	
	struct fx* minus = calloc(1, sizeof(struct fx));
	minus->returnType = FX_RETURN_MULTBOOL;
	minus->returnCount = bitLength + 1;
	minus->name = strdup("minus");
	minus->params = strdup(argList[0]);
	
	//while loop
	//argListRight != 0
	minus->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt = minus->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	tempChar = int2bin(bitLength, 0);
	tempArg = strdup(argListRight[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListRight[0])+strlen(tempChar)+2));	//add , minus \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);

	//while loop
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_WHILE;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	
	//left = left << 1; // left shift one bit
	currStmt->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	nextStmt = currStmt->nextStmt;
	currStmt = currStmt->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("dec");
	currStmt->exp2->rightString = strdup(argListLeft[0]);
	
	//right = right - 1
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListRight[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("dec");
	currStmt->exp2->rightString = strdup(argListRight[0]);
	
	//repeat while loop condition
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	currStmt->exp2->rightString = strdup(tempArg);

	free(tempArg);
	free(tempChar);
	
	nextStmt->type = STMT_RETURN;
	nextStmt->exp1 = calloc(1, sizeof(struct exp));
	nextStmt->exp1->type = EXP_ID;
	nextStmt->exp1->leftString = strdup(argListLeft[0]);
	
	printFX(minus);
	
	freeFx(minus);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}

void printLShift(int bitLength){
	char* tempChar;
	char* tempArg;
	struct stmt* currStmt;
	//stmt location for return
	struct stmt* nextStmt;
	
	//leftX is base, and rightX is shift
	
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");
	
	struct fx* lShift = calloc(1, sizeof(struct fx));
	lShift->returnType = FX_RETURN_MULTBOOL;
	lShift->returnCount = bitLength + 1;
	lShift->name = strdup("lShift");
	lShift->params = strdup(argList[0]);
	
	//while loop
	//argListRight != 0
	lShift->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt = lShift->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	tempChar = int2bin(bitLength, 0);
	tempArg = strdup(argListRight[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListRight[0])+strlen(tempChar)+2));	//add , and \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);

	//while loop
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_WHILE;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	
	//left = left << 1; // left shift one bit
	currStmt->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	nextStmt = currStmt->nextStmt;
	currStmt = currStmt->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("lShiftOne");
	currStmt->exp2->rightString = strdup(argListLeft[0]);
	
	//right = right - 1
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListRight[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("dec");
	currStmt->exp2->rightString = strdup(argListRight[0]);
	
	//repeat while loop condition
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	currStmt->exp2->rightString = strdup(tempArg);

	free(tempArg);
	free(tempChar);
	
	nextStmt->type = STMT_RETURN;
	nextStmt->exp1 = calloc(1, sizeof(struct exp));
	nextStmt->exp1->type = EXP_ID;
	nextStmt->exp1->leftString = strdup(argListLeft[0]);
	
	printFX(lShift);
	
	freeFx(lShift);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}

void printRShift(int bitLength){
	char* tempChar;
	char* tempArg;
	struct stmt* currStmt;
	//stmt location for return
	struct stmt* nextStmt;
	
	//leftX is base, and rightX is shift
	
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");
	
	struct fx* rShift = calloc(1, sizeof(struct fx));
	rShift->returnType = FX_RETURN_MULTBOOL;
	rShift->returnCount = bitLength + 1;
	rShift->name = strdup("rShift");
	rShift->params = strdup(argList[0]);
	
	//while loop
	//argListRight != 0
	rShift->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt = rShift->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	tempChar = int2bin(bitLength, 0);
	tempArg = strdup(argListRight[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListRight[0])+strlen(tempChar)+2));	//add , and \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);

	//while loop
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_WHILE;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	
	//left = left << 1; // left shift one bit
	currStmt->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	nextStmt = currStmt->nextStmt;
	currStmt = currStmt->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("rShiftOne");
	currStmt->exp2->rightString = strdup(argListLeft[0]);
	
	//right = right - 1
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListRight[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("dec");
	currStmt->exp2->rightString = strdup(argListRight[0]);
	
	//repeat while loop condition
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	currStmt->exp2->rightString = strdup(tempArg);

	free(tempArg);
	free(tempChar);
	
	nextStmt->type = STMT_RETURN;
	nextStmt->exp1 = calloc(1, sizeof(struct exp));
	nextStmt->exp1->type = EXP_ID;
	nextStmt->exp1->leftString = strdup(argListLeft[0]);
	
	printFX(rShift);
	
	freeFx(rShift);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}
/*
//depend on inc plus oneComplement
void printMinus(int bitLength){
//ref: http://en.wikipedia.org/wiki/Method_of_complements#Binary_example
	char* tempChar;
	char* tempArg;
	struct stmt* currStmt;

	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");

	struct fx* minus = calloc(1, sizeof(struct fx));
	minus->returnType = FX_RETURN_MULTBOOL;
	minus->returnCount = bitLength + 1;
	minus->name = strdup("minus");
	minus->params = strdup(argList[0]);
	
	//y = ~y
	minus->stmt1 = calloc(1, sizeof(struct stmt));
	minus->stmt1->type = STMT_ASSIGN;
	minus->stmt1->exp1 = calloc(1, sizeof(struct exp));
	minus->stmt1->exp1->type = EXP_ID;
	minus->stmt1->exp1->leftString = strdup(argListRight[0]);
	minus->stmt1->exp2 = calloc(1, sizeof(struct exp));
	minus->stmt1->exp2->type = EXP_FXCALL;
	minus->stmt1->exp2->leftString = strdup("oneComplement");
	minus->stmt1->exp2->rightString = strdup(argListRight[0]);
	
	//x = x + y
	minus->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = minus->stmt1->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("plus");
	currStmt->exp2->rightString = strdup(argList[0]);
	
	//x = x + 1;
	//due to seg fault in getafix, call plus instead of inc
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("plus");
	tempChar = int2bin(bitLength, 1);
	tempArg = strdup(argListLeft[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListLeft[0])+strlen(tempChar)+2));	//add , and \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);
	
	//return x(highest bit set to 0)
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_RETURN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp1->leftString[0] = '0';
	currStmt->exp1->leftString[1] = ',';

	if(strlen(leftVars[bitLength])>2){
		int temp;
		//overwrite the ','
		for(temp = 2; temp <= strlen(leftVars[bitLength]); temp++){
			currStmt->exp1->leftString[temp] = ' ';
		}
	}
	
	printFX(minus);
	
	freeFx(minus);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}*/

//no dependency
void printOneComplement(int bitLength){
	int temp;
	char** vars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, vars, argList, "x");
	
	struct fx* oneComplement = calloc(1, sizeof(struct fx));
	oneComplement->returnType = FX_RETURN_MULTBOOL;
	oneComplement->returnCount = bitLength + 1;
	oneComplement->name = strdup("oneComplement");
	oneComplement->params = strdup(argList[0]);
	
	oneComplement->stmt1 = calloc(1, sizeof(struct stmt));
	oneComplement->stmt1->type = STMT_RETURN;
	oneComplement->stmt1->exp1 = calloc(1, sizeof(struct exp));
	oneComplement->stmt1->exp1->type = EXP_ID;
	oneComplement->stmt1->exp1->leftString = calloc(1, strlen(argList[0])+bitLength+1+1-strlen(vars[bitLength]));
	for(temp = bitLength; temp >= 0; temp--){
		if(temp == bitLength){
			strcat(oneComplement->stmt1->exp1->leftString, "0");
		}else{
		strcat(oneComplement->stmt1->exp1->leftString, "~");
		strcat(oneComplement->stmt1->exp1->leftString, vars[temp]);
		}
		if(temp){
			strcat(oneComplement->stmt1->exp1->leftString, ",");
		}
	}
	
	printFX(oneComplement);
	
	freeFx(oneComplement);
	
	freeHalfVarName(bitLength, vars, argList);
}
/*
//depend on xor and isNotEqual lShiftOne
void printPlus(int bitLength){
//ref: http://en.wikipedia.org/wiki/Bitwise_operations_in_C#Bitwise_AND_.22.26.22
	struct stmt* currStmt;
	struct stmt* nextStmt;
	char* tempChar;
	char* tempArg;

	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);
	
	char** varsLeft = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListLeft = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsLeft, argListLeft, "left");
	
	char** varsRight = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListRight = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsRight, argListRight, "right");
	
	char** varsSum = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListSum = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsSum, argListSum, "sum");
	
	char** varsCarry = calloc(1,sizeof(char*)*(bitLength+1));
	char** argListCarry = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, varsCarry, argListCarry, "carry");

	struct fx* plus = calloc(1, sizeof(struct fx));
	plus->returnType = FX_RETURN_MULTBOOL;
	plus->returnCount = bitLength + 1;
	plus->name = strdup("plus");
	plus->params = strdup(argList[0]);
	//decl
	plus->decl1 = calloc(1, sizeof(struct decl));
	plus->decl1->declString = strdup(argListSum[0]);
	
	plus->decl1->nextDecl = calloc(1, sizeof(struct decl));
	plus->decl1->nextDecl->declString = strdup(argListCarry[0]);
	
	plus->decl1->nextDecl = calloc(1, sizeof(struct decl));
	plus->decl1->nextDecl->declString = strdup("returnTemp");

	//sum = x ^ y; // Ex - OR x and y
	plus->stmt1 = calloc(1, sizeof(struct stmt));
	plus->stmt1->type = STMT_ASSIGN;
	plus->stmt1->exp1 = calloc(1, sizeof(struct exp));
	plus->stmt1->exp1->type = EXP_ID;
	plus->stmt1->exp1->leftString = strdup(argListSum[0]);
	plus->stmt1->exp2 = calloc(1, sizeof(struct exp));
	plus->stmt1->exp2->type = EXP_FXCALL;
	plus->stmt1->exp2->leftString = strdup("xor");
	plus->stmt1->exp2->rightString = strdup(argList[0]);
	
	//carry = x & y; // AND x and y
	plus->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	plus->stmt1->nextStmt->type = STMT_ASSIGN;
	plus->stmt1->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	plus->stmt1->nextStmt->exp1->type = EXP_ID;
	plus->stmt1->nextStmt->exp1->leftString = strdup(argListCarry[0]);
	plus->stmt1->nextStmt->exp2 = calloc(1, sizeof(struct exp));
	plus->stmt1->nextStmt->exp2->type = EXP_FXCALL;
	plus->stmt1->nextStmt->exp2->leftString = strdup("and");
	plus->stmt1->nextStmt->exp2->rightString = strdup(argList[0]);
	//todo: write while loop here
	
	plus->stmt1->nextStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = plus->stmt1->nextStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	tempChar = int2bin(bitLength, 0);
	tempArg = strdup(argListCarry[0]);
	tempArg = realloc(tempArg, sizeof(char)*(strlen(argListCarry[0])+strlen(tempChar)+2));	//add , and \0
	strcat(tempArg, ",");
	strcat(tempArg, tempChar);
	currStmt->exp2->rightString = strdup(tempArg);

	
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_WHILE;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	
	//carry = carry << 1; // left shift the carry
	currStmt->stmt1 = calloc(1, sizeof(struct stmt));
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	nextStmt = currStmt->nextStmt;
	currStmt = currStmt->stmt1;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListCarry[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("lShiftOne");
	currStmt->exp2->rightString = strdup(argListCarry[0]);
	
	//x = sum; // initialize x as sum
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListLeft[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_ID;
	currStmt->exp2->leftString = strdup(argListSum[0]);
	
	//y = carry; // initialize y as carry
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListRight[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_ID;
	currStmt->exp2->leftString = strdup(argListCarry[0]);
	
	//sum = x ^ y; // sum is calculated
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListSum[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("xor");
	currStmt->exp2->rightString = strdup(argList[0]);
	
	//carry = x & y;  carry is calculated
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup(argListCarry[0]);
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("and");
	currStmt->exp2->rightString = strdup(argList[0]);
	
	//todo: repeat returnTemp
	currStmt->nextStmt = calloc(1, sizeof(struct stmt));
	currStmt = currStmt->nextStmt;
	currStmt->type = STMT_ASSIGN;
	currStmt->exp1 = calloc(1, sizeof(struct exp));
	currStmt->exp1->type = EXP_ID;
	currStmt->exp1->leftString = strdup("returnTemp");
	currStmt->exp2 = calloc(1, sizeof(struct exp));
	currStmt->exp2->type = EXP_FXCALL;
	currStmt->exp2->leftString = strdup("isNotEqual");	
	currStmt->exp2->rightString = strdup(tempArg);

	free(tempArg);
	free(tempChar);
	
	nextStmt->type = STMT_RETURN;
	nextStmt->exp1 = calloc(1, sizeof(struct exp));
	nextStmt->exp1->type = EXP_ID;
	nextStmt->exp1->leftString = strdup(argListSum[0]);
	
	printFX(plus);
	
	freeFx(plus);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
	freeHalfVarName(bitLength, varsSum, argListSum);
	freeHalfVarName(bitLength, varsCarry, argListCarry);
	freeHalfVarName(bitLength, varsLeft, argListLeft);
	freeHalfVarName(bitLength, varsRight, argListRight);
}*/

//no dependency
void printAnd(int bitLength){
	int temp;
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* and = calloc(1, sizeof(struct fx));
	and->returnType = FX_RETURN_MULTBOOL;
	and->returnCount = bitLength + 1;
	and->name = strdup("and");
	and->params = strdup(argList[0]);
	
	and->stmt1 = calloc(1, sizeof(struct stmt));
	and->stmt1->type = STMT_RETURN;
	and->stmt1->exp1 = calloc(1, sizeof(struct exp));
	and->stmt1->exp1->type = EXP_ID;
	and->stmt1->exp1->leftString = calloc(1, strlen(argList[0]) +1);	//they are of the same length
	for(temp = bitLength; temp>=0; temp--){
		strcat(and->stmt1->exp1->leftString, leftVars[temp]);
		strcat(and->stmt1->exp1->leftString, "&");
		strcat(and->stmt1->exp1->leftString, rightVars[temp]);
		if(temp){
			strcat(and->stmt1->exp1->leftString, ",");
		}
	}
	
	printFX(and);
	
	freeFx(and);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printOr(int bitLength){
	int temp;
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* or = calloc(1, sizeof(struct fx));
	or->returnType = FX_RETURN_MULTBOOL;
	or->returnCount = bitLength + 1;
	or->name = strdup("or");
	or->params = strdup(argList[0]);
	
	or->stmt1 = calloc(1, sizeof(struct stmt));
	or->stmt1->type = STMT_RETURN;
	or->stmt1->exp1 = calloc(1, sizeof(struct exp));
	or->stmt1->exp1->type = EXP_ID;
	or->stmt1->exp1->leftString = calloc(1, strlen(argList[0]) +1);	//they are of the same length
	for(temp = bitLength; temp>=0; temp--){
		strcat(or->stmt1->exp1->leftString, leftVars[temp]);
		strcat(or->stmt1->exp1->leftString, "|");
		strcat(or->stmt1->exp1->leftString, rightVars[temp]);
		if(temp){
			strcat(or->stmt1->exp1->leftString, ",");
		}
	}
	
	printFX(or);
	
	freeFx(or);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printXor(int bitLength){
	int temp;
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* xor = calloc(1, sizeof(struct fx));
	xor->returnType = FX_RETURN_MULTBOOL;
	xor->returnCount = bitLength + 1;
	xor->name = strdup("xor");
	xor->params = strdup(argList[0]);
	
	xor->stmt1 = calloc(1, sizeof(struct stmt));
	xor->stmt1->type = STMT_RETURN;
	xor->stmt1->exp1 = calloc(1, sizeof(struct exp));
	xor->stmt1->exp1->type = EXP_ID;
	xor->stmt1->exp1->leftString = calloc(1, strlen(argList[0]) +1);	//they are of the same length
	for(temp = bitLength; temp>=0; temp--){
		strcat(xor->stmt1->exp1->leftString, leftVars[temp]);
		strcat(xor->stmt1->exp1->leftString, "^");
		strcat(xor->stmt1->exp1->leftString, rightVars[temp]);
		if(temp){
			strcat(xor->stmt1->exp1->leftString, ",");
		}
	}
	
	printFX(xor);
	
	freeFx(xor);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printRShiftOne(int bitLength){	
	char** vars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, vars, argList, "x");
	
	struct fx* RShiftOne = calloc(1, sizeof(struct fx));
	RShiftOne->returnType = FX_RETURN_MULTBOOL;
	RShiftOne->returnCount = bitLength + 1;
	RShiftOne->name = strdup("rShiftOne");
	RShiftOne->params = strdup(argList[0]);
	RShiftOne->decl1 = NULL;
	
	RShiftOne->stmt1 = calloc(1, sizeof(struct stmt));
	RShiftOne->stmt1->type = STMT_RETURN;
	
	RShiftOne->stmt1->exp1 = calloc(1, sizeof(struct exp));
	RShiftOne->stmt1->exp1->type = EXP_ID;
	RShiftOne->stmt1->exp1->leftString = calloc(1, strlen(argList[0]) +1 - strlen(vars[0] +1));
	RShiftOne->stmt1->exp1->leftString[0] = '0';
	RShiftOne->stmt1->exp1->leftString[1] = ',';
	strncpy(&(RShiftOne->stmt1->exp1->leftString[2]), argList[0], strlen(argList[0]) - strlen(vars[0]) -1);
	RShiftOne->stmt1->exp1->right = NULL;
	RShiftOne->stmt1->exp1->rightString = NULL;
	RShiftOne->stmt1->exp2 = NULL;
	RShiftOne->stmt1->stmt1 = NULL;
	RShiftOne->stmt1->stmt2 = NULL;
	RShiftOne->stmt1->nextStmt = NULL;

	printFX(RShiftOne);
	
	freeFx(RShiftOne);
	
	freeHalfVarName(bitLength, vars, argList);
}

//no dependency
void printLShiftOne(int bitLength){	
	char** vars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, vars, argList, "x");
	
	struct fx* LShiftOne = calloc(1, sizeof(struct fx));
	LShiftOne->returnType = FX_RETURN_MULTBOOL;
	LShiftOne->returnCount = bitLength + 1;
	LShiftOne->name = strdup("lShiftOne");
	LShiftOne->params = strdup(argList[0]);
	LShiftOne->decl1 = NULL;
	
	LShiftOne->stmt1 = calloc(1, sizeof(struct stmt));
	LShiftOne->stmt1->type = STMT_RETURN;
	
	LShiftOne->stmt1->exp1 = calloc(1, sizeof(struct exp));
	LShiftOne->stmt1->exp1->type = EXP_ID;
	LShiftOne->stmt1->exp1->leftString = calloc(1, strlen(argList[0]) +1 - strlen(vars[bitLength] +1));
	strncpy(LShiftOne->stmt1->exp1->leftString, &argList[0][strlen(vars[bitLength])+1], strlen(argList[0]) - strlen(vars[bitLength]) -1);
	strcat(LShiftOne->stmt1->exp1->leftString, ",0");
	LShiftOne->stmt1->exp1->right = NULL;
	LShiftOne->stmt1->exp1->rightString = NULL;
	LShiftOne->stmt1->exp2 = NULL;
	LShiftOne->stmt1->stmt1 = NULL;
	LShiftOne->stmt1->stmt2 = NULL;
	LShiftOne->stmt1->nextStmt = NULL;

	printFX(LShiftOne);
	
	freeFx(LShiftOne);
	
	freeHalfVarName(bitLength, vars, argList);
}

//no dependency
void printISGT(int bitLength){
	int temp;
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isGT = calloc(1, sizeof(struct fx));
	isGT->returnType = FX_RETURN_BOOL;
	isGT->returnCount = 0;
	isGT->name = strdup("isGT");
	isGT->params = strdup(argList[0]);
	
	isGT->stmt1 = calloc(1, sizeof(struct stmt));
	struct stmt* currStmt = isGT->stmt1;
	
	for(temp = bitLength; temp >= 0; temp--){
		if(temp){
			currStmt->type = STMT_IFELSE;
		}else{
			currStmt->type = STMT_IF;	//type if when temp is 0
		}
		//if condition
		currStmt->exp1 = calloc(1, sizeof(struct exp));
		currStmt->exp1->type = EXP_NEQ;
		currStmt->exp1->leftString = strdup(leftVars[temp]);
		currStmt->exp1->rightString = strdup(rightVars[temp]);
		
		//then if
		currStmt->stmt1 = calloc(1, sizeof(struct stmt));
		currStmt->stmt1->type = STMT_IF;
		currStmt->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->exp1->type = EXP_EQ;
		currStmt->stmt1->exp1->leftString = strdup(leftVars[temp]);
		currStmt->stmt1->exp1->rightString = strdup("1");
		//		then
		currStmt->stmt1->stmt1 = calloc(1, sizeof(struct stmt));
		currStmt->stmt1->stmt1->type = STMT_RETURN;
		currStmt->stmt1->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->stmt1->exp1->type = EXP_LITERAL;
		currStmt->stmt1->stmt1->exp1->leftString = strdup("1");
		
		if(temp){
			//else
			currStmt->stmt2 = calloc(1, sizeof(struct stmt));
			currStmt = currStmt->stmt2;	//go into loop					
		}
	}
	
	isGT->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	isGT->stmt1->nextStmt->type = STMT_RETURN;
	isGT->stmt1->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isGT->stmt1->nextStmt->exp1->type = EXP_LITERAL;
	isGT->stmt1->nextStmt->exp1->leftString = strdup("0");
	
	printFX(isGT);
	
	freeFx(isGT);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printISLT(int bitLength){
	int temp;
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isLT = calloc(1, sizeof(struct fx));
	isLT->returnType = FX_RETURN_BOOL;
	isLT->returnCount = 0;
	isLT->name = strdup("isLT");
	isLT->params = strdup(argList[0]);
	
	isLT->stmt1 = calloc(1, sizeof(struct stmt));
	struct stmt* currStmt = isLT->stmt1;
	
	for(temp = bitLength; temp >= 0; temp--){
		if(temp){
			currStmt->type = STMT_IFELSE;
		}else{
			currStmt->type = STMT_IF;	//type if when temp is 0
		}
		//if condition
		currStmt->exp1 = calloc(1, sizeof(struct exp));
		currStmt->exp1->type = EXP_NEQ;
		currStmt->exp1->leftString = strdup(leftVars[temp]);
		currStmt->exp1->rightString = strdup(rightVars[temp]);
		
		//then if
		currStmt->stmt1 = calloc(1, sizeof(struct stmt));
		currStmt->stmt1->type = STMT_IF;
		currStmt->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->exp1->type = EXP_EQ;
		//change from leftVars(isGT) to rightVars
		currStmt->stmt1->exp1->leftString = strdup(rightVars[temp]);
		currStmt->stmt1->exp1->rightString = strdup("1");
		//		then
		currStmt->stmt1->stmt1 = calloc(1, sizeof(struct stmt));
		currStmt->stmt1->stmt1->type = STMT_RETURN;
		currStmt->stmt1->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->stmt1->exp1->type = EXP_LITERAL;
		currStmt->stmt1->stmt1->exp1->leftString = strdup("1");
		
		if(temp){
			//else
			currStmt->stmt2 = calloc(1, sizeof(struct stmt));
			currStmt = currStmt->stmt2;	//go into loop					
		}
	}
	
	isLT->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	isLT->stmt1->nextStmt->type = STMT_RETURN;
	isLT->stmt1->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isLT->stmt1->nextStmt->exp1->type = EXP_LITERAL;
	isLT->stmt1->nextStmt->exp1->leftString = strdup("0");
	
	printFX(isLT);
	
	freeFx(isLT);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printISNOTEQUAL(int bitLength){
	int temp;
	char** leftVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isNotEqual = calloc(1,sizeof(struct fx));
	isNotEqual->returnType = FX_RETURN_BOOL;
	isNotEqual->returnCount = 0;
	isNotEqual->name = strdup("isNotEqual");
	isNotEqual->params = strdup(argList[0]);
	
	isNotEqual->stmt1 = calloc(1,sizeof(struct stmt));
	isNotEqual->stmt1->type = STMT_IFELSE;
	isNotEqual->stmt1->exp1 = calloc(1,sizeof(struct exp));
	struct exp* currExp = isNotEqual->stmt1->exp1;
	
	for(temp = bitLength; temp >= 0; temp--){
		currExp->type = EXP_NEQ;
		currExp->leftString = strdup(leftVars[temp]);
		if(temp){
			currExp->right = calloc(1,sizeof(struct exp));
			currExp->right->type = EXP_OR;
			currExp->right->leftString = strdup(rightVars[temp]);
			currExp->right->right = calloc(1,sizeof(struct exp));
			currExp = currExp->right->right;
		}else{
			currExp->rightString = strdup(rightVars[temp]);
		}
	}
	
	isNotEqual->stmt1->stmt1 = calloc(1,sizeof(struct stmt));
	isNotEqual->stmt1->stmt1->type = STMT_RETURN;
	isNotEqual->stmt1->stmt1->exp1 = calloc(1,sizeof(struct exp));
	isNotEqual->stmt1->stmt1->exp1->type = EXP_LITERAL;
	isNotEqual->stmt1->stmt1->exp1->leftString = strdup("1");
	
	isNotEqual->stmt1->stmt2 = calloc(1,sizeof(struct stmt));
	isNotEqual->stmt1->stmt2->type = STMT_RETURN;
	isNotEqual->stmt1->stmt2->exp1 = calloc(1,sizeof(struct exp));
	isNotEqual->stmt1->stmt2->exp1->type = EXP_LITERAL;
	isNotEqual->stmt1->stmt2->exp1->leftString = strdup("0");
	
	printFX(isNotEqual);
	
	freeFx(isNotEqual);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printISEQUAL(int bitLength){
	int temp;
	char** leftVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isEqual = calloc(1,sizeof(struct fx));
	isEqual->returnType = FX_RETURN_BOOL;
	isEqual->returnCount = 0;
	isEqual->name = strdup("isEqual");
	isEqual->params = strdup(argList[0]);
	
	isEqual->stmt1 = calloc(1,sizeof(struct stmt));
	isEqual->stmt1->type = STMT_IFELSE;
	isEqual->stmt1->exp1 = calloc(1,sizeof(struct exp));
	struct exp* currExp = isEqual->stmt1->exp1;
	
	for(temp = bitLength; temp >= 0; temp--){
		currExp->type = EXP_EQ;
		currExp->leftString = strdup(leftVars[temp]);
		if(temp){
			currExp->right = calloc(1,sizeof(struct exp));
			currExp->right->type = EXP_AND;
			currExp->right->leftString = strdup(rightVars[temp]);
			currExp->right->right = calloc(1,sizeof(struct exp));
			currExp = currExp->right->right;
		}else{
			currExp->rightString = strdup(rightVars[temp]);
		}
	}
	
	isEqual->stmt1->stmt1 = calloc(1,sizeof(struct stmt));
	isEqual->stmt1->stmt1->type = STMT_RETURN;
	isEqual->stmt1->stmt1->exp1 = calloc(1,sizeof(struct exp));
	isEqual->stmt1->stmt1->exp1->type = EXP_LITERAL;
	isEqual->stmt1->stmt1->exp1->leftString = strdup("1");
	
	isEqual->stmt1->stmt2 = calloc(1,sizeof(struct stmt));
	isEqual->stmt1->stmt2->type = STMT_RETURN;
	isEqual->stmt1->stmt2->exp1 = calloc(1,sizeof(struct exp));
	isEqual->stmt1->stmt2->exp1->type = EXP_LITERAL;
	isEqual->stmt1->stmt2->exp1->leftString = strdup("0");
	
	printFX(isEqual);
	
	freeFx(isEqual);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//depend on isGT isEqual
void printISGTEQ(int bitLength){
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isGTEQ = calloc(1, sizeof(struct fx));
	isGTEQ->returnType = FX_RETURN_BOOL;
	isGTEQ->returnCount = 0;
	isGTEQ->name = strdup("isGTEQ");
	isGTEQ->params = strdup(argList[0]);
	//decl
	isGTEQ->decl1 = calloc(1, sizeof(struct decl));
	isGTEQ->decl1->declString = strdup("eq, gt");

	isGTEQ->stmt1 = calloc(1, sizeof(struct stmt));
	isGTEQ->stmt1->type = STMT_ASSIGN;
	isGTEQ->stmt1->exp1 = calloc(1, sizeof(struct exp));
	isGTEQ->stmt1->exp1->type = EXP_ID;
	isGTEQ->stmt1->exp1->leftString = strdup("eq");
	isGTEQ->stmt1->exp2 = calloc(1, sizeof(struct exp));
	isGTEQ->stmt1->exp2->type = EXP_FXCALL;
	isGTEQ->stmt1->exp2->leftString = strdup("isEqual");
	isGTEQ->stmt1->exp2->rightString = strdup(argList[0]);
	
	isGTEQ->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	isGTEQ->stmt1->nextStmt->type = STMT_ASSIGN;
	isGTEQ->stmt1->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isGTEQ->stmt1->nextStmt->exp1->type = EXP_ID;
	isGTEQ->stmt1->nextStmt->exp1->leftString = strdup("gt");
	isGTEQ->stmt1->nextStmt->exp2 = calloc(1, sizeof(struct exp));
	isGTEQ->stmt1->nextStmt->exp2->type = EXP_FXCALL;
	isGTEQ->stmt1->nextStmt->exp2->leftString = strdup("isGT");
	isGTEQ->stmt1->nextStmt->exp2->rightString = strdup(argList[0]);
	
	isGTEQ->stmt1->nextStmt->nextStmt = calloc(1, sizeof(struct stmt));
	isGTEQ->stmt1->nextStmt->nextStmt->type = STMT_RETURN;
	isGTEQ->stmt1->nextStmt->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isGTEQ->stmt1->nextStmt->nextStmt->exp1->type = EXP_OR;
	isGTEQ->stmt1->nextStmt->nextStmt->exp1->leftString = strdup("eq");
	isGTEQ->stmt1->nextStmt->nextStmt->exp1->rightString = strdup("gt");
	
	printFX(isGTEQ);
	
	freeFx(isGTEQ);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//depend on isLT isEqual
void printISLTEQ(int bitLength){
	char** leftVars = calloc(1, sizeof(char*)*(bitLength+1));
	char** rightVars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setVarName(bitLength, leftVars, rightVars, argList);

	struct fx* isLTEQ = calloc(1, sizeof(struct fx));
	isLTEQ->returnType = FX_RETURN_BOOL;
	isLTEQ->returnCount = 0;
	isLTEQ->name = strdup("isLTEQ");
	isLTEQ->params = strdup(argList[0]);
	//decl
	isLTEQ->decl1 = calloc(1, sizeof(struct decl));
	isLTEQ->decl1->declString = strdup("eq, lt");

	isLTEQ->stmt1 = calloc(1, sizeof(struct stmt));
	isLTEQ->stmt1->type = STMT_ASSIGN;
	isLTEQ->stmt1->exp1 = calloc(1, sizeof(struct exp));
	isLTEQ->stmt1->exp1->type = EXP_ID;
	isLTEQ->stmt1->exp1->leftString = strdup("eq");
	isLTEQ->stmt1->exp2 = calloc(1, sizeof(struct exp));
	isLTEQ->stmt1->exp2->type = EXP_FXCALL;
	isLTEQ->stmt1->exp2->leftString = strdup("isEqual");
	isLTEQ->stmt1->exp2->rightString = strdup(argList[0]);
	
	isLTEQ->stmt1->nextStmt = calloc(1, sizeof(struct stmt));
	isLTEQ->stmt1->nextStmt->type = STMT_ASSIGN;
	isLTEQ->stmt1->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isLTEQ->stmt1->nextStmt->exp1->type = EXP_ID;
	isLTEQ->stmt1->nextStmt->exp1->leftString = strdup("lt");
	isLTEQ->stmt1->nextStmt->exp2 = calloc(1, sizeof(struct exp));
	isLTEQ->stmt1->nextStmt->exp2->type = EXP_FXCALL;
	isLTEQ->stmt1->nextStmt->exp2->leftString = strdup("isLT");
	isLTEQ->stmt1->nextStmt->exp2->rightString = strdup(argList[0]);
	
	isLTEQ->stmt1->nextStmt->nextStmt = calloc(1, sizeof(struct stmt));
	isLTEQ->stmt1->nextStmt->nextStmt->type = STMT_RETURN;
	isLTEQ->stmt1->nextStmt->nextStmt->exp1 = calloc(1, sizeof(struct exp));
	isLTEQ->stmt1->nextStmt->nextStmt->exp1->type = EXP_OR;
	isLTEQ->stmt1->nextStmt->nextStmt->exp1->leftString = strdup("eq");
	isLTEQ->stmt1->nextStmt->nextStmt->exp1->rightString = strdup("lt");
	
	printFX(isLTEQ);
	
	freeFx(isLTEQ);
	
	freeVarName(bitLength, leftVars, rightVars, argList);
}

//no dependency
void printINC(int bitLength){
	int temp;
	int temp2;
	char* tempChar;
	char* tempChar2;
	char** vars = calloc(1,sizeof(char*)*(bitLength+1));
	char** argList = calloc(1,sizeof(char*));
	setHalfVarName(bitLength, vars, argList, "x");

	struct fx* inc = calloc(1,sizeof(struct fx));
	inc->returnType = FX_RETURN_MULTBOOL;
	inc->returnCount = bitLength + 1;
	inc->name = strdup("inc");
	inc->params = strdup(argList[0]);
	
	inc->stmt1 = calloc(1,sizeof(struct stmt));
	struct stmt* currStmt = inc->stmt1;
	
	//start from zero
	for(temp = 0; temp < bitLength; temp++){
		currStmt->type = STMT_IFELSE;
		//if condition
		currStmt->exp1 = calloc(1,sizeof(struct exp));
		currStmt->exp1->type = EXP_EQ;
		currStmt->exp1->leftString = strdup(vars[temp]);
		currStmt->exp1->rightString = strdup("0");
		
		//then return statement
		currStmt->stmt1 = calloc(1,sizeof(struct stmt));
		currStmt->stmt1->type = STMT_RETURN;
		currStmt->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->exp1->type = EXP_ID;
		currStmt->stmt1->exp1->leftString = strdup(argList[0]);
		tempChar2 = calloc(1, strlen(vars[temp])+1+1);
		strcat(tempChar2, vars[temp]);
		if(temp){
			strcat(tempChar2, ",");		
		}
		tempChar = strstr(currStmt->stmt1->exp1->leftString, tempChar2);

		free(tempChar2);
		//change current char to 1 and overwrite the rest
		*tempChar ='1';
		tempChar ++;
		for(temp2 = 0; temp2 < temp; temp2++){
			*tempChar = ',';
			tempChar ++;
			*tempChar = '0';
			tempChar ++;
		}
		*tempChar = '\0';
		
		//else
		currStmt->stmt2 = calloc(1, sizeof(struct stmt));
		if(temp != bitLength - 1){
			currStmt = currStmt->stmt2;
		}else{
			currStmt->stmt2->type = STMT_RETURN;
			currStmt->stmt2->exp1 = calloc(1, sizeof(struct exp));
			currStmt->stmt2->exp1->type = EXP_ID;
			currStmt->stmt2->exp1->leftString = strdup(argList[0]);
			tempChar2 = calloc(1, strlen(vars[temp+1])+1+1);
			strcat(tempChar2, vars[temp+1]);
			if(temp){
				strcat(tempChar2, ",");		
			}			
			tempChar = strstr(currStmt->stmt2->exp1->leftString, tempChar2);	
			free(tempChar2);
			*tempChar ='1';
			tempChar ++;
			for(temp2 = 0; temp2 <= temp; temp2++){
				*tempChar = ',';
				tempChar ++;
				*tempChar = '0';
				tempChar ++;
			}
			*tempChar = '\0';		
		}
	}
		
	printFX(inc);
	
	freeFx(inc);
	
	freeHalfVarName(bitLength, vars, argList);
}

//no dependency
void printDEC(int bitLength){
	int temp;
	int temp2;
	char* tempChar;
	char* tempChar2;
	char** vars = calloc(1, sizeof(char*)*(bitLength+1));
	char** argList = calloc(1, sizeof(char*));
	setHalfVarName(bitLength, vars, argList, "x");

	struct fx* dec = calloc(1, sizeof(struct fx));
	dec->returnType = FX_RETURN_MULTBOOL;
	dec->returnCount = bitLength + 1;
	dec->name = strdup("dec");
	dec->params = strdup(argList[0]);
	
	dec->stmt1 = calloc(1, sizeof(struct stmt));
	struct stmt* currStmt = dec->stmt1;
	
	//start from zero
	for(temp = 0; temp < bitLength; temp++){
		currStmt->type = STMT_IFELSE;
		//if condition
		currStmt->exp1 = calloc(1, sizeof(struct exp));
		currStmt->exp1->type = EXP_EQ;
		currStmt->exp1->leftString = strdup(vars[temp]);
		currStmt->exp1->rightString = strdup("1");
		
		//then return statement
		currStmt->stmt1 = calloc(1, sizeof(struct stmt));
		currStmt->stmt1->type = STMT_RETURN;
		currStmt->stmt1->exp1 = calloc(1, sizeof(struct exp));
		currStmt->stmt1->exp1->type = EXP_ID;
		currStmt->stmt1->exp1->leftString = strdup(argList[0]);
		tempChar2 = calloc(1, strlen(vars[temp])+1+1);
		strcat(tempChar2, vars[temp]);
		if(temp){
			strcat(tempChar2, ",");		
		}			
		tempChar = strstr(currStmt->stmt1->exp1->leftString, tempChar2);
		free(tempChar2);
		//change current char to 1 and overwrite the rest
		*tempChar ='0';
		tempChar ++;
		for(temp2 = 0; temp2 < temp; temp2++){
			*tempChar = ',';
			tempChar ++;
			*tempChar = '1';
			tempChar ++;
		}
		*tempChar = '\0';
		
		//else
		currStmt->stmt2 = calloc(1, sizeof(struct stmt));
		if(temp != bitLength - 1){
			currStmt = currStmt->stmt2;
		}else{
			currStmt->stmt2->type = STMT_RETURN;
			currStmt->stmt2->exp1 = calloc(1, sizeof(struct exp));
			currStmt->stmt2->exp1->type = EXP_ID;
			currStmt->stmt2->exp1->leftString = strdup(argList[0]);
			tempChar2 = calloc(1, strlen(vars[temp+1])+1+1);
			strcat(tempChar2, vars[temp+1]);
			if(temp){
				strcat(tempChar2, ",");		
			}			
			tempChar = strstr(currStmt->stmt2->exp1->leftString, tempChar2);	
			free(tempChar2);
			*tempChar ='0';
			tempChar ++;
			for(temp2 = 0; temp2 <= temp; temp2++){
				*tempChar = ',';
				tempChar ++;
				*tempChar = '1';
				tempChar ++;
			}
			*tempChar = '\0';	
		}
	}
		
	printFX(dec);
	
	freeFx(dec);
	
	freeHalfVarName(bitLength, vars, argList);
}

int main(int argc, char** argv) {
	if (argc!=2){
		fprintf(stderr,"usage: a.out bitlength\n"); 
		exit(1);
	}
	int bitLength = atoi(argv[1]);
	printf("\n");
	printAnd(bitLength);
		printf("\n");

	printOr(bitLength);
		printf("\n");

	printOneComplement(bitLength);
		printf("\n");

	printXor(bitLength);
		printf("\n");

	printRShiftOne(bitLength);
		printf("\n");

	printLShiftOne(bitLength);
		printf("\n");

	printISGT(bitLength);
		printf("\n");

	printISLT(bitLength);
		printf("\n");

	printISEQUAL(bitLength);
		printf("\n");

	printISNOTEQUAL(bitLength);
		printf("\n");

	printISGTEQ(bitLength);
		printf("\n");

	printISLTEQ(bitLength);
		printf("\n");

	printINC(bitLength);
		printf("\n");

	printDEC(bitLength);
		printf("\n");

	printPlus(bitLength);
		printf("\n");

	printMinus(bitLength);
		printf("\n");
		
	printLShift(bitLength);
		printf("\n");

	printRShift(bitLength);
		printf("\n");

	return 0;
}
