#include <stdio.h>
#include <stdlib.h>
#include "AdjList.h"
// Function to create a new node
Node* createNode(int data, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'V' vertices
AdjList* createGraph(int V) {
    AdjList* adjList = (AdjList*)malloc(sizeof(AdjList));
    adjList->V = V;

    // Create an array of pointers to Node for each vertex
    adjList->array = (Node**)malloc(V * sizeof(Node*));

    // Initialize each adjacency list as empty (NULL)
    for (int i = 0; i < V; ++i)
        adjList->array[i] = NULL;

    return adjList;
}

// Function to add an edge with a weight to an undirected graph
void addEdge(AdjList* adjList, int src, int dest, int weight) {
    // Add an edge from src to dest with the given weight
    Node* newNode = createNode(dest, weight);
    newNode->next = adjList->array[src];
    adjList->array[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src with the same weight
    newNode = createNode(src, weight);
    newNode->next = adjList->array[dest];
    adjList->array[dest] = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(AdjList* adjList) {
    for (int v = 0; v < adjList->V; ++v) {
        printf("Adjacency list of vertex %d:\n", v);
        Node* current = adjList->array[v];
        while (current) {
            printf(" -> %d (Weight: %d)", current->data, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}