int subarrayBitwiseORs(int* arr, int arrSize) {
    if (arrSize == 0) return 0;

    // Use a lightweight, local hash table directly inside the function.
    // The maximum possible number of unique OR values is bounded by 32 * arrSize.
    int capacity = arrSize * 64; 
    if (capacity < 1024) capacity = 1024; // Ensure minimum capacity for tiny arrays

    int *keys = (int*)malloc(capacity * sizeof(int));
    char *used = (char*)calloc(capacity, sizeof(char));
    int distinct_count = 0;

    // Two small fixed-size arrays to hold unique results for the current and previous element.
    // Since an integer has 32 bits, a subarray ending at any index can have at most 32 unique OR values.
    int cur_window[33];
    int cur_size = 0;

    for (int i = 0; i < arrSize; i++) {
        int x = arr[i];
        
        int next_window[33];
        int next_size = 0;

        // Start a new subarray consisting only of the current element 'x'
        next_window[next_size++] = x;
        
        // Inline Hash Set Insertion for 'x'
        unsigned int hash = (unsigned int)x % capacity;
        while (used[hash]) {
            if (keys[hash] == x) goto skip_x;
            hash = (hash + 1) % capacity;
        }
        keys[hash] = x;
        used[hash] = 1;
        distinct_count++;
        skip_x:;

        // Process all existing continuous bitwise OR chains combined with 'x'
        for (int j = 0; j < cur_size; j++) {
            int new_or = cur_window[j] | x;

            // Check if 'new_or' is already in our building window to keep elements distinct
            int duplicate = 0;
            for (int k = 0; k < next_size; k++) {
                if (next_window[k] == new_or) {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate) {
                next_window[next_size++] = new_or;
                
                // Inline Hash Set Insertion for 'new_or'
                unsigned int hash2 = (unsigned int)new_or % capacity;
                while (used[hash2]) {
                    if (keys[hash2] == new_or) goto skip_new_or;
                    hash2 = (hash2 + 1) % capacity;
                }
                keys[hash2] = new_or;
                used[hash2] = 1;
                distinct_count++;
                skip_new_or:;
            }
        }

        // Copy the built window state into cur_window for the next iteration
        cur_size = next_size;
        for (int j = 0; j < next_size; j++) {
            cur_window[j] = next_window[j];
        }
    }

    // Clean up all local dynamic heap memory allocations
    free(keys);
    free(used);
    
    return distinct_count;
}
