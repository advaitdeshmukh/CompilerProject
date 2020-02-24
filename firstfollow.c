#include "getgrammar.h"

void addtoarray(unit* head, unit* nextunit){
  unit *ptr = head;
  if(ptr -> term == NULL){
    ptr -> term = nextunit -> term;
    ptr -> terminal = nextunit->terminal;
    ptr -> next = NULL;
    return;
  }
  do{
    if(strcmp(ptr -> term, nextunit->term) == 0)
    return;

    if(ptr->next == NULL){
      break;
    }
    ptr = ptr -> next;

    if(strcmp(ptr -> term, nextunit->term) == 0)
    return;
  }while(ptr -> next);

  unit *new = calloc(1,sizeof(unit));
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
  unit* new;//= calloc(1,sizeof(unit));
  for(int i=0;i<arraySize;i++){
      if(strcmp(grammararray[i] -> term,ptr->term) == 0){
      int counter = countarray[i] -1;
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

void first(unit* input, unit* new){
  if(strcmp(input->term,"eps") == 0){
    new->term = "eps";
    new->terminal = 0;
    return;
  }else if(input->terminal == 0){
    new->term = input->term;
    new->terminal = input->terminal;
    return;
  }else{
    for(int j = 0; j < arraySize; j++){
      if(strcmp(grammararray[j] -> term,input -> term) == 0){
        unit* new2 = grammararray[j] -> next;
        int counter = countarray[j] -1;
        for(int i=0;i<counter-1;i++){
          if(!canbeEpsilon(new2))
          break;
          unit * temp = calloc(1,sizeof(unit));
          first(new2,temp);
          mergelist(temp,new);
          free(temp);
          new2 = new2->next;if(new2==NULL){break;}
        }
        unit * temp = calloc(1,sizeof(unit));
        first(new2,temp);
        mergelist(temp,new);
        free(temp);        }
      }
    }
    return;
  }

void follow(unit* input, unit* new1){
  if(strcmp("program",input -> term) == 0){
    unit * temp = calloc(1,sizeof(unit));
    temp->term = "$";
    temp->terminal = 0;
    mergelist(temp,new1);
    free(temp);
    return;
  }
  for(int j = 0; j < arraySize; j++){
    unit* new2 = grammararray[j] -> next;
    int counter = countarray[j] -1;
      for(int i=0;i<counter;i++){
        if(strcmp(new2 -> term,input -> term) == 0){//found it
          printf("found it");
          unit* new=new2;
          if(new->next == NULL){
            if(strcmp(input -> term,grammararray[j]->term) != 0){
              follow(grammararray[j],new1);
            }//otherwise let it go
          }else{
            new = new->next;
            if(strcmp(input -> term,new -> term) != 0){
              unit * temp = calloc(1,sizeof(unit));
              first(new,temp);
              printf("iska first maanga %s\n",new->term);
              mergelist(temp,new1);
              free(temp);
              while(canbeEpsilon(new)){
                if(new->next==NULL){
                  if(strcmp(input -> term,grammararray[j]->term) != 0){
                    follow(grammararray[j],new1);
                  }
                  break;
                }
                else{
                  unit * temp = calloc(1,sizeof(unit));
                  first(new->next,temp);
                  printf("iska first maanga 1 %s\n",new->next->term);
                  mergelist(temp,new1);
                  free(temp);
                  new = new->next;
                }
              }
            }
          }
        }
        new2 = new2->next;
      }
  }
  return;
}

void createfirst(){
  firstarray = initializearray(firstarray);
  for(int j = 0; j < arraySize; j++){
    firstarray[j] -> term = grammararray[j] -> term;
    firstarray[j] -> terminal = grammararray[j] -> terminal;
    firstarray[j] -> next = NULL;
  }
  for(int i = 0; i<arraySize; i++){
    unit* new1= calloc(1,sizeof(unit));
    first(grammararray[i], new1);
    mergelist(new1,firstarray[i]);
    free(new1);
    //showfirst(firstarray[i]);
    //printf("------------------------\n");
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
    unit* new1= calloc(1,sizeof(unit));
    follow(grammararray[i], new1);
    mergelist(new1,followarray[i]);
    free(new1);
    //showfollow(followarray[i]);
    //printf("------------------------\n");
  }
}


void main(){
  getgrammar();
  createfollow();
  printf("\n-------------\n");
  showfollow();
}
