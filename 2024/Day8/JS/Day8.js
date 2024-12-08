// Advent of Code 2024 - Day 8

/*
    --- Part 1 ---
    General approach


    --- Part 2 ---
    same as part 1, but antinodes keeps spawning until out of bounds
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Globals
let antinodes = [];
let antennas = [];
let maxRows = 0;
let maxCols = 0;

const addAntinodes = (x, y) => {
    console.log("Adding antinode:", x, y);
    if (x >= 0 && x < maxRows && y >= 0 && y < maxCols) {
        antinodes.push([x, y]);
    }
};

const findNodes = (grid) => {
    maxRows = grid.length;
    maxCols = grid[0].length;
    for (let rowIndex = 0; rowIndex < grid.length; rowIndex++) {
        const row = grid[rowIndex];
        for (let colIndex = 0; colIndex < row.length; colIndex++) {
            const char = row[colIndex];
            if (char !== '.') {
                antennas.push([char, rowIndex, colIndex]);
            }
        }
    }
};

// part1
const solvePart1 = () => {
    const tester_input = [
        "............",
        "........0...",
        ".....0......",
        ".......0....",
        "....0.......",
        "......A.....",
        "............",
        "............",
        "........A...",
        ".........A..",
        "............",
        "............",
    ];


    findNodes(input);

    antennas.sort((a, b) => a[0].localeCompare(b[0]));

    for (let i = 0; i < antennas.length; i++) {
        for (let j = i + 1; j < antennas.length; j++) {
            if (antennas[i][0] !== antennas[j][0]) {
                break;
            }
            const x1 = antennas[i][1];
            const y1 = antennas[i][2];
            const x2 = antennas[j][1];
            const y2 = antennas[j][2];
            const antinode1 = [2 * x1 - x2, 2 * y1 - y2];
            const antinode2 = [2 * x2 - x1, 2 * y2 - y1];

            addAntinodes(antinode1[0], antinode1[1]);
            addAntinodes(antinode2[0], antinode2[1]);
        }
    }

    const uniqueAntinodes = new Set(antinodes.map(JSON.stringify));
    const finalAntinodes = Array.from(uniqueAntinodes).map(JSON.parse);

    console.log("Unique Antinodes:", finalAntinodes);
    console.log("Part 1:", finalAntinodes.length);
};

// Part 2
const solvePart2 = () => {
    antinodes = [];
    antennas = [];
    

    const tester_input = [
        "............",
        "........0...",
        ".....0......",
        ".......0....",
        "....0.......",
        "......A.....",
        "............",
        "............",
        "........A...",
        ".........A..",
        "............",
        "............",
    ];


    findNodes(input);

    antennas.sort((a, b) => a[0].localeCompare(b[0]));

    for (let i = 0; i < antennas.length; i++) {
        for (let j = i + 1; j < antennas.length; j++) {
            if (antennas[i][0] !== antennas[j][0]) {
                break;
            }
            console.log("Antennas:");
            console.log(antennas[i]);
            console.log(antennas[j]);

            const x1 = antennas[i][1];
            const y1 = antennas[i][2];
            const x2 = antennas[j][1];
            const y2 = antennas[j][2];
            const dx = x2 - x1;
            const dy = y2 - y1;

            let antinode1 = [2 * x1 - x2, 2 * y1 - y2];
            let antinode2 = [2 * x2 - x1, 2 * y2 - y1];
            console.log("UP:");
            addAntinodes(antennas[i][1], antennas[i][2]);
            addAntinodes(antennas[j][1], antennas[j][2]);
            while (antinode1[0] >= 0 && antinode1[0] < maxRows && antinode1[1] >= 0 && antinode1[1] < maxCols) {
                addAntinodes(antinode1[0], antinode1[1]);
                antinode1[0] -= dx; 
                antinode1[1] -= dy;
            }
    
            console.log("DOWN:");
            while (antinode2[0] >= 0 && antinode2[0] < maxRows && antinode2[1] >= 0 && antinode2[1] < maxCols) {
                addAntinodes(antinode2[0], antinode2[1]);
                antinode2[0] += dx;
                antinode2[1] += dy;
            }
        }
    }

    const uniqueAntinodes = new Set(antinodes.map(JSON.stringify));
    const finalAntinodes = Array.from(uniqueAntinodes).map(JSON.parse);

    let resgrid = new Array(maxRows).fill().map(() => new Array(maxCols).fill('.'));
    for (const [x, y] of finalAntinodes) {
        resgrid[x][y] = '#';
    }

    console.log("Unique Antinodes:", finalAntinodes);
    console.log("Part 2:", finalAntinodes.length);
    for(let i = 0; i < resgrid.length; i++) {
        console.log(resgrid[i].join(''));
    }
};

solvePart1();
solvePart2();