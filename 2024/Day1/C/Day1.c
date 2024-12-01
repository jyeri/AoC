// Advent of Code 2024 - Day 1
#include <stdio.h>
#include <stdlib.h>

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

int main() {
    // Read input
    char* input = read_input("./input.txt");

    // Print input to the terminal
    printf("Input:\n%s\n", input);

    // Free allocated memory
    free(input);
    return 0;
}
