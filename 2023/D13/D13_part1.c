#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

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
        printf("%s", map[i]);
        vertical[i] = strdup(map[i]);
//        printf("vertical[%d]: %s\n", i, vertical[i]);
        linecount++;
        i++;
    }

    i = 0;
    j = 0;
    int x = 0;
    int y = 0;
//    printf("len: %d - count: %d\n", linelen, linecount);
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
//        printf("horizontal[%d]: %s \n", x, horizontal[x]);
        x++;
        j++;
    }

    int hortresult = 0;
    int vertresult = 0;
    int result = 0;
    int matched = 1;
    i = 0;
    j = 1;
    x = 0;
    y = 0;
    printf("len: %d - count: %d\n", linelen, linecount);

    while (j < linelen - 1)
    {
        x = j - 1;
        printf("hor compare[%d]: %s\n", x, horizontal[x]);
        printf("hor compare[%d]: %s\n", j, horizontal[j]);
        printf("\n");
        if (strcmp(horizontal[j], horizontal[x]) == 0)
        {
//            printf("matching hortline %d - %d\n", x, j);
            y = 1;
            while (x - y >= 0 && j + y <= linelen - 2)
            {
                printf("hor compare[%d]: %s\n", j + y, horizontal[j + y]);
                printf("hor compare[%d]: %s\n", x - y, horizontal[x - y]);
                printf("\n");
                if (strcmp(horizontal[j + y], horizontal[x - y]) == 0)
                {
                    y++;
                    matched = 1;
//                    printf("match\n");
                }
                else
                {
                    matched = 0;
                    break;
                }
            }
//            printf("x - y = %d, j + y = %d \n", x - y, j + y);
            if ((x - y < 1 || j + y >= linelen - 1) && matched == 1)
            {
//                printf("x - y = %d, j + y = %d \n", x - y, j + y);
                printf("hort match\n");
                hortresult = (x + 1);
                printf("hort res: %d\n", hortresult);
            }
        }
//        printf("%d line\n", j);
        j++;
    }
//    printf("NO hort match\n");


    i = 1;
    j = 0;
    x = 0;
    y = 0;

    if (hortresult < 2)
    {
        while (i < linecount)
        {
            x = i - 1;
            printf("ver compare[%d]: %s\n", x, vertical[x]);
            printf("ver compare[%d]: %s\n", i, vertical[i]);
            printf("\n");
            if (strcmp(vertical[i], vertical[x]) == 0)
            {
//                   printf("matching vertline %d - %d\n", x, i);
                y = 1;
                while (x - y >= 0 && i + y <= linecount - 1)
                {    
                    printf("ver compare[%d]: %s\n", i + y, vertical[i + y]);
                    printf("ver compare[%d]: %s\n", x - y, vertical[x - y]);
                    printf("\n");
                    if (strcmp(vertical[i + y], vertical[x - y]) == 0)
                    {
                        y++;
//                           printf("match\n");
                    }
                    else
                    {
                        break;
                    }
                }
                if (x - y == -1 || i + y == linecount)
                {
                        printf("vert match\n");
                        vertresult = (x + 1);
                        printf("ver res: %d\n", vertresult);
                }
            }
//               printf("%d line\n", i);
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
    printf("\n");
    printf("Horizontal res: %d, vertical res: %d  -  ", hortresult, vertresult);
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
            printf("map number: %d\n", mapnr + 1);
            result = solve_map(map, current);
            printf("%ld\n", result);
            total += result;
            current = -1;
            mapnr++;
        }
//        printf("Line: %d\n", current);
        current++;;
    }
    printf("map number: %d\n", mapnr + 1);
    result = solve_map(map, current);
//    printf("%d: map res: %ld\n", mapnr +1, result);
    total += result;
    printf("%ld\n", result);
    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}