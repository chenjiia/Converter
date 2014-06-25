#ifndef LIGER_AST_H_
#define LIGER_AST_H_

//#include "type.h"
//#include "env.h"
#include "fxGenPre.h"
#include <glib.h>

//struct from Chris

/*** Declarations. ***/

enum ast_decl_class {
      AST_DECL_VAR = 256,
      AST_DECL_FX,
};

struct decl {
	//todo: further simplify everything~~you can do it believe in yourself
	int class;
	char* id;
	int expandFlag;
	//for fx decls
	char* params;
	int returnType;
	int returnCount;
	GList* decls;    // The decls in the body of a function def.
	GList* stmts;    // The stmts in the body of a function def.
};

/*** Statements. ***/

enum ast_stmt_class {
      AST_STMT_EXP = 256,
      AST_STMT_ASSIGN,

      AST_STMT_IF,

      AST_STMT_WHILE,
      AST_STMT_FOR,

      AST_STMT_RETURN,
	  
      AST_STMT_GOTO,
};

struct stmt {
      int class;
	  char* label;
      struct exp* left;
      // Intended for the condtional exp in if, while, and "from" exp in for.
      struct exp* exp;
      struct exp* right;
      GList* block1; // Stmt list
      GList* block2;
};

/*** Expressions. ***/

enum ast_exp_class {
      AST_EXP_PLUS = 256, //ed
      AST_EXP_MINUS,	//ed
      AST_EXP_DIV,	//ed
      AST_EXP_MOD,	//ed
      AST_EXP_MUL,	//ed

      AST_EXP_OR,
      AST_EXP_AND,
      AST_EXP_NOT,
	  AST_EXP_XOR,

      AST_EXP_LSHIFT,
      AST_EXP_RSHIFT,
	  
      AST_EXP_LT,
      AST_EXP_LT_EQ,
      AST_EXP_GT,
      AST_EXP_GT_EQ,

      AST_EXP_EQ,
      AST_EXP_NOT_EQ,

      AST_EXP_NUM,
      AST_EXP_TRUE,
      AST_EXP_FALSE,
      AST_EXP_NIL,
      AST_EXP_STR,
      AST_EXP_ID,

};

enum expand_flag{
	EXPAND_FALSE = 0,
	EXPAND_TRUE = 1,
};

struct exp {
      int class;
      int num;
	  //to decide whether expansion to bitLength is needed
	  int expandFlag;
      char* id;		//->id s
      char* str;	//int s

      struct exp* left;
      struct exp* right;
	  
	  //params removed
};

struct decl* decl_var_new(char* id, int expandFlag);
struct decl* decl_fx_new(char* id, char* params, int returnType, int returnCount, GList* decls, GList* stmts);
void decl_destroy(struct decl*);
void decls_destroy(GList*);
void decl_print(struct decl*, int bitLength);
void decls_print(GList*, int bitLength);

struct exp* exp_binop_new(int class, struct exp* left, struct exp* right); 
struct exp* exp_num_new(int num, int expandFlag); 
struct exp* exp_id_new(char* id, int expandFlag);
void binop_print(const char* op, struct exp* left, struct exp* right, int bitLength);
void exp_print(struct exp*, int);
void exps_print(GList*, int);
void exp_destroy(struct exp*);
void exps_destroy(GList*);

void stmts_print(GList* stmts, int bitLength);
void stmt_print(struct stmt* stmt, int bitLength);
struct stmt* stmt_if_new(struct exp* cond, GList* then_block, GList* else_block);
struct stmt* stmt_exp_new(struct exp* exp);
struct stmt* stmt_assign_new(struct exp* left, struct exp* right);
struct stmt* stmt_return_new(struct exp* exp);
struct stmt* stmt_while_new(struct exp* cond, GList* block);
struct stmt* stmt_goto_new(char* id);
void stmt_destroy(struct stmt*);
void stmts_destroy(GList*);

void id_print(char* id, int bitLength);
typedef void (*DestroyFunc)(void*);
void list_free_full(GList* list, DestroyFunc destroy);


#endif
