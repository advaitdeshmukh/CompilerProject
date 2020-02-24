#include "parsetable.h"

typedef struct parseTree {
    int isTerminal;
    union {
        nonTermIds nonTerminal;
        tokenInfo terminal;
    };
    struct parseTree *children;
    int noOfChildren;
} parseTree;

parseTree p;
struct unit* top;

void push(char* term, int termin){
  struct unit* temp = (unit*)malloc(sizeof(unit));
  if (!temp){
    printf("\nHeap Overflow\n");
    exit(1);
  }
  temp->term = term;
  temp->terminal = termin;
  temp->next = top;
  top = temp;
}

int isEmpty(){
  return top == NULL;
}

unit* peek(){
  if (!isEmpty()){
    struct unit* temp;
    temp = top;
    return temp;
  }
  else{
    exit(1);
  }
}

void pop(){
  struct unit* temp;
  if (top == NULL) {
    printf("Stack Underflow\n");
    exit(1);
  }
  else{
    temp = top;
    top = top->next;
    temp->next = NULL;
    free(temp);
  }
}

void display(){
  struct unit* temp;
  if (top == NULL) {
    printf("\nStack Underflow\n");
    exit(1);
  }else{
    temp = top;
    while (temp != NULL){
      printf("%s %d\n",temp->term,temp->terminal);
      temp = temp->next;
    }
  }
}

void showlist1 (unit *head){
  unit *ptr = head;
  while (ptr -> next){
      printf("%s %d\n",ptr -> term , ptr->terminal);
      ptr = ptr -> next;
  }
  printf("%s %d\n",ptr -> term , ptr->terminal);
}

void reversepush(struct unit* head){
  if (head == NULL)
  return;

  reversepush(head->next);
  push(head->term , head-> terminal);
}

void parse( parseTree *p , tokenInfo * temp){
  int columnid = parseIdStr(temp->tokenName);
  printf("%d\n",columnid);
  unit * piku = peek();
  if(piku->terminal == 1){
    printf("inside nonterminal case\n");
    int rowid = parseIdStr(piku -> term);
    printf("%d\n",rowid);
    int grammarno = (table[rowid][columnid]) - 1;
    if(grammarno >= 0 ){
      printf("%d\n\n",grammarno);
      unit * gru = grammararray[grammarno];
      unit * gram = gru;
      unit * gram1 = gru;
      pop();
      reversepush(gru->next);
      printf("\n\n");
      int child = 0;

      while(gram->next!=NULL){
        child++;
        gram = gram->next;
      }

      p->noOfChildren = child;
      printf("p->child %d\n",p->noOfChildren);
      p->children = (parseTree *)malloc(p->noOfChildren * sizeof(parseTree));
      int count = 0;
      while(gru ->next != NULL){
        unit* temp1 = gru->next;
        if(temp1->terminal == 0){
        printf("hi terminal\n");
        p->children[count].isTerminal = 0;
        p->children[count].terminal.tokenName = temp1->term;
      }
      else{
        printf("hi non terminal\n");
        p->children[count].isTerminal = 1;
        p->children[count].nonTerminal = parseIdStr(temp1->term);
      }
      gru->next = gru->next ->next;
    }
    tokenInfo * temp1 = temp;
    tokenInfo * temp2 = (tokenInfo*)malloc(sizeof(tokenInfo));
    temp2 -> tokenName = "othermodules";
    temp2 -> lineNum = 2;
    parse(&p->children[0], temp1);
    parse(&p->children[1], temp2);
  }else{
    printf("Invalid entry at table\n");
    return;
  }
}
else{
  printf("ham terminal bhi hai\n");
  if(temp->tokenName == "EOF"){
    return;
  }else if(piku->term != temp->tokenName){
    printf("error");
  }else{
    p->terminal.lineNum = temp->lineNum;
    pop();
    printf("fod denge\n");
    printf("line no = %d\n",p->terminal.lineNum);
    return;
  }
}
}

// void printParseTree(parseTree *p)
// {
//     //printf("%d",p->noOfChildren);
//     int chill = p->noOfChildren;
//
//     if(chill > 0)
//     {
//         printParseTree(&p->children[0]);
//
//         printf("Non terminal hai\n");
//
//         for(int j=1; j < chill; j++)
//         printParseTree(&p->children[j]);
//     }
//     else
//     {
//         printf("terminal hai\n");
//     }
//
//
//
// }




int main(){
   //getgrammar();
   // createfirst();
   // createfollow();
   // createParseTable();
   createHASH();
  	FILE* fg = fopen("t1.txt","r");
  	tokenInfo* temp1 = (tokenInfo*)calloc(1,sizeof(struct symbols));
  	do {
  		temp1 = getnexttoken(fg);
  		printToken(temp1);
  	} while(temp1 -> tokenName != "EOF");

    // createHASH();
    // FILE* fp = fopen("t1.txt","r");
    // push("dollar",0);
    // push("program",1);
    // display();
    // printf("\n");
    // tokenInfo* temp1 = (tokenInfo*)malloc(sizeof(struct symbols));
    //
    // do {
    //  temp1 = getnexttoken(fp);
    //  //printf("%s \n",temp1->tokenName);
    //  parse( &p , temp1);
    //  display();
    // } while(temp1 -> tokenName != "EOF");
// for(int i=0;i<2;i++)
//  for(int j=0;j<7;j++)
//      table[i][j] = -1;

        // temp1->tokenName = "modules";
        // temp1->lineNum = 1;
        // parse( &p , temp1);
        // printf("\nme hoon na \n");

        // temp1->tokenName = "othermodules";
        // parse( &p , temp1);
        // printf("me hoon na \n");
        // display();

        //printParseTree(&p );



}
