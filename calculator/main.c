#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

/*
exp     -> termo {soma termo}
soma    -> + | -
termo   -> fator {mult fator}
mult    -> * | /
fator   -> (exp) | num
*/

FILE *finput = NULL;
FILE* foutput = NULL;
char token;

long expr(); long term(); long fact(); void error(int); char input(); int match(char); void clean_spaces(); long number();

void error(int status)
{
    return exit(status);
}

char input()
{
    return fgetc(finput);
}

int match(char c)
{
    if(token == c)
    {
        token = input();
        return TRUE;
    }

    error(EXIT_FAILURE);
    return FALSE;
}

void clean_spaces()
{
    while(isspace(token))
        token = input();
}

long number()
{
    long acc = 0;

    clean_spaces();
    while(isdigit(token))
    {
        acc *= 10;
        acc += token - '0';
        token = input();
    }

    return acc;
}

long term()
{
    clean_spaces();
    long value = fact();

    clean_spaces();
    while(token == '*' || token == '/')
    {
        switch (token)
        {
            case '*':
                match('*');
                value *= fact();
                break;
            
            case '/':
                match('/');
                value /= fact();
                break;
        }
    }

    return value;
}

long expr()
{
    clean_spaces();
    long value = term();

    while(token == '+' || token == '-')
    {
        switch (token)
        {
            case '+':
                match('+');
                value += term();
                break;

            case '-':
                match('-');
                value -= term();
                break;
        }
    }

    return value;
}

long fact()
{
    clean_spaces();
    long value1 = 0;
    if(token == '(')
    {
        match('(');
        clean_spaces();
        value1 = expr();
        clean_spaces();
        match(')');
    }
    else if(isdigit(token))
    {
        value1 = number(); 
    }

    return value1;
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("not enough arguments.\n");
        return EXIT_FAILURE;
    }

    finput = fopen(argv[1], "r");
    foutput = fopen(argv[2], "w");
    if(finput == NULL || foutput == NULL)
    {
        printf("cant open/create files.\n");
        return EXIT_FAILURE;
    }

    token = input();

    fprintf(foutput, "%ld", expr());

    fclose(finput);
    fclose(foutput);

    return EXIT_SUCCESS;
}