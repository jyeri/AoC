// Advent of Code 2024 - Day 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// https://www.geeksforgeeks.org/regular-expressions-in-c/ regex for C.

// rm_so is the start of the match
// rm_eo is the end of the match

// Function to read input from file
char* read_input(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';
    return buffer;
}

int p1(char *input)
{
    const char *pattern = "mul\\(([0-9]+),([0-9]+)\\)";
    regex_t regex;
    regmatch_t matches[3];
    char *pointer = input;
    int ans_p1 = 0;

    // Compile the regex
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        perror("Failed to compile regex");
        exit(EXIT_FAILURE);
    }

    // Execute the regex
    while (*pointer != '\0') {
        if (regexec(&regex, pointer, 3, matches, 0) == 0) {
            // Extract the match for the entire pattern
            int mEnd = matches[0].rm_eo;

            // Extract x and y values from capturing groups
            int xLength = matches[1].rm_eo - matches[1].rm_so;
            int yLength = matches[2].rm_eo - matches[2].rm_so;

            char x[xLength + 1];
            char y[yLength + 1];

            memcpy(x, pointer + matches[1].rm_so, xLength);
            x[xLength] = '\0';

            memcpy(y, pointer + matches[2].rm_so, yLength);
            y[yLength] = '\0';

            // Convert x and y to integers
            int xInt = atoi(x);
            int yInt = atoi(y);

            // Print and add to the sum
            printf("mul(%d,%d) = %d\n", xInt, yInt, xInt * yInt);
            ans_p1 += xInt * yInt;

            // Move the pointer forward to continue searching
            pointer += mEnd;
        } else {
            break;
        }
    }

    printf("Answer to part 1: %d\n", ans_p1);
    regfree(&regex);

    return 0;
}

int p2(char *input)
{
    const char *pattern_p2 =  "mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)";
    regex_t regex;
    regmatch_t matches[3];
    char *pointer = input;
    int decider = 1;
    int ans_p2 = 0;

    // Compile the regex
    if (regcomp(&regex, pattern_p2, REG_EXTENDED)) {
        perror("Failed to compile regex");
        exit(EXIT_FAILURE);
    }

    // Execute the regex
    while (*pointer != '\0') {
        if (regexec(&regex, pointer, 3, matches, 0) == 0) {
            // Extract the match for the entire pattern
            int mStart = matches[0].rm_so;
            int mEnd = matches[0].rm_eo;

            //instead of extracting x and y values from capturing groups, we will check if the match is "do()" or "don't()"
            char matched[mEnd - mStart + 1];
            memcpy(matched, pointer + mStart, mEnd - mStart);

            if (strncmp(matched, "do()", 4) == 0) {
                printf("do()\n");
                decider = 1;
            } else if (strncmp(matched, "don't()", 7) == 0) {
                printf("don't()\n");
                decider = 0;
            }
            else{
                if (decider == 1) {
                    // because there is not dont() present, we can mul(X,Y)
                    int xLength = matches[1].rm_eo - matches[1].rm_so;
                    int yLength = matches[2].rm_eo - matches[2].rm_so;

                    char x[xLength + 1];
                    char y[yLength + 1];

                    memcpy(x, pointer + matches[1].rm_so, xLength);
                    x[xLength] = '\0';

                    memcpy(y, pointer + matches[2].rm_so, yLength);
                    y[yLength] = '\0';

                    // Convert x and y to integers
                    int xInt = atoi(x);
                    int yInt = atoi(y);

                    // Print and add to the sum
                    printf("mul(%d,%d) = %d\n", xInt, yInt, xInt * yInt);
                    ans_p2 += xInt * yInt;
                }
            }
            // Move the pointer forward to continue searching
            pointer += mEnd;
        } else {
            break;
        }
    }

    printf("Answer to part 2: %d\n", ans_p2);
    regfree(&regex);

    return 0;
}


int main() {
    // Read input
    char* input = read_input("./input.txt");

    p1(input);
    p2(input);

    // Free allocated memory
    free(input);

    return 0;
}