#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int it_str = 0;
char* content = NULL;

int contains(int *vec, int size, int element)
{
    for(int i = 0; i < size; i++)
        if(vec[i] == element) return TRUE;

    return FALSE;
}

int id_automata()
{
    int state = 0;

    while(content[it_str] != '\0')
    {
        switch(state)
        {
            case 0:
                if(isspace(content[it_str]))
                    it_str++;

                else if(isalpha(content[it_str]))
                {
                    state = 1;
                    it_str++;
                }
                else
                {
                    state = 2;
                }
                break;
            
            case 1:
                if(isalnum(content[it_str]))
                {
                    state = 1;
                    it_str++;
                }
                else
                {
                    state = 3;
                }
                break;

            case 2:
                return FALSE;
                break;

            case 3:
                return TRUE;
                break;
        }
    }

    return EOF;
}

char* file_to_str(char *filename)
{
    FILE *file = fopen(filename, "r");

    if(!file)
    {
        printf("error: can't open file %s", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *content = malloc(sizeof(char) * (size + 1));
    
    if(content == NULL)
    {
        printf("error: can't alocate %lu bytes", sizeof(char) * (size + 1));
        fclose(file);
        return NULL;
    }

    fread(content, 1, size, file);
    content[size] = '\0';

    fclose(file);

    return content;
}

int main(int argc, char **argv)
{
    content = file_to_str(argv[1]);
    printf("%s\n", content);

    while(content[it_str] != '\0')
    {
        int bool = id_automata();
        if(bool == EOF)
        {
            printf("EOF\n");
            break;
        } 
        if(bool) printf("is_id\n");
        
        else
        {
            printf("error: %d'th in %c", it_str, content[it_str]);
            break;
        }
    }

    free(content);

    return EXIT_SUCCESS;
}