#include "lexer.h"
#include "hasher.h"

#define MAX_BUFFER_SIZE 1024

char buffer[MAX_BUFFER_SIZE]; // the input buffer
int bufferPosition; // indicates the current character to be read from the buffer
int bufferSize = -1; // the number of characters stored in the buffer (-1 indicates first use)

char getCharacter(FILE *fp) {

	if(bufferSize == -1 || bufferPosition == bufferSize) {
        // first call to getCharacter or end of buffer has been reached
        bufferSize = fread(buffer, sizeof(char), (size_t)MAX_BUFFER_SIZE, fp);
        bufferPosition = 1;
        if(bufferSize == 0)
            return 26; // eof
        else
            return buffer[0];
    }

    if(bufferSize == 0) // eof has been reached
        return 26;
    else
        return buffer[bufferPosition++];
}

tokenInfo* getnexttoken(FILE *fp){
    int state = 0;
    int idcount = 0;
    char nextChar;
    unsigned count = 0;
	tokenInfo* temp =(tokenInfo*)malloc(sizeof(tokenInfo));

	while(1){
		nextChar = getCharacter(fp);
		temp -> lexeme[count++] = nextChar;
		temp -> lineNum = line_num;
		switch(state){
			case 0:
			switch (nextChar){
				case ' ':
				case '\t':
				case '\r':
				count--;
				break;

				case ';':
				temp -> tokenName = "SEMICOL";
				return temp;

				case ':':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "ASSIGNOP";
					return temp;
				}
				else{
					bufferPosition--;//retracting
					temp -> tokenName = "COLON";
					return temp;
				}
				break;

				case ',':
				temp -> tokenName = "COMMA";
				return temp;

				case '[':
				temp -> tokenName = "SQBO";
				return temp;

				case ']':
				temp -> tokenName = "SQBC";
				return temp;

				case '(':
				temp -> tokenName = "BO";
				return temp;

				case ')':
				temp -> tokenName = "BC";
				return temp;

				case '+':
				temp -> tokenName = "PLUS";
				return temp;

				case '-':
				temp -> tokenName = "MINUS";
				return temp;

				case '/':
				temp -> tokenName = "DIV";
				return temp;

				case '*':
				nextChar = getCharacter(fp);
				int commentline = line_num;
				temp -> lexeme[count++] = nextChar;
				if (nextChar == '*'){
					int starCount = 0;
					temp -> lexeme[count-1]='\0';
					temp -> lexeme[count-2]='\0';
					int i = 1;
					while(i){
						//printf("stuck %c %s\n",nextChar,temp -> lexeme);
						nextChar = getCharacter(fp);
						switch (nextChar){
							case '*':
							starCount++;
							if (starCount == 2){
								temp -> lineNum = line_num; // yaha kuch changes karna hai.......
								i = 0;
							}
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
					bufferPosition--;
					temp -> tokenName = "MUL";
					temp -> lexeme[count-1] = '\0';
					return temp;
				}
				break;

				case '=':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "EQ";
					return temp;
				}
				else{
					bufferPosition--;
					temp -> lexeme[count-1] = 'I';
					return temp;
				}

				case '!':
				nextChar = getCharacter(fp);
				if (nextChar == '='){
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "NE";
					return temp;
				}
				else{
					bufferPosition--;
					temp -> lexeme[count-1] = 'I';
					return temp;
				}

				case '.':
				nextChar = getCharacter(fp);
				if (nextChar == '.'){
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "RANGEOP";
					return temp;
				}
				else{
					bufferPosition--;
					temp -> lexeme[count-1] = 'I';
					return temp;
				}


				case '<':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "LE";
					return temp;

					case '<':
					temp -> lexeme[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '<'){
						temp -> lexeme[count++] = nextChar;
						temp -> tokenName = "DRIVERDEF";
						return temp;
					}
					else{
						bufferPosition--;
						temp -> tokenName = "DEF";
						return temp;
					}

					default:
					bufferPosition--;
					temp -> tokenName = "LT";
					return temp;
				}
				break;

				case '>':
				nextChar = getCharacter(fp);
				switch (nextChar){
					case '=':
					temp -> lexeme[count++] = nextChar;
					temp -> tokenName = "GE";
					return temp;

					case '>':
					temp -> lexeme[count++] = nextChar;
					nextChar = getCharacter(fp);
					if (nextChar == '>'){
						temp -> lexeme[count++] = nextChar;
						temp -> tokenName = "DRIVERENDDEF";
						return temp;
					}
					else{
						bufferPosition--;
						temp -> tokenName = "ENDDEF";
						return temp;
					}

					default:
					bufferPosition--;
					temp -> tokenName = "GT";
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
					bufferPosition--;
					temp -> tokenName = "NUM";
					temp -> lexeme[count-1] = '\0';
					return temp;
				}
			break;

			case 6:
			switch(nextChar){
				case '0'...'9':
					state = 7;
					break;

				case '.':
					bufferPosition--;
					bufferPosition--;
					temp -> tokenName = "NUM";
					temp -> lexeme[count-1] = '\0';
					temp -> lexeme[count-2] = '\0';
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
					bufferPosition--;
					temp->tokenName = "RNUM";
					temp -> lexeme[count-1] = '\0';
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
				bufferPosition--;
				bufferPosition--;
				temp -> tokenName = "RNUM";
				temp -> lexeme[count-1] = '\0';
				temp -> lexeme[count-2] = '\0';
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
					bufferPosition--;
					temp -> lexeme[count-1] = '\0';
					temp->tokenName ="RNUM";
					return temp;
			}
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
					bufferPosition--;
					temp -> tokenName = "ID";
					temp -> lexeme[count-1] = '\0';
					char* token = searchInHASH(temp -> lexeme);
					if(token != NULL){
						temp -> tokenName = token;
					}
					return temp;
			}
			break;

			case 2:
			if(idcount==18)
			{
				temp->tokenName = "ID";
				bufferPosition--;
				idcount =0;
				temp -> lexeme[count-1] = '\0';
				char* token = searchInHASH(temp -> lexeme);
				if(token != NULL){
					temp -> tokenName = token;
				}
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
				bufferPosition--;
				temp -> tokenName = "ID";
				temp -> lexeme[count-1] = '\0';
				char* token = searchInHASH(temp -> lexeme);
				if(token != NULL){
					temp -> tokenName = token;
				}
				return temp;
			}
			break;
		}
		if (nextChar==26){
			temp -> lexeme[0] = (char)(26);
			temp -> tokenName = "EOF";
			temp -> lineNum = line_num;
			return temp;
		}
	}
}

void printToken(tokenInfo* t) {
    printf("line %u: tokenName:%s lexeme:|||%s|||\n", t -> lineNum, t -> tokenName, t -> lexeme);
}


int main(){
	createHASH();
	FILE* fp = fopen("testcase.txt","r");
	tokenInfo* temp1 = (tokenInfo*)malloc(sizeof(struct symbols));
	do {
		temp1 = getnexttoken(fp);
		printToken(temp1);
	} while(temp1 -> tokenName != "EOF");
}
