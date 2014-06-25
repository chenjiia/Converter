#include "lexer.h" // yyin, yylex, etc.
#include "parser.h" // yyparse, yylval, token enum, etc.
#include "fxGenPre.h" // yyparse, yylval, token enum, etc.

#include <stdlib.h>

extern int yyparse(struct innerProgram* innerProgram1);
extern FILE *yyin;

//reference: tiger code ch3
void parse(char* fname, int bitLength){
	//set a struct and send into yyparse
	struct innerProgram* innerProgram1 = calloc(1, sizeof(struct innerProgram));
	innerProgram1->bitLength = bitLength;
	
	yyin = fopen(fname,"r");
	if (!yyin){
		fprintf(stderr,"can't open file\n"); 
		exit(1);
	}
	//yyparse(innerProgram1);
	
	if (yyparse(innerProgram1) == 0) /* parsing worked */
		fprintf(stderr,"Parsing successful!\n");
	else fprintf(stderr,"Parsing failed\n");
}

int main(int argc, char **argv) {
	if (argc!=3){
		fprintf(stderr,"usage: a.out filename bitlength\n"); 
		exit(1);
	}
	int bitLength = atoi(argv[2]);
	parse(argv[1], bitLength);
	
	return 0;
}