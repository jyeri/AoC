// Advent of Code 2024 - Day 19

/*
    --- Part 1 ---
    Fairly simple day, even my fever brains manages to undestand the problem, but the one off error with empty line in input made me redo the function more than enough times.
    The idea is to check if the string can be formed by the towels.
    I would check if the string starts with a towel, if it does, I would check if the rest of the string can be formed by the towels aswell.
    If it can, I would increment the answer.
    just because the example result was prioritizing the longest towel, I would sort the towels by length.



    --- Part 2 ---
    same thing as part 1, but I would memoize the results to make it more efficient.
    I would calculate all possible ways towels can combine to match a string.
    I would check if the string can be formed by the towels.
    If it can, I would increment the answer.
    so certain strings also has values that how many ways they can be formed by the towels.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    let instructions = [];
    let towels = [];
        const tester = [
            "r, wr, b, g, bwu, rb, gb, br",
            "",
            "brwrr",
            "bggr",
            "gbbr",
            "rrbgbr",
            "ubwu",
            "bwurrg",
            "brgr",
            "bbrgwb",
    ];

    const parsedInput = input;
    // const parsedInput = tester;

    for (const row of parsedInput) {
        // line by line
        if (row.includes(',')) {
            towels.push(row.split(', '));
        } 
        else if (row === '') {
            continue;
        }
        else {
            instructions.push(row);
        }
    }
    towels = towels.flat();
    towels.sort((a, b) => b.length - a.length);
    console.log(instructions);
    console.log(towels);

    // Check instruction at a time
    // backtracking function check if the string can be formed by the towels
    // by checking if the string starts with a towel
    // if it does, then check if the rest of the string can be formed by the towels aswell
    // i should have memoed this since it was more than necessary for efficient part2
    for (let i = 0; i < instructions.length; i++) {
        let current = instructions[i];
        console.log('Current:', current);
        const canForm = (str) => {
            if (str === '') 
                return true;
            for (let t of towels) {
                if (str.startsWith(t)) {
                    console.log('Using:', t);
                    if (canForm(str.slice(t.length))) {
                        return true;
                    }
                }
            }
            return false;
        };

        if (canForm(current)) {
            console.log('Can form:', current);
            p1_ans++;
        }
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    let instructions = [];
    let towels = [];
        const tester = [
            "r, wr, b, g, bwu, rb, gb, br",
            "",
            "brwrr",
            "bggr",
            "gbbr",
            "rrbgbr",
            "ubwu",
            "bwurrg",
            "brgr",
            "bbrgwb",
    ];

    const parsedInput = input;
    // const parsedInput = tester;

    for (const row of parsedInput) {
        // line by line
        if (row.includes(',')) {
            towels.push(row.split(', '));
        } 
        else if (row === '') {
            continue;
        }
        else {
            instructions.push(row);
        }
    }
    towels = towels.flat();
    towels.sort((a, b) => b.length - a.length);
    console.log(instructions);
    console.log(towels);

    // idea is to calculate all possible ways towels can combine to match a string
    const countWays = (str, memo) => {
        if (str === '') 
            return 1;

        if (memo.has(str)) 
            return memo.get(str); // Return cached result

        let ways = 0;
        for (let t of towels) {
            if (str.startsWith(t)) {
                ways += countWays(str.slice(t.length), memo);
            }
        }

        memo.set(str, ways); // Cache the result
        return ways;
    };

    for (let i = 0; i < instructions.length; i++) {
        let current = instructions[i];
        console.log('Current:', current);

        const memo = new Map(); // Create a new memoization map for each instruction
        const ways = countWays(current, memo);
        console.log('Ways to form:', current, 'Ways:', ways);
        p2_ans += ways;
    }

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
