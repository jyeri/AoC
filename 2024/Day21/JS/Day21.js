// Advent of Code 2024 - Day 21

/*
    [7, 8, 9]   MAIN ROBOT
    [4, 5, 6]
    [1, 2, 3]
    [ , 0, A]

    [ , ^, A]   <- ROBOT
    [<, v, >]

    [ , ^, A]   <- ROBOT
    [<, v, >]

    [ , ^, A]   <- ME
    [<, v, >]


    O29A:       029A
    R1 029A:    <A^A>^^AvvvA
    R2 029A:    v<<A>>^A<A>AvA<^AA>A<vAAA>^A
    ME 029A:    <vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A       

    --- Part 1 ---
    General approach


    --- Part 2 ---
    General approach
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1

/* What I'm, tryin to achieve:
    - Parse input
    - make memo for the best moves from A to B (memo[Code, Robot index] = length of presses)
        const key = `${code},${robot}`;
        if (memo[key] !== undefined) 
            return memo[key];
    - Make recursive function to find the best path (least button presses)
        - Some kind of bfs, where i iterate the code length
        - find smallest amount of button presses for each transition
        - If robot index is not 0, then recursively call the function with robot index - 1
        - return value should be the length button presses for each transition
    - Function to fins the best path would start with BFS from A to B
        - start by finding all the paths from A to B
        - make sure we stay inbounds (inbound function)
        - only make traversal in directions where is buttons
        - after we have all the paths, we can sort allPaths by length
    - In the main we can just take the numeric part of the code and multiply it by the lengths of the paths

*/
const solvePart1 = () => {
    let p1_ans = 0;
        const tester = [

    ];

    for (const row of tester) {
        // line by line
        console.log();
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    const tester = [

    ];

    for (const row of tester) {
        // line by line
        // console.log();
    }

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
