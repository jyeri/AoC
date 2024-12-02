#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int isSafe(const char *line) {
    int numbers[SIZE];
    int count = 0;

    const char *token = line;
    char *end;

    while (*token != '\0') {
        int num = strtol(token, &end, 10);
        numbers[count++] = num;
        token = end;
        while (*token == ' ') token++;
    }

    // Check if the sequence is safe
    if (count < 2) return 1; // Safe if there are less than 2 numbers

    bool isAscending = numbers[1] > numbers[0]; // Determine initial direction
    for (int i = 0; i < count - 1; i++) {
        int diff = numbers[i + 1] - numbers[i];
        // Check for duplicates and differences > 3
        if (diff == 0 || abs(diff) > 3) {
            return 0; // Not safe
        }
        // Check for direction consistency
        if ((isAscending && diff < 0) || (!isAscending && diff > 0)) {
            return 0; // Not safe
        }
    }

    return 1; // Safe
}

char *modify_string(const char *line, int index) {
    int len = strlen(line);
    char *modified = malloc(len + 1); 
    int i = 0; 
    int j = 0; 
    int currentNumIndex = 0;

    while (line[i] != '\0') {
        if (currentNumIndex == index) {
            // Skip the number
            while (line[i] >= '0' && line[i] <= '9') {
                i++; // Skip digits
            }
            // Skip any trailing spaces
            while (line[i] == ' ') {
                i++;
            }
            currentNumIndex++;
            continue;
        }
        if (line[i] >= '0' && line[i] <= '9') {
            if (i == 0 || line[i - 1] == ' ') {
                currentNumIndex++;
            }
        }

        // Copy valid characters into the modified string
        modified[j++] = line[i++];
    }
    modified[j] = '\0';
    return modified;
}

int p1(const char *line) {
    int safe = 0;
    char *lineCopy = strdup(line);
    if (isSafe(lineCopy))
        safe = 1;
    else
        safe = 0;
    free(lineCopy);
    return safe;
}

int p2(const char *line) {
    int safe = 0;
    int rowSafeWithFix = 0;

    // Parse numbers from the line into an array
    int numbers[SIZE];
    int count = 0;

    const char *token = line;
    char *end;
    while (*token != '\0') {
        numbers[count++] = strtol(token, &end, 10);
        token = end;
        while (*token == ' ') token++;
    }

    // Check if the original line is safe
    char *lineCopy = strdup(line);
    if (isSafe(lineCopy)) {
        safe = 1;
    } else {
        printf("Checking for fix to row: %s\n", lineCopy);

        // Try removing each number
        for (int removeIndex = 0; removeIndex < count; removeIndex++) {
            // Construct a modified string without the `removeIndex` number
            char modifiedLine[SIZE] = "";
            for (int i = 0; i < count; i++) {
                if (i != removeIndex) {
                    char temp[20];
                    sprintf(temp, "%d ", numbers[i]);
                    strcat(modifiedLine, temp);
                }
            }
            modifiedLine[strlen(modifiedLine) - 1] = '\0';

            printf("With fix (remove index %d): %s\n", removeIndex, modifiedLine);

            if (isSafe(modifiedLine)) {
                rowSafeWithFix = 1;
                break;
            }
        }
    }

    free(lineCopy);
    return rowSafeWithFix + safe;
}

// Main function
int main() {
    char* input = read_input("./input.txt");
    char* inputCopy = strdup(input);
    char* line = strtok(inputCopy, "\n");

    int p1_ans = 0;
    int p2_ans = 0;

    int i = 0;
    while (line != NULL) {
        p1_ans += p1(line); // Check if the line is safe
        p2_ans += p2(line); // Check if the line is safe
        line = strtok(NULL, "\n");
    }

    // Print results
    printf("Part 1: %d\n", p1_ans);
    printf("Part 2: %d\n", p2_ans);

    // Free allocated memory
    free(input);
    free(inputCopy);

    return 0;
}