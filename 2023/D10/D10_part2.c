#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

// im warning you, this is couple off, and the fix for it is quite simple. but yet i decided just count the missing tiles ;)

typedef struct LinkedList
{
    int x;
    int y;
    int distance;
    bool start;
    struct LinkedList *next;
 } LL;

LL *create_node(char **array, int x, int y, int distance, char c, int limit, char **copy)
{
//    printf("\n3.\n");
//    printf("currently at: %c\n", array[x][y]);
    LL *new;
    new = (LL *)malloc(sizeof(LL));
    new->x = x;
    new->y = y;
    new->distance = distance;
    new->start = false;
    copy[x][y] = array[x][y];
    if (c != 'u' && x > 0 && (array[x][y] == 'J' || array[x][y] == '|' || array[x][y] == 'L'))
    {
//        printf("up\n");
        if (copy[x][y + 1] == '.')
            copy[x][y + 1] = 'X';
        new->next = create_node(array, x - 1, y, distance + 1, 'd', limit, copy);
    }
    else if (c != 'd' && (x < limit) && (array[x][y] == '7' || array[x][y] == '|' || array[x][y] == 'F'))
    {
//        printf("down\n");
        if (copy[x][y - 1] == '.')
            copy[x][y - 1] = 'X';
        new->next = create_node(array, x + 1, y, distance + 1, 'u', limit, copy);
    }
    else if (c != 'l' && (y > 0) && (array[x][y] == '7' || array[x][y] == '-' || array[x][y] == 'J'))
    {
//        printf("left\n");
        if (copy[x - 1][y] == '.')
            copy[x - 1][y] = 'X';
        new->next = create_node(array, x, y - 1, distance + 1, 'r', limit, copy);
    }
    else if (c != 'r' && (y < strlen(array[x])) && (array[x][y] == 'F' || array[x][y] == '-' || array[x][y] == 'L'))
    {
//        printf("right\n");
        if (copy[x + 1][y] == '.')
            copy[x + 1][y] = 'X';
        new->next = create_node(array, x, y + 1, distance + 1, 'l', limit, copy);
    }
    else if (array[x][y] == 'S')
    {
//        printf("End found, loop is %d long, so mid is: %f\n", new->distance, ceil(new->distance / 2));
        printf("\n\n PART 2: \n");
        int j = 0;
        int k = 0;
        int inside = 0;
        int tmp = 0;
        int linelen = strlen(copy[0]);
        while(j < limit)
        {
            while (k < linelen - 1)
            {

                if (copy[j][k] == 'X' )
                {
                    tmp = k;
                    while (copy[j][tmp] == 'X' || copy[j][tmp] == '.')
                    {
                        copy[j][tmp] = 'X';
                        if  (copy[j + 1][tmp] == '.')
                        {
                            copy[j + 1][tmp] = 'X';
                        }
                        if  (copy[j - 1][tmp] == '.')
                            copy[j - 1][tmp] = 'X';
                        tmp--;
                    }
                    tmp = k;
                    while (copy[j][tmp] == 'X' || copy[j][tmp] == '.')
                    {
                        copy[j][tmp] = 'X';
                        if  (copy[j - 1][tmp] == '.')
                            copy[j - 1][tmp] = 'X';
                        if  (copy[j + 1][tmp] == '.')
                            copy[j + 1][tmp] = 'X';
                        tmp++;
                    }
                }
                k++;
            }
            if (j > 63 && j < 68)
            {
                printf("\n FIXED %d", j);
                printf("%s\n", copy[j]);
            }
            k = 0;
            j++;
        }
        j = 0;
        k = 0;
        printf("\nLAST ITERATION:\n\n");
        while(j < limit)
        {
//            if (j > 50 && j < 80)
//            {
//                printf("\n DEBUGGING LINE %d", j);
//                printf("%s\n", copy[j]);
//            }
            printf("%s\n", copy[j]);
            while (k < linelen - 1)
            {
                if(copy[j][k] == 'X')
                    inside++;
                k++;
            }
            k = 0;
            j++;
        }
        printf("\n PART 2 RES = %d\n", inside);
        exit (1);
    }
    printf("there is error, values:\n standing at: %c\nx: %d, y: %d\nlast direction: %c\nlimit: %d\n", array[x][y], x, y, c, limit);
    sleep (10);
    return(new);
}

LL *create_start(char **array, int x, int y, int limit, char **copy)
{
    LL *new;

    new = (LL *)malloc(sizeof(LL));
    new->x = x;
    new->y = y;
    new->distance = 0;
    bool start = true;
//    printf("2.\n");
    copy[x][y] = array[x][y];
    if (array[x - 1][y] == 'F' || array[x - 1][y] == '7' || array[x - 1][y] == '|')
    {
//        printf("going up");
        sleep(3);
        new->next = create_node(array, x - 1, y, 1, 'd', limit, copy);
    }
    if (array[x + 1][y] == 'J' || array[x + 1][y] == 'L' || array[x + 1][y] == '|')
    {
//        printf("going down");
        sleep(3);
        if (!new->next)
             new->next = create_node(array, x + 1, y, 1, 'u', limit, copy);
    }
    if (array[x][y - 1] == 'F' || array[x][y - 1] == 'L' || array[x][y - 1] == '-')
    {
//        printf("going left");
        sleep(3);
        if (!new->next)
             new->next = create_node(array, x, y - 1, 1, 'r', limit, copy);
    }
    if (array[x][y + 1] == 'J' || array[x][y + 1] == '7' || array[x][y + 1] == '-')
    {
//        printf("going right");
        sleep(3);
        if (!new->next)
            new->next = create_node(array, x - 1, y, 1, 'l', limit, copy);
    }
    printf("not here");
    sleep(3);
    return (new);

}

LL *parsestart(char **array, int limit, char **copy)
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
//                printf("start found at (%d, %d)\n", x, y);
                start = create_start(array, x, y, limit, copy);
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

//    printf("parsing line: %s \n", line);

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
    char    *copy[1024];


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
        copy[current] = strdup(network[current]);
        current++;
    }
    fclose(fptr);
    int i = 0;
    int j = 0;
    while(i < current)
    {
        while (j < strlen(copy[i]) - 1)
        {
            copy[i][j] = '.';
            j++;
        }
        j = 0;
        i++;
    }
    start = parsestart(network, current, copy);
//    printf("s x: %d, s y: %d", start->x, start->y);
//    printf("result: %d\n", result);
    return result;
 
}

