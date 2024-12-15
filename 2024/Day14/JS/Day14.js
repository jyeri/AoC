// Advent of Code 2024 - Day 14

/*
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
const solvePart1 = () => {
    let grid_width = 101;
    let grid_height = 103;

    const tester = [
        "p=0,4 v=3,-3",
        "p=6,3 v=-1,-3",
        "p=10,3 v=-1,2",
        "p=2,0 v=2,-1",
        "p=0,0 v=1,3",
        "p=3,0 v=-2,-2",
        "p=7,6 v=-1,-3",
        "p=3,0 v=-1,-2",
        "p=9,3 v=2,3",
        "p=7,3 v=-1,2",
        "p=2,4 v=2,-3",
        "p=9,5 v=-3,-3",
    ];

    let robots = input.map(row => {
        let [p, v] = row.split(' ').map(e => e.split('=')[1]);
        let [pos_x, pos_y] = p.split(',').map(Number);
        let [vel_x, vel_y] = v.split(',').map(Number);
        return { pos_x, pos_y, vel_x, vel_y };
    });

    const moveRobots = (robots, grid_width, grid_height) => {
        let grid = Array.from({ length: grid_height }, () => Array(grid_width).fill(0));
        for (const robot of robots) {
            robot.pos_x = (robot.pos_x + robot.vel_x + grid_width) % grid_width;
            robot.pos_y = (robot.pos_y + robot.vel_y + grid_height) % grid_height;
            grid[robot.pos_y][robot.pos_x] += 1;
        }

        return grid;
    };

    let grid;

    // Simulator moves
    for (let i = 0; i < 100; i++) {
        grid = moveRobots(robots, grid_width, grid_height);
    }

    console.log("\nIteration 100:");
    for (let row of grid) {
        console.log(row.map(cell => (cell === 0 ? '.' : cell)).join(''));
    }

    let middleRow = Math.floor(grid.length / 2);
    let middleCol = Math.floor(grid[0].length / 2);
    
    let q1_res = 0, q2_res = 0, q3_res = 0, q4_res = 0;
    
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            // Skip the middle row and column
            if (i === middleRow || j === middleCol) {
                continue;
            }
    
            if (i < middleRow) { // Top half
                if (j < middleCol) {
                    q1_res += grid[i][j]; // Top-left
                } else if (j > middleCol) {
                    q2_res += grid[i][j]; // Top-right
                }
            } else if (i > middleRow) { // Bottom half
                if (j < middleCol) {
                    q3_res += grid[i][j]; // Bottom-left
                } else if (j > middleCol) {
                    q4_res += grid[i][j]; // Bottom-right
                }
            }
        }
    }
    
    console.log('Q1:', q1_res, 'Q2:', q2_res, 'Q3:', q3_res, 'Q4:', q4_res);
    console.log('Part 1:', q1_res * q2_res * q3_res * q4_res);
}

// Part 2
const solvePart2 = () => {
    let grid_width = 101;
    let grid_height = 103;
    let p2_ans = 0;

    const tester = [
        "p=0,4 v=3,-3",
        "p=6,3 v=-1,-3",
        "p=10,3 v=-1,2",
        "p=2,0 v=2,-1",
        "p=0,0 v=1,3",
        "p=3,0 v=-2,-2",
        "p=7,6 v=-1,-3",
        "p=3,0 v=-1,-2",
        "p=9,3 v=2,3",
        "p=7,3 v=-1,2",
        "p=2,4 v=2,-3",
        "p=9,5 v=-3,-3",
    ];

    let robots = input.map(row => {
        let [p, v] = row.split(' ').map(e => e.split('=')[1]);
        let [pos_x, pos_y] = p.split(',').map(Number);
        let [vel_x, vel_y] = v.split(',').map(Number);
        return { pos_x, pos_y, vel_x, vel_y };
    });

    const moveRobots = (robots, grid_width, grid_height) => {
        let grid = Array.from({ length: grid_height }, () => Array(grid_width).fill(0));
        for (const robot of robots) {
            robot.pos_x = (robot.pos_x + robot.vel_x + grid_width) % grid_width;
            robot.pos_y = (robot.pos_y + robot.vel_y + grid_height) % grid_height;
            grid[robot.pos_y][robot.pos_x] += 1;
        }

        return grid;
    };

    const findPattern = (grid) => {
        let count = 0;
        let maxlen = 0;
        for (let i = 0; i < grid.length; i++) {
            for (let j = 0; j < grid[0].length; j++) {
                if (grid[i][j] === 0) {
                    count = 0;
                } else if (++count >= 10) {
                    return true;
                }
            }
        }
        return false;
    }

    let grid;

    // Simulator moves
    for (let i = 0; i < 10000; i++) {
        grid = moveRobots(robots, grid_width, grid_height);
        if (findPattern(grid))
        {
            console.log('Part 2:', i);
            p2_ans = i;
            for (let row of grid) {
                console.log(row.map(cell => (cell === 0 ? '.' : cell)).join(''));
            }
            break;
        }
    }

    console.log("\nIteration 100:");
    for (let row of grid) {
        console.log(row.map(cell => (cell === 0 ? '.' : cell)).join(''));
    }

    let middleRow = Math.floor(grid.length / 2);
    let middleCol = Math.floor(grid[0].length / 2);
    
    let q1_res = 0, q2_res = 0, q3_res = 0, q4_res = 0;
    
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            // Skip the middle row and column
            if (i === middleRow || j === middleCol) {
                continue;
            }
    
            if (i < middleRow) { // Top half
                if (j < middleCol) {
                    q1_res += grid[i][j]; // Top-left
                } else if (j > middleCol) {
                    q2_res += grid[i][j]; // Top-right
                }
            } else if (i > middleRow) { // Bottom half
                if (j < middleCol) {
                    q3_res += grid[i][j]; // Bottom-left
                } else if (j > middleCol) {
                    q4_res += grid[i][j]; // Bottom-right
                }
            }
        }
    }
    
    console.log('Part 2:', p2_ans);
}
solvePart1();
solvePart2();
