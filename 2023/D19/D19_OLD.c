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

struct Rules *ruleset[100000];
long result;
int counter;

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
    int order_x;
    int order_m;
    int order_a;
    int order_s;
    int rule_amount;
    int finald;

} Rules;


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

void add_rule(char *str, int hashed)
{
    struct Rules *new;
    new = (Rules *)malloc(sizeof(Rules));
    new->name = strdup(str);
    new->x_set = false;
    new->m_set = false;
    new->a_set = false;
    new->s_set = false;
    new->order_x = INT8_MAX;
    new->order_m = INT8_MAX;
    new->order_a = INT8_MAX;
    new->order_s = INT8_MAX;
    ruleset[hashed] = new;
}

void add_values(unsigned int index, char *str, int order_num)
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
                ruleset[index]->order_x = order_num;
            }
            if(token[0] == 'm')
            {
                happy = 2;
                ruleset[index]->opm = token[1];
                ruleset[index]->m = atoi(&token[2]);
                ruleset[index]->m_set = true;
                ruleset[index]->order_m = order_num;
            }
            if(token[0] == 'a')
            {
                happy = 3;
                ruleset[index]->opa = token[1];
                ruleset[index]->a = atoi(&token[2]);
                ruleset[index]->a_set = true;
                ruleset[index]->order_a = order_num;
            }
            if(token[0] == 's')
            {
                happy = 4;
                ruleset[index]->ops = token[1];
                ruleset[index]->s = atoi(&token[2]);
                ruleset[index]->s_set = true;
                ruleset[index]->order_s = order_num;
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
            ruleset[index]->rule_amount = order_num;
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
    int rule_nm = 0;
    int i = 0;
    if(room == 99999)
    {
//        printf("REJECTED\n");
        counter++;
        return;
    }
    else if(room == 0)
    {
        printf("ACCEPTED\n");
        counter++;
        printf("Accepted input: %d\n", counter);
        result += x;
        result += m;
        result += a;
        result += s;
        printf("result is now: %ld\n", result);
        return;
    }
    else
    {
        printf("WE ARE AT ROOM %s\n", ruleset[room]->name);
        while (1)
        {
            printf("ruleamount: %d\n", ruleset[room]->rule_amount);
            printf("ruleorder_x: %d\n", ruleset[room]->order_x);
            printf("ruleorder_m: %d\n", ruleset[room]->order_m);
            printf("ruleorder_a: %d\n", ruleset[room]->order_a);
            printf("ruleorder_s: %d\n", ruleset[room]->order_s);
            while(rule_nm < ruleset[room]->rule_amount)
            {
                if (ruleset[room]->x_set == true && ruleset[room]->order_x == rule_nm)
                {
                    printf("x: %d, op: %c, rule x: %d\n", x, ruleset[room]->opx, ruleset[room]->x);
                    if (ruleset[room]->opx == '>')
                    {
                        if(x > ruleset[room]->x)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->dx);
                            return;
                        }
                    }
                    else
                    {
                        if(x < ruleset[room]->x)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->dx);
                            return;
                        }
                    }
                }
                else if (ruleset[room]->m_set == true && ruleset[room]->order_m == rule_nm)
                {
                    printf("m: %d, op: %c, rule m: %d\n", m, ruleset[room]->opm, ruleset[room]->m);
                    if (ruleset[room]->opm == '>')
                    {
                        if(m > ruleset[room]->m)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->dm);
                            return;
                        }
                    }
                    else
                    {
                        if(m < ruleset[room]->m)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->dm);
                            return;
                        }
                    }
                }
                else if (ruleset[room]->a_set == true && ruleset[room]->order_a == rule_nm)
                {
                    printf("a: %d, op: %c, rule a: %d\n", a, ruleset[room]->opa, ruleset[room]->a);
                    if (ruleset[room]->opa == '>')
                    {
                        if(a > ruleset[room]->a)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->da);
                            return;
                        }
                    }
                    else
                    {
                        if(a < ruleset[room]->a)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->da);
                            return;
                        }
                    }
                }
                else if (ruleset[room]->s_set == true && ruleset[room]->order_s == rule_nm)
                {
                    printf("s: %d, op: %c, rule s: %d\n", s, ruleset[room]->ops, ruleset[room]->s);
                    if (ruleset[room]->ops == '>')
                    {
                        if(s > ruleset[room]->s)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->ds);
                            return;
                        }
                    }
                    else
                    {
                        if(s < ruleset[room]->s)
                        {
                            printf("TRUE\n");
                            solve(x, m, a, s, ruleset[room]->ds);
                            return;
                        }
                    }
                }
                rule_nm++;
            }
            printf("ALL FALSE\n");
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
            add_rule(token, hashed);
            while((token2 = (strtok_r(line, ",", &line))) != NULL)
            {
                printf("token2: %s\n", token2);
                add_values(hashed, token2, order_num);
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