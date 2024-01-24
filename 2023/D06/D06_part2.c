#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

// quadratic equation

// remember to take negatives
// ceil is time - sqrt(pow(time, 2) + 4 * 1 * record/2)
// floor is time + sqrt(pow(time, 2) + 4 * 1 * record/2)

// then win amount is = ceil(ceil) - floor(floor) + 1

char distance[100];
char time[100];

long solve()
{
    long int res = 1;
    long int i = 0;
    long int race_res = 0;
    double highs = 0.0;
    double lows = 0.0;

    double timer = (double) atol(time);
    double distancer = (double) atol(distance);
    printf("time as ld: %f, dist as ld : %f\n", timer, distancer);
    highs = (-timer - sqrt(pow(timer, 2) + (-4.0) * (-1.0) * (-distancer)))/-2.0;
    lows = (-timer + sqrt(pow(timer, 2) + (-4.0) * (-1.0) * (-distancer)))/-2.0;
//  printf ("highs: %f, lows %f\n", highs, lows);
    race_res = (int) ((ceil(highs)) - (floor(lows) + 1));
    printf ("\nrace %ld: %f %f %ld\n", i, ceil(highs), floor(lows) + 1, race_res);
    i++;
    res *= race_res;
    printf("final: %ld\n", res);
    return res;
}

char *parser(char *line)
{
    char *new;
    char *tok1;
    char *tok2;
    int i = 0;
    int mode = 0;

    new = strdup(line);
//    printf("%s\n", new);
    if (new[0] == 'T')
        mode = 1;
    while ((tok1 = strtok_r(new, ":", &new)))
    {
        if (mode == 1)
        {
            while ((tok2 = strtok_r(tok1, " ", &tok1)))
            {
//                printf("tok: %s\n", tok2);
                if (isdigit(tok2[0]))
                {
                    strcat(time, tok2);
                    printf("time[%d]: %s\n", i, time);
                }
            }
        }
        else
        {
            while ((tok2 = strtok_r(tok1, " ", &tok1)))
            {
//                printf("tok: %s\n", tok2);
                if (isdigit(tok2[0]))
                {
                    strcat(distance, tok2);
                    printf("distance[%d]: %s\n", i, distance);
                }
            }
        }
    }
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
        parser(line);
        current++;
    }
    result = solve();
    fclose(fptr);
    return result;
 
}