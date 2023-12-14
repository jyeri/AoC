#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

int new_strcmp(char *a, char* b)
{
    int i = 0;
    int res = 0;
    while (a[i] && b[i])
    {
        if (a[i] != b[i])
            res++;
        i++;
    }
    return res;
}

int solve_map(char **map, int current)
{
    int i = 0;
    int j = 0;
    int linelen = 0;
    int linecount = 0;
    bool matching = false;
    char *vertical[300] = {0};
    char *horizontal[300] = {0};

    linelen = strlen(map[i]);
    while (i < current)
    {
        vertical[i] = strdup(map[i]);
        linecount++;
        i++;
    }

    i = 0;
    j = 0;
    int x = 0;
    int y = 0;
    while (j < linelen - 1)
    {
        i = 0;
        y = 0;
        horizontal[x] = (char *)malloc(sizeof(char) * linecount + 1);
        while (i < linecount)
        {
            horizontal[x][y] = vertical[i][j];
            i++;
            y++;
        }
        horizontal[x][y] = '\0';
        x++;
        j++;
    }

    int hortresult = 0;
    int vertresult = 0;
    int result = 0;
    int matched = 1;
    int smudges = 0;
    bool smudged = false;
    i = 0;
    j = 1;
    x = 0;
    y = 0;

    while (j < linelen - 1)
    {
        x = j - 1;
        smudges = new_strcmp(horizontal[j], horizontal[x]);
        if (smudges > 0)
            smudged = true;
        if (smudges < 2)
        {
            matched = 1;
            y = 1;
            while (x - y >= 0 && j + y <= linelen - 2 && smudges < 2)
            {
                smudges += new_strcmp(horizontal[j + y], horizontal[x - y]);
                if (smudges < 2)
                {
                    y++;
                    matched = 1;
                }
                else
                {
                    matched = 0;
                    break;
                }
            }
            if (smudges == 1 && (x - y < 1 || j + y >= linelen - 1) && matched == 1)
            {
                hortresult = (x + 1);
            }
        }
        smudges = 0;
        j++;
    }

    i = 1;
    j = 0;
    x = 0;
    y = 0;
    smudges = 0;

if (!hortresult)
{
    while (i < linecount)
    {
        x = i - 1;
        smudges = new_strcmp(vertical[i], vertical[x]);
        if (smudges > 0)
            smudged = true;
        if (smudges < 2)
        {
            y = 1;
            while (x - y >= 0 && i + y <= linecount - 1 && smudges < 2)
            {
                smudges += new_strcmp(vertical[i + y], vertical[x - y]);
                if (smudges < 2)
                {
                    y++;
//                              printf("match\n");
                }
                else
                {
                    break;
                }
            }
            if ((smudges == 1) && (x - y == -1 || i + y == linecount) && (!vertresult))
            {
                vertresult = (x + 1);
            }
        }
//                  printf("%d line\n", i);
        smudges = 0;
        i++;
    }
}


    

//    printf("NO vert match\n");

    i = 0;
    j = 0;
    while (i < linecount)
    {
        free(vertical[i]);
        i++;
    }
    while (i < linelen)
    {
        free(horizontal[i]);
        i++;
    }
    vertresult *= 100;
    return(fmax(vertresult, hortresult));
}

char *parser(char *line)
{
    char *new;
    int x;

    new = strdup(line);
    return new;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    int     instsaved = 0;
    long     total = 0;
    char    *inst;
    char    *map[300] = {0};
    int     mapnr = 0;

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
        map[current] = parser(line);
        if ((strcmp(map[current],"\n") == 0) || (strcmp(map[current],"\0") == 0))
        {
            printf("Map %d: - ", mapnr + 1);
            result = solve_map(map, current);
            printf("%ld\n", result);
            total += result;
            current = -1;
            mapnr++;
        }
//        printf("Line: %d\n", current);
        current++;;
    }
    printf("Map %d: - ", mapnr + 1);
    result = solve_map(map, current);
//    printf("%d: map res: %ld\n", mapnr +1, result);
    total += result;
    printf("%ld\n", result);
    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}