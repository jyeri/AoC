#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>

typedef struct
{
    int     index;
    char    id[4];
    char    L[4];
    int     Lid;
    char    R[4];
    int     Rid;
    bool    end;
    bool    start;
} room;

int navigate(room *network, char *inst, int limit, int starts)
{
    int i = 0;
    int res = 0;
    int x = 0;
    int j = 0;
    int *x_arr = (int *)malloc(sizeof(int) * starts);
//    printf("68: %d, 69: %d, 70: %d, 71: %d, 72: %d\n", inst[268], inst[269], inst[270], inst[271], inst[272]);

    while(x < limit)
    {
        while (strcmp(network[x].L, network[i].id))
            i++;
        network[x].Lid = network[i].index;
//        printf("%s Lid: %d\n", network[x].id, network[i].index);
        i = 0;
        while (strcmp(network[x].R, network[i].id))
            i++;
        network[x].Rid = network[i].index;
        if (network[x].start == true)
        {
            x_arr[j] = network[x].index;
            j++; 
        }
//        printf("%s Rid: %d\n", network[x].id, network[i].index);
        x++;
        i = 0;
    }
    printf("\n LAST X: %d \n", x);
    printf("network[700].id: %s, network[701].id: %s, network[702].id: %s\n",
    network[700].id, network[701].id, network[702].id);
    j = 0;
    printf("\n STARTS: \n");
    while(j < starts)
    {
        printf("x[%d] = %s \n", j, network[x_arr[j]].id);
        j++;
    }
    sleep (1);
    x = 0;
    j = 0;
    i = 0;
    while(1)
    {
//        printf("current inst[%d]: %c\n", i, inst[i]);
//        printf("%s ->", network[x].id);
        if (inst[i] == 'L')
        {
            while(j < starts)
            {
                x_arr[j] = network[x_arr[j]].Lid;
//                printf("x[%d] = %s \n", j, network[x_arr[j]].id);
                j++;
            }
            res++;
        }
        if (inst[i] == 'R')
        {
            while (j < starts)
            {
                x_arr[j] = network[x_arr[j]].Rid;
//                printf("x[%d] = %s \n", j, network[x_arr[j]].id);
                j++;
            }
            res++;
        }
        j = 0;
        if (network[x_arr[j]].end == true)
        {
            while (network[x_arr[j]].end == true)
            {
                if (j == starts - 2)
                    return res;
                j++;
            }
            j = 0;
//            printf("\n Current end points: \n");
//            while (j < starts)
//            {
//                printf("x[%d] = %s \n", j, network[x_arr[j]].id);
//                j++;
//            }
//            j = 0;
//            sleep (2);
        }
        i++;
        if (i == strlen(inst))
        {
            i = 0;
        }
//        if (res > 100000)
//            break;
//        printf("loop nro %d\n", res);
    }
    return res;
}

char *removeid(char *str)
{
    char *cp;
    int x = 0;
    int i = 0;

    cp = (char *)malloc(sizeof(char) * strlen(str) + 1);

    while(str[x] != '\n')
    {
        cp[i] = str[x];
        i++;
        x++;
    }
    cp[i] = '\0';
    return cp;

}

room parser(int id, char *line)
{
//   printf("working on line: %s\n", line);
    char *cpy;
    char *afterid;
    char *aftersemi;
    room new;
    new.index = id;
    int     i = 0;
    int     x = 0;
    memcpy(new.id, line, 3);
    new.id[3] = '\0';
    new.end = false;
    new.start = false;
    if (new.id[2] == 'Z')
    {
        new.end = true;
        printf("end.id: %s \n", new.id);
    }
    if (new.id[2] == 'A')
    {
        new.start = true;
        printf("start.id: %s \n", new.id);
    }
    while (line[x] != '(')
    {
        x++;
    }
    x++;
    memcpy(new.L, &line[x], 3);
    new.L[3] = '\0';
//    printf("-> new.L: %s \n", new.L);
    while (line[x] != ',')
    {
        x++;
    }
    x += 2;
    memcpy(new.R, &line[x], 3);
    new.R[3] = '\0';
//    printf("-> new.R: %s \n", new.R);
    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    room    network[1000];
    int     instsaved = 0;
    char    *inst;
    int     starts;

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
        if (instsaved == 0)
        {
            inst = (char *)malloc(sizeof(char) * strlen(line) + 1);
            inst = removeid(line);
            instsaved = 1;
        }
        else if (!(strcmp(line, "\n")))
        {
            current = 0;
        }
        else
        {
            network[current] = parser(current, line);
            if (network[current].start == true)
                starts++;
            current++;
        }
    }
    fclose(fptr);
    
    printf("inst: %s\ninslen: %lu\n", inst, strlen(inst));
    result = navigate(network, inst, current, starts);
    printf("result: %d\n", result);
    return result;
 
}

