#!/bin/bash

# Step 1: Ask user for the year
read -p "Enter the year for Advent of Code (e.g., 2024): " YEAR

# Step 2: Ask user for the day
read -p "Enter the day for Advent of Code (e.g., 1 for Day 1): " DAY

# Step 3: Check if the session token is available
if [ -z "$AOC_SESSION" ]; then
    echo "Error: Session token not found. Please save it in your .bashrc as AOC_SESSION."
    exit 1
fi

# Step 4: Define the URL
URL="https://adventofcode.com/$YEAR/day/$DAY/input"

# Define the folder structure
DAY_FOLDER="Day$DAY"
JS_FOLDER="$DAY_FOLDER/JS"
C_FOLDER="$DAY_FOLDER/C"

# Define result file names
JS_RESULT_FILE="$JS_FOLDER/Day$DAY.js"
C_RESULT_FILE="$C_FOLDER/Day$DAY.c"

# Step 5: Create folders only if they don't exist
if [ ! -d "$DAY_FOLDER" ]; then
    mkdir -p "$JS_FOLDER" "$C_FOLDER"
    echo "Created folders: $DAY_FOLDER, $JS_FOLDER, and $C_FOLDER"
else
    echo "Folders already exist: $DAY_FOLDER, $JS_FOLDER, and $C_FOLDER"
fi

# Create empty result files if they don't already exist
if [ ! -f "$JS_RESULT_FILE" ]; then
    touch "$JS_RESULT_FILE"
    echo "Created file: $JS_RESULT_FILE"
else
    echo "File already exists: $JS_RESULT_FILE"
fi

if [ ! -f "$C_RESULT_FILE" ]; then
    touch "$C_RESULT_FILE"
    echo "Created file: $C_RESULT_FILE"
else
    echo "File already exists: $C_RESULT_FILE"
fi

# Define the output file paths for fetched input
JS_INPUT_FILE="$JS_FOLDER/input.txt"
C_INPUT_FILE="$C_FOLDER/input.txt"

# Step 6: Fetch the data
echo "Fetching data for Year $YEAR, Day $DAY..."
curl -s -b "session=$AOC_SESSION" "$URL" -o "$JS_INPUT_FILE"

# Step 7: Check if fetch was successful
if [ $? -eq 0 ] && [ -s "$JS_INPUT_FILE" ]; then
    echo "Data successfully fetched and saved to $JS_INPUT_FILE."
    # Copy the fetched input to the C folder
    cp "$JS_INPUT_FILE" "$C_INPUT_FILE"
    echo "Data also copied to $C_INPUT_FILE."
else
    echo "Failed to fetch data. Please check your session token, date, or ensure the day is unlocked."
    # Clean up empty files if fetch failed
    rm -f "$JS_INPUT_FILE" "$C_INPUT_FILE"
fi