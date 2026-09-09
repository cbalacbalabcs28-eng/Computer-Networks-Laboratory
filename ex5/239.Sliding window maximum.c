#include <stdlib.h>

/**
 * Note: The returned array must be explicitly allocated by malloc.
 * The size of the returned array is written into the returnSize variable pointer.
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    // Allocate memory for the result array
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    int resultIdx = 0;

    // Allocate memory for the Deque to store indices
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0; // Pushes out from the front
    int rear = 0;  // Pushes out/in from the back

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are outside the current window boundary
        if (front < rear && deque[front] <= i - k) {
            front++;
        }

        // 2. Maintain monotonic order: remove smaller element indices from the back
        while (front < rear && nums[deque[rear - 1]] <= nums[i]) {
            rear--;
        }

        // 3. Add the current element's index to the back of the deque
        deque[rear++] = i;

        // 4. Once the first window is fully formed, record the maximum
        if (i >= k - 1) {
            result[resultIdx++] = nums[deque[front]];
        }
    }

    // Free the temporary deque buffer
    free(deque);
    
    return result;
}



Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
