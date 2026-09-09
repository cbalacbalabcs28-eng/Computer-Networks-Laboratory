#include <stdlib.h>
#include <string.h>

// Comparison function for qsort to initialize the first window
int compareInts(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Binary search to find the exact index of an element to remove
int findIndex(int* arr, int size, int val) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == val) return mid;
        if (arr[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Binary search to find the correct insertion position for a new element
int findInsertPosition(int* arr, int size, int val) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    double* result = (double*)malloc((*returnSize) * sizeof(double));
    
    // Maintain a sorted array of the current window elements
    int* window = (int*)malloc(k * sizeof(int));
    
    // 1. Initialize and sort the very first window
    memcpy(window, nums, k * sizeof(int));
    qsort(window, k, sizeof(int), compareInts);
    
    int resultIdx = 0;
    
    for (int i = k; i <= numsSize; i++) {
        // 2. Calculate the median of the current sorted window
        if (k % 2 == 1) {
            result[resultIdx++] = (double)window[k / 2];
        } else {
            // Cast to double first to prevent integer overflow during addition
            result[resultIdx++] = ((double)window[k / 2 - 1] + (double)window[k / 2]) / 2.0;
        }
        
        // If we've processed all elements, break out
        if (i == numsSize) break;
        
        // 3. Slide the window: Remove the element that is falling out (nums[i - k])
        int valToRemove = nums[i - k];
        int removeIdx = findIndex(window, k, valToRemove);
        
        // Shift elements left to close the gap
        memmove(&window[removeIdx], &window[removeIdx + 1], (k - 1 - removeIdx) * sizeof(int));
        
        // 4. Slide the window: Insert the new upcoming element (nums[i])
        int valToInsert = nums[i];
        // Note: The window size is temporarily k - 1 right now
        int insertIdx = findInsertPosition(window, k - 1, valToInsert);
        
        // Shift elements right to create a slot for the new value
        memmove(&window[insertIdx + 1], &window[insertIdx], (k - 1 - insertIdx) * sizeof(int));
        window[insertIdx] = valToInsert;
    }
    
    // Clean up temporary window buffer
    free(window);
    
    return result;
}


Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
Example 2:

Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 
