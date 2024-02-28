// % prefix = on / off switch, INIT OFF
//      -> if recieves HIGH pulse - ingored and nothing happens
//      -> if recieves LOW pulse - flip between on and off
//          -> if it was off, turn on and send HIGH
//          -> if it was on, turn off and send LOW

// & prefix = remembers last pulse from each modules, init to low
//      -> first to updates its memory for that input then
//      -> if it remembers highs pulses for all inputs - sends low pulse
//      -> else - sends high pulse

// inv = single input, con = double input?

// Broadcast module = re sends same pulse as input to all destination modules

// Button module = sends single low pulse to broadcast when pushed.

// All pulses much reach destination before new input
// Pulses process in the same orded they have been sent
//      -> send pulse to a, b, c
//      -> process a, then b, then c
//      -> after that a pulse can be redirected.

// EXAMPLE:
// broadcaster -> a
// %a -> inv, con
// &inv -> b
// %b -> con
// &con -> output

// EXPLAINED 1st rotation:
// 0. Button is pressed so low pulse - broadcaster
// 1.   Broadcaster -> low pulse - a
// 2.   %a -> switched to on status and send HIGH - inv, con
// 3.1  &inv -> Update last pulse from A to HIGH - Everything has been high so send LOW pulse - b
// 3.2  &con -> Update last pulse from A to HIGH - Not from all so send high pulse - output
// 4.1  %b -> switched to on status and send HIGH - con
// 4.2  output recieves high pulse
// 5.1  &con -> Update last pulse from B to HIGH - Everything has been high so send LOW pulse - output
// 6.1  output recieves low pulse

// EXPLAINED 2n rotation:
// 0. Button is pressed so low pulse - broadcaster
// 1.   Broadcaster -> low pulse - a
// 2.   %a -> switches to off and send low - inv, con
// 3.1  &inv -> update last pulse to from A to low -> everything not high so send HIGH - b
// 3.2  &con -> update A to LOW -> A is low, B is high, so send HIGH -  output
// 4.1  %b -> b recieves HIGH so nothing happend
// 4.2  output recieves HIGH

// EXPLAINED 3RD rotation
//  0. Button (LOW)-> bc
//  1. bc (LOW) -> a
//  2. %a -> switch ON-> (HIGH)-> inv, con
//  3.1 &inv -> A: HIGH-> (LOW)-> b
//  3.2 &con ->  A: HIGH B: HIGH (LOW)-> output
//  4.1 %b -> switch OFF-> (HIGH)-> con
//  4.2 output recieve LOW
//  5.1 %con -> A: HIGH B: HIGH (low)-> output
//  6.1 output recieves LOW

//  EXPLAINED 4th ROTATION
//  0. Button (LOW)-> bc
//  1. bc (LOW) -> a
//  2. %a -> switch OFF-> (LOW)-> inv, con
//  3.1 &inv -> A: LOW-> (HIGH)-> b
//  3.2 &con -> A: LOW B: HIGH-> (HIGH)->output
//  4.1 %b -> High input so nothing happens
//  4.2 output recieves HIGH

// this is the full rotation

// we are trying to count every time pulse is sent, either LOW or HIGH
// optimally we could save the start stage of all switches, and instead of going 8000 rounds
// -> when we are back to starting position (all low??)
// -> divide 8000 / rotation_length * pulses sent per rotation
// -> we should have to check all rotations just one full

// we must use queue?
// -> ill implement simple array queue

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>
#include <limits.h>

typedef struct module
{
    char *name;
    char type;
    int hash;
    char *destinations[10];
    int dc;
} module;

struct Queue 
{
    int front;
    int rear;
    int size;
    unsigned capacity;
    module *array;
};

// function to create a queue
// with init size 0
// in this case i will use too larde capacity just to be sure
struct Queue* make_queue(unsigned capacity)
{
    struct Queue* queue;
    queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
 
    queue->rear = capacity - 1;
    queue->array = (module *)malloc(queue->capacity * sizeof(module));
    return queue;
}
 
 // check if queue is full, idk if needed
int isFull(struct Queue *queue)
{
    return (queue->size == queue->capacity);
}
 
// Check if there is something in queue
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, module *item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = *item;
    queue->size = queue->size + 1;
    printf("%s enqueued to queue\n", item->name);
}
 
// Function to remove an item from queue.
// It changes front and size
module *dequeue(struct Queue* queue)
{
    module *new;
    if (isEmpty(queue))
        return NULL;
    *new = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return new;
}
 
// Function to get front of queue
module *front(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return &queue->array[queue->front];
}
 
// Function to get rear of queue
module *rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return NULL;
    return &queue->array[queue->rear];
}

long long result;
module *thearray[100000];


int hash(char *str)
{
    if (strcmp(str, "roadcaster") == 0)
        return 0;
    if (strcmp(str, "output") == 0)
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

void solve()
{
    struct Queue *q;
    q = make_queue(1000);
    enqueue(q, thearray[0]);

    while(q)
    {
        
    }

}

void make_room(char *name, int hashed)
{
    module *new;
    new = (module *)malloc(sizeof(module));
    new->name = strdup(&name[1]);
    new->hash = hashed;
    new->type = name[0];
    new->dc = 0;

    thearray[hashed] = new;
}

void add_destinations(char *name, int index)
{
    thearray[index]->destinations[thearray[index]->dc] = strdup(name);
    thearray[index]->dc++;
    printf("Added thearray[%d] - %s destination: %s\n", index, thearray[index]->name, thearray[index]->destinations[thearray[index]->dc - 1]);
}

int parser(char *line)
{
    char *new;
    char *token;
    char *token2;
    int hashed = 0;
    int phase = 0;

    new = strdup(line);
    printf("%s", new);

    while((token = (strtok_r(line, " -> ", &line))) != NULL)
    {
        if(phase == 0)
        {
            printf("token 1st phase: %s\n", token);
            hashed = hash(&token[1]);
            make_room(token, hashed);
            phase++;
        }
        else
        {
            while((token2 = (strtok_r(token, ",", &token))) != NULL)
            {
                printf("token 2nd phase: %s\n", token2);
                add_destinations(token2, hashed);
            }
        }
    }
    return 0;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;
    long     total = 0;
    int     phase = 0;
    result = 0;

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
        phase = parser(line);
        current++;;
    }
    solve();
//    printf("\n\n");
    printf("%lld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}