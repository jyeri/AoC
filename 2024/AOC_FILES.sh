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
const path = require('path');

// Get the directory of the current script
const scriptDirectory = path.dirname(__filename);

// Resolve the path to input.txt
const inputFilePath = path.join(scriptDirectory, 'input.txt');

// Read input data
const input = fs.readFileSync(inputFilePath, 'utf-8').trim();

// Print parsed input to the terminal
const parsedInput = input.split('\n').map(line => line.split(' ').map(Number));

console.log('Parsed Input:', parsedInput);

// Solution for Part 1
const p1 = () => {
    let ans_p1 = 0;
 //   for (const row of parsedInput) {
 //   
 //   }
    console.log('Answer Part 1:', ans_p1);
};

//solution for part 2
const p2 = () => {
    let ans_p2 = 0;
//    for (const row of parsedInput) {
//
//    }
    console.log('Answer Part 2:', ans_p2);
    return ans_p2;
};

p1();
p2();
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
    buffer[length] = '\\0';
    return buffer;
}

int main() {
    // Read input
    char* input = read_input("./input.txt");

    // Print input to the terminal
    printf("Input:\\n%s\\n", input);

    // Free allocated memory
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