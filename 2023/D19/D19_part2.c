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

// then it could just something like global variable as rules *roomarray[2000]
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

long long result;
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
    int     rulec;
    int     finald;
    Rule    *rules[4];

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
    roomarray[hashed] = new;
    printf("added room: %s - %d\n", new->name, new->hash);
}

void add_rules(unsigned int index, char *str, int order_num)
{
    char *token;
    char *token2;
    Rule *new;

    while((token = (strtok_r(str, ":", &str))) != NULL)
    {
        if (token[1] == '>')
        {
//            printf("Working with %s\n", token);
            // FIX THIS SYNTAX AND STRUCT
            new = (Rule *)malloc(sizeof(Rule));
            new->c = token[0];
            new->op = '>';
            new->value = atoi(&token[2]);

        }
        else if (token[1] == '<')
        {
//            printf("Working with %s\n", token);
            // FIX THIS SYNTAX AND STRUCT
            new = (Rule *)malloc(sizeof(Rule));
            new->c = token[0];
            new->op = '<';
            new->value = atoi(&token[2]);
        }
        else if (strchr(token, '}') == 0)
        {
 //           printf("Working with %s\n", token);
            new->dest = hash(token);
        }
        else
        {
            token2 = strtok(token, "}");
            roomarray[index]->rulec = order_num - 1;
            roomarray[index]->finald = hash(token2);
        }
    }
    roomarray[index]->rules[order_num] = new;
    if (roomarray[index]->finald == -1)
    {
        printf("New Rule created!\n");
        printf("Roomarray[%d]->rules[%d]\n", index, order_num);
        printf("%c %c %d : %d\n", roomarray[index]->rules[order_num]->c, roomarray[index]->rules[order_num]->op, roomarray[index]->rules[order_num]->value, roomarray[index]->rules[order_num]->dest);
    }
    else
        printf("roomarray[%d]->finald: %d\n", index, roomarray[index]->finald);

}

void solve(int xs, int xe, int ms, int me, int as, int ae, int ss, int se, int room)
{
    int rule_nm = 0;
    int i = 0;
    long resx = 0;
    long resm = 0;
    long resa = 0;
    long ress = 0;
    long long res = 0;

    if(room == 99999)
    {
//        printf("REJECTED\n");
        counter++;
        return;
    }
    else if(room == 0)
    {
        counter++;
        printf("ACCEPTED INPUT: %d\n", counter);
        printf("contains values of:\n");
        printf("xs: %d - xe: %d\n", xs, xe);
        printf("ms: %d - me: %d\n", ms, me);
        printf("as: %d - ae: %d\n", as, ae);
        printf("ss: %d - se: %d\n", ss, se);
        resx = xe - xs + 1;
        resm = me - ms + 1;
        resa = ae - as + 1;
        ress = se - ss + 1;
        res = resx * resm * resa * ress;
        result += res;
        printf("result is now: %lld\n", result);
        printf("\n\n");
        return;
    }
    else
    {
        printf("WE ARE AT ROOM %s - %d\n", roomarray[room]->name, roomarray[room]->hash);
        rule_nm = 0;
        while(rule_nm <= roomarray[room]->rulec)
        {
            if(roomarray[room]->rules[rule_nm]->op == '>')
            {
                if(roomarray[room]->rules[rule_nm]->c == 'x')
                {
                    if (xe > roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(roomarray[room]->rules[rule_nm]->value + 1, xe, ms, me, as, ae, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, roomarray[room]->rules[rule_nm]->value, ms, me, as, ae, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 'm')
                {
                    if (me > roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, roomarray[room]->rules[rule_nm]->value + 1, me, as, ae, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, ms, roomarray[room]->rules[rule_nm]->value, as, ae, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 'a')
                {
                    if (ae > roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, ms, me, roomarray[room]->rules[rule_nm]->value + 1, ae, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, ms, me, as, roomarray[room]->rules[rule_nm]->value, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 's')
                {
                    if (se > roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, ms, me, as, ae, roomarray[room]->rules[rule_nm]->value + 1, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, ms, me, as, ae, ss, roomarray[room]->rules[rule_nm]->value, room);
                        return;
                    }
                }
            }
            else
            {
                if(roomarray[room]->rules[rule_nm]->c == 'x')
                {
                    if (xs < roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, roomarray[room]->rules[rule_nm]->value -1, ms, me, as, ae, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(roomarray[room]->rules[rule_nm]->value, xe, ms, me, as, ae, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 'm')
                {
                    if (ms < roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, ms, roomarray[room]->rules[rule_nm]->value - 1, as, ae, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, roomarray[room]->rules[rule_nm]->value, me, as, ae, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 'a')
                {
                    if (as < roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, ms, me, as, roomarray[room]->rules[rule_nm]->value - 1, ss, se, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, ms, me, roomarray[room]->rules[rule_nm]->value, ae, ss, se, room);
                        return;
                    }
                }
                else if(roomarray[room]->rules[rule_nm]->c == 's')
                {
                    if (ss < roomarray[room]->rules[rule_nm]->value)
                    {
                        solve(xs, xe, ms, me, as, ae, ss, roomarray[room]->rules[rule_nm]->value - 1, roomarray[room]->rules[rule_nm]->dest);
                        solve(xs, xe, ms, me, as, ae, roomarray[room]->rules[rule_nm]->value, se, room);
                        return;
                    }
                }
            }
            rule_nm++;
        }
        printf("ALL FALSE\n");
        solve(xs, xe, ms, me, as, ae, ss, se, roomarray[room]->finald);
        return;
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
        printf("\n\n");
        return 1;
    }
    else if (phase == 0)
    {
        while ((token = (strtok_r(line, "{", &line))) != NULL)
        {
            hashed = hash(token);
            printf("\n\n");
            add_room(token, hashed);
            while((token2 = (strtok_r(line, ",", &line))) != NULL)
            {
//                printf("\n");
//                printf("token2: %s\n", token2);
                add_rules(hashed, token2, order_num);
                order_num++;
            }
        }
    }
    else
    {
        return phase;
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
    solve(1, 4000, 1,  4000, 1, 4000, 1, 4000, hash("in"));
//    printf("\n\n");
    printf("%lld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}