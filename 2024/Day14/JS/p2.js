const fs = require('fs');

// Read the file contents
const fileContents = fs.readFileSync('S14_res.txt', 'utf8').split('\n');

// Convert file contents to a 2D array
const grid = fileContents.map(line => line.split(''));

// Function to check if there is a row with a sequence of at least 10 robots
function hasCristmasTree(grid) {
    for (const row of grid) {
        let count = 0;
        for (const cell of row) {
            if (cell === '.') count = 0;
            else if (++count >= 10) {
                return true;
            }
        }
    }
    return false;
}

// Function to write the grid to a file
function writeGridToFile(grid) {
    fs.writeFileSync('christmasTree.txt', 
        grid.map(row => row.map(cell => (cell === '1' ? '#' : '.')).join('')).join('\n')
    );
}

// Function to find tree-like structures in the grid
function findTrees(grid) {
    if (hasCristmasTree(grid)) {
        writeGridToFile(grid); // Write the grid to the file only once
        console.log('Tree-like structure found and written to christmasTree.txt');
    } else {
        console.log('No tree-like structures found.');
    }
}

// Find the trees in the grid
findTrees(grid);