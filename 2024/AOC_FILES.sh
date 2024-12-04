#!/bin/bash

# Step 1: Ask user for the year & day
read -p "Enter the year for Advent of Code (e.g., 2024): " YEAR
read -p "Enter the day for Advent of Code (e.g., 7 for Day 7): " DAY

# Step 2: Check if the session token is available
if [ -z "$AOC_SESSION" ]; then
    echo "Error: Session token not found. Please save it in your .bashrc as AOC_SESSION."
    exit 1
fi

# Step 3: Define the URL and folder structure with file names
URL="https://adventofcode.com/$YEAR/day/$DAY/input"
DAY_FOLDER="Day$DAY"
JS_FOLDER="$DAY_FOLDER/JS"
C_FOLDER="$DAY_FOLDER/C"
JS_RESULT_FILE="$JS_FOLDER/Day$DAY.js"
C_RESULT_FILE="$C_FOLDER/Day$DAY.c"

# Step 4: Create folders ONLY if they don't exist, after populate the template files
if [ ! -d "$DAY_FOLDER" ]; then
    mkdir -p "$JS_FOLDER" "$C_FOLDER"
    echo "Created folders: $DAY_FOLDER, $JS_FOLDER, and $C_FOLDER"
else
    echo "Folders already exist: $DAY_FOLDER, $JS_FOLDER, and $C_FOLDER"
fi

# Create and populate JS result file
if [ ! -f "$JS_RESULT_FILE" ]; then
    cat > "$JS_RESULT_FILE" <<EOF
// Advent of Code $YEAR - Day $DAY
const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8').split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;

    for (const line of input) {
        // line by line
        console.log(`Line: ${line}`);
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;

    for (const line of input) {
        // line by line
    }

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
EOF
    chmod +x "$JS_RESULT_FILE"
    echo "Created file with basic template: $JS_RESULT_FILE"
else
    echo "File already exists: $JS_RESULT_FILE"
fi

# Create and populate C result file
if [ ! -f "$C_RESULT_FILE" ]; then
    cat > "$C_RESULT_FILE" <<EOF
// Advent of Code $YEAR - Day $DAY
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
    buffer[length] = '\\0';
    return buffer;
}

int solvePart1(char* input) {
    int p1_ans = 0;

    char* line = strtok(input, "\\n");
    while (line != NULL) {
        // line by line
        printf("Line: %s\\n", line);
        line = strtok(NULL, "\\n");
    }

    printf("Part 1: %d\\n", p1_ans);
    return p1_ans;
}

int solvePart2(char* input) {
    int p2_ans = 0;

    char* line = strtok(input, "\\n");
    while (line != NULL) {
        // line by line
        line = strtok(NULL, "\\n");
    }

    printf("Part 2: %d\\n", p2_ans);
    return p2_ans;
}

int main() {
    char* input = read_input("./input.txt");
    printf("Input:\\n%s\\n", input);

    solvePart1(input);
    solvePart2(input);

    free(input);
    return 0;
}
EOF
    chmod +x "$C_RESULT_FILE"
    echo "Created file with basic template: $C_RESULT_FILE"
else
    echo "File already exists: $C_RESULT_FILE"
fi

# Define the output file paths for fetched input
JS_INPUT_FILE="$JS_FOLDER/input.txt"
C_INPUT_FILE="$C_FOLDER/input.txt"

# Step 5: Fetch the data from the Advent of Code website, using the session token
echo "Fetching data for Year $YEAR, Day $DAY..."
curl -s -b "session=$AOC_SESSION" "$URL" -o "$JS_INPUT_FILE"

# Step 6: Check if fetch was successful
if [ $? -eq 0 ] && [ -s "$JS_INPUT_FILE" ]; then
    echo "Data successfully fetched and saved to $JS_INPUT_FILE."
    cp "$JS_INPUT_FILE" "$C_INPUT_FILE"
    echo "Data also copied to $C_INPUT_FILE."

    # Optional: Compile the C file
    gcc -o "$C_FOLDER/Day$DAY" "$C_RESULT_FILE"

else
    echo "Failed to fetch data. Please check your session token, date, or ensure the day is unlocked."
    # Clean up empty files if fetch failed
    rm -f "$JS_INPUT_FILE" "$C_INPUT_FILE"
fi