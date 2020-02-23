#include <stdio.h>
#include <stdlib.h>
#include "lexer1.h"

typedef struct unit {
    char* term;//ntot
    struct unit *next;
    int terminal;
    int count;
} unit;

char buffer[MAX_BUFFER_SIZE]; // the input buffer
int bufferPosition; // indicates the current character to be read from the buffer
int isNT = 0;
int arraySize = 50;
unit** grammararray;
unit** firstarray;
unit** followarray;

// int strcmp(const char *X, const char *Y){
//   while (*X) {
//     if (*X != *Y)
//     break;
//     X++;
//     Y++;
//   }
// 	return *(const unsigned char*)X - *(const unsigned char*)Y;
// }

void showfirstfollow (unit *head){
  unit *ptr = head;
  char* str = head->term;
  printf(" of %s -> ",ptr -> term);
  ptr = ptr -> next;
  while(ptr -> next){
      printf(" %s ",ptr -> term);
      ptr = ptr -> next;
      str = ptr -> term;
  }
  printf(" %s;\n\n",ptr -> term);
}

void showfollow(){
  char* prevterm="";
  printf("List of Follow Set: \n\n");
  for(int i = 0; i<arraySize; i++){
    if(strcmp(prevterm,followarray[i]->term)==0){
      continue;
    }
    printf("Follow ");
    showfirstfollow(followarray[i]);
    prevterm = followarray[i]->term;
  }
}

void showgrammar(){
  char* prevterm="";
  printf("Grammar: \n\n");
  for(int i = 0; i<arraySize; i++){
    if(strcmp(prevterm,grammararray[i]->term)==0){
      continue;
    }
    printf("Definition ");
    showfirstfollow(grammararray[i]);
    prevterm = grammararray[i]->term;
  }
}

void showfirst(){
  char* prevterm="";
  printf("List of First Set: \n\n");
  for(int i = 0; i<arraySize; i++){
    if(strcmp(prevterm,firstarray[i]->term)==0){
      continue;
    }
    printf("First ");
    showfirstfollow(firstarray[i]);
    prevterm = firstarray[i]->term;
  }
}

void showlist (unit *head){
  printf("showlist of %s",head->term);
    unit *ptr = head;
    while(ptr -> next){
        printf("term:%s\nterminal: %u \ncount:%u\n\n",ptr -> term, ptr -> terminal,ptr ->count);
        ptr = ptr -> next;
    }
    printf("term:%s\nterminal: %u \ncount:%u\n\n\n",ptr -> term, ptr -> terminal,ptr ->count);
}

char getnextcharacter(FILE *fp){
  if(bufferSize == -1 || bufferPosition == bufferSize){// first call to getCharacter or end of buffer has been reached
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
  unit *new = calloc(1,sizeof(unit));
  unit *ptr = head;
  new -> term = value1;
  new -> terminal = is;
  new -> next = NULL;
  while (ptr -> next){
    ptr = ptr -> next;
  }
  ptr -> next = new;
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
        char *ret = (char *)calloc(count+1,sizeof(char));
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
        char *ret = (char *)calloc((count+1),sizeof(char));
        int i = 0;
        while(i < count + 1){
          ret[i] = str[i];
          i++;
        }
        ret[count + 1] = '\0';
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
  int counter = 0;
	do{
    char* nextterm = getnextterm(fp);
    if (nextterm != NULL){
      addunit(head, nextterm, isNT);
      counter++;
    }
    bufferPosition--;
    next = getnextcharacter(fp);
	} while( next != '\n' && next != 26);
  head->count = counter;
}

unit** initializearray(unit** array){
  array = (unit **)calloc(arraySize,sizeof(unit));
  for(int i = 0; i < arraySize; i++){
    array[i] = calloc(1,sizeof(unit));
  }
  return array;
}

unit** resizearray(unit** array){
  arraySize = arraySize + 10;
  array = (unit**)realloc(array, arraySize*sizeof(unit));
  for(int i = arraySize - 10; i < arraySize; i++){
    array[i] = calloc(1, sizeof(unit));
  }
  return array;
}

void getgrammar(){
	  FILE* fp = fopen("testcase.txt", "r");
    grammararray=initializearray(grammararray);
    char next;
    int index = 0;
    do {
      if(index == arraySize){
        grammararray=resizearray(grammararray);
      }
      getnextrule(fp, grammararray[index]);
      next = getnextcharacter(fp);
      //showlist(grammararray[index]);
      index++;
  	} while( next != 26 );
    int i = 0;
    while(grammararray[i]->term != NULL){
      i++;
    }
    arraySize = i;
}
