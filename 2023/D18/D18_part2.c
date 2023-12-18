#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

long     verticles[700][2];
long     border_len;

typedef struct
{
    int id;
    long length;
    int direction;
    bool start;

} instructions;

long double countArea(int n)
{
    long double area = 0.0;
 
    long j = n - 1;
    for (long i = 0; i < n; i++)
    {
//        printf("A: %ld, B: %ld\n", (verticles[j][0] + verticles[i][0]), (verticles[j][1] - verticles[i][1]));
        area += (verticles[j][0] + verticles[i][0]) * (verticles[j][1] - verticles[i][1]);
//        printf("area atm: %Lf\n", area);
        j = i; 
    }

//    printf("\n\n pre return values:\n");
//    printf("area %Lf\n fabs(area/2): %f\n border_len: %ld\n", area, fabs(area / 2.0), border_len);
    return fabs(area / 2.0) + (border_len / 2) + 1;
}


int solve(instructions **ins, int limit)
{
    long i = 250;
    long j = 250;
    int x = 0;
    border_len = 0;
    while (x < limit)
    {
//        printf("ins[%d]->dir: %d, length: %ld\n", x, ins[x]->direction, ins[x]->length);
//        printf("startpoint i: %ld, j: %ld\n", i, j);
        verticles[x][0] = i;
        verticles[x][1] = j;
        border_len += ins[x]->length;
        if(ins[x]->direction == 1)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("1.\n");
                i++;
                k++;
            } 
        }
        else if(ins[x]->direction == 0)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("2.\n");
                j++;
                k++;
            } 
        }
        else if(ins[x]->direction == 3)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("3.\n");
                i--;
                k++;
            } 
        }
        else if(ins[x]->direction == 2)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("4.\n");
                j--;
                k++;
            } 
        }
        x++;
    }
    return 0;
}
 
// LL *parsestart(char **array, int limit)
// {
//     int x = 0;
//     int y = 0;
// 
// 
//     printf("NO START");
//     exit (-1);
// }

// LL *parsenodes(char **array, int limit, LL *start)
// {
//     int x = 0;
//     int y = 0;

//     while(x < limit)
//     {
//         while (array[x][y] != '\0')
//         {
//             if (array[x][y] == 'S')
//             {
//                 start = create_start(array, x, y);
//                 return start;
//             }
//             y++;
//         }
//         y = 0;
//         x++; 
//     }

//     printf("NO START");
//     exit (-1);
// }

instructions *parser(char *line, int current)
{
    long x = 0;
    long i = 0;
    instructions *new;
    char *tok;
    char *tmp;
    bool dir_set = false;
    bool length_set = false;
    bool clr_set = false;

    new = (instructions *)malloc(sizeof(instructions));
    new->id = current;

//    printf("\n\nline to parse: %s\n", line);

    while ((tok = strtok_r(line, " ", &line)))
    {
//        printf("tok now: %s\n", tok);
        if(isalpha(tok[0]) && dir_set == false)
        {
            dir_set = true;
        }
        else if(isdigit(tok[0]) && length_set == false)
        {
            length_set = true;
        }
        else
        {
            tmp = malloc(sizeof(char) * 7);
            strncpy(tmp, &tok[2], sizeof(char) * 5);
//            printf("holding: %s\n", tmp);
            int i = 0;
            new->length = strtol(tmp, NULL, 16);
            new->direction = tok[7] - '0';
        }
    }
//    printf("AFTER PARSE:\n");
//    printf("new->id: %d\n", new->id);
//    printf("new->dir: %d\n", new->direction);
//    printf("new->length: %ld\n", new->length);

    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;
    long double  area = 0.0;
    instructions *ins[2048];


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
//        printf("current: %d\n", current);
        ins[current] = parser(line, current);
        current++;
    }
    fclose(fptr);
//    printf("1.\n");
//    printf("2.\n");
    solve(ins, current);
    area = countArea(current);
    printf("area is: %Lf\n", area);
    return 0;
 
}
