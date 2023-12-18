#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

char    map[501][501];
int     verticles[700][2];
int     border_len;

typedef struct
{
    int id;
    int length;
    int direction;
    bool start;

} instructions;

double countArea(int n)
{
    // Initialize area
    double area = 0.0;
 
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (verticles[j][0] + verticles[i][0]) * (verticles[j][1] - verticles[i][1]);
        j = i;  // j is previous vertex to i
    }
 
    // Return absolute value
    return fabs(area / 2.0) + (border_len / 2) + 1;
}

void printmap()
{
    int i = 0;
    int j = 0;
    while(i < 500)
    {
        printf("%s\n", map[i]);
        i++;
    }
}

void   fillmap()
{
    int i = 0;
    int j = 0;
    while (i < 500)
    {
        j = 0;
        while (j < 500)
        {
            map[i][j] = '.';
            j++;
        }
        map[i][j] = '\0';
        i++;
    }
}

int solve(instructions **ins, int limit)
{
    int i = 250;
    int j = 250;
    int x = 0;
    border_len = 0;
    while (x < limit)
    {
//        printf("ins[%d]->dir: %d, length: %d\n", x, ins[x]->direction, ins[x]->length);
//        printf("startpoint i: %d, j: %d\n", i, j);
        verticles[x][0] = i;
        verticles[x][1] = j;
        border_len += ins[x]->length;
        if(ins[x]->direction == 1)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("1.\n");
                map[i][j] = '#';
                i++;
                k++;
            } 
        }
        else if(ins[x]->direction == 2)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("2.\n");
                map[i][j] = '#';
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
                map[i][j] = '#';
                i--;
                k++;
            } 
        }
        else if(ins[x]->direction == 4)
        {
            int k = 0;
            while (k < ins[x]->length)
            {
//                printf("4.\n");
                map[i][j] = '#';
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
    int x = 0;
    int i = 0;
    instructions *new;
    char *tok;
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
            if(tok[0] == 'D')
                new->direction = 1;
            else if(tok[0] == 'R')
                new->direction = 2;
            else if(tok[0] == 'U')
                new->direction = 3;
            else if(tok[0] == 'L')
                new->direction = 4;
            dir_set = true;
        }
        else if(isdigit(tok[0]) && length_set == false)
        {
            new->length = atoi(tok);
            length_set = true;
        }
        else
        {
            break;
        }
    }
//    printf("AFTER PARSE:\n");
//    printf("new->id: %d\n", new->id);
//    printf("new->dir: %d\n", new->direction);
//    printf("new->length: %d\n", new->length);

    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    double  area = 0.0;
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
    fillmap();
//    printf("2.\n");
    solve(ins, current);
    area = countArea(current);
    printf("area is: %f\n", area);
    printmap();
    return result;
 
}
