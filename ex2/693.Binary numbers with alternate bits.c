#include <stdbool.h>

bool hasAlternatingBits(int n) {
    // Get the very first bit on the right (0 or 1)
    int last_bit = n % 2; 
    n /= 2; // Shift to the next bit

    // Loop through the rest of the bits
    while (n > 0) {
        int current_bit = n % 2;
        
        // If two adjacent bits match, they are not alternating
        if (current_bit == last_bit) {
            return false;
        }
        
        last_bit = current_bit; // Update state
        n /= 2; // Move to the next bit
    }
    
    return true; // All adjacent bits were different
}
