// INPUT: Multiple lines of strings, mixed with alpha and numbers
// OUTPUT: Sum of first and last digit(check if 10 is counted or only 1) of each line
// EXECUTION:
// 1. iterate array x(starting from 1st) from front until digit, then again from end
// 2. add this value always to last combined result
// 3. keep repeating until we have gone thru whole input
// 4. return the combined sum we have gotten

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

char firstnum(char *line)
{
    char ret;
    int x = 0;
    ret = '\0';

    while (x < strlen(line) && ret == '\0')
    {
        if (isdigit(line[x]))
            ret = line[x];
        x++;
    }
    printf("First num: %c", ret);
    return ret;
}

char lastnum(char *line)
{
    char ret;
    int x;
    ret = '\0';
    x = strlen(line);

    while (x >= 0 && ret == '\0')
    {
        if (isdigit(line[x]))
            ret = line[x];
        x--;
    }
    printf(" last num: %c", ret);
    return ret;
}

int main(int argc, char **argv)
{
    char    *line;
    FILE    *fptr;
    char    values[2];
    int     result = 0;

    if (argc < 2)
    {
        printf("nono");
        return -1;
    }
    line = (char *)malloc(sizeof(char) * 64);
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("file missing, ono");
        return -1;
    }
    while (fgets(line, 64, fptr))
    {
        values[0] = firstnum(line);
        values[1] = lastnum(line);
        printf ("   adding: %d\n", atoi(values));
        result += atoi(values);
        printf("result is now: %d\n", result);
//        sleep(1);
    }
    fclose(fptr);
    free(line);
    
    printf("result: %d\n", result);
    return result;
 
}

