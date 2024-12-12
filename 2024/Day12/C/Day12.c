// Advent of Code 2024 - Day 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    --- Part 1 ---
    General approach

    ---- Part 2 ---
    General approach

*/

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Failed to allocate memory for file buffer");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, length, file);
    fclose(file);

    buffer[length] = '\0';
    return buffer;
}

char **string_split(char* buffer, int* out_row_count) {
    char **array = NULL;
    char *line = strtok(buffer, "\n");
    int rows = 0;

    while (line) {
        array = realloc(array, sizeof(char*) * (rows + 1));
        if (!array) {
            perror("Failed to allocate memory for lines array");
            exit(EXIT_FAILURE);
        }
        array[rows] = strdup(line);
        if (!array[rows]) {
            perror("Failed to allocate memory for line string");
            exit(EXIT_FAILURE);
        }
        rows++;
        line = strtok(NULL, "\n");
    }

    *out_row_count = rows;
    return array;
}

char **read_input(const char *filename, int *out_row_count) {
    char *buffer = read_file(filename);
    char **array = string_split(buffer, out_row_count);
    free(buffer);
    return array;
}

int solvePart1(char** input, int rows) {
    int part1_res = 0;

    for (int i = 0; i < rows; i++) {
        printf("Line: %s\n", input[i]);
    }

    printf("Part 1 result: %d\n", part1_res);
    return part1_res;
}

int solvePart2(char** input, int rows) {
    int part2_res = 0;

    for (int i = 0; i < rows; i++) {
        printf("Line: %s\n", input[i]);
    }

    printf("Part 2 Result: %d\n", part2_res);
    return part2_res;
}

int main() {
    int row_count = 0;
    char **input = read_input("./input.txt", &row_count);
    int rows = row_count;

    solvePart1(input, rows);
    solvePart2(input, rows);

    for (int i = 0; i < rows; i++) {
        free(input[i]);
    }
    free(input);
    return 0;
}
