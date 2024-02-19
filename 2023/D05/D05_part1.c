#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct brick
{
    int destination;
    int start;
    int range;
} brick;

int seeds[100];
int slot;
brick *seedtosoil[100];
brick *soiltofert[100];
brick *ferttowater[100];
brick *watertolight[100];
brick *lighttotemp[100];
brick *temptohumid[100];
brick *humidtoloc[100];

int solve()
{
    int i = 0;
    int x = 0;
    int value = 0;
    while(seeds[i])
    {
        value = seeds[i];
        while (seedtosoil[x])
        {
            if (value )
        }
    }
    return res;
}

void saveseeds(char *str)
{
    char    *token;
    char    *token2;
    int     i = 0;

    while ((token = strtok_r(str, ":", &str)) != NULL)
    {
        while ((token2 = strtok_r(token, " ", &token)) != NULL)
        {
            if (isdigit(token2[1]))
            {
                seeds[i] = atoi(token2);
                printf("seed added %d: %d\n", i, seeds[i]);
                i++;
            }
        }
    }
}

void add_brick(char *str, int phase)
{
    brick *new;
    new = (brick *)malloc(sizeof(brick));
    char *token;

    token = strtok_r(str, " ", &str);
        new->destination = atoi(token);
    token = strtok_r(str, " ", &str);
        new->start = atoi(token);
    token = strtok_r(str, " ", &str);
        new->range = atoi(token);
    if (phase == 2)
        seedtosoil[slot] = new;
    else if (phase == 3)
        soiltofert[slot] = new;
    else if (phase == 4)
        ferttowater[slot] = new;
    else if (phase == 5)
        watertolight[slot] = new;
    else if (phase == 6)
        lighttotemp[slot] = new;
    else if (phase == 7)
        temptohumid[slot] = new;
    else if (phase == 8)
        humidtoloc[slot] = new;
    printf("New brick added to slot: %d - phase: %d\ndest: %d, start: %d, range %d\n", slot, phase, new->destination, new->start, new->range);

}

int parser(char *line, int phase)
{

    if (phase == 0)
    {
        saveseeds(line);
        phase++;
    }
    else
    {
        if (isdigit(line[0]))
        {
            add_brick(line, phase);
            slot++;
        }
        else
        {
            if (isalpha(line[0]) != 0)
            {
                phase++;
                slot = 0;
                printf("\n\n");
            }
            return phase;
        }
    }

    return phase;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    int     phase = 0;

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
    slot = 0;
    while (fgets(line, sizeof(line), fptr))
    {
        current++;
        phase = parser(line, phase);
    }
    fclose(fptr);
    
    result = solve();
    printf("result: %d\n", result);
    return result;
 
}

