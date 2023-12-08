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
        parser(current, line);
    }
    fclose(fptr);
    
    printf("result: %d\n", result);
    return result;
 
}

