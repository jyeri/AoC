// INPUT: Many strings, containing multiple instances, divided by ;
// OUTPUT: Sum of id's of the games are less
// order of op:
// 1. split string 1 ';'
// 2. read all substrings
// 3. store and update max value of each color
// 4. check if its doable
// 5. if yes
// -> res += id
// 6. max values = 0, and redo for the next ID (String)
// 7. when all ID's done, return res.