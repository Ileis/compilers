#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

char* file_to_string(char *filename)
{
    FILE *archive = NULL;
    archive = fopen(filename, "r");

    fseek(archive, 0, SEEK_END);
    long archive_size = ftell(archive);
    char *str = malloc(sizeof(char) * archive_size + 1);
    fseek(archive, 0, SEEK_SET);

    fread(str, sizeof(char), archive_size, archive);
    str[archive_size] = '\0';

    fclose(archive);

    return str;
}

int main(int argc, char **argv)
{
    char* input = file_to_string(argv[1]);
    FILE* output = fopen(argv[2], "w");
    int in_comment = FALSE;

    for(int i = 0; input[i] != '\0'; i++)
    {
        if(input[i] == '/' && input[i + 1] == '*')
            in_comment = TRUE;
        if(input[i] == '*' && input[i + 1] == '/')
            in_comment = FALSE;

        if(in_comment)
            fputc(toupper(input[i]), output);
        else
            fputc(input[i], output);
    }

    fclose(output);

    return EXIT_SUCCESS;
}