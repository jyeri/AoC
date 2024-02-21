// Blank slate idea after rethinking the problem.
// we make 2 grids: 1st grid (maze) that is equal to input and 2nd grid (energized), that is in beginning just '.', that marks where the beam has been
// -> we can do this char by char in same time. i still think that using globals for this is best way.

// solving we use recursion, we go to function that calculates and marks energy one beam at the time, and call it recursively if we counter splitter
// -> to easier tracking make table for directions instead of using integer 1-4, makes it so much feasible to understand
// -> Use switch - cases, need to work on those aswell since they are forbidden fruit in Hive.

// So basic idea step by step
// 1. Take input and copy it - same time make copy of the map just blanks.
// 2. make a beam that starts at location 0,0
// -> Beam comes with values x, y, and direction. in beginning the should be x = 0, y = 0, dir = E.
// 3. we give these parameters to energizer
// -> check the map if its inside parameters (in beginning yes)
// -> also check if the location is already been energized (no need to do anything)
// -> switch - cases for every special character
// -> small helper functions to different characters for example blacklash(int *x, int *y, enum *d)
//      -> inside helper we have switch cases that updates basically x and y cordinates with the direction.
//      -> combine these functions to be usable with either split on blacklash mirror?
// 4. in the end we can just loop thru the energy array that we made and check how much was energized.

// in the words of best sudoku channel ever: Lets get cracking


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

# define MAX 110

char *energized[MAX];
char *input[MAX];

typedef
enum direction{
	N,
	W,
	S,
	E
} Direction;

void dot(int *x, int *y, Direction *dr)
{
    switch (*dr)
    {
        case N:
            (*x)--;
            break;

        case S:
            (*x)++;
            break;

        case W:
            (*y)--;
            break;

        case E:
            (*y)++;
            break;

        default:
            break;
    }
}

void slash(int *x, int *y, Direction *dr)
{
    switch (*dr)
    {
        case N:
            (*y)++;
            *dr = E;
            break;

        case S:
            (*y)--;
            *dr = W;
            break;

        case W:
            (*x)++;
            *dr = S;
            break;

        case E:
            (*x)--;
            *dr = N;
            break;

        default:
            break;
    }
}

void bslash(int *x, int *y, Direction *dr)
{
    switch (*dr)
    {
        case N:
            (*y)--;
            *dr = W;
            break;
        
        case W:
            (*x)--;
            *dr = N;
            break;

        case S:
            (*y)++;
            *dr = E;
            break;

        case E:
            (*x)++;
            *dr = S;
            break;

        default:
            break;
    }
}



void energizer(int x, int y, Direction dr)
{
//    printf("Energizing (%d, %d) \n", x, y);
    if (x < 0 || y < 0 || x >= MAX || y >= MAX)
        return ;
    if (energized[x][y] == '#' && (input[x][y] == '|' || input[x][y] == '-'))
        return ;
    
    int newx;
    int newy;
    Direction newdr;

    newx = x;
    newy = y;
    newdr = dr;

    energized[x][y] = '#';

    switch (input[x][y])
    {
        case '.':
//            printf(". \n");
            dot(&newx, &newy, &newdr);
            energizer(newx, newy, newdr);
            return;
        
        case '/':
//            printf("/ \n");
            slash(&newx, &newy, &newdr);
            energizer(newx, newy, newdr);
            return;

        case '\\':
//            printf("\\ \n");
            bslash(&newx, &newy, &newdr);
            energizer(newx, newy, newdr);
            return;

        case '|':
//            printf("| \n");
            if (newdr == W || newdr == E)
            {
                slash(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                newx = x;
                newy = y;
                newdr = dr;
                bslash(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                return;
            }
            else
            {
                dot(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                return;
            }
        
        case '-':
//            printf("- \n");
            if (newdr == S || newdr == N)
            {
                slash(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                newx = x;
                newy = y;
                newdr = dr;
                bslash(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                return;
            }
            else
            {
                dot(&newx, &newy, &newdr);
                energizer(newx, newy, newdr);
                return;
            }

        default:
            break;
    }

}

void printer()
{
    int i = 0;
    int j = 0;
    printf("\nINPUT:\n");
    while (i < MAX)
    {
        printf("%s\n", input[i]);
        i++;
    }
    printf("\nENERGIZED:\n");
    while (j < MAX)
    {
        printf("%s\n", energized[j]);
        j++;
    }
}

int getresult()
{
    int i = 0;
    int j = 0;
    int res = 0;
    while (i < MAX)
    {
        j = 0;
        while (j < MAX)
        {
            if (energized[i][j] == '#')
                res++;
            j++;
        }
        i++;
    }
    return res;
}

void parser(char *line, int i)
{
    int j = 0;
    int len = 0;
    len = strlen(line);
    energized[i] = (char *)malloc(sizeof(char) * len);
    input[i] = (char *)malloc(sizeof(char) * len );
    while (j < MAX)
    {
        input[i][j] = line[j];
        energized[i][j] = '.';
        j++;
    }
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    long     total = 0;
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
        parser(line, current);
        current++;
    }
    printer();
    energizer(0, 0, E);
    fclose(fptr);

    printer();
    result = getresult();
    printf("Result is: %ld\n", result);
    return result;
 
}
