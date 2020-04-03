#ifndef _SYMBOL_TABLES_H_
#define _SYMBOL_TABLES_H_
#include <stdio.h>
#include <stdlib.h>
#include "errorparse.h"
#define SIZE 20
#define HASHSIZE 20

size_t strlen(char *p)
{
    unsigned int count = 0;

    while(*p!='\0')
    {
        count++;
        p++;
    }

    return count;
}

struct functionNode{
    char name[30];
    char input[100];
    char output[100];
    struct functionNode* next;
};

typedef struct functionNode fnode;
typedef struct functionNode *fnext;


struct func_hash_table{
    fnode* table[SIZE];
};

struct tokNode{
    char name[30];
    char ifnumvalue[10];
    char scope[15];
    char type[15];
    int offset;
    int width;
    struct tokNode* next;
};

typedef struct tokNode pNode;
typedef struct tokNode *pNext;

struct hash_table
{
    pNode *table[SIZE];
};

struct hash_of_hash_tables{
    struct hash_table *functable[HASHSIZE];
};

struct hash_table* create_table(){
    struct hash_table *node = (struct hash_table *)malloc(sizeof(struct hash_table));
    return node;
}

struct tokNode* create_node(char *key, char *type, char* funcname, char* ifnumval){
    struct tokNode *node = (struct tokNode *)malloc(sizeof(struct tokNode));
    strcpy(node->name, key);
    strcpy(node->ifnumvalue, ifnumval);
    strcpy(node->scope, funcname);
    strcpy(node->type, type);
    node->offset = 0;
    node->width = 0;
    node->next = NULL;
    return node;
}

struct functionNode* create_func_node(char *funcname, char *inparam, char *outparam){
    struct functionNode *node = (struct functionNode *)malloc(sizeof(struct functionNode));
    strcpy(node->name, funcname);
    strcpy(node->input, inparam);
    strcpy(node->output, outparam);
    return node;
}

int hash(char *key){
    int value = 0;
    int i;
    for(i = 0; i < strlen(key); i++){
        value += (int)key[i];
    }
    return (value % SIZE);
}

#endif
