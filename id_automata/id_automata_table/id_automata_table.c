#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *content = NULL;
int it_str = 0;

int state0[] = {1, 3, 3};
int state1[] = {1, 1, 2};
int state2[] = {2, 2, 2};
int state3[] = {3, 3, 3};

int *id_automata_table[] = {state0, state1, state2, state3};

int consume0[] = {1, 1, 1};
int consume1[] = {1, 1, 0};
int consume2[] = {1, 1, 1};
int consume3[] = {1, 1, 1};

int *consume[] = {consume0, consume1, consume2, consume3};

typedef enum IdRegularExp IdRegularExp;
enum IdRegularExp
{
    LETTER,
    DIGIT,
    OTHER
};

IdRegularExp char_to_ER(char character)
{
    if(isalpha(character)) return LETTER;
    if(isdigit(character)) return DIGIT;
    return OTHER;
}

int id_automata(int **table, int **consume, int final_state, int error_state)
{
    int state = 0;
    while(isspace(content[it_str])) it_str++;
    while(state != error_state && state != final_state && content[it_str] != '\0')
    {
        int next_state = table[state][char_to_ER(content[it_str])];
        if(consume[state][char_to_ER(content[it_str])]) it_str++;
        state = next_state;
    }
    if(state == final_state) return 1;
    if(state == error_state) return 0;
    if(content[it_str] == '\0') return EOF;
    return 0;
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

char* get_error_str()
{
    char* p = (content + it_str);

    while(*(p - 1) != ' ')
        p--;
    
    return p;
}

int main(int argc, char **argv)
{
    content = file_to_str(argv[1]);
    printf("%s\n", content);

    while(content[it_str] != '\0')
    {
        int bool = id_automata(id_automata_table, consume, 2, 3);
        if(bool == EOF)
        {
            printf("EOF\n");
            break;
        } 

        if(bool) printf("is_id\n");
        else
        {
            printf("error: %d'th in %c\n", it_str, content[it_str]);
            break;
        }
    }

    free(content);

    return EXIT_SUCCESS;
}