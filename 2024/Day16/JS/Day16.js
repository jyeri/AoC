// Advent of Code 2024 - Day 16

/*
    --- Part 1 ---
    Ripped from the D12 puzzle, but with a twist of adding prioque.
    so BFS from S to E, but when we are checking next possible move we compare its cost with other moves and constinue with lower cost one.
    We also keep track of visited nodes and their costs.


    --- Part 2 ---
    Absolute horror. I had to ask for help from reddit.
    Solution is still similar to part 1, but my queue implementation was not working.
    I had to use priority queue to keep track of the costs.
    I had to backtrack from the end to the start to find all the best paths.
    I had to keep track of the best path tiles and print them out.
    One fix was to accuerately check both of possible directions instead one (this should have not worked even in part1)
*/

const PriorityQueue = require('./priorityQueue.js');
const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1
const solvePart1 = () => {
    const tester = [
        "#################",
        "#...#...#...#..E#",
        "#.#.#.#.#.#.#.#.#",
        "#.#.#.#...#...#.#",
        "#.#.#.#.###.#.#.#",
        "#...#.#.#.....#.#",
        "#.#.#.#.#.#####.#",
        "#.#...#.#.#.....#",
        "#.#.#####.#.###.#",
        "#.#.#.......#...#",
        "#.#.###.#####.###",
        "#.#.#...#.....#.#",
        "#.#.#.#####.###.#",
        "#.#.#.........#.#",
        "#.#.#.#########.#",
        "#S#.............#",
        "#################",
    ];

    const parsedInput = tester.map(row => row.split(''));

    const directions = [
        { dx: 0, dy: 1, dir: 'E' },  // East
        { dx: 1, dy: 0, dir: 'S' },  // South
        { dx: 0, dy: -1, dir: 'W' }, // West
        { dx: -1, dy: 0, dir: 'N' }  // North
    ];


    let startX, startY, endX, endY;
    for (let i = 0; i < parsedInput.length; i++) {
        for (let j = 0; j < parsedInput[0].length; j++) {
            if (parsedInput[i][j] === 'S') {
                startX = i;
                startY = j;
            }
            if (parsedInput[i][j] === 'E') {
                endX = i;
                endY = j;
            }
        }
    }

    const isValid = (x, y) =>
        x >= 0 && x < parsedInput.length && y >= 0 && y < parsedInput[0].length && parsedInput[x][y] !== '#';

    // Day12 with prio queue added in
    const prioq = [{ x: startX, y: startY, cost: 0, dir: 'E' }];
    const visited = new Map();

    while (prioq.length > 0) {
        prioq.sort((a, b) => a.cost - b.cost);
        const { x, y, cost, dir } = prioq.shift();

        if (x === endX && y === endY) {
            console.log('Part 1:', cost);
            return;
        }

        const key = `${x},${y},${dir}`;
        if (visited.has(key) && visited.get(key) <= cost) {
            continue;
        }
        visited.set(key, cost);

        for (let i = 0; i < directions.length; i++) {
            const { dx, dy, dir: newDir } = directions[i];
            const nx = x + dx;
            const ny = y + dy;

            if (!isValid(nx, ny)) {
                continue;
            }
            // THIS SHOULD HAVE NOT WORKED BUT IT DID.
            // ROTATION IS POSSIBLE TO EITHER DIRECTION...
            const rotationCost = dir === newDir ? 0 : 1000;
            const newCost = cost + 1 + rotationCost;

            prioq.push({ x: nx, y: ny, cost: newCost, dir: newDir });
        }
    }
};


/* 
    my queue implementation was fucked, and after talking with other people I got the tips
    to make and use priority queue that I actually should have stored into my own library.
    I want to thank 1234abcdcba4321 from reddit for providing awesome example of priority queue.
    This saved me couple of hours of sweating and crying.
*/

// Part 2

const solvePart2 = () => {
    const tester = [
        "#################",
        "#...#...#...#..E#",
        "#.#.#.#.#.#.#.#.#",
        "#.#.#.#...#...#.#",
        "#.#.#.#.###.#.#.#",
        "#...#.#.#.....#.#",
        "#.#.#.#.#.#####.#",
        "#.#...#.#.#.....#",
        "#.#.#####.#.###.#",
        "#.#.#.......#...#",
        "#.#.###.#####.###",
        "#.#.#...#.....#.#",
        "#.#.#.#####.###.#",
        "#.#.#.........#.#",
        "#.#.#.#########.#",
        "#S#.............#",
        "#################",
    ];

    // input is actual, tester just for testing
    const parsedInput = input.map(row => row.split(''));
    // const parsedInput = tester.map(row => row.split(''));

    const directions = [
        { dx: 0, dy: 1, dir: 'E' }, 
        { dx: 1, dy: 0, dir: 'S' },  
        { dx: 0, dy: -1, dir: 'W' },
        { dx: -1, dy: 0, dir: 'N' }  
    ];

    let startX, startY, endX, endY;
    for (let i = 0; i < parsedInput.length; i++) {
        for (let j = 0; j < parsedInput[0].length; j++) {
            if (parsedInput[i][j] === 'S') {
                startX = i;
                startY = j;
            }
            if (parsedInput[i][j] === 'E') {
                endX = i;
                endY = j;
            }
        }
    }

    const isValid = (x, y) =>
        x >= 0 && x < parsedInput.length && y >= 0 && y < parsedInput[0].length && parsedInput[x][y] !== '#';

    const prioque = new PriorityQueue((a, b) => a[0] - b[0]);
    const queued = {};
    const visited = {};

    prioque.push([0, startX, startY, 0, 1]);
    queued[`${startX},${startY},0,1`] = [0, []];

    const enqueue = (cost, x, y, dx, dy, prev) => {
        const key = `${x},${y},${dx},${dy}`;
        if (!queued[key] || cost < queued[key][0]) {
            queued[key] = [cost, [prev]];
            prioque.push([cost, x, y, dx, dy]);
        } else if (cost === queued[key][0]) {
            queued[key][1].push(prev);
        }
    };

    let bestCost = Infinity;

    while (prioque.size() > 0) {
        const [cost, x, y, dx, dy] = prioque.pop();

        if (cost > bestCost) {
            break;
        }

        const key = `${x},${y},${dx},${dy}`;
        if (visited[key] && visited[key] < cost) {
            continue;
        };
        visited[key] = cost;

        if (parsedInput[x][y] === 'E') {
            bestCost = cost;
        }

        if (isValid(x + dx, y + dy)) {
            enqueue(cost + 1, x + dx, y + dy, dx, dy, [x, y, dx, dy]);
        }
        // this time accurately que the rotation for either direction
        enqueue(cost + 1000, x, y, -dy, dx, [x, y, dx, dy]);
        enqueue(cost + 1000, x, y, dy, -dx, [x, y, dx, dy]);
    }

    const seats = {};
    const backtrack = (x, y, dx, dy) => {
        const key = `${x},${y},${dx},${dy}`;
        if (seats[key])
        {
            return;
        }
        seats[key] = true;
        for (const [prevX, prevY, prevDX, prevDY] of queued[key][1]) {
            backtrack(prevX, prevY, prevDX, prevDY);
        }
    };

    // we backtrack from the end to the start to find all the best paths
    // for sake of simplicity we use dir 0, 1. for input that i got only nono working is 0, -1
    backtrack(endX, endY, 0, 1);
    const bestPathTiles = new Set(Object.keys(seats).map(key => key.split(',').slice(0, 2).join(',')));

    for (let i = 0; i < parsedInput.length; i++) {
        for (let j = 0; j < parsedInput[0].length; j++) {
            const key = `${i},${j}`;
            if (bestPathTiles.has(key)) {
                parsedInput[i][j] = 'O';
            }
        }
    }

    console.log(parsedInput.map(row => row.join('')).join('\n'));
    console.log('Part 2:', bestPathTiles.size);
};

solvePart1();
solvePart2();
