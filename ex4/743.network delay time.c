#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

// Structure to represent a directed edge in the flattened adjacency list
typedef struct {
    int to;
    int weight;
    int next; // Pointer to the next edge index for the same source node
} Edge;

// Structure for Min-Heap nodes
typedef struct {
    int time;
    int node;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
} MinHeap;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* heap, int time, int node) {
    int i = heap->size++;
    heap->data[i].time = time;
    heap->data[i].node = node;
    
    // Bubble up
    while (i > 0 && heap->data[i].time < heap->data[(i - 1) / 2].time) {
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
        
        if (right < heap->size && heap->data[right].time < heap->data[left].time) {
            smallest = right;
        }
        if (heap->data[i].time <= heap->data[smallest].time) {
            break;
        }
        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
    return root;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    // 1. Build the graph using a flat array structure
    Edge* edges = (Edge*)malloc(sizeof(Edge) * timesSize);
    int* head = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        
        edges[i].to = v;
        edges[i].weight = w;
        edges[i].next = head[u];
        head[u] = i;
    }

    // 2. Initialize tracking arrays
    int* dist = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[k] = 0;

    // 3. Initialize Min-Heap (Worst-case allocation size is equal to number of edges)
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * (timesSize + 1));
    heap->size = 0;
    
    push(heap, 0, k);

    // 4. Dijkstra's core execution loop
    while (heap->size > 0) {
        HeapNode curr = pop(heap);
        int curTime = curr.time;
        int u = curr.node;

        if (curTime > dist[u]) continue;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int weight = edges[e].weight;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(heap, dist[v], v);
            }
        }
    }

    // 5. Calculate total network distribution time
    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            maxTime = -1; // Node cannot be reached
            break;
        }
        if (dist[i] > maxTime) {
            maxTime = dist[i];
        }
    }

    // Free all allocated memory blocks
    free(edges);
    free(head);
    free(dist);
    free(heap->data);
    free(heap);

    return maxTime;
}

Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2
