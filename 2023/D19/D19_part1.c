// First approach:
// we take the input until new line, and go to it line by line
// we allocate somekind of global array, that each hold the rules
// since their name is 3 char long, im thinking about hashing the array, so they are possible to find in reasonable time.
// -> this array would nee to be atleast 1500 pointers long
// -> each pointer has to hold 1 to 4 different rules
//      -> rules are divided by ','
//      -> rules them self consist 'x', 'm', 'a' or 's'
//      -> followed by operator
//      -> followed by integer
//      -> after that splitter ':' and destination if rule is true
// this makes me think it could be struct that has 
//      -> char *name
//      -> int x, m, a, s
//      -> char opx, opm, opa, ops
//      -> int(hashed) dx, dm, da, ds (these are the possible destinations for passed rule)
//      -> int final dest (if none of the rules match)

// then it could just something like global variable as rules *ruleset[2000]
// we just have to also make sure that if destination is A or R we return accordingly instantly

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>


rules *ruleset[2000];

typedef struct rules
{
    char *name;
    int x[4];
    int m[4];
    int a[4];
    int s[4];
    char opx[1];
    char opm[1];
    char opa[1];
    char ops[1];
    int dx[4];
    int dm[4];
    int da[4];
    int ds[4];
    int finald[4];

} rules;

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void add_rule(char *str)
{
    rules *new;
    new = (rules *)malloc(sizeof(rules));
    new->name = str;
    ruleset[hash(str)] = new;
}

char *parser(char *line)
{
    char *new;

    new = strdup(line);
//    printf("%s", new);
    return new;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    long     total = 0;

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
        parser(line);
        current++;;
    }
//    printf("\n\n");
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}