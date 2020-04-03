#include "parsetable.h"

typedef struct parseTree {
    int isTerminal;
    union {
        nonTermIds nonTerminal;
        tokenInfo terminal;
    };
    struct parseTree *children;
    int noOfChildren;
    int parentname;
} parseTree;

char *idRepr(int id) {
    // returns the printable representation of an id
        if(id == program) return "program";
        if(id == moduleDeclarations) return "moduleDeclarations";
        if(id == moduleDeclaration) return "moduleDeclaration";
        if(id == otherModules) return "otherModules";
    if(id == driverModule) return "driverModule";
    if(id == moduleDef) return "moduleDef";
    if(id == module) return "module";
    if(id == ret) return "ret";
    if(id == input_plist) return "input_plist";
    if(id == N1) return "N1";
    if(id == output_plist) return "output_plist";
    if(id == N2) return "N2";
    if(id == dataType) return "dataType";
    if(id == type) return "type";
    if(id == statements) return "statements";
    if(id == statement) return "statement";
    if(id == ioStmt) return "ioStmt";
    if(id == boolConstt) return "boolConstt";
    if(id == var_id_num) return "var_id_num";
    if(id == var) return "var";
    if(id == whichId) return "simpleStmt";
    if(id == simpleStmt) return "simpleStmt";
    if(id == assignmentStmt) return "assignmentStmt";
    if(id == whichStmt) return "whichStmt";
    if(id == lvalueIDStmt) return "lvalueIDStmt";
    if(id == lvalueARRStmt) return "lvalueARRStmt";
    if(id == index) return "index";
    if(id == moduleReuseStmt) return "moduleReuseStmt";
    if(id == optional) return "optional";
    if(id == idList) return "idList";
    if(id == N3) return "N3";
    if(id == U) return "U";
    if(id == new_NT) return "new_NT";
    if(id == unary_op) return "unary_op";
    if(id == arithmeticOrBooleanExpr) return "arithmeticOrBooleanExpr";
    if(id == N7) return "N7";
    if(id == AnyTerm) return "AnyTerm";
    if(id == N8) return "N8";
    if(id == expression) return "expression";
    if(id == arithmeticExpr) return "arithmeticExpr";
    if(id == N4) return "N4";
    if(id == term) return "term";
    if(id == N5) return "N5";
    if(id == factor) return "factor";
    if(id == op1) return "op1";
    if(id == op2) return "op2";
    if(id == logicalOp) return "logicalOp";
    if(id == relationalOp) return "relationalOp";
    if(id == declareStmt) return "conditionalStmt";
    if(id == conditionalStmt) return "conditionalStmt";
            if(id == caseStmts) return "caseStmts";
        if(id == N9) return "N9";
       if(id == value) return "value";
       if(id == Default) return "default";
            if(id == iterativeStmt) return "iterativeStmt";
       if(id == range_arrays) return "range_arrays";
       if(id == range) return "range";
       return "unknown";
}

parseTree p;
struct unit *top;
int errorflag =0;
tokenInfo *temp;

int strlength(const char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

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
                        p->children[count].parentname = p->nonTerminal;
                        //->children[count].noOfChildren = 0;     //change done..
                      }
                     else
                      {
                        p->children[count].isTerminal = 1;
                        p->children[count].nonTerminal = parseIdStr(temp1->term);
                        p->children[count].parentname = p->nonTerminal;
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
              printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
              errorflag = 1;
              return ;
            }
            else
            {
              p->terminal.lineNum = temp->lineNum;
              strcpy(p->terminal.lexeme,temp->lexeme);
              pop();
              display();
              temp = getnexttoken(fg,temp);
              if (strcmp(temp->tokenName,"SEMICOL")==0){
                printf("---------------------\n     GOT ONE      \n---------------------\n");
              }
              return;
            }
        }
}

void printParseTree(parseTree *p ,FILE * fp )
{
  if(errorflag ==1)
  {
    fprintf(fp,"SYNTACTIC error");
  }
  else{

      int chill = p->noOfChildren;

  if(chill > 0)
  {
    printParseTree(&p->children[0] , fp);

	fprintf(fp,"----                  ");
	fprintf(fp,"----                  ");
  fprintf(fp,"----                  ");
  fprintf(fp,"----                  ");
  fprintf(fp,"%s                    ",idRepr(p->parentname));
  fprintf(fp,"NO                    ");
  fprintf(fp,"%s                   \n",idRepr(p->nonTerminal));


  for(int j=1; j < chill; j++)
  printParseTree(&p->children[j] , fp);
  }
  else
  {
      if(p->isTerminal == 0)
      {
          printf("terminal hai %u\n",p->parentname);
      	fprintf(fp,"%s                   ",p->terminal.lexeme);
        fprintf(fp,"%d                   ",p->terminal.lineNum);
        fprintf(fp,"%s                 ",p->terminal.tokenName);
        fprintf(fp,"%s              ",p->terminal.lexeme);
        fprintf(fp,"%s              ",idRepr(p->parentname));
        fprintf(fp,"YES                ");
        fprintf(fp,"------\n");
      }
      else{
        return;
      }
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
    p.parentname = -1;
    FILE* fg = fopen("t5.txt","r");
    push("$",0);
    push("program",1);
    temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
    temp = getnexttoken(fg,temp);
    //printf("%s\n",temp->lexeme);
    parse(fg, &p);
    FILE * fip = fopen("outfile.txt","w");
    fprintf(fip,"lexemeCurrentNode     lineno              tokenName           valueIfNumber       parentNodeSymbol    isLeafNode          NodeSymbol\n\n");
    printParseTree(&p , fip);
    printf("done.\n");
}
