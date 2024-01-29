#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

int *visited_map[300] = {0};

typedef struct Beam
{
    int len;
    int dir;
    int x;
    int y;
    beam *next;
} beam;

beam *create_start()
{
    beam *start;
    start = (beam *)malloc(sizeof(beam));
    start->dir = 1;
    start->len = 0;
    start->x = 0;
    start->y = 0;
    start->next = NULL;
}

beam *create_beam(beam *start, int direction, int x, int y)
{
    beam *new;
    beam *beginning;

    beginning = start;

    while (beginning->next != NULL)
        beginning = beginning->next;
    beginning->next = new;

    new->dir = direction;
    new->len = 0;
    new->x = x;
    new->y = y;

    return start;
}

int solve_map(char **map, int lines)
{
    int len = 0;
    len = strlen(map[0]);
    beam *start;
    beam *pointer;
    int x = 0;
    int y = 0;

    start = create_beam();
    printf("len: %d, lines: %d\n", len, lines);

    while (1)
    {
        if (map[pointer->x][pointer->y] == '.')
        {
            if (pointer->dir == 1);
                pointer->y += 1;
            if (pointer->dir == 2);
                pointer->x += 1;
            if (pointer->dir == 3);
                pointer->y -= 1;
            if (pointer->dir == 4);
                pointer->x -= 1;
            pointer->len += 1;
            visited_map[pointer->x][pointer->y] = 1;
        }
        else if (map[pointer->x][pointer->y] == '\\')
        {
            if (pointer->dir == 1);
            {
                pointer->dir = 2;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->x += 1;
            }
            if (pointer->dir == 2);
            {
                pointer->dir = 1;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->y += 1;
            }
            if (pointer->dir == 3);
            {
                pointer->dir = 4;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->x -= 1;
            }
            if (pointer->dir == 4);
            {
                pointer->dir = 3;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->y -= 1;
            }
            pointer->len += 1;
        }
        else if (map[pointer->x][pointer->y] == '/')
        {
            if (pointer->dir == 1);
            {
                pointer->dir = 4;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->x -= 1;
            }
            if (pointer->dir == 2);
            {
                pointer->dir = 3;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->y -= 1;
            }
            if (pointer->dir == 3);
            {
                pointer->dir = 2;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->x += 1;
            }
            if (pointer->dir == 4);
            {
                pointer->dir = 1;
                visited_map[pointer->x][pointer->y] == '1';
                pointer->y += 1;
            }
            pointer->len += 1;
        }

        if (!(pointer->next))
            pointer = start;
    }

    return 0;
}

char *parser(char *line)
{
    char *new;

    new = strdup(line);
//    printf("%s\n", new);
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
        current++;
    }
//    printf("\n\n");
    solve_map(map, current);
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}