#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>


int solve(int *line, int len)
{
    int res = 0;
    int i = 0;
    int diff = 0;
    int *tree;
    tree = (int *)malloc(sizeof(int) * len - 1);
    bool    keep_going;
    
    keep_going = false;
    while (i < len - 1)
    {
        diff = line[i + 1] - line[i];
        tree[i] = diff;
        printf("line[%d]: %d, line[%d + 1]: %d, diff: %d\n", i, line[i], i, line[i + 1], diff);
        if (diff != 0 && keep_going == false)
            keep_going = true;
        i++;
    }
    res += diff + line[i];
    printf("\nres: %d\n", res);
    if (keep_going == true)
    {
        solve(tree, i);
    }
    return res;
}

int parseandsolve(char *line, int x)
{
    char    *new;
    char    *tok1;
    int     *parsed;
    int     i = 0;
    int     mode = 0;
    int     res = 0;

    new = strdup(line);
    parsed = (int *)malloc(sizeof(int) * strlen(new));
    printf("%s\n", new);
    while ((tok1 = strtok_r(new, " ", &new)))
    {
        parsed[i] = atoi(tok1);
        printf("saved to parsed[%d]: %d\n", i, parsed[i]);
        i++;
    }
    res = solve(parsed, i);
    return res;
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
        result = parseandsolve(line, current);
        total += result;
        printf("RESULT OF %d: %ld\n", current, result);
        printf("TOTALLING %ld\n", total);
        current++;
    }

    fclose(fptr);
    return result;
 
}