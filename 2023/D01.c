// INPUT: Multiple lines of strings, mixed with alpha and numbers
// OUTPUT: Sum of first and last digit(check if 10 is counted or only 1) of each line
// EXECUTION:
// 1. iterate array x(starting from 1st) from front until digit, then again from end
// 2. save these values as integer (1abc2 = 1, 2 = 12)
// -> atoi(1st) -> *10 -> atoi(2nd) -> add to 1st
// 3. add this value always to last combined result
// 4. keep repeating until we have gone thru whole input
// 5. return the combined sum we have gotten



int main(void)
{
    char    **str;
    char    str[0] = "1bc2";
    char    str[1] = "pqr3stu8vwx";
    char    str[2] = "a1b2c3d4e5f";
    char    str[3] = "treb7uchet";
    int x = 0;
    int y = 0;
    int i = 0;
    int res = 0;
    int current = 0;
    int first = 0;
    int second = 0;

    while (x < 4)
    {
        i = 0;
        while (str[x][i])
        {
            if (is_digit(str[x][i]))

            i++;
        }
        x++;
    }
}

