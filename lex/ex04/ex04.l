%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum Bool bool;
enum Bool{FALSE = 0, TRUE = 1};

int yywrap(void){return 1;}
%}
%%
[A-Z] {
    putchar(tolower(yytext[0]));
}

"/*" {
    char c;
    bool done = FALSE;
    ECHO;
    do
    {
        while((c = input()) != '*')
            putchar(c);
        putchar(c);

        while((c = input()) == '*')
            putchar(c);
        putchar(c);

        if(c == '/') done = TRUE;
    }
    while(!done);
}
%%
int main()
{
    yylex();
    return EXIT_SUCCESS;
}