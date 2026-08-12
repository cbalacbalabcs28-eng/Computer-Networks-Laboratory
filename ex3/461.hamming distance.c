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
