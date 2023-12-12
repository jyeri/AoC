#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>

int solver(char *puzzle, int *inst, int instlen)
{
    printf("now solving %s\n", puzzle);
    return 0;
}

int parser(char *line)
{
    char *cpy;
    int i = 0;
    int j = 0;
    cpy = strdup(line);
    char *puzzle;
    int inst[10] = {0};
    int len = 0;
    int instlen = 0;

    while(cpy[i] != ' ')
    {
        i++;
        len++;
    }
    i++;
    puzzle = strndup(cpy, len);
    while(i < strlen(cpy))
    {
        if (isdigit(cpy[i]))
        {
            while (isdigit(cpy[i]))
            {
                inst[j] = cpy[i] - '0';
                j++;
                i++;
            }
            instlen++;
        }
        i++;
    }

    // debug
    i = 0;
    printf("parsed line: %s\n", puzzle);
    printf("instructions: %d\n", instlen);
    while (i < 10)
    {
        printf("inst[%d]: %d\n", i, inst[i]);
        i++;
    }


    int nextins = 0;
    i = 0;
    int res = 0;
    if(instlen > 0)
    {
        while(i < strlen(puzzle))
        {
            res += solver(&puzzle[i], inst, instlen);
            i++;
        }
    }




//    int nextins = 0;
//    int x = 0;
//    int y = 0;
//    int k = 0;
//    int pos = 0;
//    if(instlen > 0)
//    {
//        i = 0;
//        j = 0;
//        
//        while (i < strlen(puzzle))
//        {
//            if(puzzle[i] != '.')
//            {
//                while (j < strlen(puzzle))
//                {
//                    nextins = inst[x];
//                    y = x;
//                    j = i;
//                    k = 0;
//                    while (j + k < strlen(puzzle))
//                    {
//                        printf("%s\n", &puzzle[j]);
//                        sleep(1);
//                        while (puzzle[j + k] != '.' && nextins > -2)
//                        {
//                            if (puzzle[j+ k] == '#')
//                            {
//                                while(puzzle[j + k] == '#')
//                                {
//                                    nextins--;
//                                    k++;
//                                }
//                            }
//                            else
//                            {
//                                nextins--;
//                                k++;
//                            }
//                        }
//                        if (nextins == 0 && puzzle[j + 1] != '#')
//                        {
//                            y++;
//                        }
//                        else
//                        {
//                            break;
//                        }
//                        k++;
//                        while (puzzle[j + k] == '.')
//                            k++;
//                        nextins = inst[y];
//                        if (j + k == strlen(puzzle) - 1 || nextins == 0)
//                        {
//                            printf("possibility\n");
//                            pos++;
//                        }
//                        k++;
//                    }
//                    if (j == strlen(puzzle) - 1 || nextins == 0)
//                    {
//                        printf("possibility\n");
//                        pos++;
//                    }
//                    printf("\n");
//                }     
//            }
//            i++;
//        }
//    }

    free (cpy);
    free (puzzle);
    return 0;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    int     instsaved = 0;
    char    *inst;

    if (argc < 2)
    {
        printf("nono");
        return -1;
    }
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("file missing, ono");
        return -1;
    }
    while (fgets(line, sizeof(line), fptr))
    {
        result += parser(line);
    }
    fclose(fptr);
    return result;
 
}