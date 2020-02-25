#include "lexer.h"
#include "hasher.h"

#define MAX_BUFFER_SIZE 256

char buffer1[MAX_BUFFER_SIZE]; // the input buffer
int bufferPosition1; // indicates the current character to be read from the buffer
int bufferSize1 = -1; // the number of characters stored in the buffer (-1 indicates first use)
char buffer2[100];

char *strcpy(char *destination, char *source)
{
    char *start = destination;

    while(*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0'; // add '\0' at the end
    return start;
}
char getCharacter(FILE *fp) {

	if(bufferSize1 == -1 || bufferPosition1 == bufferSize1) {
        // first call to getCharacter or end of buffer has been reached
        bufferSize1 = fread(buffer1, sizeof(char), (size_t)MAX_BUFFER_SIZE, fp);
				//printf("\n buffer size=%lu\n",(size_t)MAX_BUFFER_SIZE);
        bufferPosition1 = 1;
        if(bufferSize1 == 0)
            return 26; // eof
        else
            return buffer1[0];
    }

    if(bufferSize1 == 0) // eof has been reached
        return 26;
    else
        return buffer1[bufferPosition1++];
}

tokenInfo* getnexttoken(FILE *fp,tokenInfo* temp){
    int state = 0;
    int idcount = 0;
    char nextChar;
    unsigned count = 0;
		for(int c=0;c<100;c++){buffer2[c]='\0';}

	while(1){
		nextChar = getCharacter(fp);
		buffer2[count++] = nextChar;
		temp -> lineNum = line_num;
		switch(state){
			case 0:
			switch (nextChar){
				case ' ':
				case '\t':
				case '\r':
				count=0;
				break;

				case ';':
				temp -> tokenName = "SEMICOL";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ':':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "ASSIGNOP";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					bufferPosition1--;//retracting

					temp -> tokenName = "COLON";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case ',':
				temp -> tokenName = "COMMA";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '[':
				temp -> tokenName = "SQBO";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ']':
				temp -> tokenName = "SQBC";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '(':
				temp -> tokenName = "BO";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case ')':
				temp -> tokenName = "BC";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '+':
				temp -> tokenName = "PLUS";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '-':
				temp -> tokenName = "MINUS";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '/':
				temp -> tokenName = "DIV";
				strcpy(temp->lexeme,buffer2);
				return temp;

				case '*':
				nextChar = getCharacter(fp);
				int commentline = line_num;
				buffer2[count++] = nextChar;
				if (nextChar == '*'){
					int starCount = 0;
					buffer2[count-1]='\0';
					buffer2[count-2]='\0';
					int i = 1;
					while(i){
						//printf("stuck %c %s\n",nextChar,temp -> lexeme);
						nextChar = getCharacter(fp);
						switch (nextChar){
							case '*':
							starCount++;
							if (starCount == 2){
								//temp -> lineNum = line_num; // yaha kuch changes karna hai.......
								i = 0;
							}
							count = 0;
							break;

							case '\n':
							line_num++;
							starCount = 0;
							break;

							default:
							if (nextChar == 26){
								printf("Comment starting on line %u not finished.\n",commentline);
								i=0;
							}
							starCount = 0;
							break;
						}
					}
				}
				else{
					bufferPosition1--;
					temp -> tokenName = "MUL";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '=':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "EQ";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					bufferPosition1--;
					state=11;
				}
				break;

				case '!':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					buffer2[count++] = nextChar;
					temp -> tokenName = "NE";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				else{
					state=11;
					bufferPosition1--;
				}
				break;

				case '.':
				nextChar = getCharacter(fp);
				if (nextChar == '.'){
					buffer2[count++] = nextChar;
					temp -> tokenName = "RANGEOP";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}else{
					bufferPosition1--;
					state=11;
				}
				break;


				case '<':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					buffer2[count++] = nextChar;
					temp -> tokenName = "LE";
					strcpy(temp->lexeme,buffer2);
					return temp;

					case '<':
					buffer2[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '<'){
						buffer2[count++] = nextChar;
						temp -> tokenName = "DRIVERDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}
					else{
						bufferPosition1--;
						temp -> tokenName = "DEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}

					default:
					bufferPosition1--;
					temp -> tokenName = "LT";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '>':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					buffer2[count++] = nextChar;
					temp -> tokenName = "GE";
					strcpy(temp->lexeme,buffer2);
					return temp;

					case '>':
					buffer2[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '>'){
						buffer2[count++] = nextChar;
						temp -> tokenName = "DRIVERENDDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}
					else{
						bufferPosition1--;
						temp -> tokenName = "ENDDEF";
						strcpy(temp->lexeme,buffer2);
						return temp;
					}

					default:
					bufferPosition1--;
					temp -> tokenName = "GT";
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
				break;

				case '\n':
				line_num++;
				count--;
				temp -> lineNum = line_num;
				break;

				case '0'...'9':
				state = 5;
				break;

				case 'a'...'z':
				case 'A'...'Z':
				state = 1;
				break;

				default:
				if(nextChar != 26){
					printf("Character not allowed: %c\n",nextChar);
					count--;
				}
				break;
			}
			break;

			case 5:
				switch(nextChar){
					case '0'...'9':
					state = 5;
					break;

					case '.':
					state = 6;
					break;

					default:
					bufferPosition1--;
					temp -> tokenName = "NUM";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
				}
			break;

			case 6:
			switch(nextChar){
				case '0'...'9':
				state = 7;
				break;

				case '.':
				bufferPosition1--;
				bufferPosition1--;
				temp -> tokenName = "NUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;

			  default:
				printf("stray '.' on line: %u\n",line_num);
				bufferPosition1--;
				temp -> tokenName = "NUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;

			}
			break;

			case 7:
			switch(nextChar){
				case '0'...'9':
					state = 7;
			  	break;

				case 'E':
				case 'e':
					state = 8;
				break;

				default:
					bufferPosition1--;
					temp->tokenName = "RNUM";
					buffer2[count-1] = '\0';
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 8:
			switch(nextChar){
				case '+':
				case '-':
					state = 9;
				break;

				case '0'...'9':
					state = 10;
				break;

				default:
				bufferPosition1--;
				bufferPosition1--;
				temp -> tokenName = "RNUM";
				buffer2[count-1] = '\0';
				buffer2[count-2] = '\0';
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			break;

			case 9:
			switch(nextChar){
				case '0'...'9':
					state = 10;
				break;
			}
			break;

			case 10:
			switch(nextChar){
				case '0'...'9':
					state = 10;
				break;

				default:
					bufferPosition1--;
					buffer2[count-1] = '\0';
					temp->tokenName ="RNUM";
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 11:
			printf("Lexical Error on line: %u lexeme:'%s'\n",line_num,buffer2);
			count=0;
			state=0;
			break;

			case 1:
			switch(nextChar){
				case 'a'...'z':
				case 'A'...'Z':
				case '0'...'9':
				case '_':
				state = 2;
				break;

				default:
				//printf("yaha");
					bufferPosition1--;
					temp -> tokenName = "ID";
					buffer2[count-1] = '\0';
					char* token = searchInHASH(buffer2);
					if(token != NULL){
						temp -> tokenName = token;
					}
					strcpy(temp->lexeme,buffer2);
					return temp;
			}
			break;

			case 2:
			if(idcount==18){
				temp->tokenName = "ID";
				bufferPosition1--;
				idcount =0;
				buffer2[count-1] = '\0';
				char* token = searchInHASH(buffer2);
				if(token != NULL){
					temp -> tokenName = token;
				}
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			switch(nextChar){
				case 'a'...'z':
				case 'A'...'Z':
				case '0'...'9':
				case '_':
				idcount++;
				state = 2;
				break;

				default:
				bufferPosition1--;
				temp -> tokenName = "ID";
				buffer2[count-1] = '\0';
				char* token = searchInHASH(buffer2);
				if(token != NULL){
					temp -> tokenName = token;
				}
				strcpy(temp->lexeme,buffer2);
				return temp;
			}
			break;
		}
		if (nextChar==26){
			buffer2[0] = (char)(26);
			temp -> tokenName = "EOF";
			temp -> lineNum = line_num;
			strcpy(temp->lexeme,buffer2);
			return temp;
		}
	}
}

void printToken(tokenInfo* t) {
    printf("%u %s lexeme: %s\n", t -> lineNum, t -> tokenName, t->lexeme);
}


// int main(){
// 	createHASH();
// 	FILE* fp = fopen("testcase.txt","r");
// 	tokenInfo* temp1 = (tokenInfo*)calloc(1,sizeof(struct symbols));
// 	do {
// 		getnexttoken(fp,temp1);
// 		printToken(temp1);
// 	} while(temp1 -> tokenName != "EOF");
// 	free(temp1);
// }
