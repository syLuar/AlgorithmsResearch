#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VERTICES 51  // Number of vertices (0 to N)
#define NUM_EDGES 50

int main() {
    srand(time(NULL));

    // Declare a pointer to a pointer to represent the 2D array
    int** edges = (int**)malloc(NUM_VERTICES * sizeof(int*));
    if (edges == NULL) {
        perror("Error allocating memory for edges");
        return 1;
    }

    // Allocate memory for each row
    for (int i = 0; i < NUM_VERTICES; i++) {
        edges[i] = (int*)malloc(NUM_VERTICES * sizeof(int));
        if (edges[i] == NULL) {
            perror("Error allocating memory for edges");
            return 1;
        }
    }

    // Initialize the edges to zero
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            edges[i][j] = 0;
        }
    }

    int genEdges = 0;

    // Generate random edges for each vertex while ensuring connectivity
    for (int i = 0; i < NUM_VERTICES; i++) {
        int numEdges = 1;
        for (int j = 0; j < numEdges; j++) {
            int randomVertex;
            do {
                randomVertex = rand() % NUM_VERTICES;
            } while (randomVertex == i || edges[i][randomVertex] != 0);
            int randomWeight = rand() % 50 + 1;  // Random weight between 1 and 50
            edges[i][randomVertex] = randomWeight;
            edges[randomVertex][i] = randomWeight;
        }
        genEdges++;
    }



    for(int i=genEdges; i<NUM_EDGES; i++)
    {
        int randomVertex, randomDstVertex;
        randomVertex = rand() % NUM_VERTICES;

        do{
            randomDstVertex = rand() %NUM_VERTICES;
        } while (randomVertex == randomDstVertex || edges[randomVertex][randomDstVertex] !=0);
        int randomWeight = rand() % 50 + 1;

        edges[randomVertex][randomDstVertex] = randomWeight;
        edges[randomDstVertex][randomVertex] = randomWeight;
    }

    // Open a file for writing
    FILE* outputFile = fopen("50edges_case.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // Write the edges to the file
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i + 1; j < NUM_VERTICES; j++) {
            if (edges[i][j] != 0) {
                fprintf(outputFile, "%d %d %d\n", i, j, edges[i][j]);
            }
        }
    }

    // Close the file
    fclose(outputFile);

    // Free the dynamically allocated memory
    for (int i = 0; i < NUM_VERTICES; i++) {
        free(edges[i]);
    }
    free(edges);

    return 0;
}
