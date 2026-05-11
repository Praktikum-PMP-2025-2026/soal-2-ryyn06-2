#include <stdio.h>
#include <stdlib.h>

//referensi = https://www.geeksforgeeks.org/c/graph-cycle-detection-in-c/

#define MAX_VERTICES 100

// Graph structure
struct Graph {
    int numVertices;
    int** adjMatrix;
};

// Create a graph
struct Graph* createGraph(int vertices)
{
    struct Graph* graph
        = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjMatrix
        = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i]
            = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

// Add edge to the graph
void addEdge(struct Graph* graph, int src, int dest)
{
    graph->adjMatrix[src][dest] = 1;
}

// Utility function to detect cycle using DFS
int dfsCycleDetection(struct Graph* graph, int vertex, int* visited, int* recStack)
{
    if (!visited[vertex]) {
        // Mark the current node as visited and add to
        // recursion stack
        visited[vertex] = 1;
        recStack[vertex] = 1;

        // Recur for all vertices adjacent to this vertex
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjMatrix[vertex][v]) {
                if (!visited[v]
                    && dfsCycleDetection(graph, v, visited,
                                         recStack)) {
                    return 1;
                }
                else if (recStack[v]) {
                    return 1;
                }
            }
        }
    }
    recStack[vertex]
        = 0; // Remove the vertex from recursion stack
    return 0;
}

// Function to detect cycle in the graph
int detectCycle(struct Graph* graph)
{
    int* visited
        = (int*)malloc(graph->numVertices * sizeof(int));
    int* recStack
        = (int*)malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (dfsCycleDetection(graph, i, visited,
                              recStack)) {
            return 1;
        }
    }
    return 0;
}

int main()
{
    struct Graph* graph = createGraph(4);
    int missionNum, pasangan, a[MAX_VERTICES],b[MAX_VERTICES];
    scanf("%d %d", &missionNum,&pasangan);

    for (int i = 0; i < pasangan; i++)
    {
        scanf("%d %d", &a[i],&b[i]);
        addEdge(graph, a[i], b[i]);
    }
    
    
    if (detectCycle(graph)) {
        printf("TIDAK BISA");
    }
    else {
        printf("BISA");
    }

    return 0;
}
