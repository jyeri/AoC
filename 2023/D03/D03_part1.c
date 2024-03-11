// INPUT: Multiple lines of '.', 'symbol' or Integers
// OUTPUT: sum of all integers that have adjecent symbol (horizontal, vertical or diagonal)

// Or of op:
// 1. iterate first line until first is_digit()
// -> while is_digit() sum = sum * 10 + atoi(str[x])
// 2. check if there is symbol before or after the integer, is there diagonal of start or stop, is there horizontal of whole string
// -> if true check = 0 AND
// -> (
// -> if str[x - 1][y - 1] OR
// -> if str[x + 1][y - 1] OR
// -> if str[x + 1][y + 1] OR
// -> if str[x - 1][y + 1] OR
// -> if str[x + 1][y] OR
// -> if str[x - 1][y] OR
// -> if str[x][y - 1] OR
// -> if str[x][y + 1] == SYM OR
// -> )
// true check = 1

// 3. if true check == 1
// -> result += sum
// 4. if true check == 0
// -> sum = 0
// 5. true check = 0
// 6. iterate to next string and repeat until all arguments are done
// 7. return value is res

// new idea:
// 1. parse whole input into char **str
// 2. only modify dots to 0, letters 1, symbols 2
// 3. use same idea as above to count if some pair adds up to 3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

#define MAX 15
#define INF 9999

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

int check_plus(char **map, int x, int y, int n, int m)
{
    int i = 1;
    if ((x + 1 < n) && (map[x + 1][y] == '+'))
        return 1;
    if ((x - 1 >= 0) && (map[x - 1][y] == '+'))
        return 1;
    if ((y + 1 < m) && (map[x][y + 1] == '+'))
        return 1;
    if ((x - 1 >= 0) && (map[x][y - 1] == '+'))
        return 1;
    if ((x - 1 >= 0) && (y - 1 >= 0) && (map[x - 1][y - 1] == '+'))
        return 1;
    if ((x - 1 >= 0) && (y + 1 < m) && (map[x - 1][y + 1] == '+'))
        return 1;
    if ((x + 1 < n) && (y - 1 >= 0) && (map[x + 1][y - 1] == '+'))
        return 1;
    if ((x + 1 < n) && (y + 1 < m) && (map[x + 1][y + 1] == '+'))
        return 1;
    return 0;
    

}

void solve_map(char **map, int n, int start) 
{
    int i = 0;
    int j = 0;
    bool legit = false;
    int m = 0;
    int res = 0;
    int tempres = 0;

    m = strlen(map[0]);

    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            while (isdigit(map[i][j]))
            {
                if (tempres > 0)
                    tempres *= 10;
                tempres += map[i][j] - '0';
                if (check_plus(map, i, j, n, m) == 1)
                    legit = true;
                j++;
            }
            if (legit == true)
                res += tempres;
//            printf("res: %d\n", res);
            tempres = 0;
            legit = false;
            j++;
        }
        i++;
    }
    printf("res: %d\n", res);

}

char *parser(char *line)
{
    char *new;
    int i = 0;
    int n = strlen(line);

    new = (char *)malloc(sizeof(char) * n + 1);
    while (i < n)
    {
        if(line[i] != '.')
        {
            if (isdigit(line[i]))
                new[i] = line[i];
            else if (isprint(line[i]))
                new[i] = '+';
            else
                new[i] = line[i];
        }
        else
            new[i] = '.';
        i++;
    }
    new[i] = '\0';
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
    char    *map[141] = {0};

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
    solve_map(map, current, 0);
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}