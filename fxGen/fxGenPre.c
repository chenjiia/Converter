#include "fxGenPre.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
//todo: implement all new's
void newExp(struct exp* exp1, int type, struct exp* right, char* leftString, char* rightString){
	exp1->type = type;
	exp1->right = right;
	exp1->leftString = leftString;
	exp1->rightString = rightString;
}

void newStmt(struct stmt* stmt1,int type,struct exp* exp1,struct exp* exp2,struct stmt* inStmt1,struct stmt* inStmt2,struct stmt* nextStmt){
	stmt1->type = type;
	stmt1->exp1 = exp1;
	stmt1->exp2 = exp2;
	stmt1->stmt1 = inStmt1;
	stmt1->stmt2 = inStmt2;
	stmt1->nextStmt = nextStmt;
}

void newDecl(struct decl* decl1,char* declString,struct decl* nextDecl){
	decl1->declString = declString;
	decl1->nextDecl = nextDecl;
}

void newFx(struct fx* fx1,int returnType,int returnCount,char* name,char* params,struct stmt* stmt1,struct decl* decl1){
	fx1->returnType = returnType;
	fx1->returnCount = returnCount;
	fx1->name = name;
	fx1->params = params;
	fx1->stmt1 = stmt1;
	fx1->decl1 = decl1;
}
*/

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

//free calloc and strdup used in construction
void freeFx(struct fx* fx1){
	free(fx1->name);
	free(fx1->params);
	if(fx1->stmt1){
		freeStmt(fx1->stmt1);
	}
	if(fx1->decl1){
		freeDecl(fx1->decl1);
	}
	free(fx1);
}

void freeStmt(struct stmt* stmt1){
	if(stmt1->exp1){
		freeExp(stmt1->exp1);
	}
	if(stmt1->exp2){
		freeExp(stmt1->exp2);
	}
	if(stmt1->stmt1){
		freeStmt(stmt1->stmt1);
	}
	if(stmt1->stmt2){
		freeStmt(stmt1->stmt2);
	}
	if(stmt1->nextStmt){
		freeStmt(stmt1->nextStmt);
	}
	free(stmt1);
}

void freeDecl(struct decl* decl1){
	free(decl1->declString);
	if(decl1->nextDecl){
		freeDecl(decl1->nextDecl);
	}
	free(decl1);
}

void freeExp(struct exp* exp1){
	free(exp1->leftString);
	free(exp1->rightString);
	if(exp1->right){
		freeExp(exp1->right);
	}
	free(exp1);
}

//todo:  -) cheer up!

//print function->need to redirect. Printf for now
void printFX(struct fx* fx1){
	switch(fx1->returnType){
		case FX_RETURN_BOOL:
			printf("bool ");
		break;
		case FX_RETURN_MULTBOOL:
			printf("bool<%d> ", fx1->returnCount);
		break;
		case FX_RETURN_VOID:
			printf("vold ");
		break;
		default:
		break;
	}
	
	printf("%s", fx1->name);
	printf("(%s)\n", fx1->params);
	printf("begin\n");
	if(fx1->decl1){
		printDECL(fx1->decl1);
	}
	if(fx1->stmt1){
		printSTMT(fx1->stmt1);
	}
	printf("end\n");
}

void printDECL(struct decl* decl1){
	printf("decl ");
	printf("%s;\n", decl1->declString);
	if(decl1->nextDecl){
		printDECL(decl1->nextDecl);
	}
}

void printSTMT(struct stmt* stmt1){
	if(!stmt1){
		return;
	}
	switch (stmt1->type){
		case STMT_RETURN:
			printf("return ");
			printEXP(stmt1->exp1);
			printf(";\n");
		break;
		case STMT_IFELSE:
			printf("if (");
			printEXP(stmt1->exp1);
			printf(") then\n");
			printSTMT(stmt1->stmt1);
			printf("else \n");
			printSTMT(stmt1->stmt2);
			printf("fi\n");
		break;
		case STMT_IF:
			printf("if (");
			printEXP(stmt1->exp1);
			printf(") then\n");
			printSTMT(stmt1->stmt1);
			printf("fi\n");
		break;
		case STMT_ASSIGN:
			printEXP(stmt1->exp1);
			printf(" := ");
			printEXP(stmt1->exp2);
			printf(";\n");
		break;
		case STMT_WHILE:
			printf("while (");
			printEXP(stmt1->exp1);
			printf(") do\n");
			printSTMT(stmt1->stmt1);
			printf("od\n");
		break;
	}
	if(stmt1->nextStmt){
		printSTMT(stmt1->nextStmt);
	}
}

void printEXP(struct exp* exp1){
	if(exp1->type == EXP_NOT){
		printf("!");
	}
	
	printf("%s", exp1->leftString);
	
	switch(exp1->type){
		case EXP_LITERAL:
		break;
		case EXP_ID:
		break;
		case EXP_EQ:
			printf(" = ");
		break;
		case EXP_NEQ:
			printf(" != ");
		break;
		case EXP_AND:
			printf(" & ");
		break;
		case EXP_OR:
			printf(" | ");
		break;
		case EXP_FXCALL:
			printf(" (");
	}
	if(exp1->right){
		printEXP(exp1->right);
	}else if(exp1->rightString){
		printf("%s", exp1->rightString);
	}
	if(exp1->type == EXP_FXCALL){
		printf(")");
	}
}

//a set of fxs to generate args list and var namespace

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

void setHalfVarName(int bitLength, char** vars, char** argList, char* prefix){
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
