#ifndef FXGENPRE_H
#define FXGENPRE_H

#include <stdint.h>

//this one does not support 64bit int. right shift is cyclic?
char* int2bin(int bitLength, uint64_t num1);
int NumDigits(int n);

void setVarName(int bitLength, char** leftVars, char** rightVars, char** argList);
void freeVarName(int bitLength, char** leftVars, char** rightVars, char** argList);
void setHalfVarName(int bitLength, char** vars, char** argList, const char* prefix);
void freeHalfVarName(int bitLength, char** vars, char** argList);

#endif
