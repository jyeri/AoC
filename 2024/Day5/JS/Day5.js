// Advent of Code 2024 - Day 5
const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8').split('\n');

// make 2 arrays from input first consist the rule set = number - has to come before this number
// second array is the is instructions, each line is set of numbers that needs to be place in result array in order that follows input rules

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    const tester = [
    "47|53",
    "97|13",
    "97|61",
    "97|47",
    "75|29",
    "61|13",
    "75|53",
    "29|13",
    "97|29",
    "53|29",
    "61|53",
    "97|53",
    "61|29",
    "47|13",
    "75|47",
    "97|75",
    "47|61",
    "75|61",
    "47|29",
    "75|13",
    "53|13",
    "\n",
    "75,47,61,53,29",
    "97,61,53,29,13",
    "75,29,13",
    "75,97,47,61,53",
    "61,13,29",
    "97,13,75,29,47"
];
    let arraya = [];
    let arrayb = [];
    let intructions = [];

    for (const row of input) {
        // line by line
        console.log(row);
        while (row.includes('|')) {
            let [a, b] = row.split('|');
            arraya.push(a);
            arrayb.push(b);
//            console.log("ArrA: ", arraya, "ArrB: ",  arrayb);
            break;
        }
        while (row.includes(',')) {
            intructions.push(row.split(','));
//            console.log("Instructions: ", intructions);
            break;
        }
    }

    for (const row of intructions) {
        const seenNumbers = new Set();
//        console.log("Row: ", row);
        let ok = true;
        for (const num of row){
            for (let i = 0; i < arrayb.length; i++) {
//                console.log("Num: ", num, "ArrayA: " , arraya[i] , "ArrayB: ", arrayb[i]);
                if (arrayb[i] === num) {
                    if (!seenNumbers.has(arraya[i]) && row.includes(arraya[i])) {
//                        console.log ("there was no: ", arraya[i], "before", num);
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) {
//                console.log("Not ok: ", num);
                break;
            }
            else {
//                console.log("Ok: ", num);
            }
            seenNumbers.add(num);
        }
        if (ok) {
            let middle = Math.floor(row.length / 2);
            console.log("Ok: ", row, "adding ", row[middle], "to ans");
            p1_ans += parseInt(row[middle]);
            middle = 0;
        }
    }

    console.log('Part 1:', p1_ans);
};

// Part 2, I had high hopes of solving this one in complitely different manner, but after being couple off for way too long I had to ask help from stack overflow :D
// I will try to understand the solution provided and implement it in my own way
const solvePart2 = () => {
    let p2_ans = 0;
    let arraya = [];
    let arrayb = [];
    let instructions = [];

    for (const row of input) {
        if (row.includes('|')) {
            let [a, b] = row.split('|');
            arraya.push(parseInt(a));
            arrayb.push(parseInt(b));
        } else if (row.includes(',')) {
            instructions.push(row.split(',').map(num => parseInt(num)));
        }
    }

    // instead of having checking rules in one by one, create graph of rules
    const graph = {};
    for (let i = 0; i < arraya.length; i++) {
        const before = arraya[i];
        const after = arrayb[i];
        if (!graph[after]) graph[after] = [];
        if (!graph[before]) graph[before] = [];
        graph[after].push(before);
    }

    for (const row of instructions) {
        const numbers = row;
        let ok = true;

        //nested loop. outer loop goes through all numbers in row, inner loop goes through all numbers before current number
        // fairly similar logic than i had in part 1, but this time we are checking if all numbers before current number are in the row
        for (let i = 1; i < numbers.length; i++) {
            for (let j = i - 1; j >= 0; j--) {
                // This condition is checking if the number is allowed to be before the current number
                if (!graph[numbers[i]].includes(numbers[j]))
                {
                     ok = false;
                }
            }
        }
        // if the number is not allowed to be before the current number
        // sort the numbers in row based by the amount of rules affecting them
        // basically compares number a and b, and sorts them by the amount of rules that affect them
        if (!ok) {
            numbers.sort((a, b) => graph[a].filter(num => numbers.includes(num)).length - graph[b].filter(num => numbers.includes(num)).length);
            console.log("Fixed: ", numbers);
            // again take middle element of the row, but this time drom the fixed row.
            p2_ans += numbers[Math.floor(numbers.length / 2)];
        }
    }

    console.log('Part 2:', p2_ans);
};

// basically my previous iteration was really close to the solution and worked with most of the inputs,
// but instead of having the graph of rules the rules got checked on the order they were seen and saved, so output could be different.

solvePart1();
solvePart2();
