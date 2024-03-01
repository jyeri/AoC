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
    char *recieved_name_list[10];
    char *recieved_pulse_list[10];
    char *prev;
    int *switches[10];
    int r_pulse;
    char *destinations[10];
    int dc;
    int d_pulse;

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
void dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return ;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
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

int result[2];
module *thearray[100000];


int hash(char *str)
{
    unsigned int hash = 0;
	int x = 0;
    int i = 0;
    if (strcmp(str, "roadcaster") == 0)
        return 0;
    if (strcmp(str, "output") == 0)
        return 99999;
	while (str[i])
    {
        if (str[i] == '\n' || str[i] == '\0')
            return hash;
        else
        {
            hash += str[i];
            hash += 45;
        }
        i++;
    }
	return hash;
}

void send_pulse(module *qp, int target)
{
    int i = 0;
    bool found;

    found = false;
    if (qp->type == '%')
    {
        while (qp->recieved_name_list[i])
        {
            if (strcmp(qp->recieved_name_list[i], qp->prev))
            {
                found = true;
                break;
            }
            i++;
        }
        if (found == false)
        {
            qp->recieved_name_list[i] = strdup(qp->prev);
            qp->recieved_pulse_list[i] = qp->r_pulse;
        }
        if (qp->r_pulse == 0)
        {
            qp->switches[i] *= -1;
        }
    }
    else if (qp->type == '&')
    {

    }
    else
    {
        qp->d_pulse = qp->r_pulse;
        thearray[target]->r_pulse = qp->d_pulse;
        thearray[target]->prev = strdup(qp->name);
        i = 0;
        if (thearray[target]->recieved_name_list[i])
        {
            while(thearray[target]->recieved_name_list[i])
            {
                if (strcmp(thearray[target]->recieved_name_list[i], qp->name))
                {
                    thearray[target]->recieved_pulse_list[i] = qp->d_pulse;
                    break;
                }
                i++;
            }
        }
        else
        {
            thearray[target]->recieved_name_list[i] = strdup(qp->name);
            thearray[target]->recieved_pulse_list[i] = qp->d_pulse;
        }
    }
}

void solve(int i)
{
    int x = 0;
    int target = 0;
    int prev_pulse = -1;
    struct Queue *q;
    struct module *qp;

    q = make_queue(1000);
    enqueue(q, thearray[0]);
    result[0] += 1;
    while (i)
    {
        while(q)
        {
            qp = front(q);
            x = 0;
            target = -1;
            printf("took from que: %s\n", qp->name);
            while(x < qp->dc)
            {
                target = qp->destinations[x];
                send_pulse(qp, target);
            }
            dequeue(q);
        }
    i--;
    }

}

void make_room(char *name, int hashed)
{
    module *new;
    int x = 0;
    new = (module *)malloc(sizeof(module));
    new->name = strdup(&name[1]);
    new->hash = hashed;
    new->type = name[0];
    new->dc = 0;
    new->r_pulse = 0;
    while (x < 10)
    {
        new->switches[x] = -1;
        x++;
    }
    thearray[hashed] = new;
    printf("New room was made to thearray[%d], called: %s\n", hashed, new->name);
}

void add_destinations(char *name, int index)
{
    char *copy;

    thearray[index]->destinations[thearray[index]->dc] = strdup(name);
    thearray[index]->switches[thearray[index]->dc] = -1;
    thearray[index]->dc++;
    printf("Added thearray[%d] - %s destination: %s - %d\n", index, thearray[index]->name, thearray[index]->destinations[thearray[index]->dc - 1], hash(thearray[index]->destinations[thearray[index]->dc - 1]));
    printf("Its on prosition %d\n", thearray[index]->dc - 1);
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
            printf("\n");
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
    result[0] = 0;
    result[1] = 0;

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
        current++;
    }
    solve(1);
//    printf("\n\n");
    printf("low: %d high: %d, totals: %d\n", result[0], result[1], result[0] + result[1]);
//    printf ("%ld\n", total);
    fclose(fptr);
    return 0;
 
}