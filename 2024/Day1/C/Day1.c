// Advent of Code 2024 - Day 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 10000

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

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


int p1(int *Array1, int *Array2, int line_count) {
    int ans = 0;
    int temp = 0;
    for (int i = 0; i < line_count; i++) {
        temp = Array1[i] - Array2[i];
        ans += abs(temp);
    }
    return ans;
}

int p2(int *Array1, int *Array2, int line_count) {
    int ans = 0;
    int multiplier = 0;
    int temp = 0;
    for (int i = 0; i < line_count; i++) {
        multiplier = 0;
        for (int j = 0; j < line_count; j++) {
            if (Array1[i] == Array2[j]) {
                multiplier += 1;
            }
        }
        ans += Array1[i] * multiplier;
    }
    return ans;
}

int main() {
    char* input = read_input("./input.txt");

    int line_count = 0;
    int Array1[SIZE] = {0};
    int Array2[SIZE] = {0};
    int ans_part1 = 0;
    int ans_part2 = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        int num1 = 0, num2 = 0;
        sscanf(line, "%d   %d", &num1, &num2);
        Array1[line_count] = num1;
        Array2[line_count] = num2;
        line_count++;
        line = strtok(NULL, "\n"); // next line
    }

    qsort(Array1, line_count, sizeof(int), cmpfunc);
    qsort(Array2, line_count, sizeof(int), cmpfunc);

    ans_part1 = p1(Array1, Array2, line_count);
    ans_part2 = p2(Array1, Array2, line_count);

    // Print the result
    printf("Part 1: %d\n", ans_part1);
    printf("Part 2: %d\n", ans_part2);

    free(input);
    return 0;
}