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
console.log('Input:\n', input);

let ans_p1 = 0;
let ans_p2 = 0;
const parsedInput = input.split('\n').map(input => input.split('   ').map(Number));

let array1 = [];
let array2 = [];
for (let i = 0; i < parsedInput.length; i++) {
    array1.push(parsedInput[i][0]);
    array2.push(parsedInput[i][1]);
}
array1.sort();
array2.sort();

// Solution for Part 1
const part1 = () => {
    for (let i = 0; i < array1.length; i++) {
        ans_p1 += Math.abs(array1[i] - array2[i]);
    }
    console.log('Answer Part 1:', ans_p1);
};

const part2 = () => {
    for (let i = 0; i < array1.length; i++) {
        let multiplier = 0;
        for (let j = 0; j < array2.length; j++) {
            if (array1[i] === array2[j]) {
                multiplier += 1;
            }
        }
        ans_p2 += multiplier * array1[i];
    }
    console.log('Answer Part 2:', ans_p2);

};

part1();
part2();
