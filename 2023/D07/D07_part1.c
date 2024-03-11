// 1. read input line by line
// 2. copy input to struct (called hand)
// 3. convert it to integers?
// 4. give points to each hand, save points to struct?
// 5. compare structs?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

typedef struct 
{
    int *cards;
    int bid;
    int points;
    int rank;
    int win;

} hand;

void swap(hand *all_hands, int i, int j)
{
    int tmp_points = all_hands[i].points;
    int *tmp_cards;
    tmp_cards = all_hands[i].cards;
    int tmp_bid = all_hands[i].bid;

    all_hands[i].points = all_hands[j].points;
    all_hands[i].cards = all_hands[j].cards;
    all_hands[i].bid = all_hands[j].bid;

    all_hands[j].points = tmp_points;
    all_hands[j].cards = tmp_cards;
    all_hands[j].bid = tmp_bid;

}
void quickSort(hand *all_hands, int n)
{
    int x = 0;
    int i, j = 0;
    int tmp = 0;
    for (i = 0; i < n; ++i) 
    {
        for (j = i + 1; j < n; ++j)
        {
            if (all_hands[i].points > all_hands[j].points) 
            {
                swap(all_hands, i, j);
            }
        }
    }
}

int checkequ(int *a, int *b)
{
    int i = 0;
    while(i < 5)
    {
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return 0;
        i++;
    }
    return 0;
}

void quickWins(hand *all_hands, int n)
{
    int x = 0;
    int i, j = 0;
    int tmp = 0;
    for (i = 0; i < n; ++i) 
    {
        for (j = i + 1; j < n && all_hands[i].points == all_hands[j].points; ++j)
        {
            if(checkequ(all_hands[i].cards, all_hands[j].cards))
                swap(all_hands, i, j);
        }
    }
}


int calculate_wins(hand *all_hands, int max)
{
    quickSort(all_hands, max);
    int x = 0;
    int i = 0;
    int total = 0;
    int high = 0;
    int pair = 0;
    int doubles = 0;
    int threes = 0;
    int fulls = 0;
    int fours = 0;
    int fives = 0;
    quickWins(all_hands, max);

//    printf("\n Hands sorted\n");
    while (x < max)
    {
        all_hands[x].rank = x + 1;
        all_hands[x].win = all_hands[x].bid * (x + 1);
        printf("Hand %d:\n", x);
        printf("cards:");
        while (i < 5)
        {
            printf(" %d", all_hands[x].cards[i]);
            i++;
        }
        total += all_hands[x].win;
        if(all_hands[x].points == 0)
            high++;
        if(all_hands[x].points == 1)
            pair++;
        if(all_hands[x].points == 2)
            doubles++;
        if(all_hands[x].points == 3)
            threes++;
        if(all_hands[x].points == 4)
            fulls++;
        if(all_hands[x].points == 5)
            fours++;
        if(all_hands[x].points == 6)
            fives++;
//        printf("\n");
        printf("\n%d * %d = %d\n", all_hands[x].bid, all_hands[x].rank, all_hands[x].win);
        printf("Points: %d\n", all_hands[x].points);
//        printf("rank: %d\n", all_hands[x].rank);
//        printf("wins: %d\n", all_hands[x].win);
        printf("Solution now[%d]: %d\n", x, total);
        printf("\n");
        i = 0;
        x++;
    }
    printf("High hands: %d\n", high);
    printf("pair hands: %d\n", pair);
    printf("2pair hands: %d\n", doubles);
    printf("triple hands: %d\n", threes);
    printf("fullhouse hands: %d\n", fulls);
    printf("4ofkind hands: %d\n", fours);
    printf("fives hands: %d\n", fives);
    printf("Solution: %d\n", total);
    return 0;
    
}

int mostFrequent(int *arr)
{
    int freqMax = 0;
    int len = 5;
    int element = arr[freqMax];
    // Iterate over all elements of array
    for (int i = 0; i < len; i++)
    {
        int frequency = 1;
        // Iterate over array from index i+1 till end of array
        for (int j= i+1; j < len; j++)
        {
            // Check if element at index j is a duplicate element
            if (arr[j] == arr[i])
            {
                // If yes, then increment the frequency count
                frequency++;
            }
        }
        // Check if the frequency of ith element
        // is the maximum frequency
        if (frequency > freqMax)
        {
            freqMax = frequency;
            element = arr[i];
        }
    }
    return freqMax;
}

int cardtonum(char c)
{
    if (c == 'A')
        return 1;
    if (c == 'T')
        return 10;
    if (c == 'J')
        return 11;
    if (c == 'Q')
        return 12;
    if (c == 'K')
        return 13;
    else
        return 0;
}

int fullhouse(int *hand)
{
    int x = 0;
    int pair1 = hand[0];
    int pair2 = 0;
    while (x < 5)
    {
        if (hand[x] != pair1)
            pair2 = hand[x];
        x++;
    }
    x = 0;
    while (x < 5)
    {
        if (hand[x] != pair1 && hand[x] != pair2)
            return 0;
        x++;
    }
    return 1;
}

int two_pairs(int *hand)
{
    int res = 0;
    int i = 0;
    int j = 0;

    while (i < 5) 
    {
        j = i + 1;
        while (j < 5) 
        {
            // When such pair got found
            if (hand[i] == hand[j]) 
            {
                res++;
                if (res == 2)
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

// int straight(int *hand)
// {
//     int low;
//     int high;
//     int x = 0;
// 
//     while (x < 5)
//     {
//         if (low > hand[x])
//             low = hand[x];
//         if (high < hand[x])
//             high = hand[x];
//         x++;
//     }
//     if (high - low == 4)
//         return 1;
//     else
//         return 0;
//     
// 
// }

int calculate_points(int *hand)
{
    int freq = 0;
    freq = mostFrequent(hand);
    if (freq == 5)
    {
//        printf("fives\n");
        return 6;
    }
    if (freq == 4)
    {
//        printf("fours\n");
        return 5;
    }
    if (freq == 3)
    {
//        printf("Checking 3: ");
        if (fullhouse(hand))
        {
//            printf("fullhouse\n");
            return 4;
        }
        else
        {
//            printf("threes\n");
            return 3;
        }
    }
    if (freq == 2)
    {
//        printf("Checking 2: ");
        if(two_pairs(hand))
        {
//            printf("twopairs\n");
            return 2;
        }
        else
        {
//            printf("pair\n");
            return 1;
        }
    }
//    printf("Checking 1: ");
//    if (straight(hand))
//    {
//        printf("straight\n");
//        return 5;
//    }
    else
    {
//        printf("Highcard\n");
        return 0;
    }

}



hand parser(int id, char *line)
{
//    printf("\nworking on line: %s\n", line);
    char *cpy;
    hand new;

    new.cards = (int *)malloc(sizeof(int) * 5);
    cpy = strdup(line);
    int x = 0;

    while (x < 5)
    {
        if (isdigit(cpy[x]))
            new.cards[x] = cpy[x] - '0';
        if (isalpha(cpy[x]))
            new.cards[x] = cardtonum(cpy[x]);
        x++;
    }
    x++;
    new.bid = atoi(&cpy[x]);
    new.points = calculate_points(new.cards);

//    //DEBUG
//    x = 0;
//    printf("Hand %d processed \n", id);
//    while (x < 5)
//    {
//        printf("hand: %d ", new.cards[x]);
//        x++;
//    }
//    printf(", bid %d\n", new.bid);
//    printf("Gets: %d\n", new.points);
//    printf("\n");

    return new;
}

int main(int argc, char **argv)
{
    char    line[1024];
    FILE    *fptr;
    int     result = 0;
    int     current = 0;
    hand    all_hands[1001];

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
        all_hands[current] = parser(current, line);
//        printf("result is now: %d\n", result);
        current++;
    }
    calculate_wins(all_hands, current);
    fclose(fptr);
    
//    printf("result: %d\n", result);
    return result;
 
}

