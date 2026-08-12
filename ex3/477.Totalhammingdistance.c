int totalHammingDistance(int* nums, int numsSize) {
    int total_distance = 0;
    
    // Loop through each of the 32 bit positions
    for (int i = 0; i < 32; i++) {
        int count_ones = 0;
        
        // Count how many numbers have the i-th bit set to 1
        for (int j = 0; j < numsSize; j++) {
            if ((nums[j] >> i) & 1) {
                count_ones++;
            }
        }
        
        // Numbers with a 0 bit at the i-th position
        int count_zeros = numsSize - count_ones;
        
        // Add the combinations of (1 and 0) pairs to the total sum
        total_distance += count_ones * count_zeros;
    }
    
    return total_distance;
}
