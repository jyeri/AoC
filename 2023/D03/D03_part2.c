// INPUT: Multiple lines of '.', 'symbol' or Integers
// OUTPUT: sum of all integers that have adjecent symbol (horizontal, vertical or diagonal)

// Or of op:
// 1. iterate first line until first is_digit()
// -> while is_digit() sum = sum * 10 + atoi(str[x])
// 2. check if there is symbol before or after the integer, is there diagonal of start or stop, is there horizontal of whole string
// -> if true check = 0 AND
// -> (
// -> if str[x - 1][y - 1] OR
// -> if str[x + 1][y - 1] OR
// -> if str[x + 1][y + 1] OR
// -> if str[x - 1][y + 1] OR
// -> if str[x + 1][y] OR
// -> if str[x - 1][y] OR
// -> if str[x][y - 1] OR
// -> if str[x][y + 1] == SYM OR
// -> )
// true check = 1

// 3. if true check == 1
// -> result += sum
// 4. if true check == 0
// -> sum = 0
// 5. true check = 0
// 6. iterate to next string and repeat until all arguments are done
// 7. return value is res

// new idea:
// 1. parse whole input into char **str
// 2. only modify dots to 0, letters 1, symbols 2
// 3. use same idea as above to count if some pair adds up to 3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>


int *check_plus(char **map, int x, int y, int n, int m)
{
    int *res = (int *)malloc(sizeof(sizeof(int) * 2));
    if ((x + 1 < n) && (map[x + 1][y] == '+'))
    {
        res[0] = x + 1;
        res[1] = y;
        return res;
    }
    if ((x - 1 >= 0) && (map[x - 1][y] == '+'))
    {
        res[0] = x - 1;
        res[1] = y;
        return res;
    }
    if ((y + 1 < m) && (map[x][y + 1] == '+'))
    {
        res[0] = x;
        res[1] = y + 1;
        return res;
    }
    if ((y - 1 >= 0) && (map[x][y - 1] == '+'))
    {
        res[0] = x;
        res[1] = y - 1;
        return res;
    }
    if ((x - 1 >= 0) && (y - 1 >= 0) && (map[x - 1][y - 1] == '+'))
    {
        res[0] = x - 1;
        res[1] = y - 1;
        return res;
    }
    if ((x - 1 >= 0) && (y + 1 < m) && (map[x - 1][y + 1] == '+'))
    {
        res[0] = x - 1;
        res[1] = y + 1;
        return res;
    }
    if ((x + 1 < n) && (y - 1 >= 0) && (map[x + 1][y - 1] == '+'))
    {
        res[0] = x + 1;
        res[1] = y - 1;
        return res;
    }
    if ((x + 1 < n) && (y + 1 < m) && (map[x + 1][y + 1] == '+'))
    {
        res[0] = x + 1;
        res[1] = y + 1;
        return res;
    }
    return 0;
    

}

void solve_map(char **map, int n, int start) 
{
    int i = 0;
    int j = 0;
    bool legit = false;
    bool legit2 = false;
    int surrounds = 0;
    int m = 0;
    long res = 0;
    long tempres = 0;
    long tempres2 = 0;
    long tempres3 = 0;
    int *cordi;
    int *cordi2;
    int x = 0;
    int y = 0;

    m = strlen(map[0]);

    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            while (isdigit(map[i][j]))
            {
                tempres = 0;
                while (isdigit(map[i][j]))
                {
                    if (tempres > 0)
                        tempres *= 10;
                    tempres += map[i][j] - '0';
                    if (legit == false && check_plus(map, i, j, n, m) > 0)
                    {
                        cordi = check_plus(map, i, j, n, m);
                        legit = true;
                    }
                    j++;
                }
                if (legit == true)
                {
//                    printf("comparing %ld, with symbol cordinates %d,%d\n", tempres, cordi[0], cordi[1]);
                    x = i;
                    y = j + 1;
//                    printf("x,y: %d,%d\n", x, y);
                    while (x < n)
                    {
                        while (y < m)
                        {
                            while(isdigit(map[x][y]))
                            {
                                if (tempres2 > 0)
                                    tempres2 *= 10;
                                tempres2 += map[x][y] - '0';
                                if (legit2 == false && check_plus(map, x, y, n, m) > 0)
                                {
                                    cordi2 = check_plus(map, x, y, n, m);
                                    legit2 = true;
                                }
                                y++;
                            }
                            if (legit2 == true)
                            {
                                if (cordi[0] == cordi2[0] && cordi[1] == cordi2[1])
                                {
//                                    printf("found legit %ld, with symbol cordinates %d,%d\n", tempres2, cordi2[0], cordi2[1]);
//                                    printf("match\n");
                                    surrounds++;
                                    tempres3 = tempres2;
                                    legit2 = false;
                                }
                            }
                            tempres2 = 0;
                            legit2 = false;
                            y++;
                        }
                        y = 0;
                        x++;
                    }
                    if (surrounds == 1)
                    {
                        res += tempres * tempres3;
                        printf("res updated to: %ld\n", res);
                    }
                    tempres = 0;
                    tempres2 = 0;
                    tempres3 = 0;
                    legit2 = false;
                    surrounds = 0;
                    legit = false;
                    cordi[0] = 0;
                    cordi[1] = 0;
                    cordi2[0] = 0;
                    cordi2[1] = 0;
                    x = 0;
                    y = 0;
                }
            }
            j++;
        }
        i++;
    }
    printf("res: %ld\n", res);

}

char *parser(char *line)
{
    char *new;
    int i = 0;
    int n = strlen(line);

    new = (char *)malloc(sizeof(char) * n + 1);
    while (i < n)
    {
        if(line[i] != '.')
        {
            if (isdigit(line[i]))
                new[i] = line[i];
            else if (line[i] == '*')
                new[i] = '+';
            else
                new[i] = '.';
        }
        else
            new[i] = '.';
        i++;
    }
    new[i] = '\0';
//    printf("%s\n", new);

    return new;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    long     result = 0;
    int     current = 0;
    long     total = 0;
    char    *inst;
    char    *map[141] = {0};

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
        map[current] = parser(line);
        current++;
    }
//    printf("\n\n");
    solve_map(map, current, 0);
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}