#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

// Need to revisit djikstras algorithm, pseudo code below
// 
// function dijkstra(G, S)
//     for each vertex V in G
//         distance[V] <- infinite
//         previous[V] <- NULL
//         If V != S, add V to Priority Queue Q
//     distance[S] <- 0
// 	
//     while Q IS NOT EMPTY
//         U <- Extract MIN from Q
//         for each unvisited neighbour V of U
//             tempDistance <- distance[U] + edge_weight(U, V)
//             if tempDistance < distance[V]
//                 distance[V] <- tempDistance
//                 previous[V] <- U
//     return distance[], previous[]

int solve_map(char **map, int lines)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int n = strlen(map[0]);
    int distance[n];
    int pred[n];


    char **cost;
    while (i < lines)
    {
        cost[i] = (char *)malloc(sizeof(int) * n + 1);
        strcpy(cost[i], map[i]);
//        printf("map[%d]: %s\ncost[%d]: %s\n\n", i, map[i], i, cost[i]);
        i++;
    }

    

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