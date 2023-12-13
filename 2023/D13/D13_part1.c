#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>

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
//        printf("map     [%d]: %s\n", i, map[i]);
        vertical[i] = strdup(map[i]);
//        printf("vertical[%d]: %s\n", i, vertical[i]);
        linecount++;
        i++;
    }

    i = 0;
    j = 0;
    int x = 0;
    int y = 0;
    printf("len: %d - count: %d\n", linelen, linecount);
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
        horizontal[x][y] = '\n';
//        printf("horizontal[%d]: %s \n", x, horizontal[x]);
        x++;
        j++;
    }

    i = 0;
    j = 1;
    x = 0;
    y = 0;

    while (j < linelen - 1)
    {
        x = j - 1;
        printf("hor compare[%d]: %s\n", x, horizontal[x]);
        printf("hor compare[%d]: %s\n", j, horizontal[j]);
        if (strcmp(horizontal[j], horizontal[x]) == 0)
        {
            printf("matching hortline %d - %d\n", x, j);
            y = 1;
            while (x - y >= 0 && j + y <= linecount)
            {
                printf("hor compare[%d]: %s\n", j + y, horizontal[j + y]);
                printf("hor compare[%d]: %s\n", x - y, horizontal[x - y]);
                if (strcmp(horizontal[j + y], horizontal[x - y]) == 0)
                {
                    y++;
                    printf("match\n");
                }
                else
                {
                    break;
                }
            }
            printf("x - y = %d, j + y = %d \n", x - y, j + y);
            if (x - y < 1 || j + y > linecount)
            {
                printf("x - y = %d, j + y = %d \n", x - y, j + y);
                printf("hort match\n");
                return (x + 1);
            }
        }
        printf("%d line\n", j);
        j++;
    }
    printf("NO hort match\n");


    i = 1;
    j = 0;
    x = 0;
    y = 0;

    while (i < linecount)
    {
        x = i - 1;
        printf("ver compare[%d]: %s\n", x, vertical[x]);
        printf("ver compare[%d]: %s\n", j, vertical[i]);
        if (strcmp(vertical[i], vertical[x]) == 0)
        {
            printf("matching vertline %d - %d\n", x, i);
            y = 1;
            while (x - y >= 0 && i + y < linelen)
            {    
                printf("ver compare[%d]: %s\n", i + y, vertical[i + y]);
                printf("ver compare[%d]: %s\n", x - y, vertical[x - y]);
                if (strcmp(vertical[i + y], vertical[x - y]) == 0)
                {
                    printf("match\n");
                }
                y++;
            }
            if (x - y <= 0 || i + y >= linelen)
            {
                printf("vert match\n");
                return x + 1 * 100;
            }
        }
        printf("%d line\n", i);
        i++;
    }

    printf("NO vert match\n");

    return 0;
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
    int     result = 0;
    int     current = 0;
    int     instsaved = 0;
    int     total = 0;
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
        map[current] = parser(line);
        if ((strcmp(map[current],"\n") == 0) || (strcmp(map[current],"\0") == 0))
        {
            result = solve_map(map, current);
            printf("map res: %d\n", result);
            printf("\n\n");
            current = -1;
        }
//        printf("Line: %d\n", current);
        current++;;
    }
    result = solve_map(map, current);
    printf("map res: %d\n", result);
    printf ("%d\n", total);
    fclose(fptr);
    return result;
 
}