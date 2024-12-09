// Advent of Code 2024 - Day 9

/*
    --- Part 1 ---
    straight forward construct the arrays of spaces and files, then swap the spaces with the files
    and calculate the checksum

    --- Part 2 ---
    same start but create chunks of the spaces and files. files needs to be sorted in descending order
    then try to place each file in the spaces. if a file can't be placed, skip it.
    then calculate the checksum
*/

const fs = require('fs');
const input = fs.readFileSync('./input.txt', 'utf8').trim().split('\n');

const groupChunks = (array) => {
    let chunks = [];
    let currentType = array[0];
    let currentStart = 0;
    let currentLength = 0;

    for (let i = 0; i < array.length; i++) {
        if (array[i] === currentType) {
            currentLength++;
        } else {
            chunks.push({
                type: currentType,
                start: currentStart,
                length: currentLength,
            });
            currentType = array[i];
            currentStart = i;
            currentLength = 1;
        }
    }

    chunks.push({
        type: currentType,
        start: currentStart,
        length: currentLength,
    });

    return chunks;
};

const constructor = (constructedArray, mode, num, char) => {
    while (num > 0) {
        if (mode === 'file') {
            constructedArray.push(char);
        } else if (mode === 'space') {
            constructedArray.push('.');
        }
        num--;
    }
    return constructedArray;
};

const swapper = (constructedArray, charIndexes, spaceIndexes) => {
    let result = [...constructedArray];
    let spaces = [...spaceIndexes];
    let chars = [...charIndexes];

//        console.log("Initial result:", result);
//        console.log("Spaces:", spaces);
//        console.log("Chars:", chars);

    while (spaces.length > 0 && chars.length > 0) {
        const space = spaces.shift();
        const char = chars.pop();
//           console.log("Swapping space:", space, "with char:", char);
        if (space < char) {
            result[space] = result[char];
            result[char] = '.';
        }
    }
    return result;
};

// Part 1
const solvePart1 = () => {
    let p1_ans = 0;
    const tester = ["2333133121414131402"];
    let constructedArray = [];
    let spaceIndexes = [];
    let charIndexes = [];

    for (const row of tester) {
        console.log("Input Row:", row);
        let j = 0;
        let mode = "file";
        for (let i = 0; i < row.length; i++) {
            const char = row[i];
            if (i % 2 !== 0) {
                mode = "space";
                constructedArray = constructor(constructedArray, mode, parseInt(char), '.');
            } else {
                mode = "file";
                constructedArray = constructor(constructedArray, mode, parseInt(char), j);
                j++;
            }
        }
        console.log("Constructed Array:", constructedArray.join(''));
    }

    for (let i = 0; i < constructedArray.length; i++) {
        if (constructedArray[i] === '.') {
            spaceIndexes.push(i);
        } else {
            charIndexes.push(i);
        }
    }
//    console.log("Space Indexes:", spaceIndexes);
//    console.log("Character Indexes:", charIndexes);

    let resultArray = swapper(constructedArray, charIndexes, spaceIndexes);

    console.log("Result Array:", resultArray.join(''));

    for (let i = 0; i < resultArray.length; i++) {
        if (resultArray[i] !== '.') {
            const fileID = parseInt(resultArray[i]);
            p1_ans += fileID * i;
        }
    }

    console.log('Part 1 Checksum:', p1_ans);
};

// Part 2
const solvePart2 = () => {
    let p2_ans = 0;
    let constructedArray = [];
    const tester = ["2333133121414131402"];

    for (const row of input) {
        let j = 0;
        let mode = 'file';
        for (let i = 0; i < row.length; i++) {
            const char = row[i];
            if (i % 2 !== 0) {
                mode = 'space';
                constructedArray = constructor(constructedArray, mode, parseInt(char), '.');
            } else {
                mode = 'file';
                constructedArray = constructor(constructedArray, mode, parseInt(char), j);
                j++;
            }
        }
    }

//    console.log('Constructed Array for Part 2:', constructedArray.join(''));

    let chunks = groupChunks(constructedArray);
    let spaces = chunks.filter(chunk => chunk.type === '.');
    let files = chunks
        .filter(chunk => chunk.type !== '.')
        .sort((a, b) => b.type - a.type);

    for (const fileChunk of files) {
        let placed = false;

        for (let i = 0; i < spaces.length; i++) {
            const spaceChunk = spaces[i];

            if (spaceChunk.length >= fileChunk.length && spaceChunk.start < fileChunk.start) {
                for (let j = 0; j < fileChunk.length; j++) {
                    constructedArray[spaceChunk.start + j] = fileChunk.type;
                    constructedArray[fileChunk.start + j] = '.';
                }
                spaceChunk.start += fileChunk.length;
                spaceChunk.length -= fileChunk.length;

                if (spaceChunk.length === 0) {
                    spaces.splice(i, 1);
                }

                placed = true;
                break;
            }
        }

        if (!placed) {
            continue;
        }
    }

    console.log('Final Array:', constructedArray.join(''));

    // Calculate checksum
    for (let i = 0; i < constructedArray.length; i++) {
        if (constructedArray[i] !== '.') {
            const fileID = parseInt(constructedArray[i]);
            p2_ans += fileID * i;
        }
    }

    console.log('Part 2 Checksum:', p2_ans);
};


solvePart1();
solvePart2();
