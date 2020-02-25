#include "firstfollow.h"

typedef enum
  {program, moduleDeclarations, moduleDeclaration, otherModules, driverModule, moduleDef, module, ret, input_plist, N1, output_plist, N2, dataType, type, statements, statement, ioStmt, boolConstt, var_id_num, var, whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, index, moduleReuseStmt, optional, idList, N3, U, new_NT, unary_op, arithmeticOrBooleanExpr, N7, AnyTerm, N8, expression, arithmeticExpr, N4, term, N5, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, Default, iterativeStmt, range_arrays, range}nonTermIds;

enum Terminals
  {ID, NUM, RNUM, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, DRIVERDEF, DRIVERENDDEF, COLON, RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC,  $, eps };

#define NO_OF_TERMINALS 57
#define NO_OF_NONTERMINALS 57

int table[57][57];

int parseIdStr(char *idStr) {
     // For Non - Terminals
    if(strcmp(idStr, "program") == 0) return program;
    if(strcmp(idStr, "moduleDeclarations") == 0) return moduleDeclarations;
    if(strcmp(idStr, "moduleDeclaration") == 0) return moduleDeclaration;
    if(strcmp(idStr, "otherModules") == 0) return otherModules;
    if(strcmp(idStr,"driverModule")==0) return driverModule;
    if(strcmp(idStr,"moduleDef")==0) return moduleDef;
    if(strcmp(idStr,"module")==0) return module;
    if(strcmp(idStr,"ret")==0) return ret;
    if(strcmp(idStr,"input_plist")==0) return input_plist;
    if(strcmp(idStr,"N1")==0) return N1;
    if(strcmp(idStr,"output_plist")==0) return output_plist;
    if(strcmp(idStr,"N2")==0) return N2;
    if(strcmp(idStr,"dataType")==0) return dataType;
    if(strcmp(idStr,"type")==0) return type;
    if(strcmp(idStr,"statements")==0) return statements;
    if(strcmp(idStr,"statement")==0) return statement;
    if(strcmp(idStr,"ioStmt")==0) return ioStmt;
    if(strcmp(idStr,"boolConstt")==0) return boolConstt;
    if(strcmp(idStr,"var_id_num")==0) return var_id_num;
    if(strcmp(idStr,"var")==0) return var;
    if(strcmp(idStr,"whichId")==0) return whichId;
    if(strcmp(idStr,"simpleStmt")==0) return simpleStmt;
    if(strcmp(idStr,"assignmentStmt")==0) return assignmentStmt;
    if(strcmp(idStr,"whichStmt")==0) return whichStmt;
    if(strcmp(idStr,"lvalueIDStmt")==0) return lvalueIDStmt;
    if(strcmp(idStr,"lvalueARRStmt")==0) return lvalueARRStmt;
    if(strcmp(idStr,"index")==0) return index;
    if(strcmp(idStr,"moduleReuseStmt")==0) return moduleReuseStmt;
    if(strcmp(idStr,"optional")==0) return optional;
    if(strcmp(idStr,"idList")==0) return idList;
    if(strcmp(idStr,"N3")==0) return N3;
    if(strcmp(idStr,"U")==0) return U;
    if(strcmp(idStr,"new_NT")==0) return new_NT;
    if(strcmp(idStr,"unary_op")==0) return unary_op;
    if(strcmp(idStr,"arithmeticOrBooleanExpr")==0) return arithmeticOrBooleanExpr;
    if(strcmp(idStr,"N7")==0) return N7;
    if(strcmp(idStr,"AnyTerm")==0) return AnyTerm;
    if(strcmp(idStr,"N8")==0) return N8;
    if(strcmp(idStr,"expression")==0) return expression;
    if(strcmp(idStr,"arithmeticExpr")==0) return arithmeticExpr;
    if(strcmp(idStr,"N4")==0) return N4;
    if(strcmp(idStr,"term")==0) return term;
    if(strcmp(idStr,"N5")==0) return N5;
    if(strcmp(idStr,"factor")==0) return factor;
    if(strcmp(idStr,"op1")==0) return op1;
    if(strcmp(idStr,"op2")==0) return op2;
    if(strcmp(idStr,"logicalOp")==0) return logicalOp;
    if(strcmp(idStr,"relationalOp")==0) return relationalOp;
    if(strcmp(idStr,"declareStmt")==0) return declareStmt;
    if(strcmp(idStr,"conditionalStmt")==0) return conditionalStmt;
    if(strcmp(idStr,"caseStmts")==0) return caseStmts;
    if(strcmp(idStr,"N9")==0) return N9;
    if(strcmp(idStr,"value")==0) return value;
    if(strcmp(idStr,"default")==0) return Default;
    if(strcmp(idStr,"iterativeStmt")==0) return iterativeStmt;
    if(strcmp(idStr,"range_arrays")==0) return range_arrays;
    if(strcmp(idStr,"range")==0) return range;

    // For Terminals

    if(strcmp(idStr,"ID")==0) return ID;
    if(strcmp(idStr,"NUM")==0) return NUM;
    if(strcmp(idStr,"RNUM")==0) return RNUM;
    if(strcmp(idStr,"INTEGER")==0) return INTEGER;
    if(strcmp(idStr,"REAL")==0) return REAL;
    if(strcmp(idStr,"BOOLEAN")==0) return BOOLEAN;
    if(strcmp(idStr,"OF")==0) return OF;
    if(strcmp(idStr,"ARRAY")==0) return ARRAY;
    if(strcmp(idStr,"START")==0) return START;
    if(strcmp(idStr,"END")==0) return END;
    if(strcmp(idStr,"DECLARE")==0) return DECLARE;
    if(strcmp(idStr,"MODULE")==0) return MODULE;
    if(strcmp(idStr,"DRIVER")==0) return DRIVER;
    if(strcmp(idStr,"PROGRAM")==0) return PROGRAM;
    if(strcmp(idStr,"GET_VALUE")==0) return GET_VALUE;
    if(strcmp(idStr,"PRINT")==0) return PRINT;
    if(strcmp(idStr,"USE")==0) return USE;
    if(strcmp(idStr,"WITH")==0) return WITH;
    if(strcmp(idStr,"PARAMETERS")==0) return PARAMETERS;
    if(strcmp(idStr,"TRUE")==0) return TRUE;
    if(strcmp(idStr,"FALSE")==0) return FALSE;
    if(strcmp(idStr,"TAKES")==0) return TAKES;
    if(strcmp(idStr,"INPUT")==0) return INPUT;
    if(strcmp(idStr,"RETURNS")==0) return RETURNS;
    if(strcmp(idStr,"AND")==0) return AND;
    if(strcmp(idStr,"OR")==0) return OR;
    if(strcmp(idStr,"FOR")==0) return FOR;
    if(strcmp(idStr,"IN")==0) return IN;
    if(strcmp(idStr,"SWITCH")==0) return SWITCH;
    if(strcmp(idStr,"CASE")==0) return CASE;
    if(strcmp(idStr,"BREAK")==0) return BREAK;
    if(strcmp(idStr,"DEFAULT")==0) return DEFAULT;
    if(strcmp(idStr,"WHILE")==0) return WHILE;
    if(strcmp(idStr,"PLUS")==0) return PLUS;
    if(strcmp(idStr,"MINUS")==0) return MINUS;
    if(strcmp(idStr,"MUL")==0) return MUL;
    if(strcmp(idStr,"DIV")==0) return DIV;
    if(strcmp(idStr,"LT")==0) return LT;
    if(strcmp(idStr,"LE")==0) return LE;
    if(strcmp(idStr,"GE")==0) return GE;
    if(strcmp(idStr,"GT")==0) return GT;
    if(strcmp(idStr,"EQ")==0) return EQ;
    if(strcmp(idStr,"NE")==0) return NE;
    if(strcmp(idStr,"DEF")==0) return DEF;
    if(strcmp(idStr,"ENDEF")==0) return ENDDEF;
    if(strcmp(idStr,"DRIVERDEF")==0) return DRIVERDEF;
    if(strcmp(idStr,"DRIVERENDDEF")==0) return DRIVERENDDEF;
    if(strcmp(idStr,"COLON")==0) return COLON;
    if(strcmp(idStr,"RANGEOP")==0) return RANGEOP;
    if(strcmp(idStr,"SEMICOL")==0) return SEMICOL;
    if(strcmp(idStr,"COMMA")==0) return COMMA;
    if(strcmp(idStr,"ASSIGNOP")==0) return ASSIGNOP;
    if(strcmp(idStr,"SQBO")==0) return SQBO;
    if(strcmp(idStr,"SQBC")==0) return SQBC;
    if(strcmp(idStr,"BO")==0) return BO;
    if(strcmp(idStr,"BC")==0) return BC;
    if(strcmp(idStr,"$")==0) return $;
    if(strcmp(idStr,"eps")==0) return eps;

}

int idbatao(char *idStr) {
     // For Non - Terminals
    if(strcmp(idStr, "program") == 0) return 0;
    if(strcmp(idStr, "moduleDeclarations") == 0) return 1;
    if(strcmp(idStr, "moduleDeclaration") == 0) return 3;
    if(strcmp(idStr, "otherModules") == 0) return 4;
    if(strcmp(idStr,"driverModule")==0) return 6;
    if(strcmp(idStr,"moduleDef")==0) return 7;
    if(strcmp(idStr,"module")==0) return 8;
    if(strcmp(idStr,"ret")==0) return 9;
    if(strcmp(idStr,"input_plist")==0) return 11;
    if(strcmp(idStr,"N1")==0) return 12;
    if(strcmp(idStr,"output_plist")==0) return 14;
    if(strcmp(idStr,"N2")==0) return 15;
    if(strcmp(idStr,"dataType")==0) return 17;
    if(strcmp(idStr,"type")==0) return 21;
    if(strcmp(idStr,"statements")==0) return 24;
    if(strcmp(idStr,"statement")==0) return 26;
    if(strcmp(idStr,"ioStmt")==0) return 31;
    if(strcmp(idStr,"boolConstt")==0) return 33;
    if(strcmp(idStr,"var_id_num")==0) return 35;
    if(strcmp(idStr,"var")==0) return 38;
    if(strcmp(idStr,"whichId")==0) return 40;
    if(strcmp(idStr,"simpleStmt")==0) return 42;
    if(strcmp(idStr,"assignmentStmt")==0) return 44;
    if(strcmp(idStr,"whichStmt")==0) return 45;
    if(strcmp(idStr,"lvalueIDStmt")==0) return 47;
    if(strcmp(idStr,"lvalueARRStmt")==0) return 48;
    if(strcmp(idStr,"index")==0) return 49;
    if(strcmp(idStr,"moduleReuseStmt")==0) return 51;
    if(strcmp(idStr,"optional")==0) return 52;
    if(strcmp(idStr,"idList")==0) return 54;
    if(strcmp(idStr,"N3")==0) return 55;
    if(strcmp(idStr,"U")==0) return 57;
    if(strcmp(idStr,"new_NT")==0) return 58;
    if(strcmp(idStr,"unary_op")==0) return 60;
    if(strcmp(idStr,"arithmeticOrBooleanExpr")==0) return 62;
    if(strcmp(idStr,"N7")==0) return 63;
    if(strcmp(idStr,"AnyTerm")==0) return 65;
    if(strcmp(idStr,"N8")==0) return 67;
    if(strcmp(idStr,"expression")==0) return 69;
    if(strcmp(idStr,"arithmeticExpr")==0) return 71;
    if(strcmp(idStr,"N4")==0) return 72;
    if(strcmp(idStr,"term")==0) return 74;
    if(strcmp(idStr,"N5")==0) return 75;
    if(strcmp(idStr,"factor")==0) return 77;
    if(strcmp(idStr,"op1")==0) return 78;
    if(strcmp(idStr,"op2")==0) return 80;
    if(strcmp(idStr,"logicalOp")==0) return 82;
    if(strcmp(idStr,"relationalOp")==0) return 84;
    if(strcmp(idStr,"declareStmt")==0) return 90;
    if(strcmp(idStr,"conditionalStmt")==0) return 91;
    if(strcmp(idStr,"caseStmts")==0) return 92;
    if(strcmp(idStr,"N9")==0) return 93;
    if(strcmp(idStr,"value")==0) return 95;
    if(strcmp(idStr,"default")==0) return 98;
    if(strcmp(idStr,"iterativeStmt")==0) return 100;
    if(strcmp(idStr,"range_arrays")==0) return 102;
    if(strcmp(idStr,"range")==0) return 103;
}


void findfirstofstring(unit * ptr , int * array,int k)
{
    unit * temp = ptr;
    int index = 0;
    int count = 0;
    int flag= 0;
    while(ptr != NULL)
    {
       // printf("grammar term right = %s\n",ptr->term);

        if(ptr->terminal == 1)
        {   //printf("***********\nkitni baar aaye\n");
            unit * temp = firstarray[idbatao(ptr->term)];
            //printf("%u",temp);
            flag =0;
            while(temp->next != NULL)
            {
                //printf("hellooooooo\n");
                //printf("%s \n", temp->next->term);
                array[count] = parseIdStr(temp->next->term);
                temp = temp ->next;
                if(array[count] == 57)
                {
                    flag = 1;
                    //printf("flageps\n");
                }
                count++;
            }
        }
        else
        {
            array[count++] = parseIdStr(ptr->term);
            break;
        }

        if(flag == 0 )
        {   //printf("break flag %d\n",flag);
            break;
        }
        ptr = ptr->next;
    }
}

void createParseTable()
{

    int leftid;
    for(int i=0; i<57; i++)
    {
      for(int j=0; j<57; j++)
      {
        table[i][j] = -1;
      }
    }

    int rightside[30] ;
    int firstarr[30] ;
    int followarr[30];

    for(int k = 0 ; k < arraySize ; k++)
    {

        for(int i = 0; i < 30;i++)
        {
            rightside[i] = -1;
            firstarr[i] = -1;
            followarr[i] = -1;
        }

        leftid = parseIdStr(grammararray[k] -> term);
        //printf("\nleftid = %d\n",leftid);

        unit* ptr = grammararray[k];

          int countg =0;
          unit *ptr1 = ptr->next;
          unit *ptr2 = ptr1;
          int flag = 0;
          while(ptr2 !=NULL)
          {
            if(strcmp(ptr2->term,"eps")==0)
            {
              flag = 1;
            }
            ptr2 = ptr2 ->next;
          }

      if(flag == 1)
      {
        unit * adv = followarray[idbatao(grammararray[k]->term)];
        int countadv = 0;
        while(adv->next != NULL)
        {
            followarr[countadv++] = parseIdStr(adv->next->term);
            adv = adv ->next;
        }
        //printf("\nk = %d ###",k);
        for(int f =0;f<30;f++)
        {
            if(followarr[f] != 57 && followarr[f] != -1)
            {
                table[leftid][followarr[f]] = k;
                //printf("%d ",followarr[f]);
            }
        }
        //printf("\n");
      }
      else
      {
        findfirstofstring(ptr1 , firstarr , k);

        //printf("k = %d ***",k);

        // for(int j=0;j<30;j++)
        // {
        //     printf("%d ",firstarr[j]);
        // }
        // printf("\n");

        for(int f =0;f<30;f++)
        {
            if(firstarr[f] != -1 && firstarr[f] != 57)
            {
                table[leftid][firstarr[f]] = k;
            }
            else if(firstarr[f] == 57)
            {
                unit * ful = followarray[leftid];

                while(ful->next != NULL)
                {
                    if(strcmp(ful->next->term,"eps")!=0)
                    {
                        table[leftid][parseIdStr(ful->next->term)] = k;
                    }

                    ful = ful->next;
                }
            }
        }
    }

}
}
// void main()
// {
//     getgrammar();
//     createfirst();
//     createfollow();
//     // showlist(grammararray[99]);
//     // printf("\n___________\nfirst\n");
//     // showlist(firstarray[99]);
//     // printf("\n___________\nfollow\n");
//     // showlist(followarray[99]);
//     //showfirst();
//     //showlist(follow(grammararray[65]));
//     createParseTable();
//   }
