// Advent of Code 2024 - Day 10

/*
    --- Part 1 ---
    Question was how many of the trailheads actually end up at 9, instead how many differet paths lead to 9.
    I ended up parsing the input again even though it was unnecessary in the ens, but i xhanges it to 2D array of numbers.
    After input check I looped through input to find every single 0 and stored them in array as starting points.
    When I had all starting points locates I called dfs function for each of them. I utilized visited set to keep track of visited nodes, this way I could avoid going redudant paths.
    I also used directions array to move in 4 directions, and inbounds function to check if the move is valid.
    Finally when path reaches 9, I add this paths score.
    when all paths are checked I add all the trailscores to p1_ans and print it.


    --- Part 2 ---
    Part2 was beyond easy because I already did it as my first iteration to part1.
    This time I keep every single path that reaches 9, instead only 1 per starting point.
    rest of the operations are the same as part 1.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    const directions = [
        { x: 0, y: 1 },
        { x: 1, y: 0 },
        { x: 0, y: -1 },
        { x: -1, y: 0 },
    ];

    const tester = [
        "89010123",
        "78121874",
        "87430965",
        "96549874",
        "45678903",
        "32019012",
        "01329801",
        "10456732",
    ].map(row => row.split('').map(Number));

    const parsedinput = input.map(row => row.split('').map(Number)); 
    const rows = parsedinput.length;
    const cols = parsedinput[0].length;

    const inbounds = (x, y) => x >= 0 && y >= 0 && x < rows && y < cols;

    const dfs = (x, y, visited) => {
        if (parsedinput[x][y] === 9) {
            return 1;
        }

        let score = 0;
        for (const dir of directions) {
            const nx = x + dir.x;
            const ny = y + dir.y;

            // if hte number is 1 up, and inbounds we can visit it -> add it to visited array and call dfs
            if (inbounds(nx, ny) && parsedinput[nx][ny] === parsedinput[x][y] + 1 && !visited.has(`${nx},${ny}`)) {
                visited.add(`${nx},${ny}`);
                score += dfs(nx, ny, visited);
            }
        }
        return score;
    };

    for (let x = 0; x < rows; x++) {
        for (let y = 0; y < cols; y++) {
            if (parsedinput[x][y] === 0) {
                const visited = new Set();
                visited.add(`${x},${y}`);
                const score = dfs(x, y, visited);
                p1_ans += score;
            }
        }
    }

    console.log("part 1:", p1_ans);
};

solvePart1();

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    let starts = [];
    let dir = [
        { x: 0, y: 1 },
        { x: 1, y: 0 },
        { x: 0, y: -1 },
        { x: -1, y: 0 },
    ];
    const iinputi = [
        "89010123",
        "78121874",
        "87430965",
        "96549874",
        "45678903",
        "32019012",
        "01329801",
        "10456732"
    ];

    const linputl = [
        "0123",
        "1234",
        "8765",
        "9876",
    ]

    for (let i = 0; i < input.length; i++) {
        const row = input[i];
        for (let j = 0; j < row.length; j++) {
            if (row[j] === '0') {
                starts.push({ x: i, y: j });
            }
        }
    }
    console.log(starts);

    const inbounds = (x, y) => x >= 0 && y >= 0 && x < input.length && y < input[0].length;

    const dfs = (x, y, currentPath) => {
        if (parseInt(input[x][y]) === 9) {
            p2_ans++;
            return;
        }

        for (let i = 0; i < 4; i++) {
            let nx = x + dir[i].x;
            let ny = y + dir[i].y;
            if (inbounds(nx, ny) && parseInt(input[nx][ny]) === parseInt(input[x][y]) + 1) {
                dfs(nx, ny, [...currentPath, { x: nx, y: ny }]);
            }
        }
    };

    for (const start of starts) {
        dfs(start.x, start.y, [start]);
    }

    console.log('Part 2:', p2_ans);
};

solvePart1();
solvePart2();
