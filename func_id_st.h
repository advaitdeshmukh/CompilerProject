#include "symboltable.h"

struct hash_of_hash_tables *ht;
struct func_hash_table *functable;

int count, funcnum = 0;
char array[100][100];

void *memset(void *blk, int c, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i)
        ((unsigned char *) blk)[i] = c;

    return blk;
}

int strncmp( const char * s1, const char * s2, size_t n )
{
    while ( n && *s1 && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
    }
}

char* strtok(char *str, const char* delim) {
    static char* _buffer;
    if(str != NULL) _buffer = str;
    if(_buffer[0] == '\0') return NULL;

    char *ret = _buffer, *b;
    const char *d;

    for(b = _buffer; *b !='\0'; b++) {
        for(d = delim; *d != '\0'; d++) {
            if(*b == *d) {
                *b = '\0';
                _buffer = b+1;

                // skip the beginning delimiters
                if(b == ret) {
                    ret++;
                    continue;
                }
                return ret;
            }
        }
    }

    return ret;
}

int hash_insert_func(char *key, char* inparam, char* outparam){
    int value = hash(key);
    struct functionNode* iter = create_func_node(key, inparam, outparam);
    if(iter == NULL){
        return 0;
    }
    while(functable->table[value]->next != NULL){
        return 0;
    }
    functable->table[value]->next = iter;
    strcpy(array[funcnum++], key);
    return value;
}


int get_func_hash_value(char* funcname){
    int value = hash(funcname);
    while(functable->table[value]->next != NULL){
        if(strcmp(functable->table[value]->next->name, funcname) == 0){
            return value;
        }
        value++;
    }
    return -1;
}

void func_display(){
    int m;
    int j = 1;
    fnode* iter;
    for(m = 0; m < SIZE; m++){
        if(functable->table[m]->next != NULL && ((int)(functable->table[m]->next->name) < 100000000)){
            iter = functable->table[m]->next;
            printf("%d. I am    %s    module\n",j++,functable->table[m]->next->name);
        }
    }
}

char* get_Function_input_type(char* functionname){
    int i;
    char intype[1000] = {'\0'};
    int j = 1;

    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(intype, functable->table[i]->next->input);
            }
        }
    }
    return intype;
}

char* get_Function_output_type(char* functionname){
    int i;
    int j=1;
    char outtype[1000] = {'\0'};
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,functionname) == 0){
                strcpy(outtype, functable->table[i]->next->input);
            }
        }
    }
    return outtype;
}

int check_func_present(char* funcname){
    int i;
    int j = 1;
    for(i=0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name,funcname) == 0){
               return 1;
            }
        }
    }
    return 0;
}

fnode* directfunctionpointer(char* funcname){
    int a;
    for(a=0;a<SIZE;a++){
        if(functable->table[a]->next != NULL && ((int)(functable->table[a]->next->name) < 100000000)){
            if(strcmp(functable->table[a]->next->name,funcname) == 0){
               return functable->table[a]->next;
            }
        }
    }
    return NULL;
}

int offseter = 0;
int sequencenum = 1;
int offset = 0;

int hashinsert(char* key, char* type, char* functionname, char* ifnumvalue)
{
    int j = get_func_hash_value(functionname);
    int value = hash(key);
    struct tokNode* iter = create_node(key, type, functionname, ifnumvalue);

    if(iter == NULL){
        return 0;
    }

    while(ht->functable[j]->table[value]->next != NULL){
        value++;
    }
    ht->functable[j]->table[value]->next = iter;
    int width =0;
       if(strcmp(ht->functable[j]->table[value]->next->type,"INTEGER") ==0){
        width = 2;
       }
       if(strcmp(ht->functable[j]->table[value]->next->type,"REAL") ==0){
        width = 4;
       }
       if(strcmp(ht->functable[j]->table[value]->next->type,"BOOLEAN") ==0){
           width = 1;
       }
       if(strncmp(ht->functable[j]->table[value]->next->type,"ARRAY",5) ==0){
        char type[50];
        memset(type, '\0', sizeof(type));
        strcpy(type, ht->functable[j]->table[value]->next->type);
        int range = 0;

                char *tok = NULL;
                    tok = strtok(type, "(");
                    if(tok!=NULL){
                        tok = strtok(NULL, ",");

                        if(strcmp(tok, "INTEGER")==0)
                            width = 2;
                        if(strcmp(tok, "REAL")==0)
                            width = 4;
                        if(strcmp(tok, "BOOLEAN")==0)
                            width = 1;


                        tok = strtok(NULL, ")");
                        if(tok!=NULL){
                            range = atoi(tok);

                        }}


                // assert(0);

        width = width*range;
       }
        ht->functable[j]->table[value]->next->width = width;

        ht->functable[j]->table[value]->next->offset = offset;
        offset += width;
    return 1;
}

int checksymbolpresent(char *key, char* funcname){
    int a = get_func_hash_value(funcname);
    int value = hash(key);
    if(ht->functable[a]->table[value]==NULL){
        return 0;
    }
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return 1;
        }
        value++;
    }
    return 0;
}

int getoffset(char* key, char* funcname){
    int a = get_func_hash_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return ht->functable[a]->table[value]->next->offset;
        }
        value++;
    }
    return -1;
}

char* gettype(char* key, char* funcname){
    int a = get_func_hash_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->name) == 0){
            return ht->functable[a]->table[value]->next->type;
        }
        value++;
    }
    return NULL;
}

void automateoffset(char* funcname){
    int i;
    int a = get_func_hash_value(funcname);
    int offset = 0;
    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"") != 0){
            if(strcmp(ht->functable[a]->table[i]->next->type,"INTEGER") == 0){
                offset += 4;
            }
            if(strcmp(ht->functable[a]->table[i]->next->type,"REAL") == 0){
                offset += 8;
            }
            if(strcmp(ht->functable[a]->table[i]->next->type,"ARRAY") == 0){
                offset += 0;
            }
            ht->functable[a]->table[i]->next->offset = offset;
        }
    }
}

pNode* getdirectpointer(char* key, char* funcname){
    int a = get_func_hash_value(funcname);
    int value = hash(key);
    while(ht->functable[a]->table[value]->next != NULL){
        if(strcmp(key, ht->functable[a]->table[value]->next->type) == 0){
            return ht->functable[a]->table[value]->next;
        }
        value++;
    }
    return NULL;
}

void display1(char* funcname){
    int i;
    int a = get_func_hash_value(funcname);

    for(i=0;i<SIZE;i++){
        pNode* iter = ht->functable[a]->table[i]->next;
        if(iter != NULL && strcmp(iter->name,"")!=0){

            if(strncmp( ht->functable[a]->table[i]->next->type,"ARRAY",5)==0)
                printf("%-5d %-20s %-22s %-20s %d %d\n",(sequencenum++),ht->functable[a]->table[i]->next->name,"ARRAY",ht->functable[a]->table[i]->next->scope,ht->functable[a]->table[i]->next->width,offseter);
            else
                printf("%-5d %-20s %-22s %-20s %d %d\n",(sequencenum++),ht->functable[a]->table[i]->next->name,ht->functable[a]->table[i]->next->type,ht->functable[a]->table[i]->next->scope,ht->functable[a]->table[i]->next->width,offseter);

            offseter += ht->functable[a]->table[i]->next->width;
        }
    }
}

void displaySymbolTable(){
    int i;
    printf("\t\t\t---- Symbol Table ----\n");
    printf("%-3s %-20s %-22s %-20s %5s %6s\n","No.","Identifier name","Type", "Module Scope","Width","Offset");

    for(i=0;i<funcnum;i++){
        display1(array[i]);
    }
}
