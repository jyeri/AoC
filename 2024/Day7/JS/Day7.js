// Advent of Code 2024 - Day 7
const fs = require('fs');
const { join } = require('path');
const input = fs.readFileSync('./input.txt', 'utf8').split('\n');

const concatter = (a, b) => {
    return parseInt(`${a}${b}`);
}

// Function to generate all possible combinations of given length
const generateCombinations = (length, ops) => {
    let combinations = [];

    const generate = (comb, depth) => {
        if (depth === length) {
            // we have reached the end of the combination, so we push the comb we are currently working on to the combinations array
            combinations.push(comb.join(''));
            return;
        }

        for (const op of ops) {
            // we push the operator to the comb array and then call the function recursively with the new comb array and depth + 1
            comb.push(op);
            generate(comb, depth + 1);
            // back tracking, we pop the last element of the comb array so we can try the other operator
            comb.pop();
        }
    };
    // recursive apprcoach since we have to generate all possible combinations, not just swap last one like last iteration I had.
    generate([], 0);

    return combinations;
};

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
        const tester = [
            "190: 10 19",
            "3267: 81 40 27",
            "83: 17 5",
            "156: 15 6",
            "7290: 6 8 6 15",
            "161011: 16 10 13",
            "192: 17 8 14",
            "21037: 9 7 18 13",
            "292: 11 6 16 20"
    ];
    
    let ops = ['+', '*'];

    for (const row of input) {
        // line by line
//        console.log(row);
        let to_add = 0;
        let ok = false;
        let parts = row.split(':');
        let sum = parseInt(parts[0]);
        let numbers = parts[1].split(' ').map(x => parseInt(x.trim())).filter(x => !isNaN(x));

        // first ill make array of all possible combinations of the given numbers (1 + 2 + 3, 1 + 2 * 3, 1 * 2 + 3, 1 * 2 * 3)
        // added the -1, since there must alway be 1 more number than operator
        const combinations = generateCombinations(numbers.length - 1, ops);
//        console.log("possible combinations:\n", combinations);

        // then i will check if the sum is equal to the numbers using all of the possible combinations of given 2 operators (+, *)
        for (const comb of combinations) {
            to_add = 0;
            ok = false;
            let combinationSum = numbers[0];
            for (let i = 0; i < comb.length; i++) {
                if (comb[i] === '+') {
                    combinationSum += numbers[i + 1];
                } else {
                    combinationSum *= numbers[i + 1];
                }
            }
            if (combinationSum === sum) {
                ok = true;
                to_add = combinationSum;
                break;
            }
        }
        if (ok) {
            p1_ans += to_add;
        }
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    const tester = [
        "190: 10 19",
        "3267: 81 40 27",
        "83: 17 5",
        "156: 15 6",
        "7290: 6 8 6 15",
        "161011: 16 10 13",
        "192: 17 8 14",
        "21037: 9 7 18 13",
        "292: 11 6 16 20"
];

let ops = ['+', '*', '|'];

for (const row of input) {
    // line by line
//    console.log(row);
    let to_add = 0;
    let ok = false;
    let parts = row.split(':');
    let sum = parseInt(parts[0]);
    let numbers = parts[1].split(' ').map(x => parseInt(x.trim())).filter(x => !isNaN(x));

    // first ill make array of all possible combinations of the given numbers (1 + 2 + 3, 1 + 2 * 3, 1 * 2 + 3, 1 * 2 * 3)
    // added the -1, since there must alway be 1 more number than operator
    const combinations = generateCombinations(numbers.length - 1, ops);
//    console.log("possible combinations:\n", combinations);

    // then i will check if the sum is equal to the numbers using all of the possible combinations of given 2 operators (+, *)
    for (const comb of combinations) {
        to_add = 0;
        ok = false;
        let combinationSum = numbers[0];
        // i have to create a copy since the concatter result is modified into numbers array
        let tempNumbers = [...numbers];
        for (let i = 0; i < comb.length; i++) {
            if (comb[i] === '+') {
                combinationSum += numbers[i + 1];
            } else if (comb[i] === '*') {
                combinationSum *= numbers[i + 1];
            }
            else if (comb[i] === '|') {
                let concatted = concatter(combinationSum, tempNumbers[i + 1]);
                combinationSum = concatted;

            }
        }
        if (combinationSum === sum) {
            ok = true;
            to_add = combinationSum;
            break;
        }
    }
    if (ok) {
        p2_ans += to_add;
    }
}

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
