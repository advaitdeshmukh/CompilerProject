#include "first.h"


#define NO_OF_TERMINALS 57
#define NO_OF_NONTERMINALS 57

int table[57][57];



void createParseTable()
{	

	int leftid;
	int rightside[10] ;
	int firstarr[10] ;
	int followarr[10];
	
	
	for(int i=0; i<57; i++)
		for(int j=0; j<57; j++)
		{
			table[i][j] = -1;
		}

	for(int k = 0 ; k < 71 ; k++)
	{  
        int flag = 0;
		for(int i = 0; i < 10;i++)
		{
			rightside[i] = -1;
			firstarr[i] = -1;
			followarr[i] = -1;
		}

		leftid = parseIdStr(grammararray[k] -> term);
		printf("\nleftid = %d\n",leftid);

		unit* ptr = grammararray[k];
        printf("grammar\n");
        
		int countg =0;
		while(ptr->next != NULL)
		{	
			printf("%d  %s\n",parseIdStr(ptr->next->term),ptr->next->term);
			rightside[countg] = parseIdStr(ptr->next->term);
			ptr = ptr->next;
			countg++;
		}
		

		for(int x = 0; x < countg; x++)
		{
			if(rightside[x] == 57)
			{
				flag = 1;
			}

		}


		if(flag == 0)
		{	
			
			unit * temp = first(grammararray[k]);
            printf("first\n");
            
			int countf = 0;
			while(temp != NULL)
			{
				printf("%d  %s\n",parseIdStr(temp->term),temp->term);
				firstarr[countf] = parseIdStr(temp->term);
				temp = temp->next;
				countf++;
			}

			
            for(int i=0;i<10;i++)
            {
                if(firstarr[i] != -1 && firstarr[i] != 57)
                {   
                    printf("leftid = %d firstarr = %d \n",leftid,firstarr[i]);
                    table[leftid][firstarr[i]] = k+1;
                }
            }
			
		}
		else
		{
			
			unit * temp2 = follow(grammararray[k]);
            printf("follow\n");
            
			int countfo = 0;
			while(temp2 != NULL)
			{
				printf("%d  %s\n",parseIdStr(temp2->term),temp2->term);
				followarr[countfo] = parseIdStr(temp2->term);
				temp2 = temp2->next;
				countfo++;
			}
			
			
			for(int i=0;i<10;i++)
            {
                if(followarr[i] != -1 && followarr[i] != 57)
                {
                    printf("leftid = %d followarr = %d \n",leftid,followarr[i]);
                    table[leftid][followarr[i]] = k+1;
                }
            }
			
			
		}

		
	}
    
    for(int i=0;i<57;i++)
    {   
        printf("row no %d\n",i+1);
        for(int j=0; j<57; j++)
        {
                printf("%d ", table[i][j]);
        }
        printf("\n");

    }
}   
     




int main()
{	
	getgrammar();
    //showlist(follow(grammararray[65]));
	createParseTable();

  
}


