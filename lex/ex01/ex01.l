%{
#include <stdio.h>
#include <stdlib.h>

int yywrap(void){return 1;}

int lineno = 1;
%}
line .*\n
%%
{line} {printf("%5d %s", lineno++, yytext);}
%%
int main(void)
{
    yylex();   
    return EXIT_SUCCESS;
}