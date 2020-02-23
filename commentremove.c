#include "lexer1.h"

void commentremove(FILE *fp){
  int starcount = 0;
  char nextChar;
  int state = 0;
  while(1){
		nextChar = getCharacter(fp);
    switch (state){
      case 0:
      switch(nextChar){
        case '*':
        state = 1;
        break;

        case 26:
        return;

        default:
        state = 0;
        printf("%c",nextChar);
        break;
      }//end inner switch
      break;

      case 1://something*
      switch(nextChar){
        case '*':
        state = 2;
        break;

        case 26:
        printf("*");
        return;

        default:
        printf("*%c",nextChar);
        state = 0;
        break;
      }//end inner switch
      break;

      case 2://something**something
      switch(nextChar){
        case '*':
        state = 3;
        break;

        case 26:
        return;

        default:
        if (nextChar=='\n'){
          printf("%c",nextChar);
        }
        state = 2;
        break;
      }//end inner switch
      break;

      case 3://something**something*
      switch(nextChar){
        case '*':
        state = 0;
        break;

        case 26:
        return;

        default:
        state = 2;
        break;
      }//end inner switch
      break;
    }//end outer switch

  }printf("seriosly?\n");
}



int main(){
	FILE* fp = fopen("t1.txt","r");
	commentremove(fp);
}
