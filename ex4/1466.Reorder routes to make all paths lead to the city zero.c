#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a directed edge in our flattened adjacency list
typedef struct {
    int to;
    int is_original; // 1 if original direction (away from capital), 0 if artificial back-edge
    int next;        // Pointer to the next edge index for the same source node
} Edge;

int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    // Total bidirectional edges will be 2 * (n - 1)
    int edgeCount = 2 * (n - 1);
    Edge* edges = (Edge*)malloc(sizeof(Edge) * edgeCount);
    
    // Head array to track the starting edge index for each node
    int* head = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }

    int edgeIdx = 0;
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];

        // 1. Add original edge (u -> v) with weight 1 (meaning it points away from 0)
        edges[edgeIdx].to = v;
        edges[edgeIdx].is_original = 1;
        edges[edgeIdx].next = head[u];
        head[u] = edgeIdx++;

        // 2. Add artificial reverse edge (v -> u) with weight 0 (points toward 0)
        edges[edgeIdx].to = u;
        edges[edgeIdx].is_original = 0;
        edges[edgeIdx].next = head[v];
        head[v] = edgeIdx++;
    }

    // Allocate memory for BFS queue and visited tracking array
    int* queue = (int*)malloc(sizeof(int) * n);
    int* visited = (int*)calloc(n, sizeof(int));
    
    int front = 0, rear = 0;
    int reorderCount = 0;

    // Start BFS traversal from capital (city 0)
    queue[rear++] = 0;
    visited[0] = 1;

    while (front < rear) {
        int curr = queue[front++];

        // Traverse all edges coming out of the current city
        for (int e = head[curr]; e != -1; e = edges[e].next) {
            int neighbor = edges[e].to;
            
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                // If it's an original edge pointing away from 0, it must be flipped (+1)
                reorderCount += edges[e].is_original; 
                queue[rear++] = neighbor;
            }
        }
    }

    // Free all allocated memory blocks
    free(edges);
    free(head);
    free(queue);
    free(visited);

    return reorderCount;
}


Example 1:

Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
Output: 3
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 2:

Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
Output: 2
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
