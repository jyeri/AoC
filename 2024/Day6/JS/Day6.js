// Advent of Code 2024 - Day 6
const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8').split('\n');


// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    let directions = {
        'U': [-1, 0],
        'R': [0, 1],
        'D': [1, 0],
        'L': [0, -1],
    };

    const tester = [
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#...",
    ];

    // had to use copy of the grid because it was making part2 give wrong answers.
    let grid = [...input];
    let column_count = grid[0].length;
    let row_count = grid.length;

    let x = 0;
    let y = 0;

    for (const row of grid) {
        if (row.includes('^')) {
            y = row.indexOf('^');
            x = grid.indexOf(row);
            console.log("Starting position:", x, y);
        }
    }

    let dir = 'U';

    const inbounds = (x, y) => x >= 0 && y >= 0 && x < row_count && y < column_count;

    while (inbounds(x, y)) {
        let [dx, dy] = directions[dir];
        let next_x = x + dx;
        let next_y = y + dy;

        if (!inbounds(next_x, next_y)) {
//            console.log('Out of bounds at:', next_x, next_y);
            x = next_x; y = next_y;
            p1_ans++;
            break;
        }

        if (grid[next_x][next_y] === '#') {
//            console.log('Wall ahead at:', next_x, next_y);
            // make a turn to in U->R->D->L order, so clockwise if ur not dumb.
            if (dir === 'L') {
                dir = 'U';
            } else if (dir === 'U') {
                dir = 'R';
            } else if (dir === 'R') {
                dir = 'D';
            } else if (dir === 'D') {
                dir = 'L';
            }
//            console.log('New direction:', dir);
            continue;
        }

        x = next_x;
        y = next_y;

        if (grid[x][y] === '.') {
            // Immutable strings in my ass.
            grid[x] = grid[x].substring(0, y) + 'X' + grid[x].substring(y + 1);
            p1_ans++;
        }

//        console.log('Current:', x, y);
    }

    console.log("Exit at:", x, y);
    console.log('Part 1:', p1_ans);
};

const solvePart2 = () => {
    let p2_ans = 0;
    const directions = {
        'U': [-1, 0],
        'R': [0, 1],
        'D': [1, 0],
        'L': [0, -1],
    };

    const test_input = [
        "....#.....",
        ".........#",
        "..........",
        "..#.......",
        ".......#..",
        "..........",
        ".#..^.....",
        "........#.",
        "#.........",
        "......#...",
    ];

    const row_count = input.length;
    const column_count = input[0].length;

    const inbounds = (x, y) => x >= 0 && y >= 0 && x < row_count && y < column_count;

    const solver = (grid) => {
        let x = 0
        let y = 0
        let dir = 'U'
        let p2_ans = 0;

        for (const row of grid) {
            if (row.includes('^')) {
                y = row.indexOf('^');
                x = grid.indexOf(row);
                break;
            }
        }

        const visited = new Set();
        while (inbounds(x, y)) {
            const [dx, dy] = directions[dir];
            const next_x = x + dx;
            const next_y = y + dy;

            if (!inbounds(next_x, next_y))
            {
                // console.log('Out of bounds at:', next_x, next_y);
                return false;
            }

            if (grid[next_x][next_y] === '#') {
                if (dir === 'L') 
                    dir = 'U';
                else if (dir === 'U') 
                    dir = 'R';
                else if (dir === 'R') 
                    dir = 'D';
                else if (dir === 'D') 
                    dir = 'L';
                continue;
            }

            const currentState = `${x},${y},${dir}`;
            if (visited.has(currentState))
            {
//                console.log('Loop detected at:', x, y);
                return true;
            }
            visited.add(currentState);
            x = next_x;
            y = next_y;
        }
        return false;
    };

    let runs = 0;

    for (let i = 0; i < row_count; i++) {
        for (let j = 0; j < column_count; j++) {
            if (input[i][j] === '.') {

                const modifiedGrid = [...input];
                // fucking JS and immutable strings again....
                modifiedGrid[i] = modifiedGrid[i].substring(0, j) + '#' + modifiedGrid[i].substring(j + 1);
                const isLoop = solver(modifiedGrid);
                if (isLoop)
                {
                    p2_ans++;
                }
                runs++;
            }
        }
    }

    console.log('Times solver runned:', `${runs}`);
    console.log('Part 2:', p2_ans);
};

console.log('\n---------------------\n');
solvePart1();
console.log('\n---------------------\n');
solvePart2();
console.log('\n---------------------\n');