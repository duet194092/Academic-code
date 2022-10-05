#include <cstdio>
#include <cstdlib>
#include <cstring>

#define N 8
#define INFINITY 99999

// Reading graph matrix.
void ReadFile(int graph[][N])
{
	FILE *fp = fopen("input.txt", "r");

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fscanf(fp, "%d ", &graph[i][j]);
		}
	}
}

// Choose u from among those vertices not in S and distance[u] is minimum.
// Vertex u will be adjacent from some vertices in S.
int ChooseU(int S[], int distance[])
{
	int min = INFINITY;
	int u;

	for (int i = 0; i < N; i++)
	{
		// If vertex is not in the S list.
		// If the minimum was found, it would have been in the S list.
		if (S[i] != 1)
		{
			if (min > distance[i])
			{
				min = distance[i];
				u = i;
			}
		}
	}

	return u;
}

int main()
{
	int graph[N][N]; // Graph information, adjacency matrix
	int distance[N]; // Length of shortest path from vertex s to any vertex.
	int S[N];		 // Vertices (including s) to which the shortest paths have already been generated. Indicated by boolean value (1, 0).
	int src = 0;	 // Source vertex.

	ReadFile(graph);

	for (int v = 0; v < N; v++)
	{
		S[v] = 0; // Not any vertex's minimum is calculated.
		distance[v] = graph[src][v]; // Store edge costs (src, v).
	}

	// We start off by the source. Its minimum distance is calculated.
	S[src] = 1;
	distance[src] = 0;

	// Except for the source, do if for the rest.
	for (int i = 1; i < N; i++)
	{
		// Choose u from among those vertices not in S and distance[u] is minimum.
		int u = ChooseU(S, distance);

		// Now u's minimum distance from src will be calculated.
		S[u] = 1;

		// For each vertex (v) adjacent to u with v is not in S.
		// Update distances.
		for (int v = 0; v < N; v++)
		{
			if (graph[u][v] != INFINITY && S[v] == 0)
			{
				if (distance[v] > distance[u] + graph[u][v])
					distance[v] = distance[u] + graph[u][v];
			}
		}
	}

	// Display distance from src to any vertex.
	printf("Distances From Source to Any Vertex\n\n");

	for (int d = 0; d < N; d++)
	{
		printf("%d\n", distance[d]);
	}
}

// FOCA
// 0 99999 99999 99999 99999 99999 99999 99999
// 300 0 99999 99999 99999 99999 99999 99999
// 1000 800 0 99999 99999 99999 99999 99999
// 99999 99999 1200 0 99999 99999 99999 99999
// 99999 99999 99999 1500 0 250 99999 99999
// 99999 99999 99999 1000 99999 0 900 1400
// 99999 99999 99999 99999 99999 99999 0 1000
// 1700 99999 99999 99999 99999 99999 99999 0
