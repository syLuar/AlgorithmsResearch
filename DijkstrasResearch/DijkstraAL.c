#include "AdjList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

typedef struct MinHeapNode {
    int vertex;
    int dist;
} MinHeapNode;

// Structure to represent a min-heap (priority queue)
typedef struct MinHeap {
    int size;
    int capacity;
    int* pos;  
    MinHeapNode** array;
} MinHeap;

MinHeapNode* createMinHeapNode(int vertex, int dist) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    newNode->vertex = vertex;
    newNode->dist = dist;
    return newNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNodes(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

bool isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;
    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int vertex, int dist) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNodes(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(MinHeap* minHeap, int vertex) {
    if (minHeap->pos[vertex] < minHeap->size)
        return true;
    return false;
}

void printShortestPath(int dist[], int n) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

void dijkstra(AdjList* adjList, int src) {
    int V = adjList->V;
    int dist[V]; 
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        minHeap->array[v] = createMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        Node* current = adjList->array[u];
        while (current != NULL) {
            int v = current->data;
            int weight = current->weight;

            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && (dist[u] + weight < dist[v])) {
                dist[v] = dist[u] + weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            current = current->next;
        }
    }

    printShortestPath(dist, V);
}


int main() {
    int V = 9; 
    AdjList* adjList = createGraph(V);

    addEdge(adjList, 0, 1, 4);
    addEdge(adjList, 0, 7, 8);
    addEdge(adjList, 1, 2, 8);
    addEdge(adjList, 1, 7, 11);
    addEdge(adjList, 2, 3, 7);
    addEdge(adjList, 2, 8, 2);
    addEdge(adjList, 2, 5, 4);
    addEdge(adjList, 3, 4, 9);
    addEdge(adjList, 3, 5, 14);
    addEdge(adjList, 4, 5, 10);
    addEdge(adjList, 5, 6, 2);
    addEdge(adjList, 6, 7, 1);
    addEdge(adjList, 6, 8, 6);
    addEdge(adjList, 7, 8, 7);

    int src = 0; 

    clock_t start_time = clock();
    dijkstra(adjList, src);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken to find the shortest path: %.6f seconds\n", time_taken);

    return 0;
}