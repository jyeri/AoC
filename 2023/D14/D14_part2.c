#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

int solve_map(char **map, int lines)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int k = 0;
    int changed = 0;
    int beam[2];
    int len;
    long cycles = 10000;

    len = strlen(map[0]);

    printf("\nSolving\n");
    while (k < 1000)
    {
        //north
        i = 0;
        j = 0;
        x = 0;
        changed = 0;
//        printf("north\n");
        while (j < len - 1)
        {
            i = 0;
            beam[0] = 0;
            beam[1] = 0;
            while(i < lines)
            {
                if(map[i][j] == '#')
                {
                    beam[0] = i;
                    beam[1] = j;
                }
                else if (map[i][j] == 'O')
                {
                    x = beam[0];
                    while (x < i)
                    {
                        if(map[x][j] == '.')
                        {
                            map[x][j] = 'O';
                            changed = 1;
                            break;
                        }
                        x++;
                    }
                    if (changed == 1)
                        map[i][j] = '.';
                }
                changed = 0;
                i++;
            }
            j++;
        }

//        j = 0;
//        i = 0;
//        while(j < len - 1)
//        {
//            printf("%s", map[j]);
//            j++;
//        }
//        printf("\n");

        //west
//        printf("west\n");
        i = 0;
        j = 0;
        x = 0;
        changed = 0;
        while (i < lines)
        {
//            printf("map[%d] = %s\n", i,  map[i]);
            j = 0;
            beam[0] = 0;
            beam[1] = 0;
            while(j < len - 1)
            {
                if(map[i][j] == '#')
                {
                    beam[0] = i;
                    beam[1] = j;
                }
                else if (map[i][j] == 'O')
                {
                    x = beam[1];
                    while (x < j)
                    {
                        if(map[i][x] == '.')
                        {
                            map[i][x] = 'O';
                            changed = 1;
                            break;
                        }
                        x++;
                    }
                    if (changed == 1)
                        map[i][j] = '.';
                }
                changed = 0;
                j++;
            }
            i++;
        }
//
//        j = 0;
//        i = 0;
//        while(j < len - 1)
//        {
//            printf("%s", map[j]);
//            j++;
//        }
//        printf("\n");
//
//        //south
//        printf("south\n");
        i = lines - 1;
        j = len - 2;
        x = 0;
        changed = 0;
        while (j >= 0)
        {
//            printf("map[%d]: %s\n", j, map[j]);
            i = lines - 1;
            beam[0] = lines - 1;
            beam[1] = len - 1;
            while(i >= 0)
            {
                if(map[i][j] == '#')
                {
                    beam[0] = i;
                    beam[1] = j;
                }
                else if (map[i][j] == 'O')
                {
                    x = beam[0];
                    while (x > i)
                    {
                        if(map[x][j] == '.')
                        {
                            map[x][j] = 'O';
                            changed = 1;
                            break;
                        }
                        x--;
                    }
                    if (changed == 1)
                    {
                        map[i][j] = '.';
                    }
                }
                changed = 0;
                i--;
            }
            j--;
        }
//
//        j = 0;
//        i = 0;
//        while(j < len - 1)
//        {
//            printf("%s", map[j]);
//            j++;
//        }
//        printf("\n");
//
//        //east
//        printf("east\n");
        i = lines - 1;
        j = len - 1;
        x = 0;
        changed = 0;
        while (i >= 0)
        {
//            printf("map[%d]: %s\n", i, map[i]);
            j = len - 1;
            beam[0] = lines - 1;
            beam[1] = len - 1;
            while(j >= 0)
            {
                if(map[i][j] == '#')
                {
                    beam[0] = i;
                    beam[1] = j;
                }
                else if (map[i][j] == 'O')
                {
                    x = beam[1];
                    while (x > j)
                    {
                        if(map[i][x] == '.')
                        {
                            map[i][x] = 'O';
                            changed = 1;
                            break;
                        }
                        x--;
                    }
                    if (changed == 1)
                        map[i][j] = '.';
                }
                changed = 0;
                j--;
            }
            i--;
        }
//        j = 0;
//        i = 0;
//        while(j < len - 1)
//        {
//            printf("%s", map[j]);
//            j++;
//        }
//        printf("\n");
//        printf("\n");
        i = 0;
        j = 0;
        x = 0;
        int rock = 1;
        long load = 0;

        while (j < len - 1)
        {
            i = 0;
            while(i < lines)
            {
                if(map[i][j] == '#')
                {
                    rock = 1;
                }
                else if (map[i][j] == 'O')
                {
                    load += (lines - i);
                }
                i++;
            }
            j++;
        }
        printf ("load: %ld on cycle: %d\n", load, k);
        k++;
    }

    //debug
//    j = 0;
//    i = 0;
//    while(j < len - 1)
//    {
//        printf("%s", map[j]);
//        j++;
//    }
//    printf("\n");
    

    return(0);
}

char *parser(char *line)
{
    char *new;

    new = strdup(line);
//    printf("%s", new);
    return new;
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
        map[current] = parser(line);
        current++;;
    }
//    printf("\n\n");
    solve_map(map, current);
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}