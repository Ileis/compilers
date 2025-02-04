%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int yywrap(void){return 1;}

%}
%%
"/*" {
    char c;
    int in_comment = TRUE;
    fprintf(yyout, "%s", yytext);
    do
    {
        while((c = input()) != '*')
            fputc(toupper(c), yyout);
        fputc(toupper(c), yyout);

        while((c = input()) == '*')
            fputc(toupper(c), yyout);
        fputc(toupper(c), yyout);

        if(c == '/') in_comment = FALSE;
    }
    while(in_comment);
}
%%

int main(int argc, char **argv)
{
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");

    yylex();

    fclose(yyin);
    fclose(yyout);

    return EXIT_SUCCESS;
}