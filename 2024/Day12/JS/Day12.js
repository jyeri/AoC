// Advent of Code 2024 - Day 12

/*
    --- Part 1 ---
    Simple BFS problem.
    count the area and perimeter of each region and calculate the cost.
    add the cost to the total cost.


    --- Part 2 ---
    Had to use reddit for this one. I was stuck on this for a while.
    The solution is to keep track of the edges of each region.
    The cost is the area of the region multiplied by the number of edges.
    I had problems with counting the edges and polarities, that I still cannot explain.
    I had to look at the solution to understand it.

    What i ended up doing is BFS for each region, and for each region I would count the edges.
    I save the edges in a set, but if the edge is already in the set, I would decrement the edge count.
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8')
    .trim()
    .split('\n');

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    const tester = [
        "RRRRIICCFF",
        "RRRRIICCCF",
        "VVRRRCCFFF",
        "VVRCCCJFFF",
        "VVVVCJJCFE",
        "VVIVCCJJEE",
        "VVIIICJJEE",
        "MIIIIIJJEE",
        "MIIISIJEEE",
        "MMMISSJEEE",
    ];

    const parsedInput = tester.map(row => row.split(''));

    const bfs = (grid, startX, startY, visited) => {
        const directions = [
            { dx: 0, dy: 1 }, // Right
            { dx: 1, dy: 0 }, // Down
            { dx: 0, dy: -1 }, // Left
            { dx: -1, dy: 0 }, // Up
        ];
        const queue = [{ x: startX, y: startY }];
        const type = grid[startX][startY];
        visited.add(`${startX},${startY}`);

        let area = 0;
        let perimeter = 0;

        while (queue.length > 0) {
            const { x, y } = queue.shift();
            area++;

            for (const { dx, dy } of directions) {
                const nx = x + dx;
                const ny = y + dy;

                if (nx < 0 || nx >= grid.length || ny < 0 || ny >= grid[0].length) {
                    perimeter++;
                } else if (grid[nx][ny] === type && !visited.has(`${nx},${ny}`)) {
                    queue.push({ x: nx, y: ny });
                    visited.add(`${nx},${ny}`);
                } else if (grid[nx][ny] !== type) {
                    perimeter++;
                }
            }
        }

        return { area, perimeter };
    };

    const visited = new Set();

    for (let x = 0; x < parsedInput.length; x++) {
        for (let y = 0; y < parsedInput[0].length; y++) {
            const key = `${x},${y}`;
            if (!visited.has(key)) {
                const { area, perimeter } = bfs(parsedInput, x, y, visited);
                const cost = area * perimeter;
                p1_ans += cost;
                console.log(`Region ${parsedInput[x][y]}: Area: ${area} * Perimeter: ${perimeter} = Cost: ${cost}`);
            }
        }
    }

    console.log('Part 1:', p1_ans);
};


// Part 2
const solvePart2 = () => {
    const directions = [
        [0, 1],
        [0, -1],
        [1, 0],
        [-1, 0],
    ];

    function inBounds([x, y]) {
        return x >= 0 && y >= 0 && x < input.length && y < input[0].length;
    }

    function getAdjacent([x, y]) {
        const adjacents = [];
        for (const dir of directions) {
          let x1 = x + dir[0];
          let y1 = y + dir[1];
          adjacents.push([x1, y1]);
        }
        return adjacents;
      }

    const grid = [
        "AAAA",
        "ABBA",
        "ABBA",
        "AAAA",
    ];
    
    const input = grid.map(row => row.split(''));
    let p2_ans = 0;
    const visited = new Set();
    
    for (let i = 0; i < input.length; i++) {
      for (let j = 0; j < input[0].length; j++) {
        if (!visited.has(`${i},${j}`)) {
          bfs([i, j]);
        }
      }
    }
    
    function bfs(coordinates) {
      let Area = 0;    
      let edges = new Set();
      let edgeCount = 0;
    
      const type = input[coordinates[0]][coordinates[1]];
      const queue = [coordinates];
    
      while (queue.length > 0) {
        const current = queue.shift();
        const key = current.join(",");
    
        if (visited.has(key)) {
          continue;
        } else {
          visited.add(key);
        }
        Area++;

//        console.log("Currently under review: " + current);
    
        let adjecentArray = getAdjacent(current);
        for (let polarity = 0; polarity < adjecentArray.length; polarity++) {
          let neighbor = adjecentArray[polarity];
          if (!inBounds(neighbor) || input[neighbor[0]][neighbor[1]] !== type) {
            edgeCount++;
            edges.add(`${polarity},${neighbor[0]},${neighbor[1]}`);
//            console.log("Edge added: " + `${polarity},${neighbor[0]},${neighbor[1]}`);
    
            for(const n2 of getAdjacent(neighbor)) {
              if(edges.has(`${polarity},${n2[0]},${n2[1]}`)) {
//                console.log("Edge removed: " + `${polarity},${n2[0]},${n2[1]}` + " is already in set\n");
                edgeCount--;
              }
            }
          }
          else {
            queue.push(neighbor);
          }
    
        }
      }
      const fenceCost = Area * edgeCount;
      console.log("Region:", type, "Area:", Area, "Edges:", edgeCount, "fenceCost:", fenceCost);
      p2_ans += fenceCost;
    }
    
    console.log("Part 2:", p2_ans);
};

solvePart1();
solvePart2();
