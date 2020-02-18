#ifndef lexer
#define lexer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

union number{
	float f;
	int i;
};

typedef struct symbols {
	char *tokenName;
	unsigned int lineNum;
	char lexeme[100];
	union number val;
}tokenInfo;

int line_num = 1;

#endif
char * hasher(char * id);
tokenInfo* getnexttoken(FILE *fp);
//tokenInfo lexing(FILE * fp);
