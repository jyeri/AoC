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

void    sort_bricks()
{

}

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
    sortbricks(current);
//  mark_supports(current);
//  solve(current);
    fclose(fptr);
    return current;
 
}