#include "func_id_st.h"

void createsymboltable(){
    functable = (struct func_hash_table*)malloc(sizeof(struct func_hash_table*));
    int i;
    char *temp = "";
    char *inp = "";
    char *outp = "";
    for(i=0;i<SIZE;i++){
        functable->table[i] = create_func_node(temp,inp,outp);
    }
    ht = (struct hash_of_hash_tables*)malloc(sizeof(struct hash_of_hash_tables));
    int j;
    for(j=0;j<HASHSIZE;j++){
        ht->functable[j] = create_table();
        for(i=0;i<SIZE;i++){
            char *key = "";
            char* functionname = "";
            char* type = "";
            char* ifnumval = "";
            ht->functable[j]->table[i] = create_node(key, type, functionname, ifnumval);

        }
    }
}

void populateFunctionDefinitions(char* funcname, parseTree* ast){
  if (ast == NULL)
  return;

  if(ast->noOfChildren>0){
    populateFunctionDefinitions(funcname, &ast->children[0]);
  }

  if(ast->isTerminal == 0 && (ast->parent)){
    if ((strcmp(idRepr(ast->parent->nonTerminal),"module")==0) && strcmp(funcname,ast->terminal.lexeme)==0){
      parseTree ipList = ast->parent->children[1];
      char inputtype[1000] = {'\0'};
      char outputtype[1000] = {'\0'};

      switch(ipList.children[1].ruleno){
        case 17:
          strcat(inputtype,"INTEGER");
          break;

        case 18:
          strcat(inputtype,"REAL");
          break;

        case 19:
          strcat(inputtype,"BOOLEAN");
          break;

        case 20:{
          parseTree range = ipList.children[1].children[1];
          int num1 = atoi(range.children[0].children[0].terminal.lexeme);
          int num2 = atoi(range.children[1].children[0].terminal.lexeme);
          int r = num2 - num1 +1;
          char size[3];
          char type[100] = {'\0'};
          switch(ipList.children[1].children[2].ruleno){
            case 21:
              strcat(inputtype,"ARRAY(INTEGER, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;

            case 22:
              strcat(inputtype,"ARRAY(REAL, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;

            case 23:
              strcat(inputtype,"ARRAY(BOOLEAN, ");
              strcat(inputtype,size);
              strcat(inputtype,")");
              break;
          }
          break;
        }
      }

      parseTree N1 = ipList.children[2];
       while(N1.ruleno != 13){
         switch(N1.children[1].ruleno){
          case 17:
            strcat(inputtype,"; INTEGER");
            break;

          case 18:
            strcat(inputtype,"; REAL");
            break;

          case 19:
            strcat(inputtype,"; BOOLEAN");
            break;

          case 20:{
            parseTree range = N1.children[1].children[1];
            int num1 = atoi(range.children[0].terminal.lexeme);
            int num2 = atoi(range.children[1].terminal.lexeme);
            int r = num2 - num1 +1;
            char size[3];
            char type[100] = {'\0'};
            switch(range.parent->children[(range.childnum)+1].ruleno){
              case 21:
                strcat(inputtype,"; ARRAY(INTEGER, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;

              case 22:
                strcat(inputtype,"; ARRAY(REAL, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;

              case 23:
                strcat(inputtype,"; ARRAY(BOOLEAN, ");
                strcat(inputtype,size);
                strcat(inputtype,")");
                break;
            }
            break;
          }
         }

        N1 = N1.children[2];
      }

      if(ast->parent->children[2].ruleno != 10){
        parseTree opList = ast->parent->children[2].children[0];
        switch(opList.children[1].ruleno){
          case 21:
          strcat(outputtype, "INTEGER");
          break;

          case 22:
          strcat(outputtype, "REAL");
          break;

          case 23:
          strcat(outputtype, "BOOLEAN");
          break;
        }

        parseTree N2 = opList.children[2];
        while(N2.ruleno!=16){
          switch(N2.children[1].ruleno){
            case 21:
              strcat(outputtype, "; INTEGER");
              break;

            case 22:
              strcat(outputtype, "; REAL");
              break;

            case 23:
              strcat(outputtype, "; BOOLEAN");
              break;
          }
          N2 = N2.children[2];
        }
      }

      //printf("I am %s %s %s\n",funcname,inputtype,outputtype);
      hash_insert_func(funcname,inputtype, outputtype);
      return;
    }
  }

  if(ast->parent){
    if(ast->childnum < (ast->parent->noOfChildren)-1){
      parseTree* sibling = &ast->parent->children[(ast->childnum)+1];
      populateFunctionDefinitions(funcname,sibling);
    }
  }
}

void main()
{
    getgrammar();
    createfirst();
    createfollow();
    //showfirst();
    createParseTable();
    createHASH();
    createsymboltable();

    FILE* fg = fopen("t4.txt","r");
    push("$",0);
    push("program",1);
    display();
    temp = (tokenInfo*)calloc(1,sizeof(struct symbols));
    temp = getnexttoken(fg,temp);
    p.parent = (parseTree *)malloc(sizeof(parseTree));
    p.parent->nonTerminal = parseIdStr("root");
    //printf("",p);

    parse(fg, &p);
    printf("complete parsing \n");
    //printparseTree(&p);
    printf("\ncomplete printing parse tree\n");

    ast.isTerminal = 0;
    ast.nonTerminal = parseIdStr("program");
    ast.parent = (parseTree *)malloc(sizeof(parseTree));
    ast.parent->nonTerminal = parseIdStr("root");
    createAbstractSyntaxTree(&p, &ast);
    printf("\nComplete creating abstract syntax tree\n\n");
    printastree(&ast);
    printf("\ncomplete ast\n");
    //printf("-----------------------------\n%s\n",ast);
    populateFunctionDefinitions("compute",&ast);
    //hash_insert_func("global","INT,INT","INT");
    //func_display();
}
