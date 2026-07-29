int findComplement(int num) {
    if (num == 0) {
        return 1;
    }
    unsigned int mask = 0;
    int temp = num;
    while (temp > 0) {
        mask = (mask << 1) | 1;
        temp = temp >> 1;
    }
    return num ^ mask;
}

Input: num = 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.

Input: num = 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
