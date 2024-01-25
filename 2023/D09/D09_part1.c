#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

// quadratic equation

// remember to take negatives
// ceil is time - sqrt(pow(time, 2) + 4 * 1 * record/2)
// floor is time + sqrt(pow(time, 2) + 4 * 1 * record/2)

// then win amount is = ceil(ceil) - floor(floor) + 1

long matrix[201][25];

long solve(int x)
{
    long diff = 0;
    int i = 0;
    long res = 0;

    diff = matrix[x][1] - matrix[x][0];

    while (x >= 0)
    {
        while (matrix[x][i])
        {
            i++;
        }
//        printf("matrix[%d][%d]: %ld\n", x, i - 1, matrix[x][i - 1]);
        diff = matrix[x][i - 1] + diff;
        printf("diff: %ld\n", diff);
        res += diff;
        x--;
    }
    printf("res: %ld\n", res);
    return res;
}

int parser(char *line, int x)
{
    char *new;
    char *tok1;
    int i = 0;
    int mode = 0;

    new = strdup(line);
//    printf("%s\n", new);
    while ((tok1 = strtok_r(new, " ", &new)))
    {
        matrix[x][i] = atoi(tok1);
//        printf("saved to matrix[%d][%d]: %ld\n", x, i, matrix[x][i]);
        i++;
    }
    return 0;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    long     total = 0;
    char    *inst;
    char    *map[300] = {0};

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
        parser(line, current);
        current++;
    }
    result = solve(current - 1);
    fclose(fptr);
    return result;
 
}