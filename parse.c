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
int errorflag =0;
tokenInfo * temp;


void push(char* term, int termin){
  struct unit* temp = (unit*)malloc(sizeof(unit));
  if (!temp){
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
    exit(1);
  }else{
    temp = top;
    while (temp != NULL){
      temp = temp->next;
    }
  }
}

void reversepush(struct unit* head){
  if (head == NULL || head->term == "eps")
  return;

  reversepush(head->next);
  push(head->term , head-> terminal);
}

void parse( FILE *fg, parseTree *p )
{
    //printf("token name %s  \n",temp->tokenName);
    int columnid = parseIdStr(temp->tokenName);

    unit * piku = peek();
    if(strcmp(piku->term,"$")==0)
    {
        return;
    }
    if(piku->terminal == 1)
    {

      int rowid = parseIdStr(piku -> term);

      int grammarno = ( table[rowid][columnid]);
          if(grammarno >= 0 )
          {
                unit * gru = grammararray[grammarno];
                unit * gram = gru;
                unit * gram1 = gru;
                unit * gggg = gru;
                pop();
                reversepush(gru->next);
                display();

                int child = 0;
                while(gram->next!=NULL)
                {
                  child++;
                  gram = gram->next;
                }

                p->noOfChildren = child;
                p->children = (parseTree *)malloc(p->noOfChildren * sizeof(parseTree));
                int count = 0;

                while(gru ->next != NULL)
                {
                      unit* temp1 = gru->next;
                      if(temp1->terminal == 0)
                      {

                        p->children[count].isTerminal = 0;
                        p->children[count].terminal.tokenName = temp1->term;
                        //->children[count].noOfChildren = 0;     //change done..
                      }
                     else
                      {
                        p->children[count].isTerminal = 1;
                        p->children[count].nonTerminal = parseIdStr(temp1->term);
                      }
                       gru = gru ->next;
                       count++;
                  }

                  for(int j = 0; j < p->noOfChildren; j++)
                  {
                      parse(fg, &p->children[j]);

                      if(errorflag == 1 || (strcmp(temp->tokenName,"EOF")==0 ))
                      {
                        return;
                      }

                  }
            }
            else
            {
              printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
              errorflag =1;
              return;
            }
      }
      else
      {
            if(strcmp(p->terminal.tokenName,"eps")==0)
            {
                pop();
                display();
                return;
            }
            if(strcmp(temp->tokenName ,"EOF")==0)
            {
              return;
            }
            else if(strcmp(piku->term , temp->tokenName)!=0)
            {
              printf("SYNTACTIC ERROR on line number %u\n",temp->lineNum);
              errorflag = 1;
              return ;
            }
            else
            {
              p->terminal.lineNum = temp->lineNum;
              pop();
              display();
              temp = getnexttoken(fg,temp);
              return;
            }
        }
}

int main()
{
    getgrammar();
    createfirst();
    createfollow();
    createParseTable();
    createHASH();

    FILE* fg = fopen("t1.txt","r");
    push("$",0);
    push("program",1);
    temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
    temp = getnexttoken(fg,temp);
    parse(fg, &p);
}
