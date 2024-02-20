#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct brick
{
    long destination;
    long start;
    long range;
    long end;
    long offset;
} brick;

typedef struct seeds
{
    long start;
    long len;
    long end;
} seeds;

int slot;
long deeds[100];
long rangemax;
long rangemin;
seeds *seedarr[100];
brick *seedtosoil[100];
brick *soiltofert[100];
brick *ferttowater[100];
brick *watertolight[100];
brick *lighttotemp[100];
brick *temptohumid[100];
brick *humidtoloc[100];

long    phases(long seed)
{
    int x = 0;
    while (seedtosoil[x])
    {
        if ((seed >= seedtosoil[x]->start) && (seed <= seedtosoil[x]->end))
        {
            seed += seedtosoil[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of soil: %ld\n", seed);
    x = 0;
    while (soiltofert[x])
    {
        if ((seed >= soiltofert[x]->start) && (seed <= soiltofert[x]->end))
        {
            seed += soiltofert[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of fert: %ld\n", seed);
    x = 0;
    while (ferttowater[x])
    {
        if ((seed >= ferttowater[x]->start) && (seed <= ferttowater[x]->end))
        {
            seed += ferttowater[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of water: %ld\n", seed);
    x = 0;
    while (watertolight[x])
    {
        if ((seed >= watertolight[x]->start) && (seed <= watertolight[x]->end))
        {
            seed += watertolight[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of light: %ld\n", seed);
    x = 0;
    while (lighttotemp[x])
    {
        if ((seed >= lighttotemp[x]->start) && (seed <= lighttotemp[x]->end))
        {
            seed += lighttotemp[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of temp: %ld\n", seed);
    x = 0;
    while (temptohumid[x])
    {
        if ((seed >= temptohumid[x]->start) && (seed <= temptohumid[x]->end))
        {
            seed += temptohumid[x]->offset;
            break;
        }
        x++;
    }
//    printf("value of humid: %ld\n", seed);
    x = 0;
    while (humidtoloc[x])
    {
        if ((seed >= humidtoloc[x]->start) && (seed <= humidtoloc[x]->end))
        {
            seed += humidtoloc[x]->offset;
            break;
        }
        x++;
    }
    return seed;
}

long solve()
{
    int i = 0;
    long res = INT64_MAX;
    long s = 0;
    long e = 0;
    long hold = 0;
    printf("in solve\n");
    while(seedarr[i])
    {
        printf("Saved seeds on array:\n");
        printf("seed[%d]\nstart: %ld - end: %ld\n", i, seedarr[i]->start, seedarr[i]->end);
        i++;
    }
    i = 0;
    // we would need to apply for whole range of the seeds instead at the time..
    while (seedarr[i])
    {
        s = seedarr[i]->start;
        e = seedarr[i]->end;
        printf("iterating seeds: %ld -> %ld\n", s, e);
        while (s <= e)
        {
            if (s >= rangemin && s <= rangemax)
                hold = phases(s);
            if (hold < res)
                res = hold;
            s++;
        }
        printf("SEEDSET %d DONE\n", i);
        i++;
    }
    return (res);
}

seeds *createseed(long start, long len)
{
    printf("in createseed\n");
    seeds *new;

    new = malloc(sizeof(seeds));
    new->len = len;
    new->start = start;
    new->end = len + start;
    return new;
}

void part2seeds(int i)
{
    printf("in part2seed\n");
    int j = 0;
    int x = 0;
    long start = 0;
    long len = 0;
    seeds seed;

    while (x < i)
    {
        start = deeds[x];
        len = deeds[x + 1];
        seedarr[j] = createseed(start, len);
        printf("seed[%d] created\n", j);
        j++;
        x += 2;
    }
}

void saveseeds(char *str)
{
    printf("in saveseeds\n");
    char    *token;
    char    *token2;
    int     i = 0;

    while ((token = strtok_r(str, ":", &str)) != NULL)
    {
        while ((token2 = strtok_r(token, " ", &token)) != NULL)
        {
            if (isdigit(token2[1]))
            {
                deeds[i] = atol(token2);
                //printf("deed added %d: %ld\n", i, deeds[i]);
                i++;
            }
        }
    }
    //printf("1\n");
    part2seeds(i);
}

void add_brick(char *str, int phase)
{
    brick *new;
    new = (brick *)malloc(sizeof(brick));
    char *token;

    token = strtok_r(str, " ", &str);
        new->destination = atol(token);
    token = strtok_r(str, " ", &str);
        new->start = atol(token);
    token = strtok_r(str, " ", &str);
        new->range = atol(token);
    new->end = new->start + new->range;
    new->offset = new->destination - new->start;
    if (new->start < rangemin)
        rangemin = new->start;
    if (new->end > rangemax)
        rangemax = new->end;
    if (phase == 2)
    {
        seedtosoil[slot] = new;
    }
    else if (phase == 3)
    {
        soiltofert[slot] = new;
    }
    else if (phase == 4)
    {
        ferttowater[slot] = new;
    }
    else if (phase == 5)
    {
        watertolight[slot] = new;
    }
    else if (phase == 6)
    {
        lighttotemp[slot] = new;
    }
    else if (phase == 7)
    {
        temptohumid[slot] = new;
    }
    else if (phase == 8)
    {
        humidtoloc[slot] = new;
    }
    printf("New brick added to slot: %d - phase: %d\ndest: %ld, start: %ld, range %ld\n", slot, phase, new->destination, new->start, new->range);
    printf("range ends: %ld - offset: %ld\n\n", new->end, new->offset);

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
                //printf("\n\n");
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
    long     result = 0;
    int     current = 0;
    int     phase = 0;

    rangemax = INT64_MIN;
    rangemin = INT64_MAX;

    if (argc < 2)
    {
        //printf("nono");
        return -1;
    }
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        //printf("file missing, ono");
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
    printf("result: %ld\n", result);
    return result;
 
}

