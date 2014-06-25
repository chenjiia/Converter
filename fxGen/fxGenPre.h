#ifndef FXGENPRE_H
#define FXGENPRE_H

#include <stdint.h>

//expression types
enum {
      EXP_EQ = 256,
      EXP_NEQ,
      EXP_GT,
      EXP_LT,
	  EXP_AND,
	  EXP_OR,
	  EXP_FXCALL,
	  EXP_NOT,
	  EXP_ID,				//or IDs
	  EXP_LITERAL			//or literals
};

//statement types
enum {
      STMT_IFELSE = 456,
      STMT_IF,
      STMT_RETURN,
	  STMT_WHILE,
	  STMT_ASSIGN
};

//function return types
enum {
      FX_RETURN_BOOL = 556,
      FX_RETURN_MULTBOOL,
      FX_RETURN_VOID
};

//exp is a bin tree.
struct exp{
	int type;
	struct exp* left;
	struct exp* right;
	char* leftString;
	char* rightString;
};

struct stmt{
	int type;
	struct exp* exp1;
	struct exp* exp2;
	struct stmt* stmt1;
	struct stmt* stmt2;
	struct stmt* nextStmt;
};

struct decl{
	char* declString;	//like "S0, S1, S2"
	struct decl* nextDecl;
};

struct fx{
	int returnType;
	int returnCount;
	char* name;
	char* params;
	struct stmt* stmt1;
	struct decl* decl1;
};

struct innerProgram{
	int bitLength;
	struct stmt* stmt1;
};

//this one does not support 64bit int. right shift is cyclic?
char* int2bin(int bitLength, uint64_t num1);

//constructors for structs.-->not used
/*
void newExp(struct exp* exp1, int type, struct exp* right, char* leftString, char* rightString);
void newStmt(struct stmt* stmt1,int type,struct exp* exp1,struct exp* exp2,struct stmt* inStmt1,struct stmt* inStmt2,struct stmt* nextStmt);
void newDecl(struct decl* decl1,char* declString,struct decl* nextDecl);
void newFx(struct fx* fx1,int returnType,int returnCount,char* name,char* params,struct stmt* stmt1,struct decl* decl1);
*/

void printFX(struct fx* fx1);
void printSTMT(struct stmt* stmt1);
void printEXP(struct exp* exp1);
void printDECL(struct decl* decl1);

int NumDigits(int n);
void freeFx(struct fx* fx1);
void freeStmt(struct stmt* stmt1);
void freeExp(struct exp* exp1);
void freeDecl(struct decl* decl1);

void setVarName(int bitLength, char** leftVars, char** rightVars, char** argList);
void freeVarName(int bitLength, char** leftVars, char** rightVars, char** argList);
void setHalfVarName(int bitLength, char** vars, char** argList, char* prefix);
void freeHalfVarName(int bitLength, char** vars, char** argList);

#endif
