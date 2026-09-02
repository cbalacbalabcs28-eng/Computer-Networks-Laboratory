int hammingDistance(int x, int y) {
    int xor_result = x ^ y;
    int distance = 0;
    
    // Count the number of set bits (1s)
    while (xor_result > 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    
    return distance;
}

Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
The above arrows point to positions where the corresponding bits are different.
