#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

typedef struct LinkedList
{
    int x;
    int y;
    int distance;
    bool start;
    struct LinkedList *next;
 } LL;

LL *create_node(char **array, int x, int y, int distance, char c, int limit)
{
    printf("\n3.\n");
    printf("currently at: %c\n", array[x][y]);
    LL *new;
    new = (LL *)malloc(sizeof(LL));
    new->x = x;
    new->y = y;
    new->distance = distance;
    new->start = false;
    if (c != 'u' && x > 0 && (array[x][y] == 'J' || array[x][y] == '|' || array[x][y] == 'L'))
    {
        printf("up\n");
        new->next = create_node(array, x - 1, y, distance + 1, 'd', limit);
    }
    else if (c != 'd' && (x < limit) && (array[x][y] == '7' || array[x][y] == '|' || array[x][y] == 'F'))
    {
        printf("down\n");
        new->next = create_node(array, x + 1, y, distance + 1, 'u', limit);
    }
    else if (c != 'l' && (y > 0) && (array[x][y] == '7' || array[x][y] == '-' || array[x][y] == 'J'))
    {
        printf("left\n");
        new->next = create_node(array, x, y - 1, distance + 1, 'r', limit);
    }
    else if (c != 'r' && (y < limit) && (array[x][y] == 'F' || array[x][y] == '-' || array[x][y] == 'L'))
    {
        printf("right\n");
        new->next = create_node(array, x, y + 1, distance + 1, 'l', limit);
    }
    else if (array[x][y] == 'S')
    {
        printf("End found, loop is %d long, so mid is: %f\n", new->distance, ceil(new->distance / 2));
        exit (1);
    }
 
    sleep (10);
    return(new);
}

LL *create_start(char **array, int x, int y, int limit)
{
    LL *new;

    new = (LL *)malloc(sizeof(LL));
    new->x = x;
    new->y = y;
    new->distance = 0;
    bool start = true;
    printf("2.\n");
    if (array[x - 1][y] == 'F' || array[x - 1][y] == '7' || array[x - 1][y] == '|')
    {
        printf("going up");
        sleep(3);
        new->next = create_node(array, x - 1, y, 1, 'd', limit);
    }
    if (array[x + 1][y] == 'J' || array[x + 1][y] == 'L' || array[x + 1][y] == '|')
    {
        printf("going down");
        sleep(3);
        if (!new->next)
             new->next = create_node(array, x + 1, y, 1, 'u', limit);
    }
    if (array[x][y - 1] == 'F' || array[x][y - 1] == 'L' || array[x][y - 1] == '-')
    {
        printf("going left");
        sleep(3);
        if (!new->next)
             new->next = create_node(array, x, y - 1, 1, 'r', limit);
    }
    if (array[x][y + 1] == 'J' || array[x][y + 1] == '7' || array[x][y + 1] == '-')
    {
        printf("going right");
        sleep(3);
        if (!new->next)
            new->next = create_node(array, x - 1, y, 1, 'l', limit);
    }
    printf("not here");
    sleep(3);
    return (new);

}

LL *parsestart(char **array, int limit)
{
    int x = 0;
    int y = 0;
    LL *start;
    
    printf("1. \n");
    while(x < limit)
    {
        while (array[x][y] != '\0')
        {
            if (array[x][y] == 'S')
            {
                printf("start found at (%d, %d)\n", x, y);
                start = create_start(array, x, y, limit);
                return start;
            }
            y++;
        }
        y = 0;
        x++; 
    }

    printf("NO START");
    exit (-1);
}

// LL *parsenodes(char **array, int limit, LL *start)
// {
//     int x = 0;
//     int y = 0;

//     while(x < limit)
//     {
//         while (array[x][y] != '\0')
//         {
//             if (array[x][y] == 'S')
//             {
//                 start = create_start(array, x, y);
//                 return start;
//             }
//             y++;
//         }
//         y = 0;
//         x++; 
//     }

//     printf("NO START");
//     exit (-1);
// }

char *parser(char *line)
{
    char *new;
    int x;

    printf("parsing line: %s \n", line);

    new = strdup(line);
    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    char    *network[1024];
    LL      *start;


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
        network[current] = parser(line);
        current++;
    }
    fclose(fptr);
    
    start = parsestart(network, current);
    printf("s x: %d, s y: %d", start->x, start->y);
    printf("result: %d\n", result);
    return result;
 
}

