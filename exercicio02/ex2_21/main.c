#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../file_to_string/file_to_string.h"

#define TRUE 1
#define FALSE 0

char cur_word[20];

char *reserved_words[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
int size_reserved = 32;

int is_reserved(char* str)
{
    for(int i = 0; i < size_reserved; i++)
    {
        if(strcmp(str, reserved_words[i]) == 0)
            return TRUE;
    }
    return FALSE;
}

int get_current_word(char *str)
{
    if(str[0] == ' ')
    {
        strcpy(cur_word, " ");
        return 1;
    }
    if(str[0] == '\n')
    {
        strcpy(cur_word, "\n");
        return 1;
    }

    int size;
    for(size = 0; str[size] != ' ' && str[size] != '\0' && str[size] != '\n'; size++)
        cur_word[size] = str[size];

    cur_word[size] = '\0';

    return size;
}

void cur_to_upper()
{
    for(int i = 0; cur_word[i] != '\0'; i++)
        cur_word[i] = toupper(cur_word[i]);
}

int main(int argc, char **argv)
{
    char* input = file_to_string(argv[1]);
    FILE* output = fopen(argv[2], "w");
    int in_comment = FALSE;

    int i = 0;

    while(input[i] != '\0')
    {
        if(input[i] == '/' && input[i + 1] == '*')
            in_comment = TRUE;
        if(input[i] == '*' && input[i + 1] == '/')
            in_comment = FALSE;

        int word_size = get_current_word(input + i);

        if(in_comment && is_reserved(cur_word))
        {
            cur_to_upper();
            fprintf(output, "%s", cur_word);
            i += word_size;
        }
        else
        {
            fprintf(output, "%s", cur_word);
            i += word_size;
        }
    }

    fclose(output);

    return EXIT_SUCCESS;
}