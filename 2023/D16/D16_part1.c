// Blank slate idea after rethinking the problem.
// we make 2 grids: 1st grid (maze) that is equal to input and 2nd grid (energized), that is in beginning just '.', that marks where the beam has been
// -> we can do this char by char in same time. i still think that using globals for this is best way.

// solving we use recursion, we go to function that calculates and marks energy one beam at the time, and call it recursively if we counter splitter
// -> to easier tracking make table for directions instead of using integer 1-4, makes it so much feasible to understand
// -> Use switch - cases, need to work on those aswell since they are forbidden fruit in Hive.

// So basic idea step by step
// 1. Take input and copy it - same time make copy of the map just blanks.
// 2. make a beam that starts at location 0,0
// -> Beam comes with values x, y, and direction. in beginning the should be x = 0, y = 0, dir = E.
// 3. we give these parameters to energizer
// -> check the map if its inside parameters (in beginning yes)
// -> also check if the location is already been energized (no need to do anything)
// -> switch - cases for every special character
// -> small helper functions to different characters for example blacklash(int *x, int *y, enum *d)
//      -> inside helper we have switch cases that updates basically x and y cordinates with the direction.
//      -> combine these functions to be usable with either split on blacklash mirror?
// 4. in the end we can just loop thru the energy array that we made and check how much was energized.

// in the words of best sudoku channel ever: Lets get cracking