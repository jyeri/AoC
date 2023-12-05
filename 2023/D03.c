// INPUT: Multiple lines of '.', 'symbol' or Integers
// OUTPUT: sum of all integers that have adjecent symbol (horizontal, vertical or diagonal)

// Or of op:
// 1. iterate first line until first is_digit()
// -> while is_digit() sum = sum * 10 + atoi(str[x])
// 2. check if there is symbol before or after the integer, is there diagonal of start or stop, is there horizontal of whole string
// -> if true check = 0 AND
// -> (
// -> if str[x - 1][y - 1] OR
// -> if str[x + 1][y - 1] OR
// -> if str[x + 1][y + 1] OR
// -> if str[x - 1][y + 1] OR
// -> if str[x + 1][y] OR
// -> if str[x - 1][y] OR
// -> if str[x][y - 1] OR
// -> if str[x][y + 1] == SYM OR
// -> )
// true check = 1

// 3. if true check == 1
// -> result += sum
// 4. if true check == 0
// -> sum = 0
// 5. true check = 0
// 6. iterate to next string and repeat until all arguments are done
// 7. return value is res