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
    char    *name;
    int     hashed;
    char    type;
    int     d_pulse;
    int     d_count;
    int     r_count;
    char    *destinations[10];
    int     r_pulse[10];
    char    *recieved[10];
    int     switches[10];

} module;

struct Queue 
{
    int front;
    int rear;
    int size;
    int capacity;
    module *array;
};

int result[2];
module *thearray[100000];

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
int isEmpty(struct Queue *queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue *queue, module *item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = *item;
    queue->size = queue->size + 1;
//    printf("%s enqueued to queue\n", queue->array[queue->rear].name);
}

module *frontq(struct Queue *queue)
{
    if (isEmpty(queue))
        return NULL;
    return &queue->array[queue->front];
}
 
// Function to remove an item from queue.
// It changes front and size
void dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
        return ;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
}


int hash(char *str)
{
    unsigned int hash = 0;
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

int in_rlist(int target, char *name)
{
    int i;
    bool found;

    found = false;
    i = 0;
    while (i < thearray[target]->r_count)
    {
        if (strcmp(thearray[target]->recieved[i], &name[1]) == 0)
        {
            found = true;
            break;
        }
        i++;
    }
    if (found == false)
    {
        thearray[target]->recieved[i] = strdup(&name[1]);
        thearray[target]->r_count++;
    }
    return i;
}

void send_pulse(struct Queue *q, module *qp)
{
    int x;
    int target;
    int index;

    index = 0;
    target = 0;
    x = 0;
    if (qp->type == '%')
    {
        if(qp->switches[0] == 1)
            qp->d_pulse = 1;
        else
            qp->d_pulse = 0;
    }
    else if (qp->type == '&')
    {
        x = 0;
        qp->d_pulse = 0;
        printf("&room r_count: %d\n", qp->r_count);
        while (x < qp->r_count)
        {
            if (qp->r_pulse[x] == 0)
            {
                qp->d_pulse = 1;
                break;
            }
            x++;
        }
    }
//    printf("%s - %d\n", qp->name, qp->d_pulse);
    x = 0;
    while (x < qp->d_count)
    {
//        printf("%s = destination\n", qp->destinations[x]);
        target = hash(qp->destinations[x]);
        result[qp->d_pulse]++;
        printf("%s -%d-> %s\n", qp->name, qp->d_pulse, thearray[target]->name);
        if (thearray[target]->type == '%')
        {
            if(qp->d_pulse == 0)
            {
                thearray[target]->r_count = 1;
                thearray[target]->switches[0] *= -1;
                enqueue(q, thearray[target]);
            }
        }
        else if (thearray[target]->type == '&')
        {
            index = in_rlist(target, qp->name);
            thearray[target]->r_pulse[index] = qp->d_pulse;
            enqueue(q, thearray[target]);
        }
        else
        {
            if (target != 99999)
                enqueue(q, thearray[target]);
        }
        x++;
    }
}

void solve()
{
    printf("\n\n SOLVE PART BELOVE:\n\n");
    struct Queue *q;
    module *qp;

    q = make_queue(10);
    qp = thearray[0];
    enqueue(q, qp);
    result[0]++;
    while (q)
    {
        qp = frontq(q);
        if (qp == NULL)
            return;
        send_pulse(q, qp);
        dequeue(q);
    }

}

void make_room(char *name, int hashed)
{
    module *new;
    int x = 0;
    new = (module *)malloc(sizeof(module));
    new->name = strdup(&name[1]);
    new->hashed = hashed;
    new->type = name[0];
    new->d_pulse = 0;
    new->d_count = 0;
    new->r_count = 0;
    while (x < 10)
    {
        new->destinations[x] = NULL;
        new->recieved[x] = NULL;
        new->r_pulse[x] = 0;
        new->switches[x] = -1;
        x++;
    }
    thearray[hashed] = new;
    printf("New room was made to thearray[%d], called: %s\n", hashed, new->name);
}

void add_destinations(char *name, int index)
{
    thearray[index]->destinations[thearray[index]->d_count] = strdup(name);
    thearray[index]->d_count++;
    printf("Added thearray[%d] - %s destination: %s - %d\n", index, thearray[index]->name, thearray[index]->destinations[thearray[index]->d_count - 1], hash(thearray[index]->destinations[thearray[index]->d_count - 1]));
    printf("Its on position %d\n", thearray[index]->d_count - 1);
}

int parser(char *line)
{
    char *new;
    char *token;
    char *token2;
    int hashed = 0;
    int phase = 0;

    new = strdup(line);
    printf("%s\n", new);

    while((token = (strtok_r(line, " -> ", &line))) != NULL)
    {
        if(phase == 0)
        {
            hashed = hash(&token[1]);
            make_room(token, hashed);
            phase++;
        }
        else
        {
            printf("\n");
            while((token2 = (strtok_r(token, ",", &token))) != NULL)
            {
                add_destinations(token2, hashed);
            }
        }
    }
    make_room("output", 99999);
    return 0;
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
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
        parser(line);
    }
    solve();
    printf("Lows: %d Highs: %d - Result: %d\n", result[0], result[1], result[0] + result[1]);
    fclose(fptr);
    return 0;
 
}