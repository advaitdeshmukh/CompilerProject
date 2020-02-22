#include <stdio.h>
#include <stdlib.h>
#include "getgrammar.h"

unit** firstarray;
unit** followarray;
int isEpsilon = 0;

enum nonTerminals
  {program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, moduleDef, module, ret, input_plist, N1, output_plist, N2, dataType, type, statements, statement, ioStmt, boolConstt, var_id_num, var, whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, index, moduleReuseStmt, optional, idList, N3, U, new_NT, unary_op, arithmeticOrBooleanExpr, N7, AnyTerm, N8, expression, arithmeticExpr, N4, term, N5, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, Default, iterativeStmt, range_arrays, range};

enum Terminals
  {ID, NUM, RNUM, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, eps, $ };

int strcmp(const char *X, const char *Y){
  while (*X) {
    if (*X != *Y)
    break;
    X++;
    Y++;
  }
	return *(const unsigned char*)X - *(const unsigned char*)Y;
}

void addtoarray(unit* head, unit* nextunit){
  unit *ptr = head;
  if(ptr -> term == NULL){
    ptr -> term = nextunit -> term;
    ptr -> terminal = nextunit->terminal;
    ptr -> next = NULL;
    return;
  }
  do{
    if(ptr->next == NULL){
      break;
    }
    ptr = ptr -> next;

    if(strcmp(ptr -> term, nextunit->term) == 0)
    return;
  }while(ptr -> next);

  unit *new = malloc(sizeof(unit));
  new -> term = nextunit->term;
  new -> terminal = nextunit->terminal;
  new -> next = NULL;
  ptr -> next = new;
}

void mergelist(unit* list1,unit* list2){//list1 added to list2
    if(list1 == NULL){
      return;
    }
    if(list1->term == NULL){
      return;
    }
    unit* str = list1;
    do{
      addtoarray(list2,str);
      if(str->next ==NULL){
        break;
      }
      str = str->next;
    }while(str->term != NULL);
}

int canbeEpsilon(unit* ptr){
  if (strcmp("eps",ptr->term) == 0){
    return 1;
  }
  if(ptr->terminal == 0){
    return 0;
  }
  unit* new= calloc(1,sizeof(unit));
  for(int i=0;i<arraySize;i++){
      if(strcmp(grammararray[i] -> term,ptr->term) == 0){
      int counter = grammararray[i]->count -1;
      new = grammararray[i]->next;
      int j;
      for(j=0;j<counter;j++){
        if(!canbeEpsilon(new))
        break;
        new = new->next;
      }
      if(counter == j){
        return 1;
      }
    }
  }
  return 0;
}


unit* first(unit* input){
  unit* new= calloc(1,sizeof(unit));
  if(strcmp(input->term,"eps") == 0){
    new->term = "eps";
    new->terminal = 0;
    return new;
  }else if(input->terminal == 0){
    new->term = input->term;
    new->terminal = input->terminal;
    return new;
  }else{
    for(int j = 0; j < arraySize; j++){
      if(strcmp(grammararray[j] -> term,input -> term) == 0){
        unit* new2 = grammararray[j] -> next;
        int counter = grammararray[j]->count -1;
        for(int i=0;i<counter-1;i++){
          if(!canbeEpsilon(new2))
          break;

          mergelist(first(new2),new);
          new2 = new2->next;if(new2==NULL){break;}
        }
        mergelist(first(new2),new);
        }
      }
    }
    return new;
  }

unit* follow(unit* input){
  unit* new1= calloc(1,sizeof(unit));
  if(strcmp("program",input -> term) == 0){
    new1->term = "$";
  }
  for(int j = 0; j < arraySize; j++){
    unit* new2 = grammararray[j] -> next;
    int counter = grammararray[j]->count -1;
      for(int i=0;i<counter;i++){
        if(strcmp(new2 -> term,input -> term) == 0){//found it
          printf("%s \n",new2->term);

          unit* new= calloc(1,sizeof(unit));
          new->term = new2->term;
          new->terminal = new2->terminal;
          new->next = new2->next;

          if(new->next == NULL){
            if(strcmp(input -> term,grammararray[j]->term) != 0){
              mergelist(follow(grammararray[j]),new1);
            }//otherwise let it go
          }else{
            new = new->next;
            if(strcmp(input -> term,new -> term) != 0){
              mergelist(first(new),new1);

              if(canbeEpsilon(new)){
                if(new->next==NULL){
                  if(strcmp(input -> term,grammararray[j]->term) != 0){
                    mergelist(follow(grammararray[j]),new1);
                  }
                }else{
                  mergelist(follow(new),new1);
                }

              }
            }
          }
        }
        new2 = new2->next;
      }
  }
  return new1;
}

void createfirst(){
  firstarray = initializearray(firstarray);
  for(int j = 0; j < arraySize; j++){
    firstarray[j] -> term = grammararray[j] -> term;
    firstarray[j] -> terminal = grammararray[j] -> terminal;
    firstarray[j] -> next = NULL;
  }

  int i;
  for(i = 0; i<arraySize; i++){
    unit* head = first(grammararray[i]);
    mergelist(head,firstarray[i]);
  }
}

void createfollow(){
  followarray = initializearray(followarray);
  for(int j = 0; j < arraySize; j++){
    followarray[j] -> term = grammararray[j] -> term;
    followarray[j] -> terminal = grammararray[j] -> terminal;
    followarray[j] -> next = NULL;
  }

  int i;
  for(i = 0; i<arraySize; i++){
    unit* head = first(grammararray[i]);
    mergelist(head,followarray[i]);
  }
}

void main(){
  getgrammar();
  createfirst();
  createfollow();
}
