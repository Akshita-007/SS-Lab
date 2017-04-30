%{

#include "y.tab.c"

%}

%%

a return A;

b return B;

.|\n return yytext[0];

%%

 

int yywrap(void){return 1;}
