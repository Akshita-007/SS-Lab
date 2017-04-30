%{

#include<stdio.h>

int valid=1;

%}

%token A B

%%

str:S'\n' {return 0;}

S:c S d

|  

c : c A

|

d : d B

|

;

%%

 

int yyerror()

{

printf("Invalid String\n");

exit(0);

}

 

main()

{

  printf("Enter the string:\n");

  yyparse();

  if(valid==1)

  printf("---valid string---\n");

}
