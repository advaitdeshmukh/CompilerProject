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
  if (head == NULL || head->term == "eps")
  return;

  reversepush(head->next);
  printf("******************fuckit\n*********************");
  push(head->term , head-> terminal);
}

void parse( FILE *fg, parseTree *p )
{
    //printf("token name %s  \n",temp->tokenName);
    int columnid = parseIdStr(temp->tokenName);
    printf("column id %d\n",columnid);

    unit * piku = peek();
    if(strcmp(piku->term,"$")==0)
    {
        return;
    }
    if(piku->terminal == 1)
    {

      printf("inside nonterminal case\n");
      int rowid = parseIdStr(piku -> term);
      printf(" row id = %d\n",rowid);

      int grammarno = ( table[rowid][columnid]);
      printf("grammar no = %d\n\n",grammarno);
          if(grammarno >= 0 )
          {
                printf("grammar no is greater than 0\n");
                unit * gru = grammararray[grammarno];
                unit * gram = gru;
                unit * gram1 = gru;
                unit * gggg = gru;
                pop();
                printf("reversepush grno %u for %s\n",grammarno,grammararray[grammarno]->next->term);
                reversepush(gru->next);
                printf("after reverse push \n");
                printf("*****************\n");
                display();

                printf("\n\n");
                int child = 0;
                while(gram->next!=NULL)
                {
                  child++;
                  gram = gram->next;
                }

                p->noOfChildren = child;
                printf("p->child  = %d\n",p->noOfChildren);
                p->children = (parseTree *)malloc(p->noOfChildren * sizeof(parseTree));
                int count = 0;

                while(gru ->next != NULL)
                {     printf("%s \n",gru->next->term);
                      unit* temp1 = gru->next;
                      if(temp1->terminal == 0)
                      {
                        printf("hi terminal\n");
                        p->children[count].isTerminal = 0;
                        p->children[count].terminal.tokenName = temp1->term;
                        //->children[count].noOfChildren = 0;     //change done..
                      }
                     else
                      {
                        printf("hi non terminal\n");
                        p->children[count].isTerminal = 1;
                        p->children[count].nonTerminal = parseIdStr(temp1->term);
                      }
                       gru = gru ->next;
                       count++;
                  }

                  for(int j = 0; j < p->noOfChildren; j++)
                  {
                      printf("me bhi baccha\n");
                      parse(fg, &p->children[j]);

                      if(errorflag == 1 || (strcmp(temp->tokenName,"EOF")==0 ))
                      {
                        return;
                      }

                      printf("just returned from j=%u_____________%s\n",j,temp->tokenName);

                  }
            }
            else
            {
             printf("Invalid entry at table\n");
             errorflag =1;
             return;
            }
      }
      else
      {
            printf("ham terminal bhi hai\n");
            if(strcmp(p->terminal.tokenName,"eps")==0)
            {
                pop();
                printf("after reaching eps node\n");
                printf("*****************\n");
                display();
                printf(".....\n");
                return;
            }
            if(strcmp(temp->tokenName ,"EOF")==0)
            {
              return;
            }
            else if(strcmp(piku->term , temp->tokenName)!=0)
            {
              printf("error\n");
              errorflag = 1;
              return ;
            }
            else
            {
              p->terminal.lineNum = temp->lineNum;
              pop();
              printf("*****************\n");
              display();
              printf("fod denge\n");
              printf("line no = %d\n",p->terminal.lineNum);
              temp = getnexttoken(fg,temp);
              return;
            }
        }
}


void printParseTree(parseTree *p , FILE * fip)
{
  //printf("%d",p->noOfChildren);

  int chill = p->noOfChildren;

  if(chill > 0)
  {
    printParseTree(&p->children[0],fip);

    printf("Non terminal hai\n");
    fprintf(fip,"non terminal hai\n");


    for(int j=1; j < chill; j++)
    printParseTree(&p->children[j],fip);

  }
  else
  {
    printf("terminal hai\n");
    fprintf(fip,"terminal hai\n");
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
    display();
    printf("me hoon sanyam\n");
    temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
    temp = getnexttoken(fg,temp);
    parse(fg, &p);
    printf("\n complete\n\n");
    printf("\n");
    //showfirst();
    // unit * san = grammararray[17];
    // //printf("%s",grammararray[17]->next->term);
    // while(san!= NULL)
    // {
    //   printf("%s \n",san->term);
    //    san = san->next;
    // }

}
