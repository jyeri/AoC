// Advent of Code 2024 - Day 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    char dir;
} Direction;


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

int inbounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int solvePart1(char** input_org, int rows) {
    int part1_res = 0;
    Direction start;
    Direction current;
    Direction next;
    Direction UP = {-1, 0, 'U'};
    Direction DOWN = {1, 0, 'D'};
    Direction LEFT = {0, -1, 'L'};
    Direction RIGHT = {0, 1, 'R'};
    Direction dir[] = 
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    char *tester[] = {
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#...",
    };
    int tester_rows = 10;
    int tester_cols = strlen(tester[0]);
    int cols = strlen(input_org[0]);

    char **modifiable_tester = malloc(tester_rows * sizeof(char *));
    for (int i = 0; i < tester_rows; i++) {
        modifiable_tester[i] = strdup(tester[i]);
    }

    char **input = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        input[i] = strdup(input_org[i]);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (input[i][j] == '^') {
                start.y = j;
                start.x = i;
                start.dir = 'U';
                printf("Start: %d, %d\n", start.x, start.y);
                break;
            }
        }
    }

    int dirInd = 0;
    current = start;

    while (inbounds(current.x, current.y, rows, cols)) {
        printf("Current: %d, %d\n", current.x, current.y);
        next.x = current.x + dir[dirInd].x;
        next.y = current.y + dir[dirInd].y;
        if (!inbounds(next.x, next.y, rows, cols)) {
            current = next;
            part1_res++;
            break;
        }
        if (input[next.x][next.y] == '#') {
            printf("Hit wall\n");
            dirInd++;
            if (dirInd == 4) {
                dirInd = 0;
            }
            continue;
        }
        current = next;
        if (input[current.x][current.y] == '.') {
            input[current.x][current.y] = 'X'; 
            part1_res++;
        }
    }

    printf("exit at: %d, %d\n", current.x, current.y);
    printf("Part 1 result: %d\n", part1_res);

    free(modifiable_tester);
    free(input);
    return part1_res;
}

int solvePart2(char** input_org, int rows) {
    int part2_res = 0;

    Direction start;
    Direction current;
    Direction next;
    Direction UP = {-1, 0, 'U'};
    Direction DOWN = {1, 0, 'D'};
    Direction LEFT = {0, -1, 'L'};
    Direction RIGHT = {0, 1, 'R'};
    Direction dir[] = 
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    char *tester[] = {
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#...",
    };
    int tester_rows = 10;
    int tester_cols = strlen(tester[0]);
    int cols = strlen(input_org[0]);

    char **modifiable_tester = malloc(tester_rows * sizeof(char *));
    for (int i = 0; i < tester_rows; i++) {
        modifiable_tester[i] = strdup(tester[i]);
    }

    char **input = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        input[i] = strdup(input_org[i]);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (input[i][j] == '^') {
                start.y = j;
                start.x = i;
                start.dir = 'U';
                printf("Start: %d, %d\n", start.x, start.y);
            }
        }
    }

    int dirInd = 0;
    current = start;

    while (inbounds(current.x, current.y, rows, cols)) {
        printf("Current: %d, %d\n", current.x, current.y);
        next.x = current.x + dir[dirInd].x;
        next.y = current.y + dir[dirInd].y;
        if (!inbounds(next.x, next.y, rows, cols)) {
            current = next;
            part2_res++;
            break;
        }
        if (input[next.x][next.y] == '#') {
            printf("Hit wall\n");
            dirInd++;
            if (dirInd == 4) {
                current.dir = dir[dirInd].dir;
                dirInd = 0;
            }
            continue;
        }
        current = next;
        if (input[current.x][current.y] == '.') {
            input[current.x][current.y] = current.dir;
            part2_res++;
        }
    }
    
    free(modifiable_tester);
    free(input);
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