#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>
#include <limits.h>

char    *array[1000];
int     start[2];
int     step;
int     resetarr[10000][2];

typedef struct Tile 
{
    int x;
    int y;
} Tile;

// Tile    *visited[1000];

typedef struct Queue 
{
    int front;
    int rear;
    int size;
    int capacity;
    Tile *array;
} Queue;

void printer(int x)
{
    int i = 0;
    if (step > 0 && step < 100)
    {
        printf("after %d: \n", step);
        while (i < x)
        {
            printf("%s", array[i]);
            i++;
        }
    }
    step++;
    printf("\n\n---------------------------------\n\n");
}

Queue*  make_queue(unsigned capacity)
{
    Queue* queue;
    queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (Tile *)malloc(queue->capacity * sizeof(Tile));
    return queue;
}
 
 // check if queue is full, idk if needed
int     isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}
 
// Check if there is something in queue
int     isEmpty(Queue *queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void    enqueue(struct Queue *queue, Tile *item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = *item;
    queue->size = queue->size + 1;
//    printf("%s enqueued to queue\n", queue->array[queue->rear].name);
}

Tile    *frontq(Queue *queue)
{
    if (isEmpty(queue))
        return NULL;
    return &queue->array[queue->front];
}
 
// Function to remove an item from queue.
// It changes front and size
void    dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return ;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
}

Tile    *make_tile(int x, int y)
{
    Tile *new;
    new = (Tile *)malloc(sizeof(Tile));
    new->x = x;
    new->y = y;

//    printf("New tile made (%d,%d)\n", new->x, new->y);
    return new;
}

// void    unmark(int j)
// {
//     int i = 0;
//     while (i < j)
//     {
//         array[visited[i]->x][visited[i]->y] = '.';
//         visited[i]->x = 0;
//         visited[i]->y = 0;
//         i++;
//     }
// }

int resulter(int max_x,int max_y)
{
    int x = 0;
    int y = 0;
    int res = 0;

    while(x < max_x)
    {
        while(y < max_y)
        {
            if (array[x][y] == 'O')
                res++;
            y++;
        }
        x++;
        y = 0;
    }
    return res;
}

int     eligiblity_check(Tile *qp, Queue *q, int max_x, int max_y, int i)
{
    int x = qp->x;
    int y = qp->y;
    int res;

    res = 0;
    printf("Checking (%d, %d) - %c\n", x, y, array[x][y]);
    if(x - 1 >= 0 && (array[x - 1][y] == '.' || array[x - 1][y] == 'S'))
    {
        printf(" -> Added: (%d, %d)\n", x - 1, y);
        array[x - 1][y] = 'O';
        enqueue(q, make_tile(x - 1, y));
        res++;
    }
    if(x + 1 < max_x && (array[x + 1][y] == '.' || array[x + 1][y] == 'S'))
    {
        printf(" -> Added: (%d, %d)\n", x + 1, y);
        array[x + 1][y] = 'O';
        enqueue(q, make_tile(x + 1, y));
        res++;
    }
    if(y - 1 >= 0 && (array[x][y - 1] == '.' || array[x][y - 1] == 'S'))
    {
        printf(" -> Added: (%d, %d)\n", x , y - 1);
        array[x][y - 1] = 'O';
        enqueue(q, make_tile(x, y - 1));
        res++;
    }
    if(y + 1 < max_y && (array[x][y + 1] == '.' || array[x][y + 1] == 'S'))
    {
        printf(" -> Added: (%d, %d)\n", x , y + 1);
        array[x][y + 1] = 'O';
        enqueue(q, make_tile(x, y + 1));
        res++;
    }
    resetarr[i][0] = x;
    resetarr[i][1] = y;
    return res;
}

int    solve (int max_x, int steps)
{
    int max_y;
    Tile *beginning;
    Queue *q;
    Tile *qp;
    int x = 0;
    int added = 1;
    int k = 0;
    int i = 0;
    int last_add = 0;

    q = make_queue(1000);
    beginning = NULL;
    qp = NULL;
    max_y = strlen(array[0]) - 1;
    printf("max_x = %d, max_y: %d\n", max_x, max_y);
    beginning = make_tile(start[0], start[1]);
    printf("Begin created to pos (%d,%d)\n", beginning->x, beginning->y);

    enqueue(q, beginning);
    printer(max_x);
    while(i < steps - 1)
    {
        printf("\n DEBUG VALUES:\nx: %d, k:%d, last_add: %d, added: %d, step: %d\n\n", x, k, last_add, added, i);
        printer(max_x);
        while (x < added)
        {
            qp = frontq(q);
            last_add += eligiblity_check(qp, q, max_x, max_y, x);
            dequeue(q);
            x++;
        }
        while(k < x)
        {
            printf("Resetting (%d, %d)\n", resetarr[k][0], resetarr[k][1]);
            array[resetarr[k][0]][resetarr[k][1]] = '.';
            resetarr[k][0] = -1;
            resetarr[k][1] = -1;
            k++;
        }
        k = 0;
        x = 0;
        added = last_add;
        last_add = 0;
        i++;
    }
//    printer(max_x);
    return (resulter(max_x, max_y));
}


int     parser(char *line, int current)
{
    int i;

    i = 0;
    array[current] = strdup(line);
    printf("%s\n", array[current]);
    if (strchr(array[current], 'S'))
    {
        while(array[current][i] != 'S')
            i++;
        start[0] = current;
        start[1] = i;
    }
    return 0;
}


int     main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current;
    int     steps;
    int     res;

    step = 0;
    steps = 64;
    current = 0;
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
    if (start[0])
        printf("S FOUND: %d,%d\n", start[0], start[1]);
    printf("\n\nSOLVE PART STARTS\n\n");
    res = solve(current, steps);
    printf("Final result is: %d\n", res);
}