#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

int tree[201][25];
long result_final;

int extrapolate(int len, int x, int j)
{
    int i = 0;
    int diff = 0;
    int res = 0;
    tree[x][j] = 0;
//    printf ("\n\n\nx: %d, j: %d\n\n", x, j);
    while (x > 0)
    {
        x--;
        printf("prev: %d, prev history: %d\n", tree[x][j], tree[x + 1][j - 1]);
        tree[x][j - 1] = (tree[x][j] - tree[x + 1][j - 1]);
        printf("tree[%d][%d]: %d\n", x, j - 1, tree[x][j - 1]);
    }
    res = tree[x][j - 1];
    printf("extrapolate return value: %d\n", res);
    result_final += res;
    return res;
}

int solve(int len, int x, int tree_len)
{
    int res = 0;
    int i = len;
    int diff = 0;
    int total = 0;
    bool    keep_going;

    keep_going = false;
    while (i > 1)
    {
        diff = tree[x][i] - tree[x][i - 1];
        tree[x + 1][i - 1] = diff;
//        printf("tree[%d][%d]: %d, tree[%d][%d - 1]: %d, diff: %d\n",x, i, tree[x][i],x, i, tree[x][i - 1], diff);
//        printf("tree[%d][%d]: %d\n", x + 1, i - 1, tree[x+1][i - 1]);
        if (diff != 0 && keep_going == false)
            keep_going = true;
        i--;
    }

    x++;
    printf("\n\n");
    if (keep_going == true)
    {
        solve(len - 1, x, tree_len);
    }
    else
        res = extrapolate(len, x, i);
    if (res > total)
        total = res;
    return total;
}

int parseandsolve(char *line)
{
    char    *new;
    char    *tok1;
    int     **parsed;
    int     i = 1;
    int     mode = 0;
    int     res = 0;
    int     x = 0;
    int     total = 0;

    new = strdup(line);
    printf("%s\n", new);
    while ((tok1 = strtok_r(new, " ", &new)))
    {
        tree[x][i] = atoi(tok1);
        printf("tree[%d][%d]: %d\n", x, i, tree[x][i]);
        i++;
    }
    printf("\n\n");
    solve(i - 1, 0, i);
//    x = 0;
//    i = 0;
//    int j = 0;
//    while(tree[x][j])
//    {
//        j = 0;
//        while(j <= print_len)
//        {
//            printf("tree[%d][%d]: %d\n", x, j, tree[x][j]);
//            j++;
//            print_len--;
//        }
//        x++;
//    }
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
        result = parseandsolve(line);
        total += result;
        current++;
    }

    printf("final: %ld\n", result_final);
    fclose(fptr);
    return result;
 
}