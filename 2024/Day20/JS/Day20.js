// Advent of Code 2024 - Day 20

/*
    --- Part 1 ---
    Lets just say im fucking cooked.
    I had to look up the solution for this one.
    I solved part1 alone but it was noway near convertable to part2.


    --- Part 2 ---
    Yes. fun.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

const findS = (grid) => {
    for (let x = 0; x < grid.length; x++) {
        for (let y = 0; y < grid[x].length; y++) {
            if (grid[x][y] === 'S') 
                return {x, y};
        }
    }
};

const buildPath = (grid) => {
    const steps = new Map();
    let next = findS(grid);
    let i = 0;
    if (next[0] === -1) 
        console.log('No start found!');

    while (true) {
        const key = `${next.x},${next.y}`;
        steps.set(key, i);

        if (grid[next.x][next.y] === 'E')
            return steps;

        if (isValid(next, grid, 'N', steps)) 
            next = setNext(next, 'N');
        else if (isValid(next, grid, 'S', steps)) 
            next = setNext(next, 'S');
        else if (isValid(next, grid, 'E', steps)) 
            next = setNext(next, 'E');
        else if (isValid(next, grid, 'W', steps)) 
            next = setNext(next, 'W');
        else throw `something is wrong! ${next.x}, ${next.y}`;
        i++;
    }
};

const setNext = (next, dir) => {
    return { x: next.x + rowMap[dir], y: next.y + colMap[dir] };
};

const isValid = (next, grid, dir, path) => {
    const x = next.x + rowMap[dir];
    const y = next.y + colMap[dir];
    const key = `${x},${y}`;
    if (path.has(key)) 
        return false;
    return grid[x][y] === '.' || grid[x][y] === 'E';
};

const rowMap = {
    N: -1,
    S: 1,
    E: 0,
    W: 0,
};

const colMap = {
    N: 0,
    S: 0,
    E: 1,
    W: -1,
};

const findShortcuts = (path, maxCheatTime) => {
    let res = 0;

    for (const node of path) {
        const maxDistance = maxCheatTime;
        const [org_x, org_y] = node[0].split(',').map((x) => parseInt(x));
        for (let i = -maxDistance; i <= maxDistance; i++) {
            for (let j = -maxDistance; j <= maxDistance; j++) {
                const distance = Math.abs(i) + Math.abs(j);
                if (distance <= maxDistance) {
                    res += tryPos(`${org_x + i},${org_y + j}`, path, node[1], distance);
                }
            }
        }
    }
    return res;
};

const tryPos = (key, path, compare, steps) => {
    const goal = path.size > 100 ? 100 : 74;
    const val = path.get(key);

    if (val - compare - steps >= goal) {
        return 1;
    }
    return 0;
};

const solvePart1 = () => {
    const path = buildPath(input);
    const p1_ans = findShortcuts(path, 2);
    console.log('Part 1:', p1_ans);
};

const solvePart2 = () => {
    const path = buildPath(input);
    const p2_ans = findShortcuts(path, 20);
    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();