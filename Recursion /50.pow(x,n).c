double myPow(double x, int n) {
    long long N = n;
    
    // Handle negative exponents
    if (N < 0) {
        x = 1.0 / x;
        N = -N;
    }
    
    double result = 1.0;
    
    // Optimize bitwise traversal
    while (N > 0) {
        // (N & 1) checks if the lowest bit is 1 (equivalent to N % 2 == 1)
        if (N & 1) {
            result *= x;
        }
        // Square the base
        x *= x;
        // Bitwise right shift by 1 (equivalent to N /= 2)
        N >>= 1;
    }
    
    return result;
}
