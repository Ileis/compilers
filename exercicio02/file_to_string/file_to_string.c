#include <stdlib.h>
#include <stdio.h>
#include "file_to_string.h"

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