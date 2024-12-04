// Advent of Code 2024 - Day 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
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

int check (int x, int y, int direction, char** test, Direction* directions) {
    char target[4] = "XMAS";
    int i = 0;
    while (target[i] == test[x][y]) {
        x += directions[direction].x;
        y += directions[direction].y;
        i++;
        if (i == 4) {
            return 1;
        }
    }
    return 0;
}

int solvePart1(char** input, int rows) {
    int part1_res = 0;
    char* test[] = {
        "MMMSXXMASM",
        "MSAMXMSMSA",
        "AMXSXMAAMM",
        "MSAMASMSMX",
        "XMASAMXAMM",
        "XXAMMXXAMA",
        "SMSMSASXSS",
        "SAXAMASAAA",
        "MAMMMXMMMM",
        "MXMXAXMASX"
    };
    //(x,y)
    Direction directions[8] = {
        {0, 1}, // right
        {1, 0}, // down
        {0, -1}, // left
        {-1, 0}, // up
        {-1, -1},  // up-left
        {-1, 1},  // up-right
        {1, 1},  // down-right
        {1,  -1}  // down-left

    };

    int i = 0;
    int x = 0;
    int y = 0;

    int cols = strlen(input[0]);
    char target[4] = "XMAS";

    printf("Rows: %d\n", rows);
    printf("Cols: %d\n", cols);

    while (x < rows) {
        y = 0;
        while (y < cols) {
            if (input[x][y] == target[0]) {
                i = 0;
                while (i < 8)
                {
                    if (x + (directions[i].x * 3) < 0 || x + (directions[i].x * 3) >= rows || y + (directions[i].y * 3) < 0 || y + (directions[i].y * 3) >= cols) {
                        i++;
                        continue;
                    }
                    if (check(x, y, i, input, directions))
                    {
                        printf("Found at (%d, %d)\n", x, y);
                        part1_res++;
                    }
                    i++;
                }
            }
            y++;
        }
        x++;
    }

    printf("Part 1 result: %d\n", part1_res);
    return part1_res;
}

int check_part2(int x, int y, char **input, Direction *directions) {
    int i = 0;
    while (i < 4)
    {
        int newX1 = x + directions[i].x;
        int newY1 = y + directions[i].y;
        int newX2 = x + directions[i + 1].x;
        int newY2 = y + directions[i + 1].y;
        if ((input[newX1][newY1] != 'M' && input[newX1][newY1] !='S') || (input[newX2][newY2] != 'M' && input[newX2][newY2] !='S'))
        {
            return 0;
        }
        if (input[newX1][newY1] == input[newX2][newY2])
        {
            return 0;
        }
        i += 2;
    }
    return 1;
}

int solvePart2(char **input, int rows) {
    int part2_res = 0;

    Direction directions[4] = {
    {-1, -1},  // up-left
    {1, 1},  // down-right
    {-1, 1},  // up-right
    {1,  -1}  // down-left
    };

    int i = 0;
    int x = 1;
    int y = 1;
    int cols = strlen(input[0]);

    while (x < rows - 1)
    {
        y = 1;
        while (y < cols - 1)
        {
            if (input[x][y] == 'A' && check_part2(x, y, input, directions))
            {
                printf("Found at (%d, %d)\n", x, y);
                part2_res++;
            }
            y++;
        }
        x++;
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
