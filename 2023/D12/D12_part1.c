#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>

// had to take some help since C aint known for being too easy with these.
// not aiming for hischores so didn't feel too quilty :D


int solver(char *puzzle, int nums, int *inst, int instlen)
{

//    printf("%s - %d\n", puzzle, nums);
//    printf("%d - %d\n", inst[0], instlen);

    if(instlen <= 0 || inst[0] == 0)
        return 1;

    int i = 0;
    int j = 0;
    int res = 0;
    int possible = 0;

//    printf("current: %s\n", puzzle);

    // we check all possibilities as long as have possibility to fit on string
    while (i <= nums - inst[0]) 
    {
        possible = 1;
        j = 0;
        // loop to check first instruction
        while (j < inst[0]) 
        {
            // check if there is block
            if (puzzle[i+j] == '.') 
            {
                possible = 0;
            }
            j++;
        }
        // check if current index + first instruction is under the length of the string and there is # next to this position (cant be)
        if (i + inst[0] < nums && puzzle[i + inst[0]] == '#') 
        {
            possible = 0;
        }
        // check if we are on string but last char was #. (cant be since there has to be atleast one between each picross)
        if (i > 0 && puzzle[i-1] == '#') 
        {
            possible = 0;
        }
        // if there was only one instruction we dont go recursive
        if (instlen == 1) 
        {
            j = i+inst[0]+1;
            //check if there is still something that has to be part of it, or we gucci
            while (j < nums) 
            {
                if (puzzle[j] == '#') 
                {
                    possible = 0;
                }
                j++;
            }
        }
        // if variable was not changed, this conf is possible, and we move to next instruction check
        // that being possible to start from puzzle[i + last instruction length + 1 empty space]
        if (possible) 
        {
            res += solver(&puzzle[i+inst[0]+1], nums-i-inst[0]-1, &inst[1], instlen-1);
        }
        if (puzzle[i] == '#')
        {
            break;
        }
        i++;
    }
//    printf("\n");
    return res;
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
    char *token;
    char *token2;

    while(cpy[i] != ' ')
    {
        i++;
        len++;
    }
    i++;
    puzzle = strndup(cpy, len);
    while((token = strtok_r(cpy, " ", &cpy)) != NULL)
    {
        while((token = strtok_r(cpy, ",", &cpy)) != NULL)
        {
            inst[j] = atoi(token);
            j++;
            instlen++;
        }
    }

//    // debug
//    i = 0;
//    printf("parsed line: %s\n", puzzle);
//    printf("instructions: %d\n", instlen);
//    while (i < 10)
//    {
//        printf("inst[%d]: %d\n", i, inst[i]);
//        i++;
//    }
//
//
//    int nextins = 0;
//    i = 0;
    int res = 0;
    len = strlen(puzzle);
    res = solver(puzzle, len, inst, instlen);

//    printf("my res: %d\n", res);
    free (cpy);
    free (puzzle);
    return res;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 1;
    int     instsaved = 0;
    int     total = 0;
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
        result = parser(line);
        printf("Line: %d - %d\n", current, result);
        total += result;
        current++;
    }
    printf ("%d\n", total);
    fclose(fptr);
    return result;
 
}