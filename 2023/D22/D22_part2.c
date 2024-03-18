#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

typedef struct Brick
{
    int sx;
    int sy;
    int sz;
    int ex;
    int ey;
    int ez;

    int *give_support;
    int *get_support;
} Brick;

Brick   *brickarray[1500];
bool    chainreact[1500];
int     total;

// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}
 
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%d enqueued to queue\n", item);
}
 
// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT32_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
// Function to get front of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT32_MIN;
    return queue->array[queue->front];
}
 
// Function to get rear of queue
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT32_MIN;
    return queue->array[queue->rear];
}
 
Brick   *create_brick()
{
    Brick *new;

    new = (Brick *)malloc(sizeof(Brick));
    new->sx = -1;
    new->sy = -1;
    new->sz = -1;
    new->ex = -1;
    new->ey = -1;
    new->ez = -1;
    int i = 0;
    new->give_support = (int *)malloc(sizeof(int) * 10);
    new->get_support = (int *)malloc(sizeof(int) * 10);
    while(i < 10)
    {
        new->give_support[i] = -1;
        new->get_support[i] = -1;
        i++;
    }

    return (new);
}

void swap(int i, int j)
{
    int tmp_sx  = brickarray[i]->sx;
    int tmp_sy  = brickarray[i]->sy;
    int tmp_sz  = brickarray[i]->sz;
    int tmp_ex  = brickarray[i]->ex;
    int tmp_ey  = brickarray[i]->ey;
    int tmp_ez  = brickarray[i]->ez;

    brickarray[i]->sx = brickarray[j]->sx;
    brickarray[i]->sy = brickarray[j]->sy;
    brickarray[i]->sz = brickarray[j]->sz;
    brickarray[i]->ex = brickarray[j]->ex;
    brickarray[i]->ey = brickarray[j]->ey;
    brickarray[i]->ez = brickarray[j]->ez;

    brickarray[j]->sx = tmp_sx;
    brickarray[j]->sy = tmp_sy;
    brickarray[j]->sz = tmp_sz;
    brickarray[j]->ex = tmp_ex;
    brickarray[j]->ey = tmp_ey;
    brickarray[j]->ez = tmp_ez;
}

void    sort_bricks(int max)
{
    int i = 0;
    int j = 0;
    while (i < max)
    {
        j = i + 1;
        while (j < max)
        {
            if (brickarray[i]->sz > brickarray[j]->sz)
                swap(i, j);
            j++;
        }
        i++;
    }
}

bool    overlap(Brick *b1, Brick *b2)
{
    if (fmax(b1->sx, b2->sx) <= fmin(b1->ex, b2->ex) && fmax(b1->sy, b2->sy) <= fmin(b1->ey, b2->ey))
    {
        return true;
    }
    return false;
}


// Marking the falling bricks:
// iterate sorted array, brick by brick
// keep track of minimum value it can fall into (new z position) (also update endingz)
// in second thoughts:
// iterate from array[i] until array[0] or until array[i - x] already has overlap value

void    mark_falling(int maximum)
{
    int i = 0;
    int j = 0;
    int min_z = 1;
//    int x = 0;
    Brick *b;
    Brick *bcomp;

    while (i < maximum)
    {
        min_z = 1;
        b = brickarray[i];
        j = 1;
        while (i - j >= 0)
        {
            bcomp = brickarray[i - j];
            if (overlap(b, bcomp))
            {
                min_z = fmax(min_z, bcomp->ez + 1);
                // Move this, bit slower but much more reasonable, and easier to manage that only 1 belove can support
//                b->get_support[x] = i - j;
//                k = 0;
//                while(bcomp->give_support[k] > 0)
//                    k++;
//                bcomp->give_support[k] = i;
//                printf("brickarray[%c] is supported by brickarray[%c]\n", 'a' + i, 'a' + (i - j));
//                x++;
            }
            j++;
        }
        b->ez -= b->sz - min_z;
        b->sz = min_z;
        i++;
    }

}

void    mark_supports(int maximum)
{
    int i = maximum - 1;
    int j = maximum - 1;
    int x = 0;
    int k = 0;
    Brick *lower;
    Brick *upper;
    lower = NULL;
    upper = NULL;

    while (i >= 0)
    {
        upper = brickarray[i];
        j = i - 1;
        x = 0;
        k = 0;
        while (j >= 0)
        {
            lower = brickarray[j];
            if (overlap(lower, upper) && (upper->sz == lower->ez + 1))
            {
                upper->get_support[x] = j;
                k = 0;
                while (lower->give_support[k] > -1)
                {
                    k++;
                }
                lower->give_support[k] = i;
                printf("brickarray[%c]->[%d] supports brickarray[%c]\n", 'a' + j, k, 'a' + i);
                x++;
            }
            j--;
        }
        i--;
    }
}


int     part2(int i, int maximum)
{
    int i = 0;
    int x = 0;
    int k = 0;
    struct Queue* queue = createQueue(1000);
    struct Queue* fallen = createQueue(1000);

    enqueue(queue, i);
    enqueue(fallen, i);
    while (queue)
    {

    }

}

void    solve(int maximum)
{
    int i = 0;
    int x = 0;
    int k = 0;
    int sup = 0;
    Brick *brick;
    Brick *supported;

    while (i < maximum)
    {
        brick = brickarray[i];
        while (brick->give_support[x] > -1)
        {
            supported = brickarray[brick->give_support[x]];
            k = 0;
            while (supported->get_support[k] > -1)
                k++;
            if (k < 2)
                sup--;
            else
                sup++;
            x++;
        }
        if(sup == x)
        {
            printf("Brick %c is BEDGE\n", 'a' + i);
            chainreact[i] = false;
        }
        else
        {
            printf("Brick %c is CAN CAUSE CHAIN REACTION\n", 'a' + i);
            chainreact[i] = true;
        }
        sup = 0;
        x = 0;
        i++;
    }

    i = 0;
    x = 0;
    k = 0;
    sup = 0;
    int res = 0;
    int total = 0;

    while (i < maximum)
    {
        res = 0;
        if(chainreact[i] == true)
        {
            res = part2(i, maximum);
            chainreact[i] = false;
        }
        if (res > total)
            total = res;
        i++;
    }
    print("Total of %d would disencrate\n", total);
}

int     parser(char *line, int current)
{
 //   char *new;
    char *token;
    char *token2;
    Brick *brick;

//    new = strdup(line);
//    printf("%s\n", new);
    brick = create_brick();
    token = strtok_r(line, "~", &line);
    token2 = (strtok_r(token, ",", &token));
    brick->sx = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->sy = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->sz = atoi(token2);
    token = strtok_r(line, "~", &line);
    token2 = (strtok_r(token, ",", &token));
    brick->ex = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->ey = atoi(token2);
    token2 = (strtok_r(token, ",", &token));
    brick->ez = atoi(token2);

    printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", current,  brick->sx, brick->sy, brick->sz, brick->ex, brick->ey, brick->ez);
    
    brickarray[current] = brick;
    return 0;
}


int     main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;


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
        parser(line, current);
        current++;
    }
//    printf("\n\n");
//    printf("%ld\n", result);
//    printf ("%ld\n", total);
    sort_bricks(current);
    printf("\nsorted\n\n");
    for(int i = 0; i < current; i++)
    {
         printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", i,  brickarray[i]->sx, brickarray[i]->sy, brickarray[i]->sz, brickarray[i]->ex, brickarray[i]->ey, brickarray[i]->ez);
    }
    mark_falling(current);
    printf("\nsorted fallen\n\n");
    for(int i = 0; i < current; i++)
    {
         printf("Brick %d: [%d, %d, %d] ~ [%d, %d, %d]\n", i,  brickarray[i]->sx, brickarray[i]->sy, brickarray[i]->sz, brickarray[i]->ex, brickarray[i]->ey, brickarray[i]->ez);
    }
    mark_supports(current);
    solve(current);
    fclose(fptr);
    return current;
 
}