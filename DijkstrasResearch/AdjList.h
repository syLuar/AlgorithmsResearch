// Structure to represent a node in the adjacency list
#ifndef ADJLIST_H
#define ADJLIST_H

typedef struct Node {
    int data;
    int weight;          // Weight of the edge
    struct Node* next;
} Node;

// Structure to represent an adjacency list
typedef struct AdjList {
    int V;             // Number of vertices
    struct Node** array; // Array of pointers to Node
} AdjList;

Node* createNode(int data, int weight);
AdjList* createGraph(int V);
void addEdge(AdjList* adjList, int src, int dest, int weight);
void printGraph(AdjList* adjList);

#endif

