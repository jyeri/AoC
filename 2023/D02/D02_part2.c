// INPUT: Many strings, containing multiple instances, divided by ;
// OUTPUT: Sum of id's of the games are less
// order of op:
// 1. split string 1 ';'
// 2. read all substrings
// 3. store and update max value of each color
// 4. check if its doable
// 5. if yes
// -> res += id
// 6. max values = 0, and redo for the next ID (String)
// 7. when all ID's done, return res.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

typedef struct
{
    int id;
    int red;
    int blue;
    int green;
} colors;

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

colors parser(int id, char *line)
{
//    printf("\nworking on line: %s\n", line);
    char *cpy;
    char *afterid;
    char *aftersemi;
    colors new;
    int mred = 0;
    int cred = 0;
    int mgre = 0;
    int cgre = 0;
    int mblu = 0;
    int cblu = 0;

    cpy = strdup(line);
    char *token;
    char *token2;
    new.id = id + 1;

	// Take off the 'Game x:' part.
    cpy = removeid(cpy);
//    printf("now: %s\n", cpy);
    while ((token = strtok_r(cpy, ";", &cpy)) != NULL)
    {
//        printf("tok1: %s\n", token);
        while ((token2 = strtok_r(token, ",", &token)) != NULL)
        {
//            printf("tok2: %s\n", token2);
            if (strstr(token2, "red"))
            {
                cred = getval(token2, "red");
                if (cred > mred)
                {
                    mred = cred;
                }
            }
            if (strstr(token2, "green"))
            {
                cgre = getval(token2, "green");
                if (cgre > mgre)
                {
                    mgre = cgre;
                }
            }
            if (strstr(token2, "blue"))
            {
                cblu = getval(token2, "blue");
                if (cblu > mblu)
                {
                    mblu = cblu;
                }
            }
        }
    }
    new.red = mred;
    new.green = mgre;
    new.blue = mblu;
    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    char    values[2];
    int     result = 0;
    int     MAXR = 0;
    int     MAXB = 0;
    int     MAXG = 0;
    int     current = 0;
    int     thisgame = 0;
    colors  clr[124];

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
        clr[current] = parser(current, line);
        thisgame = (clr[current].red * clr[current].blue * clr[current].green);
        result += thisgame;
        printf("result is now: %d\n", result);
        thisgame = 0;
        current++;
    }
    fclose(fptr);
    
    printf("result: %d\n", result);
    return result;
 
}

