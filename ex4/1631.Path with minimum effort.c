#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 1e9

// Structure to represent a cell in the min-heap
typedef struct {
    int effort;
    int r;
    int c;
} HeapNode;

// Fast array-based Min-Heap implementation
typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* heap, int effort, int r, int c) {
    int i = heap->size++;
    heap->data[i].effort = effort;
    heap->data[i].r = r;
    heap->data[i].c = c;
    
    // Bubble up
    while (i > 0 && heap->data[i].effort < heap->data[(i - 1) / 2].effort) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode pop(MinHeap* heap) {
    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    
    int i = 0;
    // Bubble down
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = left;
        
        if (right < heap->size && heap->data[right].effort < heap->data[left].effort) {
            smallest = right;
        }
        if (heap->data[i].effort <= heap->data[smallest].effort) {
            break;
        }
        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
    return root;
}

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int rows = heightsSize;
    int cols = heightsColSize[0];
    
    // 2D flattened array for tracking minimum efforts
    int* efforts = (int*)malloc(sizeof(int) * rows * cols);
    for (int i = 0; i < rows * cols; i++) {
        efforts[i] = INF;
    }
    efforts[0] = 0;
    
    // Maximum nodes in heap will not exceed 4 * rows * cols
    MinHeap* heap = createMinHeap(rows * cols * 4);
    push(heap, 0, 0, 0);
    
    // Directions vectors: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    int minEffortRequired = 0;
    
    while (heap->size > 0) {
        HeapNode curr = pop(heap);
        int curEffort = curr.effort;
        int r = curr.r;
        int c = curr.c;
        
        // Target reached
        if (r == rows - 1 && c == cols - 1) {
            minEffortRequired = curEffort;
            break;
        }
        
        // Skip stale heap data
        if (curEffort > efforts[r * cols + c]) continue;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int stepEffort = abs(heights[r][c] - heights[nr][nc]);
                int nextEffort = (curEffort > stepEffort) ? curEffort : stepEffort;
                
                if (nextEffort < efforts[nr * cols + nc]) {
                    efforts[nr * cols + nc] = nextEffort;
                    push(heap, nextEffort, nr, nc);
                }
            }
        }
    }
    
    // Free allocated memory
    free(heap->data);
    free(heap);
    free(efforts);
    
    return minEffortRequired;
}



Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
