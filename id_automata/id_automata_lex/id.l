/* definicoes */
%{
#include <stdio.h>
#include <stdlib.h>

int yywrap(void){return 1;}

int lineno = 1;
%}
id [a-zA-Z]+
%%
[ \t]+ ;
\n+ ;
{id} {printf("<id-token>\n");}
%%
/* rotinas aux */
int main()
{
    yylex();

    return EXIT_SUCCESS;
}