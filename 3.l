%{

#include "y.tab.c"

extern int yylval;

%}

%%

[0-9]+ { yylval=atoi(yytext); return NUMBER; }

\n { return NL ;}

. { return yytext[0]; }

%%

 

int yywrap(void){return 1;}