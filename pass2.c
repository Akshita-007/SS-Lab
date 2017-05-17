#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
  {
    char a[10],ad[10],label[10],opcode[10],operand[10],mnemonic[10],symbol[10],c,d,temp[10];
    int i,address,code,add,len,actual_len,u,v,start,length=0;
    char obj[100][100];
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("output.txt","w");
    fp2=fopen("symtab.txt","r");
    fp3=fopen("input.txt","r");
    fp4=fopen("optab.txt","r");
    fp5=fopen("objectcode.txt","w");
    fscanf(fp3,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
     fprintf(fp1,"%s\t%s\t%s\n",label,opcode,operand);
     strcpy(obj[0],label);
     start = atoi(operand);
     strcpy(obj[1],operand);
     fscanf(fp3,"%x%s%s%s",&address,label,opcode,operand);
    }
    else
    {
     strcpy(obj[0],"**");
     strcpy(obj[1],"000000");
    }
    strcpy(obj[2],"null");
    int p=3;
  
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(opcode,"BYTE")==0)
        {
            fprintf(fp1,"%x\t%s\t%s\t%s\t",address,label,opcode,operand);
            len = strlen(operand);
            for(i=2;i<len-1;i++)
            {
            fprintf(fp1,"%x",operand[i]);
            sprintf(temp,"%x",operand[i]);
            strcat(obj[p],temp);
            length++;
            }
            fprintf(fp1,"\n");
            p++;
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            fprintf(fp1,"%x\t%s\t%s\t%s\t00000%s\n",address,label,opcode,operand,operand);
            strcpy(obj[p],"00000");
            strcat(obj[p],operand);
            p++;
            length=length+3;
        }
        else if((strcmp(opcode,"RESB")==0) || (strcmp(opcode,"RESW")==0))
        {
            fprintf(fp1,"%x\t%s\t%s\t%s\n",address,label,opcode,operand);
        }
        else
        {
        rewind(fp4);
        fscanf(fp4,"%s%x",mnemonic,&u);
        while(strcmp(opcode,mnemonic)!=0)
            fscanf(fp4,"%s%x",mnemonic,&u);
        rewind(fp2);
        fscanf(fp2,"%s%x",mnemonic,&v);
        while(strcmp(operand,mnemonic)!=0)
            fscanf(fp2,"%s%x",mnemonic,&v);
        fprintf(fp1,"%x\t%s\t%s\t%s\t%x%x\n",address,label,opcode,operand,u,v);
         sprintf(obj[p],"%x%x",u,v);
         length=length+3;
        p++;
        }
        fscanf(fp3,"%x%s%s%s",&address,label,opcode,operand);
    }
    fprintf(fp1,"%x\t%s\t%s\t%s\n",address,label,opcode,operand);
    sprintf(obj[2],"%x",address);
    start = atoi(obj[2]) - start;
    sprintf(obj[2],"%d",start);
    //print header record
    fprintf(fp5,"H %s %s %s\n",obj[0],obj[1],obj[2]);
    //text record
    fprintf(fp5,"T %s %x ",obj[1],length);
    for(i=3;i<p;i++)
      fprintf(fp5,"%s ",obj[i]);
    fprintf(fp5,"\nE %s",obj[1]);
    fcloseall();
  }
