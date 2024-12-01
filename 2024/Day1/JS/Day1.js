// Advent of Code 2024 - Day 1
const fs = require('fs');
const path = require('path');

// Get the directory of the current script
const scriptDirectory = path.dirname(__filename);

// Resolve the path to input.txt
const inputFilePath = path.join(scriptDirectory, 'input.txt');

// Read input data
const input = fs.readFileSync(inputFilePath, 'utf-8').trim();

// Print input to the terminal
console.log('Input:', input);

// Solution for Part 1
// Add your solution here
