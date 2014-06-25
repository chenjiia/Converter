#include "ast.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

static struct stmt* stmt_new(int class);
static struct exp* exp_new(int class);
static struct decl* decl_new(int class);

/*** Declarations. ***/

struct decl* decl_var_new(char* id, int expandFlag) {
      struct decl* d = decl_new(AST_DECL_VAR);
      d->id = id;
      d->expandFlag = expandFlag;
      return d;
}

struct decl* decl_fx_new(char* id, char* params, int returnType, int returnCount, GList* decls, GList* stmts) {
      struct decl* d = decl_new(AST_DECL_FX);
      d->id = id;
      d->params = params;
      d->returnType = returnType;
      d->returnCount = returnCount;
      d->decls = decls;
      d->stmts = stmts;
      return d;
}

struct decl* decl_new(int class) {
      struct decl* d = calloc(1, sizeof(struct decl));
	  d->class = class;
      return d;
}

void decl_print(struct decl* d, int bitLength) {
	switch(d->class){
		case AST_DECL_VAR:
			printf("decl ");
			if(d->expandFlag == EXPAND_TRUE){
				id_print(d->id, bitLength);
			}else{
				printf("%s", d->id);
			}
			printf(";\n");	
			break;
		case AST_DECL_FX:
			break;
		default:
			break;
	}
}

void decls_print(GList* decls, int bitLength) {
	//iterate through GList
	GList* node;
	node = g_list_first(decls);
	while(node){
		decl_print(node->data, bitLength);
		node = g_list_next(node);
	}
}

void decl_destroy(struct decl* d) {
      if (!d) return;
	  //free(d->id);	free id at stmts
      free(d);
}

void decls_destroy(GList* decls) {
      list_free_full(decls, (DestroyFunc)decl_destroy);
}

void id_print(char* id, int bitLength) {
		char** var = malloc(sizeof(char*)*(bitLength+1));
		char** argList = malloc(sizeof(char*));
		setHalfVarName(bitLength, var, argList, id);
		printf("%s", argList[0]);
		freeHalfVarName(bitLength, var, argList);
}

/*** Statements. ***/

static struct stmt* stmt_new(int class) {
      struct stmt* this = calloc(1, sizeof(struct stmt));
      this->class = class;
      return this;
}

struct stmt* stmt_exp_new(struct exp* exp) {
      struct stmt* this = stmt_new(AST_STMT_EXP);
      this->exp = exp;
      return this;
}

struct stmt* stmt_if_new(struct exp* cond, GList* then_block, GList* else_block) {
      struct stmt* this = stmt_new(AST_STMT_IF);
      this->exp = cond;
      this->block1 = then_block;
      this->block2 = else_block;
      return this;
}

struct stmt* stmt_while_new(struct exp* cond, GList* block) {
      struct stmt* this = stmt_new(AST_STMT_WHILE);
      this->exp = cond;
      this->block1 = block;
      return this;
}

struct stmt* stmt_assign_new(struct exp* left, struct exp* right) {
      struct stmt* this = stmt_new(AST_STMT_ASSIGN);
      this->left = left;
      this->right = right;
      return this;
}

struct stmt* stmt_goto_new(char* id) {
      struct stmt* this = stmt_new(AST_STMT_GOTO);
      this->left = exp_id_new(id, EXPAND_FALSE);
      return this;
}

struct stmt* stmt_return_new(struct exp* exp) {
      struct stmt* this = stmt_new(AST_STMT_RETURN);
      this->exp = exp;
      return this;
}

void stmt_print(struct stmt* stmt, int bitLength) {
	if(stmt->label){
		printf("%s: ", stmt->label);
	}
      assert(stmt);
      switch (stmt->class) {
            case AST_STMT_EXP:
                  exp_print(stmt->exp, bitLength);
				  printf(";\n");
                  break;
            case AST_STMT_ASSIGN:
                  exp_print(stmt->left, bitLength);
                  printf(" := ");
                  exp_print(stmt->right, bitLength);
				  printf(";\n");
                  break;
			case AST_STMT_IF:{
				struct exp* expTemp = exp_id_new(strdup("returnTemp"), EXPAND_FALSE);
				struct stmt* stmtTemp = stmt_assign_new(expTemp, stmt->exp);
				stmt_print(stmtTemp, bitLength);
				printf("if (");
				exp_print(expTemp, bitLength);
				printf(") then\n");
				stmts_print(stmt->block1, bitLength);
				if(stmt->block2){
					printf("else \n");
					stmts_print(stmt->block2, bitLength);
				}
				printf("fi\n");
				exp_destroy(expTemp);
				free(stmtTemp);
				break;
				}
			case AST_STMT_WHILE:{
				struct exp* expTemp = exp_id_new(strdup("returnTemp"), EXPAND_FALSE);
				struct stmt* stmtTemp = stmt_assign_new(expTemp, stmt->exp);
				stmt_print(stmtTemp, bitLength);
				printf("while (");
				exp_print(expTemp, bitLength);
				printf(") do\n");
				stmts_print(stmt->block1, bitLength);
				stmt_print(stmtTemp, bitLength);
				printf("od\n");
				//custom free fxs
				exp_destroy(expTemp);
				free(stmtTemp);
				break;
				}
			case AST_STMT_GOTO:
				printf("goto ");
				exp_print(stmt->left, bitLength);
				printf(";\n");
				break;
/*
            case AST_STMT_FOR:
                  printf("for ");
                  exp_print(stmt->left);
                  printf(" ");
                  exp_print(stmt->exp);
                  printf(" ");
                  exp_print(stmt->right);
                  stmts_print(stmt->block1);
                  break;

            case AST_STMT_RETURN:
                  printf("return");
                  if (stmt->exp) {
                        printf(" ");
                        exp_print(stmt->exp);
                  }
                  break;*/
      }
}

void stmts_print(GList* stmts, int bitLength) {
	//iterate through GList
	GList* node;
	node = g_list_first(stmts);
	while(node){
		stmt_print(node->data, bitLength);
		node = g_list_next(node);
	}
}

void stmt_destroy(struct stmt* stmt) {
      if (!stmt) return;
	  if(stmt->label) free(stmt->label);
      exp_destroy(stmt->left);
      exp_destroy(stmt->exp);
      exp_destroy(stmt->right);
      stmts_destroy(stmt->block1);
      stmts_destroy(stmt->block2);
      free(stmt);
}

void stmts_destroy(GList* stmts) {
      list_free_full(stmts, (DestroyFunc)stmt_destroy);
}

/*** Expressions. ***/

static struct exp* exp_new(int class) {
      struct exp* this = calloc(1, sizeof(struct exp));
      this->class = class;
      return this;
}

struct exp* exp_binop_new(int class, struct exp* left, struct exp* right) {
      struct exp* this = exp_new(class);
      this->left = left;
      this->right = right;
      return this;
}

struct exp* exp_num_new(int num, int expandFlag) {
      struct exp* this = exp_new(AST_EXP_NUM);
      this->num = num;
      this->expandFlag = expandFlag;
      return this;
}

struct exp* exp_id_new(char* id, int expandFlag) {
      struct exp* this = exp_new(AST_EXP_ID);
      this->id = id;
      this->expandFlag = expandFlag;
      return this;
}

void binop_print(const char* op, struct exp* left, struct exp* right, int bitLength) {
		//needed: turn operator to fx call
		printf("%s", op);
		printf("(");
		exp_print(left, bitLength);
		printf(",");
		exp_print(right, bitLength);
		printf(")");
}

void exp_print(struct exp* exp, int bitLength) {
      if (!exp) return;
      switch (exp->class) {
			case AST_EXP_NUM:
				if(exp->expandFlag == EXPAND_FALSE){
					printf("%d", exp->num);
				}else{
					char* tempChar;
					tempChar = int2bin(bitLength, exp->num);
					printf("%s", tempChar);
					free(tempChar);
				}
				break;
			case AST_EXP_ID:
				if(exp->expandFlag == EXPAND_FALSE){
					printf("%s", exp->id);
				}else{
					id_print(exp->id, bitLength);
				}
				break;
            case AST_EXP_PLUS:
                  binop_print("plus", exp->left, exp->right, bitLength);
                  break;
			case AST_EXP_MINUS:
                  binop_print("minus", exp->left, exp->right, bitLength);
                  break;
			case AST_EXP_OR:
			  binop_print("or", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_AND:
                  binop_print("and", exp->left, exp->right, bitLength);
                  break;
			case AST_EXP_XOR:
                  binop_print("xor", exp->left, exp->right, bitLength);
                  break;
            
            case AST_EXP_LT:
                  binop_print("isLT", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_LT_EQ:
                  binop_print("isLTEQ", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_GT:
                  binop_print("isGT", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_GT_EQ:
                  binop_print("isGTEQ", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_EQ:
                  binop_print("isEqual", exp->left, exp->right, bitLength);
                  break;
            case AST_EXP_NOT_EQ:
                  binop_print("isNotEqual", exp->left, exp->right, bitLength);
                  break;
			case AST_EXP_LSHIFT:
                  binop_print("lShift", exp->left, exp->right, bitLength);
                  break;
			case AST_EXP_RSHIFT:
                  binop_print("rShift", exp->left, exp->right, bitLength);
                  break;
            /*
			case AST_EXP_NOT:
                  printf("!"); 
				  type_print_pretty_with_colon(exp->type);
				  exp_print(exp->right);
                  break;
				  case AST_EXP_MINUS:
                  binop_print("-", exp->type, exp->left, exp->right);
                  break;
            case AST_EXP_DIV:
                  binop_print("/", exp->type, exp->left, exp->right);
                  break;
            case AST_EXP_MOD:
                  binop_print("%", exp->type, exp->left, exp->right);
                  break;
            case AST_EXP_MUL:
                  binop_print("*", exp->type, exp->left, exp->right);
                  break;
            case AST_EXP_TRUE:
                  printf("true");
                  break;
            case AST_EXP_FALSE:
                  printf("false");
                  break;
            case AST_EXP_NIL:
                  printf("nil");
                  break;
            case AST_EXP_STR:
                  printf("str");
				  printf("%s", exp->str);
                  break;
            

            case AST_EXP_STRUCT_LIT:
                  printf("struct-lit");
                  field_inits_print(exp->params);
                  break;

            case AST_EXP_ARRAY_LIT:
                  printf("array-lit");
                  exps_print(exp->params);
                  break;

            case AST_EXP_FUN_CALL:
                  printf("fun-call");
                  id_print(exp->id);
                  printf(" ");
                  exps_print(exp->params);
                  break;

            case AST_EXP_ARRAY_INDEX:
                  printf("array-idx");
                  exp_print(exp->left);
                  printf(" ");
                  exp_print(exp->right);
                  break;
            case AST_EXP_FIELD_LOOKUP:
                  printf("field-lkup");
                  exp_print(exp->left);
                  printf(" ");
                  id_print(exp->id);*/
      }
}

void exps_print(GList* exps, int bitLength) {
      //iterate through GList
	GList* node;
	node = g_list_first(exps);
	while(node){
		exp_print(node->data, bitLength);
		node = g_list_next(node);
	}
}

void exp_destroy(struct exp* exp) {
      if (!exp) return;

      if (exp->str) free(exp->str);
      if (exp->id) free(exp->id);
      exp_destroy(exp->left);
      exp_destroy(exp->right);
      
      free(exp);
}

void exps_destroy(GList* exps) {
      list_free_full(exps, (DestroyFunc)exp_destroy);
}

/*** Bonus list manipulation functions. ***/

// Defined in later versions of glib.
void list_free_full(GList* list, DestroyFunc destroy) {
      assert(destroy);
      list = g_list_first(list);
      g_list_foreach(list, (GFunc)destroy, NULL);
      g_list_free(list);
}

