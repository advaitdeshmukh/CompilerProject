#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1024

char buffer[MAX_BUFFER_SIZE]; // the input buffer
int bufferPosition; // indicates the current character to be read from the buffer
int bufferSize = -1; // the number of characters stored in the buffer (-1 indicates first use)
int isNT = 0;
typedef struct unit {
    char* term;
    struct unit *next;
    int terminal;
} unit;

unit* array[104];
char getnextcharacter(FILE *fp){
	if(bufferSize == -1 || bufferPosition == bufferSize){
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

void addunit(unit *head, char* value1, int is){
    if(head -> term == NULL){
        head -> term = value1;
        head-> terminal = is;
        return;
    }

    unit *new = malloc(sizeof(unit)), *ptr = head;
    new -> term = value1;
    new -> terminal = is;
    new -> next = NULL;
    while (ptr -> next) ptr = ptr -> next;
    ptr -> next = new;
}

void showlist (unit *head) {
    unit *ptr = head;
    while(ptr -> next){
        printf("%s %u \n", ptr -> term, ptr -> terminal);
        ptr = ptr -> next;
    }
    printf ("%s %u \n\n", ptr -> term, ptr -> terminal);
}

char* getnextterm(FILE *fp){
  char str[100];
  int count = 0;
  while(1){
    char nextChar = getnextcharacter(fp);
    isNT = 0;
    switch(nextChar){
      case '-':
      case '>':
      case '<':
      isNT = 1;
      case ' ':
      if (count){
        str[count] = '\0';
        char *ret = (char *)malloc(sizeof(char)*(count+1));
        int i = 0;
        while(i < count+1){
          ret[i] = str[i];
          i++;
        }
        ret[count+1] = '\0';
        return ret ;
      }
      break;

      case '\n':
      if (count){
        str[count] = '\0';
        char *ret = (char *)malloc(sizeof(char)*(count+1));
        int i = 0;
        while(i < count+1){
          ret[i] = str[i];
          i++;
        }
        ret[count+1] = '\0';
        return ret ;
      }
      case 26:
      return NULL;

      default:
      str[count] = nextChar;
      count++;
    }
  }
}

void getnextrule(FILE *fp, unit* head){
  char next;
	do {
    //buffer--;
    char* nextterm = getnextterm(fp);
    if (nextterm != NULL){
      addunit(head, nextterm, isNT);
    }

    bufferPosition--;
    next = getnextcharacter(fp);
		//showrule();
	} while( next != '\n' && next != 26);
}

int main(){
	  FILE* fp = fopen("grammar.txt", "r");
    char next;
    for(int i = 0; i < 104; i++){
      array[i] = malloc(sizeof(unit));
    }

    int index = 0;
    do {
      getnextrule(fp, array[index]);
      printf("line no : %u\n", index+1);
      showlist(array[index]);
      next = getnextcharacter(fp);
      index++;
  	} while( next != 26 && index < 104);
}
