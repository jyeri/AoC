// initial thought since jump in diffculty caught me bit off guard
// -> we have 256 different boxes (hashed of given label?)
// -> and every box has their own multiplier?
//      -> in every box we have lenses


//  "rn=1 is 30"
// rn is label, hashed tells us which box to be placed
// '=' or '-' tells us is the operation insertion or delete
// -> if '='
//      -> there is no lens with same hash, we add lens[30] with focal strength of 1
//      -> if there is already lens with hash 30, we modify focal value to 30 (replace the lens)
// -> if '-'
//      -> if there is lens in box.lens[30] we delete it?
//      -> if not "nothing interesting happens"

// so general idea:
//
// 1. Loop
//     1.1 take label until we get to - or =
//     1.2 take next value (1-9) and save it as focal strengt
//     1.3 send these variables to be either added or deleted function


// 2. addition
//     2.1 hash the label to get box where it belong
//     2.2 loop to check if there is already lens with this label
//     2.3 if yes, we update box->lens->focal
//     2.4 if not, we copy this new label and its focal into box array

// 3. deletion
//     3.1 hash the label to get box where it belong
//     3.2 loop to check if there is matching
//     3.3 if yes, we move everything from that point up front by one?
//     3.4 if not, we just simply ignore and start with next input

// 4. result
//      4.1 loop thru boxes (that has length)
//      4.2 we take values of box number * lens index (not hash) * focal of this lens
//      4.3 sum this to total value
//      4.4 return total

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>
#include <assert.h>


typedef struct
{
    char    id[15];
    int     foc;
} Lens;

typedef struct
{
    Lens    lens[512];
    int     amount;
} Box;

//some more clever guy tempted me to use globals more ofter (forbidden in Hive)
Box     boxes[256];


int hasher(char *str)
{
    int i = 0;
    int res = 0;

    while(str[i])
    {
        res += str[i];
        res *= 17;
        res %= 256;
        i++;
    }
    return res;
}

void addition(char *name, int hashed, int foc)
{
    bool found;
    int i = 0;
    found = false;

    while(i < boxes[hashed].amount)
    {
        if (strcmp(boxes[hashed].lens[i].id, name) == 0)
        {
            found = true;
            boxes[hashed].lens[i].foc = foc;
        }
        i++;
    }
    if(found == false)
    {
        //add to last position of the list 
        strcpy(boxes[hashed].lens[boxes[hashed].amount].id, name);
        boxes[hashed].lens[boxes[hashed].amount].foc = foc;
        boxes[hashed].amount++;
    }

}

void deletion(char *name, int hashed)
{
    bool found;
    int i = 0;
    found = false;

    while (i < boxes[hashed].amount)
    {
        if (strcmp(boxes[hashed].lens[i].id, name) == 0)
        {
            found = true;
            break;
        }
        i++;
    }
    if (found == true)
    {
        while (i < boxes[hashed].amount)
        {
            boxes[hashed].lens[i] = boxes[hashed].lens[i + 1];
            i++;
        }
        boxes[hashed].amount--;
    }
}

void showbox(void)
{
    int i = 0;
    int j = 0;
    while (i < 256)
    {
        j = 0;
        if (boxes[i].amount > 0)
        {
            printf("BOX[%d]: ", i);
            while(j < boxes[i].amount)
            {
                printf("[%s %d] ", boxes[i].lens[j].id, boxes[i].lens[j].foc);
                j++;
            }
            printf("\n");
        }
        i++;
    }
    printf("\n");
    printf("\n");
}

int main(int argc, char **argv)
{
    FILE    *fptr;
    long    result = 0;
    long    total = 0;
    int     current = 0;
    int     id_len = 0;
    int     foc = 0;
    int     c = 0;
    char    id[10];

// it in fact kinda bit in the ass

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

        if(c == '=')
        {
            foc = fgetc(fptr) - '0';
            printf("before add: %s - %d\n", id, foc);
            addition(id, hasher(id), foc);
            showbox();
            result = 0;
            id_len = 0;
            id[id_len] = '\0';
        }
        else if(c == '-')
        {
            foc = fgetc(fptr) - '0';
            printf("before del: %s - %d\n", id, foc);
            deletion(id, hasher(id));
            showbox();
            result = 0;
            id_len = 0;
            id[id_len] = '\0';
        }
        else
        {
            if(c == ',')
                c = fgetc(fptr);
            if (c)
            {
                id[id_len] = c;
                id_len++;
                id[id_len] = '\0';
            }
        }
    }
    int i = 0;
    int j = 0;
    while (i < 256)
    {
        j = 0;
        if (boxes[i].amount > 0)
        {
            while(j < boxes[i].amount)
            {
                total += ((i + 1) * (j + 1) * boxes[i].lens[j].foc);
                printf("total: %ld\n", total);
                j++;
            }
        }
        i++;
    }
    printf("%ld\n", total);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}