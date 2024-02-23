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

struct Rules *ruleset[2000];
long result;

typedef struct Rules
{
    char *name;
    int x;
    int m;
    int a;
    int s;
    bool x_set;
    bool m_set;
    bool a_set;
    bool s_set;
    char opx;
    char opm;
    char opa;
    char ops;
    int dx;
    int dm;
    int da;
    int ds;
    int finald;

} Rules;


unsigned long hash(char *str)
{
	unsigned int hash = 0;
	int c;
    if (strcmp(str, "A") == 0)
    {
//        printf("hash: 0\n");
        return 0;
    }
    if (strcmp(str, "R") == 0)
    {
//        printf("hash: 1999\n");
        return 1999;
    }
    
	while (*str++)
    {
        c = *str;
	    hash += c;
    }
//    printf("hash: %d\n", hash);
	return hash;
}

void add_rule(char *str, int hashed)
{
    struct Rules *new;
    new = (Rules *)malloc(sizeof(Rules));
    new->name = strdup(str);
    new->x_set = false;
    new->m_set = false;
    new->a_set = false;
    new->s_set = false;
    ruleset[hashed] = new;
}

void add_values(unsigned int index, char *str)
{
    char *token;
    char *token2;
    int happy = 0;

    while ((token = (strtok_r(str, ":", &str))) != NULL)
    {
        if (token[1] == '>' || token[1] == '<')
        {
            if(token[0] == 'x')
            {
                happy = 1;
                ruleset[index]->opx = token[1];
                ruleset[index]->x = atoi(&token[2]);
                ruleset[index]->x_set = true;
            }
            if(token[0] == 'm')
            {
                happy = 2;
                ruleset[index]->opm = token[1];
                ruleset[index]->m = atoi(&token[2]);
                ruleset[index]->m_set = true;
            }
            if(token[0] == 'a')
            {
                happy = 3;
                ruleset[index]->opa = token[1];
                ruleset[index]->a = atoi(&token[2]);
                ruleset[index]->a_set = true;
            }
            if(token[0] == 's')
            {
                happy = 4;
                ruleset[index]->ops = token[1];
                ruleset[index]->s = atoi(&token[2]);
                ruleset[index]->s_set = true;
            }
        }
        else if (happy > 0)
        {
            if (happy == 1)
                ruleset[index]->dx = hash(token);
            else if (happy == 2)
                ruleset[index]->dm = hash(token);
            if (happy == 3)
                ruleset[index]->da = hash(token);
            if (happy == 4)
                ruleset[index]->ds = hash(token);
            happy = 0;
        }
        else
        {
            ruleset[index]->finald = hash(strtok(token, "}"));
            break;
        }
    }
//    printf("NEW RULE ADDED WITH INDEX %d\n", index);
//    if (ruleset[index]->x_set == true)
//    {
//        printf("X op: %c\n", ruleset[index]->opx);
//        printf("X: %d\n" ,ruleset[index]->x);
//        printf("X dest: %d\n" ,ruleset[index]->dx);
//    }
//    else
//        printf ("X NOT SET\n");
//
//    if (ruleset[index]->m_set == true)
//    {
//        printf("M op: %c\n", ruleset[index]->opm);
//        printf("M: %d\n" ,ruleset[index]->m);
//        printf("M dest: %d\n" ,ruleset[index]->dm);
//    }
//    else
//        printf ("M NOT SET\n");
//
//    if (ruleset[index]->a_set == true)
//    {
//        printf("A op: %c\n", ruleset[index]->opa);
//        printf("A: %d\n" ,ruleset[index]->a);
//        printf("A dest: %d\n" ,ruleset[index]->da);
//    }
//    else
//        printf ("A NOT SET\n");
//
//    if (ruleset[index]->s_set == true)
//    {
//        printf("S op: %c\n", ruleset[index]->ops);
//        printf("S: %d\n" ,ruleset[index]->s);
//        printf("S dest: %d\n" ,ruleset[index]->ds);
//    }
//    else
//        printf ("S NOT SET\n");
}

void solve(int x, int m, int a, int s, int room)
{
    printf("WE ARE AT ROOM %d\n", room);
    if(room == 1999)
    {
        printf("REJECTED\n");
        return;
    }
    else if(room == 0)
    {
        printf("ACCEPTED\n");
        result += x;
        result += m;
        result += a;
        result += s;
        return;
    }
    else
    {
        while (1)
        {
            if (ruleset[room]->x_set == true)
            {
                printf("XXX");
                if (ruleset[room]->opx == '>')
                {
                    if(x > ruleset[room]->x)
                    {
                        solve(x, m, a, s, ruleset[room]->dx);
                        return;
                    }
                }
                else
                {
                    if(x < ruleset[room]->x)
                    {
                        solve(x, m, a, s, ruleset[room]->dx);
                        return;
                    }
                }
            }
            if (ruleset[room]->m_set == true)
            {
                printf("MMM");
                if (ruleset[room]->opm == '>')
                {
                    if(m > ruleset[room]->m)
                    {
                        solve(x, m, a, s, ruleset[room]->dm);
                        return;
                    }
                }
                else
                {
                    if(m < ruleset[room]->m)
                    {
                        solve(x, m, a, s, ruleset[room]->dm);
                        return;
                    }
                }
            }
            if (ruleset[room]->a_set == true)
            {
                printf("AAA");
                if (ruleset[room]->opa == '>')
                {
                    if(a > ruleset[room]->a)
                    {
                        solve(x, m, a, s, ruleset[room]->da);
                        return;
                    }
                }
                else
                {
                    if(a < ruleset[room]->a)
                    {
                        solve(x, m, a, s, ruleset[room]->da);
                        return;
                    }
                }
            }
            if (ruleset[room]->s_set == true)
            {
                printf("SSS");
                if (ruleset[room]->ops == '>')
                {
                    if(s > ruleset[room]->s)
                    {
                        solve(x, m, a, s, ruleset[room]->ds);
                        return;
                    }
                }
                else
                {
                    if(s < ruleset[room]->s)
                    {
                        solve(x, m, a, s, ruleset[room]->ds);
                        return;
                    }
                }
            }
            solve(x, m, a, s, ruleset[room]->finald);
            return;
        }
    }
}

int parser(char *line, int phase)
{
    char *new;
    char *token;
    char *token2;
    int hashed = 0;
    int res = 0;
    int counter = 0;
    int i = 0;
    int x = 0;
    int m = 0;
    int a = 0;
    int s = 0;

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
            printf("ROOM: %s - %d\n", token, hashed);
            add_rule(token, hashed);
            while((token2 = (strtok_r(line, ",", &line))) != NULL)
            {
//                printf("token2: %s\n", token2);
                add_values(hashed, token2);
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
        printf("solve values\nx: %d - m: %d - a: %d -  s: %d\n\n", x, m, a, s);
        solve(x, m, a, s, hash("in"));
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