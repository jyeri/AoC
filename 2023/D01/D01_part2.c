#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

char isdigitword(char *line)
{
//    printf("checking words from: %s\n", line);
    char ret = '\0';
    if (strstr(line, "one"))
        ret = '1';
    else if (strstr(line, "two"))
        ret = '2';
    else if (strstr(line, "three"))
        ret = '3';
    else if (strstr(line, "four"))
        ret = '4';
    else if (strstr(line, "five"))
        ret = '5';
    else if (strstr(line, "six"))
        ret = '6';
    else if (strstr(line, "seven"))
        ret = '7';
    else if (strstr(line, "eight"))
        ret = '8';
    else if (strstr(line, "nine"))
        ret = '9';
    return ret;
}

char firstnum(char *line)
{
    char ret;
    int x = 0;
    ret = '\0';
    char memline[65];

    while (x < strlen(line) && ret == '\0')
    {
        memcpy(memline, line, x + 1);
        if (x > 2 && isdigitword(memline))
            ret = isdigitword(memline);
        else if (isdigit(line[x]))
            ret = line[x];
        x++;
        memset(memline, '\0', x);
    }
//    printf("First num: %c", ret);
    return ret;
}

char lastnum(char *line)
{
    char ret;
    int x;
    ret = '\0';
    x = strlen(line);
    int len = strlen(line);
    char memline[65];
    int count = 0;

    while (x >= 0 && ret == '\0')
    {
        memcpy(memline, &line[x], count++);
        if (count > 2 && isdigitword(memline))
            ret = isdigitword(memline);
        else if (isdigit(line[x]))
            ret = line[x];
        x--;
        memset(memline, '\0', count);
    }
//    printf(" last num: %c", ret);
    return ret;
}

int main(int argc, char **argv)
{
    char    *line;
    FILE    *fptr;
    char    values[2];
    int     result = 0;
    int     linec = 1;

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
        printf("\n%d: %s\n",linec, line);
        values[0] = firstnum(line);
        values[1] = lastnum(line);
        printf("Adding: %d \n", atoi(values));
        result += atoi(values);
        linec++;
//        printf("\n\n");
//        sleep(1);
    }
    fclose(fptr);
    free(line);
    
    printf("%d\n", result);
    return result;
 
}

