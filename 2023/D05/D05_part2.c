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
} brick;

long deeds[100];
long seeds[100];
long seedse[100];
long seedtosoil_max;
long soiltofert_max;
long ferttowater_max;
long watertolight_max;
long lighttotemp_max;
long temptohumid_max;
long humidtoloc_max;
long maxilimian;
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
    int k = 0;
    int amount;
    long res = INT64_MAX;
    long value = 0;
    while(seeds[i])
    {
        amount = seedse[i];
        k = 0;
        while(amount--)
        {
            value = seeds[i] + k;
            if (value > maxilimian)
                break;
            else
            {
                if (value < seedtosoil_max)
                //printf("value of seed[%d]: %ld\n", i, value);
                {
                    while (seedtosoil[x])
                    {
                        if ((value > seedtosoil[x]->start) && (value < (seedtosoil[x]->start + seedtosoil[x]->range)))
                        {
//                            //printf("seedtosoil[%d]: %d\ndest: %d, start: %d, range: %d\n", x, seeds[i], seedtosoil[x]->destination, seedtosoil[x]->start, seedtosoil[x]->range);
                            value += seedtosoil[x]->destination - seedtosoil[x]->start;
                            break;
                        }
                        x++;
                    }
                }
                //printf("value of soil: %ld\n", value);
                x = 0;
                if (value < soiltofert_max)
                {
                    while (soiltofert[x])
                    {
                        if ((value >= soiltofert[x]->start) && (value <= (soiltofert[x]->start + soiltofert[x]->range)))
                        {
                            value += soiltofert[x]->destination - soiltofert[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of fert: %ld\n", value);
                }
                x = 0;
                if (value < ferttowater_max)
                {
                    while (ferttowater[x])
                    {
                        if ((value >= ferttowater[x]->start) && (value <= (ferttowater[x]->start + ferttowater[x]->range)))
                        {
                            value += ferttowater[x]->destination - ferttowater[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of water: %ld\n", value);
                }
                x = 0;
                if (value < watertolight_max)
                {
                    while (watertolight[x])
                    {
                        if ((value >= watertolight[x]->start) && (value <= (watertolight[x]->start + watertolight[x]->range)))
                        {
                            value += watertolight[x]->destination - watertolight[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of light: %ld\n", value);
                }
                x = 0;
                if (value < lighttotemp_max)
                {
                    while (lighttotemp[x])
                    {
                        if ((value >= lighttotemp[x]->start) && (value <= (lighttotemp[x]->start + lighttotemp[x]->range)))
                        {
                            value += lighttotemp[x]->destination - lighttotemp[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of temp: %ld\n", value);
                }
                x = 0;
                if (value < temptohumid_max)
                {
                    while (temptohumid[x])
                    {
                        if ((value >= temptohumid[x]->start) && (value <= (temptohumid[x]->start + temptohumid[x]->range)))
                        {
                            value += temptohumid[x]->destination - temptohumid[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of humid: %ld\n", value);
                }
                x = 0;
                if (value < humidtoloc_max)
                {
                    while (humidtoloc[x])
                    {
                        if ((value >= humidtoloc[x]->start) && (value <= (humidtoloc[x]->start + humidtoloc[x]->range)))
                        {
                            value += humidtoloc[x]->destination - humidtoloc[x]->start;
                            break;
                        }
                        x++;
                    }
                    //printf("value of loc: %ld\n\n", value);
                }
                x = 0;
            }
            if (res > value)
                res = value;
            k++;
        }
        i++;
    }
    return res;
}

void part2seeds(int i)
{
    int x = 0;
    long amount = 0;
    int j = 0;
    while (x < i)
    {
        seeds[j] = deeds[x];
        seedse[j] = deeds[x + 1];
        x += 2;
        j++;
    }
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
    if (phase == 2)
    {
        seedtosoil[slot] = new;
        if (seedtosoil_max < new->start + new->range)
            seedtosoil_max = new->start + new->range;
    }
    else if (phase == 3)
    {
        soiltofert[slot] = new;
        if (soiltofert_max < new->start + new->range)
            soiltofert_max = new->start + new->range;
    }
    else if (phase == 4)
    {
        ferttowater[slot] = new;
        if (ferttowater_max < new->start + new->range)
            ferttowater_max = new->start + new->range;
    }
    else if (phase == 5)
    {
        watertolight[slot] = new;
        if (ferttowater_max < new->start + new->range)
            ferttowater_max = new->start + new->range;
    }
    else if (phase == 6)
    {
        lighttotemp[slot] = new;
        if (watertolight_max < new->start + new->range)
            watertolight_max = new->start + new->range;
    }
    else if (phase == 7)
    {
        temptohumid[slot] = new;
        if (temptohumid_max < new->start + new->range)
            temptohumid_max = new->start + new->range;
    }
    else if (phase == 8)
    {
        humidtoloc[slot] = new;
        if (humidtoloc_max < new->start + new->range)
            humidtoloc_max = new->start + new->range;
    }
    if (new->start + new->range > maxilimian)
        maxilimian = new->start + new->range;
//    //printf("New brick added to slot: %d - phase: %d\ndest: %ld, start: %ld, range %ld\n", slot, phase, new->destination, new->start, new->range);

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
    int     result = 0;
    int     current = 0;
    int     phase = 0;
    maxilimian = 0;

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
    printf("result: %d\n", result);
    return result;
 
}

