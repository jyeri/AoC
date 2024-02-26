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

// biggest regret of the whole shit.
// i did not realise that the input is mixed order -> rules are not following the x->m->a->s path
// redo the input parse and add some kind of mechanig to check what rule is first to be checked.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

struct Room *roomarray[100000];
long result;
int counter;

typedef struct Rule
{
    char    c;
    char    op;
    int     value;
    int     dest;

} Rule;

typedef struct Room
{
    char    *name;
    int     hash;
    Rule    *rules;
    int     finald;

} Room;


int hash(char *str)
{
    if (strcmp(str, "A") == 0)
        return 0;
    if (strcmp(str, "R") == 0)
        return 99999;

    unsigned int hash = 0;
    while (*str != '\0')
    {
        hash *= 25;
        hash += (*str++);
    }
    if (hash < 5000)
        hash -= 2545;
    else
        hash -= 63200;
    return hash;
}

void add_room(char *str, int hashed)
{
    Room *new;
    new = (Room *)malloc(sizeof(Room));
    new->name = strdup(str);
    new->hash = hashed;
    new->finald = -1;
    printf("added room: %s - %d\n", new->name, new->hash);
}

void add_rules(unsigned int index, char *str, int order_num)
{
    char *token;
    char *token2;
    
    while(token = (strtok_r(str, ":", &str)))
    {
        if (token[1] == '>')
        {
            // FIX THIS SYNTAX AND STRUCT
            roomarray[index]->rules[order_num]->op
        }
        
    }
}

void solve(int x, int m, int a, int s, int room)
{

}

int parser(char *line, int phase)
{
    char *new;
    char *token;
    char *token2;
    int hashed = 0;
    int counter = 0;
    int i = 0;
    int x = 0;
    int m = 0;
    int a = 0;
    int s = 0;
    int order_num = 0;

    new = strdup(line);
//    printf("%s", new);
    if (line[0] == '\n')
    {
        printf("SOS\n");
        return 1;
    }
    else if (phase == 0)
    {
        while ((token = (strtok_r(line, "{", &line))) != NULL)
        {
            hashed = hash(token);
            add_room(token, hashed);
            while((token2 = (strtok_r(line, ",", &line))) != NULL)
            {
                printf("token2: %s\n", token2);
                add_rules(hashed, token2, order_num);
                order_num++;
            }
        }
    }
    else
    {
        counter = 0;
        while ((token = (strtok_r(line, ",", &line))) != NULL)
        {
            i = 0;
            while (token[i] != '=' && token[i])
            {
                i++;
            }
            i++;
            if (counter == 0)
            {
                x = atoi(&token[i]);
                counter++;
            }
            else if (counter == 1)
            {
                m = atoi(&token[i]);
                counter++;
            }
            else if (counter == 2)
            {
                a = atoi(&token[i]);
                counter++;
            }
            else if (counter == 3)
            {
                s = atoi(&token[i]);
                counter++;
            }
        }
//        printf("solve values\nx: %d - m: %d - a: %d -  s: %d\n\n", x, m, a, s);
//        solve(x, m, a, s, hash("in"));
    }
    return phase;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;
    long     total = 0;
    int     phase = 0;
    counter = 0;

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
        phase = parser(line, phase);
        current++;;
    }
//    printf("\n\n");
    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}