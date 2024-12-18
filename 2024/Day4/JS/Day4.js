// Advent of Code 2024 - Day 4
const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8').split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    let test = [
"MMMSXXMASM",
"MSAMXMSMSA",
"AMXSXMAAMM",
"MSAMASMSMX",
"XMASAMXAMM",
"XXAMMXXAMA",
"SMSMSASXSS",
"SAXAMASAAA",
"MAMMMXMMMM",
"MXMXAXMASX",];

    const target = 'XMAS';
    const directions = [
        { x: 0, y: 1 },  // right
        { x: 0, y: -1 },  // left
        { x: 1, y: 0 },  // down
        { x: -1, y: 0 },  // up
        { x: -1, y: -1 },  // up-left
        { x: -1, y: 1 },  // up-right
        { x: 1, y: 1 },  // down-right
        { x: 1, y: -1 }  // down-left
    ]

    const inBounds = (x, y) => {
        if (x >= 0 && x < input[0].length && y >= 0 && y < input.length) {
            return true;
        }
        return false;
    };

    const check = (x, y, direction) => {
        for (let i = 0; i < target.length; i++) {
            const newX = x + i * direction.x;
            const newY = y + i * direction.y;
            if (!inBounds(newX, newY)) {
                return false;
            }
            if (input[newY][newX] !== target[i]) {
                return false;
            }
        }
        return true;
    }

    for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < input[0].length; x++) {
            for (const direction of directions) {
                if (check(x, y, direction)) {
                    p1_ans++;
                }
            }
        }
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    let test = [
        "MMMSXXMASM",
        "MSAMXMSMSA",
        "AMXSXMAAMM",
        "MSAMASMSMX",
        "XMASAMXAMM",
        "XXAMMXXAMA",
        "SMSMSASXSS",
        "SAXAMASAAA",
        "MAMMMXMMMM",
        "MXMXAXMASX",
    ];

    const directions = [
        { x: -1, y: -1 },  // up-left
        { x: 1, y: 1 },  // down-right
        { x: -1, y: 1 },  // up-right
        { x: 1, y: -1 }  // down-left
    ];

    const check = (x, y) => {
        for (let i = 0; i < directions.length; i += 2) {
            const dir1 = directions[i];
            const opposite = directions[i + 1];

            const newX1 = x + dir1.x;
            const newY1 = y + dir1.y;
            const newX2 = x + opposite.x;
            const newY2 = y + opposite.y;

            if (!inBounds(newX1, newY1) || !inBounds(newX2, newY2)) {
                return false;
            }

            const char1 = input[newY1][newX1];
            const char2 = input[newY2][newX2];

            if ((char1 !== 'M' && char1 !== 'S') || (char2 !== 'M' && char2 !== 'S')) {
                return false;
            }

            if (char1 === char2) {
                return false;
            }
        }
        return true;
    };

    for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < input[0].length; x++) {
            if (input[y][x] === 'A' && check(x, y)) {
                p2_ans ++;
            }
        }
    }

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
