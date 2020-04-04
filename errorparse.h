#include "parsetable.h"
typedef struct parseTree {
    int isTerminal;
    union {
        nonTermIds nonTerminal;
        tokenInfo terminal;
    };
    struct parseTree *children;
    struct parseTree *parent;
    int noOfChildren;
    int ruleno;
    int childnum;
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
       return "root";
}

parseTree p,ast;
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
      printf("%s\n",temp->term);
      temp = temp->next;
    }
  }
  printf("\n");
}

void reversepush(struct unit* head){
  if (head == NULL || head->term == "eps")
  return;

  reversepush(head->next);
  push(head->term , head-> terminal);
}

void parse( FILE *fg, parseTree *p )
{
    if(strcmp(temp->tokenName,"EOF")==0)
    {   //printf("hiloigfngjf\n");
        temp->tokenName = "$";
    }
    //printf("token name %s  \n",temp->tokenName);
    int columnid = parseIdStr(temp->tokenName);

    unit * piku = peek();
    //printf("peek == %s  \n",piku->term);
    if(strcmp(piku->term,"$")==0)
    {
        return;
    }
    int rowid = parseIdStr(piku -> term);

    if(piku->terminal == 1)
    {
      int grammarno =  table[rowid][columnid];


      //printf("****grammar no =  %d   rowid = %d  columnid = %d\n",grammarno, rowid, columnid);
          if(grammarno >= 0 )
          {     //printf("fod diya\n");
                unit * gru = grammararray[grammarno];
                unit * gram = gru;
                unit * gram1 = gru;
                unit * gggg = gru;
                pop();
                reversepush(gru->next);
                //display();

                int child = 0;
                while(gram->next!=NULL)
                {
                  child++;
                  gram = gram->next;
                }

                p->noOfChildren = child;
                p->children = (parseTree *)malloc(p->noOfChildren * sizeof(parseTree));
                p->ruleno = grammarno;
                int count = 0;

                while(gru ->next != NULL)
                {
                      unit* temp1 = gru->next;
                      if(temp1->terminal == 0)
                      {

                        p->children[count].isTerminal = 0;
                        p->children[count].terminal.tokenName = temp1->term;
                        p->children[count].noOfChildren = 0;
                        p->children[count].ruleno = -1;
                        p->children[count].parent = p;
                        p->children[count].childnum = count;
                        //printf("!!!! %d\n",count);     //change done..
                      }
                     else
                      {
                        p->children[count].isTerminal = 1;
                        p->children[count].nonTerminal = parseIdStr(temp1->term);
                        p->children[count].noOfChildren = 0;
                        p->children[count].ruleno = -1;
                        p->children[count].parent = p;
                        p->children[count].childnum = count;
                        //printf("!!!! %d\n",count);
                      }
                       gru = gru ->next;
                       count++;
                  }

                  for(int j = 0; j < p->noOfChildren; j++)
                  {
                      if(p->children[j].isTerminal == 0)
                      {
                          if(strcmp(p->children[j].terminal.tokenName , "eps")==0)
                          {
                              pop();
                              return;
                          }
                          else
                          {
                              parse(fg, &p->children[j]);
                          }

                      }
                      else
                      {
                            parse(fg, &p->children[j]);
                      }

                      if(errorflag == 1)
                      {
                        return;
                      }

                  }

            }
        else
            {
              if(grammarno == -1)
                {
                    printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
                      //errorflag =1;
                      int flag = 1;
                      while(flag == 1)
                      {
                        unit * teemp = peek();
                        if(teemp->terminal==0)
                        {
                            pop();
                        }
                        else
                        {
                            flag = 0;
                        }
                      }
                      temp = getnexttoken(fg,temp);
                      return;

                    }
              else
              {
                if(grammarno == -200)
                {
                      pop();
                      return;
                }
              }
     }
    }
    else
    {
            if(strcmp(p->terminal.tokenName,"eps")==0)
            {
                pop();
                //display();
                return;
            }
            if(strcmp(temp->tokenName ,"EOF")==0)
            {
              return;
            }
            else if(strcmp(piku->term , temp->tokenName)!=0)
            {
              printf("SYNTACTIC ERROR ON LINE NO %u\n",temp->lineNum);
              //errorflag =1;
              //int flag = 1;
              //while(flag == 1)
              //{
                unit * teemp = peek();
                //if(teemp->terminal==0)
                //{
                    pop();
               // }
               // else
                //{
                 //   flag = 0;
                //}
              //}

              temp = getnexttoken(fg,temp);
              return;
            }
            else
            {
              p->terminal.lineNum = temp->lineNum;
              strcpy(p->terminal.lexeme ,temp->lexeme);
              p->terminal.tokenName = temp->tokenName;
              //printf("sanyam fuck it.\n");
              pop();
              //display();
              temp = getnexttoken(fg,temp);
              //if(strcmp(temp->tokenName,"EOF")==0)
              //{
                  //strcpy(temp->tokenName,"$");
              //}
              return;
            }
        }
}

void printParseTree(parseTree *p )
{
  if(p == NULL)
  {
      printf("\nTree is empty\n");
  }
  if(errorflag ==1)
  {
    printf("SYNTACTIC error\n");
  }
  else
  {

      int chill = p->noOfChildren;

    if(chill > 0)
  {
    printParseTree(&p->children[0]);

  printf("---- %d                 ",p->ruleno);
  printf("**** %s                ",idRepr(p->parent->nonTerminal));
  printf("----                  ");
  printf("----                  ");
  printf("----                  ");
  printf("NO                    ");
  printf("%s                   \n",idRepr(p->nonTerminal));


  for(int j=1; j < chill; j++)
  printParseTree(&p->children[j]);
  }
  else
  {
      if(p->isTerminal == 0)
      {

        printf("---- %d                   ",p->ruleno);
        printf("**** %s                  ",idRepr(p->parent->nonTerminal));
        printf("%d                   ",p->terminal.lineNum);
        printf("%s                 ",p->terminal.tokenName);
        printf("%s              ",p->terminal.lexeme);
        printf("YES                ");
        printf("------\n");
      }
      else{
        return;
      }
  }

}
}

void printastree(parseTree *pt )
{if(pt == NULL)
  {
      printf("\nTree is empty\n");
      return;
  }
  if(errorflag ==1)
  {
    printf("SYNTACTIC error\n");
    return;
  }
  else
  {

    int chill = pt-> noOfChildren;

    if(chill > 0)
    {
        printf("NO NT1 ---        ");
        printf("rulenp = %d               ",pt->ruleno);
        printf("*** %s           ",idRepr(pt->parent->nonTerminal));
        printf("baap === %d           ",pt->parent->isTerminal);
        printf("%s \n",idRepr(pt->nonTerminal));




        printastree(&pt->children[0]);



        for(int j=1; j < chill; j++)
        {
            printastree(&pt->children[j]);
        }

    }
    else
    {
      if(pt->isTerminal == 0)
      {
        printf("YES Ter ***  " );
        printf("ruleno = %d               ",pt->ruleno);
        printf("*** %s           ",idRepr(pt->parent->nonTerminal));
        printf("baap=== %d           ",pt->parent->isTerminal);
        printf("lexeme = %s      ",pt->terminal.lexeme);
        printf(" lnno = %d       ",pt->terminal.lineNum);
        printf("---\n");
      }
      else
     {
        printf("NO NT ---             ");
        printf("%s         ",idRepr(pt->nonTerminal));
        printf("rulens = %d               ",pt->ruleno);
        printf("*** %s           ",idRepr(pt->parent->nonTerminal));
        printf("baap=== %d           ",pt->parent->isTerminal);
        printf("%s",idRepr(pt->nonTerminal));
        printf("nofchildren == %d \n",pt->noOfChildren);

        }
    }

}
}

int isUseful(char * idStr) {
    if(strcmp(idStr, "PRINT") == 0) return 1;
    if(strcmp(idStr, "AND") == 0) return 1;
    if(strcmp(idStr, "EQ") == 0) return 1;
    if(strcmp(idStr, "GE") == 0) return 1;
    if(strcmp(idStr, "NE") == 0) return 1;
    if(strcmp(idStr, "LE") == 0) return 1;
    if(strcmp(idStr, "GT") == 0) return 1;
    if(strcmp(idStr, "LT") == 0) return 1;
    if(strcmp(idStr, "DIV") == 0) return 1;
    if(strcmp(idStr, "MUL") == 0) return 1;
    if(strcmp(idStr, "MINUS") == 0) return 1;
    if(strcmp(idStr, "PLUS") == 0) return 1;
    if(strcmp(idStr, "RNUM") == 0) return 1;
    if(strcmp(idStr, "NUM") == 0) return 1;
    if(strcmp(idStr, "ID") == 0) return 1;
    if(strcmp(idStr, "WHILE") == 0) return 1;
    if(strcmp(idStr, "FALSE") == 0) return 1;
    if(strcmp(idStr, "TRUE") == 0) return 1;
    if(strcmp(idStr, "GET_VALUE") == 0) return 1;
    if(strcmp(idStr, "ARRAY") == 0) return 1;
    if(strcmp(idStr, "BOOLEAN") == 0) return 1;
    if(strcmp(idStr, "REAL") == 0) return 1;
    if(strcmp(idStr, "INTEGER") == 0) return 1;
    if(strcmp(idStr, "FOR") == 0) return 1;
    if(strcmp(idStr, "OR") == 0) return 1;
    else return 0;
}

void createAbstractSyntaxTree(parseTree *p, parseTree *ast)
{
    //printf("hi ast function\n");
    int i, j, usefulChildrenCount = 0;

    for(i = 0; i < p->noOfChildren; i++)
        // all nonterminals are useful
        if(p->children[i].isTerminal == 1 || isUseful(p->children[i].terminal.tokenName))
            usefulChildrenCount++;

    ast->noOfChildren = usefulChildrenCount;
    ast->ruleno = p->ruleno;
    //printf("children = %d\n\n",usefulChildrenCount);
    ast->children = (parseTree *)malloc(ast->noOfChildren * sizeof(parseTree));
    ast->parent = p->parent;

    i = 0, j = 0;
    while(i < p->noOfChildren) {
        if(p->children[i].isTerminal == 0) {
            if(isUseful(p->children[i].terminal.tokenName)) {
                // copy ith node of p to jth node of ast
                //printf("TT === i = %d  j = %d \n",i,j);
                ast->children[j].isTerminal = 0;
                //printf("tt = %s \n",p->children[i].terminal.tokenName);
                ast->children[j].terminal.tokenName = p->children[i].terminal.tokenName;
                //printf("tt = %s \n",ast->children[j].terminal.tokenName);
                strcpy(ast->children[j].terminal.lexeme, p->children[i].terminal.lexeme);
                ast->children[j].terminal.lineNum = p->children[i].terminal.lineNum;
                ast->children[j].ruleno = p->children[i].ruleno;
                ast->children[j].noOfChildren = 0;
                ast->children[j].parent = p->children[i].parent;
                ast->children[j].childnum = j;
                //printf("\n $$$$$  %s $$$$\n",ast->children[j].children.nonTerminal);
                j++;
            }
        }
        else {
            // recursively construct the ast rooted here
            //printf("NT === i = %d  j = %d \n",i,j);
            //printf("\n\nlast statement then do it\n");
            if(p->children[i].noOfChildren > 0)
            {
                ast->children[j].nonTerminal = p->children[i].nonTerminal;
                ast->children[j].isTerminal = 1;
                ast->children[j].ruleno = p->children[i].ruleno;
                ast->children[j].noOfChildren = 0;
                ast->children[j].parent = p->children[i].parent;
                ast->children[j].childnum = j;
                //printf("nntt = %s\n",idRepr(ast->children[j].nonTerminal));
                createAbstractSyntaxTree(&p->children[i], &ast->children[j]);
                j++;
            }
            else
            {
                return;
            }
        }
        i++;
    }
}


// void main()
// {
//     getgrammar();
//     createfirst();
//     createfollow();
//     showfirst();
//     createParseTable();
//     createHASH();
//
//     FILE* fg = fopen("t6.txt","r");
//     push("$",0);
//     push("program",1);
//     display();
//     temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
//     temp = getnexttoken(fg,temp);
//     p.parent = (parseTree *)malloc(sizeof(parseTree));
//     p.parent->nonTerminal = parseIdStr("root");
//     //printf("",p);
//
//     parse(fg, &p);
//     printf("complete parsing \n");
//     printParseTree(&p);
//    printf("\ncomplete printing parse tree\n");
//
//     ast.isTerminal = 0;
//     ast.nonTerminal = parseIdStr("program");
//     ast.parent = (parseTree *)malloc(sizeof(parseTree));
//     ast.parent->nonTerminal = parseIdStr("root");
//     createAbstractSyntaxTree(&p, &ast);
//     printf("\nComplete creating abstract syntax tree\n\n");
//     printastree(&ast);
//     printf("\ncomplete ast\n");
//
// }
