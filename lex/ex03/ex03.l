%{
#include <stdio.h>
#include <stdlib.h>

int yywrap(void){return 1;}

%}
ends_with_a .*a\n
begins_with_a a.*\n
%%
{ends_with_a} {printf("<ends-with-a>\n");}
{begins_with_a} {printf("<begins-with-a>\n");}
.*\n ECHO;
%%

int main()
{
    yylex();

    return EXIT_SUCCESS;
}