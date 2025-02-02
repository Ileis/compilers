%{
#include <stdio.h>
#include <stdlib.h>

int yywrap(void){return 1;}

int count = 0;
%}
digit [0-9]
number {digit}+
%%
{number} {
    printf("match number\n");
    int n = atoi(yytext);
    printf("%x", n);
    if(n > 9) count++;
}
%%
int main()
{
    yylex();
    fprintf(stderr, "numero de substituicoes = %d\n", count);

    return EXIT_SUCCESS;
}