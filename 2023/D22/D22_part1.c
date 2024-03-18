#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

typedef struct Brick
{
    int sx;
    int sy;
    int sz;
    int ex;
    int ey;
    int ez;

    int *give_support;
    int *get_support;
} Brick;

Brick *brickarray[1500];

Brick   *create_brick()
{
    Brick *new;

    new = (Brick *)malloc(sizeof(Brick));
    new->sx = -1;
    new->sy = -1;
    new->sz = -1;
    new->ex = -1;
    new->ey = -1;
    new->ez = -1;
    new->give_support = (int *)malloc(sizeof(int) * 10);
    new->get_support = (int *)malloc(sizeof(int) * 10);

    return (new);
}

void swap(int i, int j)
{
    int tmp_sx  = brickarray[i]->sx;
    int tmp_sy  = brickarray[i]->sy;
    int tmp_sz  = brickarray[i]->sz;
    int tmp_ex  = brickarray[i]->ex;
    int tmp_ey  = brickarray[i]->ey;
    int tmp_ez  = brickarray[i]->ez;

    brickarray[i]->sx = brickarray[j]->sx;
    brickarray[i]->sy = brickarray[j]->sy;
    brickarray[i]->sz = brickarray[j]->sz;
    brickarray[i]->ex = brickarray[j]->ex;
    brickarray[i]->ey = brickarray[j]->ey;
    brickarray[i]->ez = brickarray[j]->ez;

    brickarray[j]->sx = tmp_sx;
    brickarray[j]->sy = tmp_sy;
    brickarray[j]->sz = tmp_sz;
    brickarray[j]->ex = tmp_ex;
    brickarray[j]->ey = tmp_ey;
    brickarray[j]->ez = tmp_ez;
}

void    sort_bricks(int max)
{
    int i = 0;
    int j = 0;
    while (i < max)
    {
        j = i + 1;
        while (j < max)
        {
            if (brickarray[i]->sz > brickarray[j]->sz)
                swap(i, j);
            j++;
        }
        i++;
    }
}

bool    overlap(Brick *b1, Brick *b2)
{
    if (fmax(b1->sx, b2->sx) <= fmin(b1->ex, b2->ex) && fmax(b1->sy, b2->sy) <= fmin(b1->ey, b2->ey))
        return true;
    return false;
}


// Marking the falling bricks:
// iterate sorted array, brick by brick
// keep track of minimum value it can fall into (new z position) (also update endingz)
// in second thoughts:
// iterate from array[i] until array[0] or until array[i - x] already has overlap value

void    mark_falling(int maximum)
{
    int i = 0;
    int j = 0;
    int min_z = 1;
    Brick *b;
    Brick *bcomp;

    while (i < maximum)
    {
        b = brickarray[i];
        j = 1;
        while (i - j >= 0)
        {
            bcomp = brickarray[i - j];
            if (overlap(b, bcomp))
            {
                min_z = fmax(min_z, bcomp->ez + 1);
            }
            j++;
        }
        b->sz = min_z - b->ez;
        b->ez = min_z;
        i++;
    }

}

//void    mark_supports(int max)
//{
//
//}

int     parser(char *line, int current)
{
 //   char *new;
    char *token;
    char *token2;
    Brick *brick;

//    new = strdup(line);
//    printf("%s\n", new);
    brick = create_brick();
    token = strtok_r(line, "~", &line);
    token2 = (strtok_r(token, ",", &token));
    brick->sx = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->sy = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->sz = atoi(token2);
    token = strtok_r(line, "~", &line);
    token2 = (strtok_r(token, ",", &token));
    brick->ex = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->ey = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->ez = atoi(token2);

    printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", current,  brick->sx, brick->sy, brick->sz, brick->ex, brick->ey, brick->ez);
    
    brickarray[current] = brick;
    return 0;
}


int     main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;


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
//    printf("\n\n");
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    sort_bricks(current);
    printf("\nsorted\n\n");
    for(int i = 0; i < current; i++)
    {
         printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", i,  brickarray[i]->sx, brickarray[i]->sy, brickarray[i]->sz, brickarray[i]->ex, brickarray[i]->ey, brickarray[i]->ez);
    }
    mark_falling(current);
    printf("\nsorted fallen\n\n");
    for(int i = 0; i < current; i++)
    {
         printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", i,  brickarray[i]->sx, brickarray[i]->sy, brickarray[i]->sz, brickarray[i]->ex, brickarray[i]->ey, brickarray[i]->ez);
    }
//    mark_supports(current);
//    solve(current);
    fclose(fptr);
    return current;
 
}