%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAXTOKENLEN 40
#define OUTPUTLEN 60

int yywrap(void){return 1;}

char token_string[MAXTOKENLEN + 1];
char output_buffer[OUTPUTLEN + 1];

typedef enum TokenType TokenType;
enum TokenType
{
    TEOF,
    ERROR,
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    READ,
    WRITE,
    ASSIGN,
    EQ,
    LT,
    PLUS,
    MINUS,
    TIMES,
    OVER,
    LPAREN,
    RPAREN,
    SEMI,
    NUM,
    ID
};

%}

digit [0-9]
number {digit}+
letter [a-zA-Z]
identifier {letter}+
newline \n
whitespace [ \t]+

%%

"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}
":="            {return ASSIGN;}
"="             {return EQ;}
"<"             {return LT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {yylineno++;}
{whitespace}    {}
"{"             {
                    char c;
                    do
                    {
                        c = input();
                        if(c == '\n') yylineno++;
                    }
                    while(c != '}');
                }

%%

TokenType get_token()
{
    TokenType current_token = yylex();
    strncpy(token_string, yytext, MAXTOKENLEN);
    
    return current_token;
}

int output_format()
{
    TokenType current_token = get_token();
    fprintf(yyout, "<%s-token>", token_string);
    return current_token;
}

int main(int argc, char **argv)
{
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");

    int flag = TRUE;
    do
    {
        flag = output_format();
    }
    while(flag);

    return EXIT_SUCCESS;
}