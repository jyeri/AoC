#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < n - 1; i++) 
    { 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[min_idx]) 
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]); 
    } 
} 


int getval(char *token, char *color)
{
    char    *pnt;
    char    strclr[4];
    int     val = 0;

    pnt = strstr(token, color);
    if (pnt)
    {
        sscanf(token, "%s ", strclr);
        val = (int)strtol(strclr, NULL, 10);
//        printf("val: %d\n", val);
    }
    return val;
}

char *removeid(char *str)
{
    char *cp;
    int x = 0;
    int i = 0;

    cp = (char *)malloc(sizeof(char) * strlen(str) + 1);
    while(str[x] != ':')
        x++;
    x += 2;
    while(str[x])
    {
        cp[i] = str[x];
        i++;
        x++;
    }
    cp[i] = '\0';
    return cp;

}

int comparestrings(int *my, int *given)
{
    selectionSort(my, 10);
    selectionSort(given, 25);
    int i = 0;
    int j = 0;
    int res = 0;
    int bounty = 1;
    int interval = 0;

    while (my[i] && given[j])
    {
//        printf("comparing my[%d]: %d = giv[%d]: %d\n", i, my[i], j, given[j]);
        if (my[i] == given[j])
        {
            res += bounty;
            interval++;
            if (res > 1)
            {
                bounty = bounty * 2;
                interval = 0;
            }
            i++;
            j++;
        }
        else if (my[i] > given[j])
        {
            j++;
        }
        else
            i++;
    }
//    printf("compare result: %d\n", res);
    return res;
}

int parser(char *line)
{
//    printf("\nworking on line: %s\n", line);
    char *cpy;
    char *afterid;
    char *aftersemi;
    int res = 0;
    int change = 0;

    cpy = strdup(line);
    char *token;
    char *token2;
    int *my;
    int *given;
    int x = 0;

    given = (int *)malloc(sizeof(int) * 25);
    my = (int *)malloc(sizeof(int) * 10);

	// Take off the 'Game x:' part.
    cpy = removeid(cpy);
//    printf("now: %s\n", cpy);
    while ((token = strtok_r(cpy, "|", &cpy)) != NULL)
    {
//        printf("token: %s\n", token);
        x = 0;
        if (change == 1)
        {
            while ((token2 = strtok_r(token, " ", &token)) != NULL)
            {
                given[x] = atoi(token2);
//                printf("given[%d]: %d\n", x, given[x]);
                x++;
            }
            change--;
        }
        if (change == 0)
        {
            while ((token2 = strtok_r(token, " ", &token)) != NULL)
            {
                my[x] = atoi(token2);
//                printf("my[%d]: %d\n", x, my[x]);
                x++;
            }
            change++;
        }
    }
    res = comparestrings(my, given);

    return res;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;

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
        result += parser(line);
    }
    fclose(fptr);
    
    printf("result: %d\n", result);
    return result;
 
}

