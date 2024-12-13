// Advent of Code 2024 - Day 13

/*
    --- Part 1 ---
    Okay, part1 my head made it so much trickier than it actually is.
    What i did is after parsing the input for each machine, I would generate all possible solutions for X and Y.
    I found the solutions using the Extended Euclidean Algorithm.
    I would then find the minimum cost for each solution.
    If the cost is less than Infinity, I would add it to the total cost.


    --- Part 2 ---
    Instead of doing ALL of that unnecessary work from part 1 (that caused massive memory issues when tried to implement to part2)
    I found a equation on the internet that was much simpler.
    Starting again with parsing the input for each machine, I would calculate the determinant of the matrix of the machines and the prize.
    if the cost coming back was more than 0, machine has solution and it gets added into the total cost.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Extended Euclidean Algorithm
// its recursive implementation to return greatest common divisor (gcd), scrapped from my hive project and converted to JS
// a⋅x + b⋅y = gcd(x,y).
const extendedGCD = (a, b) => {
    // recursively keep reducing b until it reaches 0
    if (b === 0) {
        return [a, 1, 0];
    }
    const [gcd, x1, y1] = extendedGCD(b, a % b);
    return [gcd, y1, x1 - Math.floor(a / b) * y1];
};

// THIS MY FRIENDS IS WHAT I CALL OVERENGINEERING
// THERE IS SO MANY OPTIMAL SOLUTIONS ON THE INTERNET, BUT I HAD TO TRY TO MAKE MY OWN
// I AM NOT PROUD OF THIS
// Generate solutions for the equation a*x + b*y = target
const generateSolutions = (a, b, target) => {
    // Calculate the greatest common divisor (gcd)
    const [gcd, x0, y0] = extendedGCD(a, b);

    if (target % gcd !== 0) {
        return null;
    }

    const scale = target / gcd;
    const scaledX0 = x0 * scale;
    const scaledY0 = y0 * scale;

    const stepA = b / gcd;
    const stepB = -a / gcd;

//    console.log(`Scaled initial solution: x0=${scaledX0}, y0=${scaledY0}`);
//    console.log(`Step increments: stepA=${stepA}, stepB=${stepB}`);

    // Determine range for t
    let tMin = -Infinity;
    let tMax = Infinity;

    if (stepA > 0) tMin = Math.max(tMin, Math.ceil(-scaledX0 / stepA));
    if (stepA < 0) tMax = Math.min(tMax, Math.floor(-scaledX0 / stepA));
    if (stepB > 0) tMin = Math.max(tMin, Math.ceil(-scaledY0 / stepB));
    if (stepB < 0) tMax = Math.min(tMax, Math.floor(-scaledY0 / stepB));

    const solutions = [];
    for (let t = tMin; t <= tMax; t++) {
        const x = scaledX0 + t * stepA;
        const y = scaledY0 + t * stepB;

        if (x >= 0 && y >= 0) {
            solutions.push([x, y]);
        }
    }

//    console.log(`Generated solutions: ${solutions}\n`);
    return solutions;
};

const NotOverEngineeringThisTime = (a, b, p) => {
    // p2 prize adjustments (* 10000000000000)
    p.x += 10000000000000;
    p.y += 10000000000000;
  
    /*
        trying to follow this logic at I shamelessly got from the internet
        determinant = a.x * b.y - a.y * b.x
        xCost = (p.x * b.y - p.y * b.x) / determinant
        yCost = (a.x * p.y - a.y * p.x) / determinant
        if xCost and yCost are integers, then the cost is xCost + yCost, and because xCost is 3 * x, we can just return 3 * xCost + yCost
    */
    const det = a.x * b.y - a.y * b.x;
  
    if (det === 0) {
      return 0;
    }
  
    const xCost = (p.x * b.y - p.y * b.x) / det;
    const yCost = (a.x * p.y - a.y * p.x) / det;
  
    if (xCost % 1 === 0 && yCost % 1 === 0) {
      return xCost * 3 + yCost;
    }
  
    return 0;
  };


// Part 1
const solvePart1 = () => {
    const ButtonA = [];
    const ButtonB = [];
    const Prize = [];
    let p1_ans = 0;

    const tester = [
        "Button A: X+94, Y+34",
        "Button B: X+22, Y+67",
        "Prize: X=8400, Y=5400",
        "",
        "Button A: X+26, Y+66",
        "Button B: X+67, Y+21",
        "Prize: X=12748, Y=12176",
        "",
        "Button A: X+17, Y+86",
        "Button B: X+84, Y+37",
        "Prize: X=7870, Y=6450",
        "",
        "Button A: X+69, Y+23",
        "Button B: X+27, Y+71",
        "Prize: X=18641, Y=10279",
    ];

    for (const row of input) {
        if (row.includes('Button A')) {
            ButtonA.push(row);
        }
        if (row.includes('Button B')) {
            ButtonB.push(row);
        }
        if (row.includes('Prize')) {
            Prize.push(row);
        }
    }

    for (let i = 0; i < ButtonA.length; i++) {
        const Ax = parseInt(ButtonA[i].split(' ')[2].substring(2));
        const Ay = parseInt(ButtonA[i].split(' ')[3].substring(2));
        const Bx = parseInt(ButtonB[i].split(' ')[2].substring(2));
        const By = parseInt(ButtonB[i].split(' ')[3].substring(2));
        const Px = parseInt(Prize[i].split(' ')[1].substring(2));
        const Py = parseInt(Prize[i].split(' ')[2].substring(2));

//        console.log('Button A: (' +Ax + ',' + Ay + ')');
//        console.log('Button B: (' +Bx + ',' + By + ')');
//        console.log('Prize: (' +Px + ',' + Py + ')');

        // we need to save all possible solutions for X and Y, and save them.
        const solutionsX = generateSolutions(Ax, Bx, Px);
        const solutionsY = generateSolutions(Ay, By, Py);

//        console.log('\nSolutions X:', solutionsX);
//        console.log('Solutions Y:', solutionsY);
//        console.log('\n');

        if (!solutionsX || !solutionsY) {
            console.log('No solution exists');
            continue;
        }

        let minCost = Infinity;
        // when we have the solutions for X and Y, we need to find the minimum cost
        // valid solution must be ax = ay and bx = by
        for (const [aX, bX] of solutionsX) {
            for (const [aY, bY] of solutionsY) {
                if (aX === aY && bX === bY) {
                    const cost = 3 * aX + bX;
                    minCost = Math.min(minCost, cost);
                }
            }
        }

        if (minCost < Infinity) {
            p1_ans += minCost;
        }
    }

    console.log('Part 1:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    const ButtonA = [];
    const ButtonB = [];
    const Prize = [];
    let p2_ans = 0;
  
    const tester = [
      "Button A: X+94, Y+34",
      "Button B: X+22, Y+67",
      "Prize: X=8400, Y=5400",
      "",
      "Button A: X+26, Y+66",
      "Button B: X+67, Y+21",
      "Prize: X=12748, Y=12176",
      "",
      "Button A: X+17, Y+86",
      "Button B: X+84, Y+37",
      "Prize: X=7870, Y=6450",
      "",
      "Button A: X+69, Y+23",
      "Button B: X+27, Y+71",
      "Prize: X=18641, Y=10279",
    ];
  
    // Parse input
    for (const row of input) {
      if (row.includes("Button A")) {
        ButtonA.push(row);
      }
      if (row.includes("Button B")) {
        ButtonB.push(row);
      }
      if (row.includes("Prize")) {
        Prize.push(row);
      }
    }
  
    for (let i = 0; i < ButtonA.length; i++) {
      const Ax = parseInt(ButtonA[i].split(" ")[2].substring(2));
      const Ay = parseInt(ButtonA[i].split(" ")[3].substring(2));
      const Bx = parseInt(ButtonB[i].split(" ")[2].substring(2));
      const By = parseInt(ButtonB[i].split(" ")[3].substring(2));
      const Px = parseInt(Prize[i].split(" ")[1].substring(2));
      const Py = parseInt(Prize[i].split(" ")[2].substring(2));
  
      // ill change the form just for easy access
      const a = { x: Ax, y: Ay };
      const b = { x: Bx, y: By };
      const p = { x: Px, y: Py };
  
      const cost = NotOverEngineeringThisTime(a, b, p);
  
      if (cost > 0) {
        console.log(`Machine ${i}: Cost=${cost}`);
        p2_ans += cost;
      } 
      else 
      {
        console.log(`No solution exists for machine ${i}`);
      }
    }
  
    console.log("Part 2:", p2_ans);
  };
  

solvePart1();
solvePart2();
