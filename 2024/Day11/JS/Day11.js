// Advent of Code 2024 - Day 11

/*
    --- Part 1 ---
    1st part was fairly simple, we take the input and split it into an array of numbers.
    we go through the array and for each number we check if it is 0, if it is we add 1 to the next line.
    if the number is even we split it in half and add both halves to the next line.
    if the number is odd we multiply it by 2024 and add it to the next line.
    we repeat this process X amount of times to the nextline.


    --- Part 2 ---
    First time ever i stumbled across memory issues in JS.
    decided to go over the direction of handling the numbers in a map instead of an array.
    that way for example

    [ 127, 2, 127, 4, 5, 6, 127, 8, 127, 10 ]
    would be stored as =>

    127: 4
    2: 1
    4: 1
    ...

    this way i can keep track of the counts of each number instead of having to store multiple copies of the same number.

    Most efficient way? probably not. Easiest for me to grasp and implement? Yes.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
        const tester = [
            "125 17"
    ];
    let results = [];

    const solve = (line, amt) => {
        for (i = 0; i < amt; i++) {
            let nextline = [];
            for (const number of line) {
                let charnmbr = number.toString();
                let middle = 0;
                let charnmbr1 = '';
                let charnmbr2 = '';

                if (number === 0)
                    nextline.push(1);
                else if (charnmbr.length % 2 === 0)
                {
                    middle = charnmbr.length / 2;
                    charnmbr1 = charnmbr.slice(0, middle);
                    charnmbr2 = charnmbr.slice(middle);
                    nextline.push(Number(charnmbr1));
                    nextline.push(Number(charnmbr2));
                }
                else
                {
                    nextline.push(number * 2024);
                }
            }
            line = nextline;
            console.log("After ", i, "blink:", line);
        }
        return line;
    }

    const oneline = input[0].split(' ').map(Number);

    p1_ans = solve(oneline, 25);

    console.log('Part 1:', p1_ans.length);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    const tester = [
            "125 17"
    ];
    const oneline = input[0].split(' ').map(Number);

    const solve = (line, amt) => {
        // Map lets me track the counts of number instead of having to store multiple copies of the same number
        // This is more memory efficient. atleast i think so
        let numberCounts = new Map();

        // Initialize the map with the starting numbers
        for (const num of line) {
            numberCounts.set(num, (numberCounts.get(num) || 0) + 1);
        }

        for (let i = 0; i < amt; i++) {
            //nextCounts in just a new map to keep values for next iteration.
            const nextCounts = new Map();
            
            // allows me to go over multiple same digits in row, instead going over each digit in real order.
            for (const [number, count] of numberCounts) {
                const charnmbr = number.toString();

                if (number === 0) {
                    nextCounts.set(1, (nextCounts.get(1) || 0) + count);
                } else if (charnmbr.length % 2 === 0) {
                    const middle = charnmbr.length / 2;
                    const left = Number(charnmbr.slice(0, middle));
                    const right = Number(charnmbr.slice(middle));

                    nextCounts.set(left, (nextCounts.get(left) || 0) + count);
                    nextCounts.set(right, (nextCounts.get(right) || 0) + count);
                } else {
                    const newNumber = number * 2024;
                    nextCounts.set(newNumber, (nextCounts.get(newNumber) || 0) + count);
                }
            }

            numberCounts = nextCounts;

            console.log("after " + (i + 1) + " blink: " + numberCounts.size + " different elements");
        }

        return numberCounts;
    };

    const resultCounts = solve(oneline, 75);

    // check the total number of numbers in the map
    let totalNumbers = 0;
    for (const count of resultCounts.values()) {
        totalNumbers += count;
    }

    console.log('Part 1:', totalNumbers);
};

solvePart1();
solvePart2();
