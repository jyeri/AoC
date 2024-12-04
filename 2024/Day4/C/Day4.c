// Advent of Code 2024 - Day 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int solvePart1(char* input) {
    int p1_ans = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        // line by line
        printf("Line: %s\n", line);
        line = strtok(NULL, "\n");
    }

    printf("Part 1: %d\n", p1_ans);
    return p1_ans;
}

int solvePart2(char* input) {
    int p2_ans = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        // line by line
        line = strtok(NULL, "\n");
    }

    printf("Part 2: %d\n", p2_ans);
    return p2_ans;
}

int main() {
    char* input = read_input("./input.txt");
    printf("Input:\n%s\n", input);

    solvePart1(input);
    solvePart2(input);

    free(input);
    return 0;
}
