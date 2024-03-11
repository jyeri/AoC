#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

int main(int argc, char **argv)
{
    char        line[1024];
    FILE        *fptr;
    int         galaxies[500][2] = {0};
    char        space[300][300] = {0};
    int         y = 0;
    int         x = 0;
    int         i = 0;
    int         max_y = 0;
    int         max_x = 0;
    int         galaxy = 0;
    long        distance = 0;
    long        result = 0;
    int         galaxycount = 0;
    int         rows[10] = {0};
    int         columns[10] = {0};

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
// loop to read and copy input
    while (fgets(line, sizeof(line), fptr))
    {
        galaxy = 0;
        y = 0;
        while (line[y])
        {
            if (line[y] == '#')
                galaxy++;
            y++;
        }
        memcpy(space[x], line, y * sizeof(char));
        x++;
//      find vertical expand slots
        if(!galaxy)
        {
            rows[i++] = x - 1;
        }
    }

    max_y = y - 1;
    max_x = x - 1;
    i = 0;

//    printf("max_x: %d, max_y: %d\n", max_x, max_y);
    y = 0;
    x = 0;

// loop to check vertical expand slots
    while (y <= max_y)
    {
        x = 0;
        galaxy = 0;
        while (x <= max_x)
        {
            if(space[x][y]=='#')
            {
                galaxy++;
                break;
            }
            x++;
        }
//        printf("galaxies: %d\n", galaxy);
        if (!galaxy)
        {
            columns[i++] = y;
        }
        y++;
    }

// save galaxy coordinates on galaxy list
    y = 0;
    x = 0;
    i = 0;

    while (y <= max_y)
    {
        x = 0;
        while (x <= max_x)
        {
            if(space[x][y]=='#')
            {
                galaxies[i][0] = x;
                galaxies[i][1] = y;
                galaxycount++;
                i++;
            }
            x++;
        }
        y++;
    }

// calculate the distances of galaxies (after expansion, so calculate also values in rows and columns)
    x = 0;
    y = 0;
    int shit = 0;
//    while (x < i)
//    {
//        y = x + 1;
//        while (y < i)
//        {
//            distance = 0;
//            shit = 0;
//            while(shit < 10)
//            {
//                if(galaxies[x][0] < rows[shit] && galaxies[y][0] > rows[shit])
//                    distance += 1;
//                shit++;
//            }
//            distance += abs(galaxies[x][0] - galaxies[y][0]);
//            shit = 0;
//            while(shit < 10)
//            {
//                if(galaxies[x][1] < columns[shit] && galaxies[y][1] > columns[shit])
//                    distance += 1;
//                shit++;
//            }
//            distance += abs(galaxies[x][1] - galaxies[y][1]);
//            result += distance;
//            y++;
//        }
//        x++;
//    }
    


    //debug prints
    y = 0;
    x = 0;
    i = 0;


    while (x <= max_x)
    {
    //    printf("%s\n", space[x]);
        y = 0;
        while (y <= max_y)
        {
            printf("%c ", space[x][y]);
            y++;
        }
        printf("\n");
        x++;
    }

    printf("\n");
    y = 0;
    x = 0;
    i = 0;
    while (i < 10)
    {
        printf("rows[%d]: %d, colums[%d]: %d\n", i, rows[i], i, columns[i]);
        i++;
    }

// calculate the distances of galaxies (after expansion, so calculate also values in rows and columns)
    x = 0;
    y = 0;
    shit = 0;
    while (x < galaxycount)
    {
        y = x + 1;
        while (y < galaxycount)
        {
//            printf("\nGalaxy %d - Galaxy %d\n", x + 1, y + 1);
            distance = 0;
            shit = 0;
            while(shit < 10)
            {
                if(galaxies[x][0] < rows[shit] && galaxies[y][0] > rows[shit])
                {
//                    printf("row added\n");
                    distance += 999999;
                }
                shit++;
            }
//            printf("pre expansion distance on X: %d\n", abs(galaxies[x][0] - galaxies[y][0]));
            distance += abs(galaxies[x][0] - galaxies[y][0]);
            shit = 0;
            while(shit < 10)
            {
                if(galaxies[x][1] < columns[shit] && galaxies[y][1] > columns[shit])
                {
//                    printf("column added\n");
                    distance += 999999;
                }
                shit++;
            }
//            printf("pre expansion distance on Y: %d\n", abs(galaxies[x][1] - galaxies[y][1]));
            distance += abs(galaxies[x][1] - galaxies[y][1]);
//            printf("total distance then: %d\n", distance);
            result += distance;
//            printf("result this far: %d\n", result);
            y++;
        }
        x++;
    }


    printf("\n");
    y = 0;
    x = 0;
    i = 0;
    while (i < galaxycount)
    {
        printf("Galaxy %d: (%d , %d)\n", i, galaxies[i][0], galaxies[i][1]);
        i++;
    }

    printf("\n\nRESULT: %ld\n\n", result);

    fclose(fptr);
    return 0;

}

