#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define NO_OF_TERMINALS 2
#define NO_OF_NONTERMINALS 3


typedef struct fisty{
    char* ntot;
    struct fisty *next;
}fisty;

fisty* FIRSTHASH[2];
fisty* FOLLOWHASH[2];
fisty* GRAMMAR[3];

void addnode (fisty *head, char* value1) {
    fisty *new = malloc(sizeof(fisty)), *ptr = head;
    new -> ntot = value1;
    

    new -> next = NULL;
    while (ptr -> next) ptr = ptr -> next;
    ptr -> next = new;
}

void showlist (fisty *head) {
  fisty *ptr = head;

  while (ptr -> next) {
      printf("%s ",ptr -> ntot);
      ptr = ptr -> next;
  }

  printf ("%s  \n", ptr -> ntot);
}
void addKeyToken1(int index , char *ntot)
{
  
  fisty *ptr = FIRSTHASH[index];

  if(ptr -> ntot == NULL){
    FIRSTHASH[index] -> ntot = ntot;
   
  }
  else{
    addnode(FIRSTHASH[index], ntot);
  }
}

void addKeyToken2(int index , char *ntot)
{
  
  fisty *ptr = FOLLOWHASH[index];

  if(ptr -> ntot == NULL){
    FOLLOWHASH[index] -> ntot = ntot;
   
  }
  else{
    addnode(FOLLOWHASH[index], ntot);
  }
}

void addKeyToken3(int index , char *ntot)
{
  
  fisty *ptr = GRAMMAR[index];

  if(ptr -> ntot == NULL){
    GRAMMAR[index] -> ntot = ntot;
   
  }
  else{
    addnode(GRAMMAR[index], ntot);
  }
}

void createHASH(){
  for(int i = 0; i < 2; i++){
    FIRSTHASH[i] = malloc(sizeof(fisty));
    FOLLOWHASH[i] = malloc(sizeof(fisty));
    GRAMMAR[i] = malloc(sizeof(fisty));
    
  }
  GRAMMAR[2] = malloc(sizeof(fisty));

 	addKeyToken1(0,"program");
 	addKeyToken1(0,"ritik");
 	addKeyToken1(0,"modules");
 	addKeyToken1(1,"trues");
 	addKeyToken1(1,"ritik");
 	addKeyToken1(1,"othermodules");

 	addKeyToken2(0,"program");
 	addKeyToken2(0,"dollar");
 	addKeyToken2(0,"bools");
 	addKeyToken2(1,"dollar");

 	addKeyToken3(0,"program");
 	addKeyToken3(0,"eps");
 	addKeyToken3(1,"boolst");

 	addKeyToken3(1,"bools");
 	addKeyToken3(1,"trues falses");

 	addKeyToken3(2,"boolsy");
 	addKeyToken3(2,"eps");

 	

}

enum ts{modules,othermodules, trues,falses,ritik,dollar,eps};
enum nts{program, bools, boolsy};



int table[3][7];

int parseIdStr(char *idStr) {
    
	if(strcmp(idStr, "program") == 0) return program;
	if(strcmp(idStr, "bools") == 0) return bools;
	if(strcmp(idStr, "ritik") == 0) return ritik;
	if(strcmp(idStr, "modules") == 0) return modules;
	if(strcmp(idStr,"dollar")==0) return dollar;
	if(strcmp(idStr,"eps")==0) return eps;

	return -1;

}


void createParseTable()
{	

	int leftid;
	int rightside[10] ;
	int firstarr[10] ;
	int followarr[10];
	int flag = 0;
	for(int i=0;i<10;i++)
	{
		rightside[i] = -1;
		firstarr[i] = -1;
		followarr[i] = -1;

	}
	for(int i=0; i<3; i++)
		for(int j=0; j<7; j++)
		{
			table[i][j] = -1;
		}

	for(int k=0;k<1;k++)
	{
		leftid = parseIdStr(GRAMMAR[k]-> ntot);
		printf("%d\n",leftid);

		fisty* ptr = GRAMMAR[k];
		
	
		int countg =0;
		while(ptr->next != NULL)
		{	
			printf("%s ",ptr->next->ntot);
			rightside[countg] = parseIdStr(ptr->next->ntot);
			ptr = ptr->next;
			printf("%d \n",rightside[countg]);
			countg++;
		}
		printf("lavika ki maa ki \n");

		
		for(int x = 0; x < countg;x++)
		{
			if(rightside[x] == 6)
			{
				flag = 1;
				printf("flag");
			}

		}


		if(flag == 0)
		{	
			printf("fuckkkkkkkkkkkkk");
			fisty * temp = FIRSTHASH[leftid];
			int countf = 0;
			while(temp->next != NULL)
			{
				printf("%s ",temp->next->ntot);
				firstarr[countf] = parseIdStr(temp->next->ntot);
				temp = temp->next;
				printf("%d \n",firstarr[countf]);
				countf++;
			}

			int rand = 0;
			while(firstarr[rand] != -1)
			{
				table[leftid][firstarr[rand]] = k+1;
				rand++;
			}


			printf("fuck advait.....fuck parse table\n");
			for(int g = 0; g < 1; g++)
			{
				printf("        modules othermodules  trues     falses     ritik       dollar eps\n");
			}
			printf("%s ",GRAMMAR[k]->ntot);
			for(int g = 0; g < 7; g++)
			{
				printf("%d           ",table[k][g]);
			}

		}
		else
		{
			printf("fuck you vandana\n");
			fisty * temp2 = FOLLOWHASH[leftid];
			int countfo = 0;
			while(temp2->next != NULL)
			{
				printf("%s ",temp2->next->ntot);
				followarr[countfo] = parseIdStr(temp2->next->ntot);
				temp2 = temp2->next;
				printf("%d \n",followarr[countfo]);
				countfo++;
			}
			for(int w=0;w<10;w++)
			{

			}
			int rand1 = 0;
			while(followarr[rand1] != -1)
			{	
				printf("fuck advait");
				table[leftid][followarr[rand1]] = k+1;
				rand1++;
				printf("hi\n");
			}
			printf("fuck ritik");
			printf("fuck advait.....fuck parse table\n");
			
			printf("        modules othermodules  trues     falses     ritik       dollar eps\n");
			
			printf("%s ",GRAMMAR[k]->ntot);
			for(int g = 0; g < 7; g++)
			{
				printf("%d           ",table[k][g]);
			}

		}






	}

}

int main()
{
	printf("hi bro\n");
	createHASH();

	for(int k=0;k<2;k++){
		showlist(FIRSTHASH[k]);
	}

	printf("\n\n");

	for(int k=0;k<2;k++){
		showlist(FOLLOWHASH[k]);
	}
printf("\n\n");
	for(int k=0;k<2;k++){
		showlist(GRAMMAR[k]);
	}
	printf("fhsdjhfsdh\n");
	
	createParseTable();



}

