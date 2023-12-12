#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// DONE UNDER HEAVY INFULENCE OF REDDIT, CANT TAKE EITHER CREDIT OR BLAME FOR THE SOLUTION

// okay so part1 keeps crashing so its time to redo
// only way I found this feasible to achieve (thanks reddit) was using huge global variables
// to cut down time, we make 2d array called cache.
// in cache we store previous results of same substring

int instructions[512];
char puzzle[512];
int puzzle_len;
int instructions_len;
long cache[512][512];

long solver(int i_ind, int p_ind) 
{
    // solver itself functions like in part 1, with couple of twists
    if (i_ind == instructions_len) 
    {
        return 1;
    }
    // check if we have already seen this variation, if we have we just return the value of last time from cache
    if (p_ind < puzzle_len && cache[i_ind][p_ind] != -1) 
    {
        return cache[i_ind][p_ind];
    }

    long result = 0;
    int i = p_ind;
    // again starting from the beginning we go c by c as long as i + instruction actually fits
    while (i <= puzzle_len - instructions[i_ind]) 
    {
        int possible = 1;
        int j = 0;
        // check if there is '.' -> cant be placed
        while (j < instructions[i_ind]) 
        {
            if (puzzle[i+j] == '.') {
                possible = 0;
            }
            j++;
        }
        // check if there is '#' instead of empty space after -> cant be placed
        if (i + instructions[i_ind] < puzzle_len && puzzle[i + instructions[i_ind]] == '#') 
        {
            possible = 0;
        }
        // if there is '#' just before -> cant be placed
        if (i > 0 && puzzle[i-1] == '#') 
        {
            possible = 0;
        }
        // we are at last instruction
        if (i_ind == instructions_len - 1) 
        {
            j = i+instructions[i_ind]+1;
            // check if there is still '#' after instructions have used
            while (j < puzzle_len) 
            {
                if (puzzle[j] == '#') 
                {
                    possible = 0;
                }
                j++;
            }
        }
        // when everything checks out and can be placed, we go recursive with next index values
        // -> (next instruction, index + last instruction length + 1 empty space)
        if (possible) 
        {
            result += solver(i_ind + 1, i + instructions[i_ind] + 1);
        }
        if (puzzle[i] == '#') 
        {
            break;
        }
        i++;
    }
    // we save the result in cache
    if (p_ind < puzzle_len) 
    {
        cache[i_ind][p_ind] = result;
    }
    return result;
}

int main(int argc, char **argv)
{
    FILE    *fptr;
    long    result = 0;
    int     current = 1;
    long    total = 0;
    int     i = 0;
    int     j = 0;

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
    // first time using fscan and fgetc :D
    while (!feof(fptr))
    { 
        instructions_len = 0;
        fscanf(fptr, "%s ", puzzle);
        puzzle_len = strlen(puzzle);

        i = 1;
        while (i < 5) 
        {
            puzzle[(puzzle_len + 1) * i - 1] = '?';
            j = 0;
            while (j < puzzle_len) 
            {
                puzzle[j + (puzzle_len + 1) * i] = puzzle[j];
                j++;
            }
            i++;
        }
        puzzle_len = puzzle_len * 5 + 4;

        int c = ',';
        while (c == ',') 
        {
            fscanf(fptr, "%d", &instructions[instructions_len]);
            instructions_len ++;
            c = fgetc(fptr);
        }

        i = 1;
        while (i < 5) 
        {
            j = 0;
            while (j < instructions_len) 
            {
                instructions[j + instructions_len * i] = instructions[j];
                j++;
            }
            i++;
        }
        instructions_len *= 5;

        i = 0;
        j = 0;
        while (i < instructions_len) 
        {
            j = 0;
            while (j < puzzle_len) 
            {
                cache[i][j] = -1;
                j++;
            }
            i++;
        }

        result = solver(0, 0);
        printf("%d %ld\n", current, result);
        current++;
        total += result;
    }

    printf("%ld\n", total);
    fclose(fptr);
}