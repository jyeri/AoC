#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

long matrix[201][25];
long tree[201][25];

int len(long *str)
{
    int x = 1;
    while(str[x])
    {
        x++;
    }
    return x;
}

long solve(int x, int len)
{
    long diff = 0;
    long res = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    bool still_digits = true;

    while (i < len)
    {
        printf("matrix[%d][%d]: %ld\n", x, i, matrix[x][i]);
        tree[j][k] = matrix[x][i];
        printf("tree[%d][%d]: %ld\n", j, k, tree[j][k]);
        i++;
        k++;
    }

    i = 0;
    j = 0;
    k = 0;
    while (still_digits == true)
    {
        while (k <= len)
        {
            diff = tree[j][k + 1] - tree[j][k];
            tree[j + 1][k] = diff;
            if(diff != 0)
                count++;
            
            if (k == len && count == 0)
            {
                still_digits = false;
            }
            k++;
        }

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
        printf("saved to matrix[%d][%d]: %ld\n", x, i, matrix[x][i]);
        i++;
    }
    matrix[x][i] = '\0';
    return i;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    long     total = 0;
    int     len = 0;
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
        len = parser(line, current);
        result += solve(current, len);
        printf("RESULT OF %d: %ld\n", current, result);
        current++;
    }

    fclose(fptr);
    return result;
 
}