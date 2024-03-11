#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

char *parser(char *line)
{
    char *map;
    
    map = strdup(line);
    return map;
}

int main(int argc, char **argv)
{
    FILE    *fptr;
    long    result = 0;
    long    total = 0;
    int     c = 0;

// today we solve only one line so no need for parsing. ill use getc func again
// and seems like it bit in the ass on part 2:)))

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
    while (!(feof(fptr)))
    {
        // get next char int value from file
        c = fgetc(fptr);

        if(c == ',' || c == EOF)
        {
            printf("res: %ld\n", result);
            total += result;
            result = 0;
        }
        else
        {
            result += c;
            result *= 17;
            result %= 256;
        }
    }
    printf("%ld\n", total);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}