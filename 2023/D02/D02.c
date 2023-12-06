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

int main(int argc, char **argv)
{
    char    *line;
    FILE    *fptr;
    char    values[2];
    int     result = 0;
    int     id = 0;
    int     red = 0;
    int     blue = 0;
    int     green = 0;

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
        while (*line != ':')
            id = get_id(line);
        red = get_red(&line);
        green = get_green(&line);
        blue = get_blue(&line);
        if (13 > red && 14 > green && 15 > blue)
            result += id;
        printf("result is now: %d\n", result);
        id = 0;
        red = 0;
        green = 0;
        blue = 0;
//        sleep(1);
    }
    fclose(fptr);
    free(line);
    
    printf("result: %d\n", result);
    return result;
 
}

