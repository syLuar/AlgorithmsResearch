#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "AdjMatrix.h"

int minDistance(int* distances, bool* visited, int V) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; ++v) {
        if (!visited[v] && distances[v] < min) {
            min = distances[v];
            min_index = v;
        }
    }

    return min_index;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    graph->matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; ++i) {
        graph->matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                graph->matrix[i][j] = 0;
            } else {
                graph->matrix[i][j] = INT_MAX;
            }
        }
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight;
}

void dijkstra(Graph* graph, int start) {
    int V = graph->V;
    int* distances = (int*)malloc(V * sizeof(int));
    bool* visited = (bool*)malloc(V * sizeof(bool));

    for (int i = 0; i < V; ++i) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    distances[start] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = minDistance(distances, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph->matrix[u][v] != INT_MAX
                && distances[u] != INT_MAX
                && distances[u] + graph->matrix[u][v] < distances[v]) {
                distances[v] = distances[u] + graph->matrix[u][v];
            }
        }
    }

    printf("Shortest distances from vertex %d to all other vertices:\n", start);
    for (int i = 0; i < V; ++i) {
        printf("Vertex %d: %d\n", i, distances[i]);
    }

}
