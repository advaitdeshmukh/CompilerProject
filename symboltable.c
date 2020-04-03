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

void populateFunctionDefinitions(char* funcname, parseTree ast){
  if (ast == NULL)
  return;

  populateFunctionDefinitions(funcname, ast->children);

  if ((strcmp(idRepr(ast->parent.nonTerminal),"module")==0) && strcmp(funcname,ast.terminal.lexeme)==0){

    parseTree ipList = ast->parent.children[1];
    char inputtype[1000] = {'\0'};
    char outputtype[1000] = {'\0'};
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

    FILE* fg = fopen("t5.txt","r");
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
    //printParseTree(&p);
   printf("\ncomplete printing parse tree\n");

    ast.isTerminal = 0;
    ast.nonTerminal = parseIdStr("program");
    ast.parent = (parseTree *)malloc(sizeof(parseTree));
    ast.parent->nonTerminal = parseIdStr("root");
    createAbstractSyntaxTree(&p, &ast);
    printf("\nComplete creating abstract syntax tree\n\n");
    //printastree(&ast);
    printf("\ncomplete ast\n");

}
