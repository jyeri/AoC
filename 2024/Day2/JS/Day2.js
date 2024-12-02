// Advent of Code 2024 - Day 2
const fs = require('fs');
const path = require('path');

// Get the directory of the current script
const scriptDirectory = path.dirname(__filename);

// Resolve the path to input.txt
const inputFilePath = path.join(scriptDirectory, 'input.txt');

// Read input data
const input = fs.readFileSync(inputFilePath, 'utf-8').trim();

let ans_p1 = 0;
let ans_p2 = 0;
const parsedInput = input.split('\n').map(line => line.split(' ').map(Number));

const isSafe = (row) => {
    let isAscending = null;
    for (let i = 0; i < row.length - 1; i++) {
        const diff = row[i + 1] - row[i];
        if (diff === 0) return false;
        if (Math.abs(diff) > 3) return false;
        if (isAscending === null) {
            isAscending = diff > 0;
        } else if ((isAscending && diff < 0) || (!isAscending && diff > 0)) {
            return false;
        }
    }
    return true;
};

const p1 = () => {
    for (const row of parsedInput) {
        if (isSafe(row)) {
            ans_p1++;
            continue;
        }
    }
    console.log('Answer Part 1:', ans_p1);
};

const p2 = () => {
    for (const row of parsedInput) {
        if (isSafe(row)) {
            ans_p2++;
            continue;
        }
        let rowSafeWithDampener = false;
        for (let i = 0; i < row.length; i++) {
            const modifiedRow = row.slice(0, i).concat(row.slice(i + 1));
            if (isSafe(modifiedRow)) {
                rowSafeWithDampener = true;
                break;
            }
        }
        if (rowSafeWithDampener) {
            ans_p2++;
        }
    }
    console.log('Answer Part 2:', ans_p2);
    return ans_p2;
};

p1();
p2();