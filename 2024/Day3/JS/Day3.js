// Advent of Code 2024 - Day 3
const fs = require('fs');
const path = require('path');

// Get the directory of the current script
const scriptDirectory = path.dirname(__filename);

// Resolve the path to input.txt
const inputFilePath = path.join(scriptDirectory, 'input.txt');

// Read input data
const input = fs.readFileSync(inputFilePath, 'utf-8').trim();

console.log('Input:\n', input);

const regex = /mul\((\d+),(\d+)\)/g;

// regex to match all the patterns, mul(X,Y), do(), don't()
const regexp2 = /mul\((\d+),(\d+)\)|do\(\)|don't\(\)/g;

// Print parsed input to the terminal
const parsedInput = [];

console.log('Parsed Input:', parsedInput);

// Solution for Part 1
const p1 = () => {
    let ans_p1 = 0;
    let match; 
    while ((match = regex.exec(input)) !== null) {
        console.log(match[1], "*" ,match[2], "=", match[1] * match[2]);
        ans_p1 += match[1] * match[2];
    }
    console.log('Answer Part 1:', ans_p1);
};

//solution for part 2
const p2 = () => {
    let test = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";
    let ans_p2 = 0;
    let match;
    let decider = 1;
    while ((match = regexp2.exec(input)) !== null) {
        if (match[0] === "do()") {
            console.log("do()");
            decider = 1;
        } else if (match[0] === "don't()") {
            console.log("don't()");
            decider = 0;
        } else if (decider === 1) {
            console.log(match[1], "*" ,match[2], "=", match[1] * match[2]);
            ans_p2 += match[1] * match[2];
        }
    }
    console.log('Answer Part 2:', ans_p2);
    return ans_p2;
};

p1();
p2();
