#include "lexer.h"

typedef struct node{
    char* keyword;
    char* token;
    struct node *next;
} node;

node* HASH[26];

int strcmp(const char *X, const char *Y){
  while (*X) {
    if (*X != *Y)
    break;
    X++;
    Y++;
  }

	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

void addnode (node *head, char* value1, char *value2) {
    node *new = malloc(sizeof(node)), *ptr = head;
    new -> keyword = value1;
    new -> token = value2;

    new -> next = NULL;
    while (ptr -> next) ptr = ptr -> next;
    ptr -> next = new;
}

void showlist (node *head) {
  node *ptr = head;

  while (ptr -> next) {
      printf("%s %s\n",ptr -> keyword, ptr -> token);
      ptr = ptr -> next;
  }

  printf ("%s %s\n", ptr -> keyword, ptr -> token);
}

char* searchInHASH(char *str){
  int index = (int) str[0];
  if (index > 96){
    index = index - 97;
  }
  else if (index == 65){
          index = 0;
  }
  else if (index == 79){
    index = 14;
  }
  else return NULL;

  node *ptr = HASH[index];
  if(ptr -> keyword == NULL){
     return NULL;
  }

  while (ptr -> next) {
    if(strcmp(ptr -> keyword, str) == 0){
      return ptr -> token;
    }
    ptr = ptr -> next;
  }

  if(strcmp(ptr -> keyword, str) == 0){
    return ptr -> token;
  }
  else{
    return NULL;
  }

}

void addKeyToken(char *keyword,char* token){
  int index = (int) keyword[0];

  if (index > 96){
    index = index - 97;
  }
  else if (index == 65){
    index = 0;
  }
  else if (index == 79){
    index = 14;
  }else return;

  node *ptr = HASH[index];

  if(ptr -> keyword == NULL){
    HASH[index] -> keyword = keyword;
    HASH[index] -> token = token;
  }
  else{
    addnode(HASH[index], keyword, token);
  }
}

void createHASH(){
  for(int i = 0; i < 26; i++){
    HASH[i] = malloc(sizeof(node));
  }
  addKeyToken("AND", "AND");
  addKeyToken("array", "ARRAY");
  addKeyToken("break", "BREAK");
  addKeyToken("case", "CASE");
  addKeyToken("declare", "DECLARE");
  addKeyToken("default", "DEFAULT");
  addKeyToken("driver", "DRIVER");
  addKeyToken("end", "END");
  addKeyToken("false", "FALSE");
  addKeyToken("for", "FOR");
  addKeyToken("get_value", "GET_VALUE");
  addKeyToken("input", "INPUT");
  addKeyToken("integer", "INTEGER");
  addKeyToken("in", "IN");
  addKeyToken("module", "MODULE");
  addKeyToken("OR", "OR");
  addKeyToken("of", "OF");
  addKeyToken("parameters", "PARAMETERS");
  addKeyToken("program", "PROGRAM");
  addKeyToken("print", "PRINT");
  addKeyToken("real", "REAL");
  addKeyToken("returns", "RETURNS");
  addKeyToken("start","START");
  addKeyToken("switch", "SWITCH");
  addKeyToken("true", "TRUE");
  addKeyToken("takes", "TAKES");
  addKeyToken("use","USE");
  addKeyToken("with","WITH");
  addKeyToken("while", "WHILE");
}
