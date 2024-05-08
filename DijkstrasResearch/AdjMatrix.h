#ifndef ADJMATRIX_H
#define ADJMATRIX_H

typedef struct {
    int V; // Number of vertices
    int** matrix; // Adjacency matrix
} Graph;

Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int start);

#endif
