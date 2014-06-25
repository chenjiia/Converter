%code top {

#include "frontend.h"
#include "ast.h"
#include <glib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

extern int yylex(void);
extern int yyerror(int *, const char*);

}

%define parse.error verbose

%code requires {

#include "ast.h"
#include "fxGenPre.h"
#include <glib.h>

GList* stmtList;
}

%union {
      char* id;
      char* str;
      int num;
	  
	  struct decl* decl;
	  struct exp* exp;
	  struct stmt* stmt;
	  struct field_init* fieldinit;
	  
	  GList* list;
};

/* Ids could be types or exps. */
%token <id> T_ID
%token <str> T_STR
%token <num> T_NUM

%type <decl> var_decl
%type <list> var_decls stmts block
%type <exp> exp
%type <stmt> stmt

%token T_LT_EQ "<="
%token T_GT_EQ ">="
%token T_EQ "=="
%token T_NOT_EQ "!="
%token T_LSHIFT "<<"
%token T_RSHIFT ">>"

%token T_VAR T_TYPE T_FUNCTION
      T_FOR T_TO T_WHILE T_IF T_ELSE T_RETURN T_GOTO
      T_NIL T_TRUE T_FALSE
      T_INT T_BOOL
      T_UNKNOWN

%left '|'
%left '^'
%left '&'
%left "==" "!="
%left '<' '>' "<=" ">="
%left "<<" ">>"
%left '+' '-'
%left '*' '/' '%'
%left T_UMINUS T_UPLUS '!'

%parse-param {int *bitLength}

%start program

%%

program:
	//todo: get stmt here and working
      var_decls stmts{
			//append current stmt list to stmts from decl
			$2 = g_list_concat(stmtList, $2);
            done_parsing($1, $2);
			//decls_print($1);
      }

var_decls: 
	  %empty {
		$$ = g_list_append(NULL, decl_var_new(strdup("returnTemp"), EXPAND_FALSE));
		stmtList = g_list_append(stmtList, stmt_assign_new(exp_id_new(strdup("returnTemp"), EXPAND_FALSE), exp_num_new(0, EXPAND_FALSE)));
	   }
      | var_decls var_decl {
		$$ = g_list_append($1, $2);
	  }

var_decl: 
      T_VAR T_ID ';' {
		//init to zero if not inited in decl
		//$2 is from strndup
		stmtList = g_list_append(stmtList, stmt_assign_new(exp_id_new($2, EXPAND_TRUE), exp_num_new(0, EXPAND_TRUE)));
		$$ = decl_var_new($2, EXPAND_TRUE);
	  }
      | T_VAR T_ID '='  exp ';' {
		stmtList = g_list_append(stmtList, stmt_assign_new(exp_id_new($2, EXPAND_TRUE), $4));
		//stmts_print(stmtList, *bitLength);
		$$ = decl_var_new($2, EXPAND_TRUE);
	  }

stmts: 
	  %empty {
		$$ = NULL;
	  }
      | stmts stmt  {
		$$ = g_list_append($1, $2);
	  }
	  
stmt: 
	  T_ID ':' stmt{
	    $$ = $3;
		$$->label = $1;
	  }
      | exp ';' {
		$$ = stmt_exp_new($1);
	  }
      | T_ID '=' exp ';' {
		$$ = stmt_assign_new(exp_id_new($1, EXPAND_TRUE), $3);
	  }
      | T_IF '(' exp ')' block T_ELSE block {
		$$ = stmt_if_new($3, $5, $7);
	  }
      | T_IF '(' exp ')' block {
		$$ = stmt_if_new($3, $5, NULL);
	  }
      | T_WHILE '(' exp ')' block {
		$$ = stmt_while_new($3, $5);
	  }
	  | T_GOTO T_ID ';' {
		$$ = stmt_goto_new($2);
	  }
	  /*
      | T_FOR '(' lvalue '=' exp T_TO exp ')' block {
		$$ = stmt_for_new($3, $5, $7, $9);
	  }
      | T_RETURN '(' exp ')' ';' {
		$$ = stmt_return_new($3);
	  }
      | T_RETURN ';' {
		$$ = stmt_return_new(NULL);
	  }*/

block: 
      '{' stmts '}' {
		$$ = $2;
	  }
	  
exp:
	//todo: implement xor
	 T_NUM {
		$$ = exp_num_new($1, EXPAND_TRUE);
	  }
	  |'(' exp ')' {
		$$ = $2;
	  }
	  |	T_ID {
		$$ = exp_id_new($1, EXPAND_TRUE);
	  }
	  | exp '+' exp {
		$$ = exp_binop_new(AST_EXP_PLUS, $1, $3);
	  }
	  | exp '^' exp {
		$$ = exp_binop_new(AST_EXP_XOR, $1, $3);
	  }
	  | exp '-' exp {
		$$ = exp_binop_new(AST_EXP_MINUS, $1, $3);
	  }
	  | exp '|' exp {
		$$ = exp_binop_new(AST_EXP_OR, $1, $3);
	  }
      | exp '&' exp {
		$$ = exp_binop_new(AST_EXP_AND, $1, $3);
	  }
	  | exp "<<" exp {
		$$ = exp_binop_new(AST_EXP_LSHIFT, $1, $3);
	  }
	  | exp ">>" exp {
		$$ = exp_binop_new(AST_EXP_RSHIFT, $1, $3);
	  }
      | exp '<' exp {
		$$ = exp_binop_new(AST_EXP_LT, $1, $3);
	  }
      | exp "<=" exp {
		$$ = exp_binop_new(AST_EXP_LT_EQ, $1, $3);
	  }
      | exp '>' exp {
		$$ = exp_binop_new(AST_EXP_GT, $1, $3);
	  }
      | exp ">=" exp {
		$$ = exp_binop_new(AST_EXP_GT_EQ, $1, $3);
	  }
      | exp "==" exp {
		$$ = exp_binop_new(AST_EXP_EQ, $1, $3);
	  }
      | exp "!=" exp {
		$$ = exp_binop_new(AST_EXP_NOT_EQ, $1, $3);
	  }
	  

%%

int yyerror(int *bitLength, const char *p) { 
      fprintf(stderr, "Error: %s\n", p);
      return 0;
}

