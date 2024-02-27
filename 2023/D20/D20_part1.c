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








#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <stdbool.h>
#include <math.h>

long long result;

typedef struct Rule
{
    char    c;

} Rule;


int hash(char *str)
{
    if (strcmp(str, "A") == 0)
        return 0;
    if (strcmp(str, "R") == 0)
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

void solve(int x, int m, int a, int s, int room)
{

}

int parser(char *line, int phase)
{
    char *new;
    char *token;
    char *token2;
    int hashed = 0;

    new = strdup(line);
    printf("%s", new);

    while ((token = (strtok_r(line, "{", &line))) != NULL)
    {
        hashed = hash(token);
        while((token2 = (strtok_r(line, ",", &line))) != NULL)
        {

        }
    }
}


int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     current = 0;
    long     total = 0;
    int     phase = 0;

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
        phase = parser(line, phase);
        current++;;
    }
//    printf("\n\n");
    printf("%ld\n", result);
//    printf ("%ld\n", total);
    fclose(fptr);
    return result;
 
}