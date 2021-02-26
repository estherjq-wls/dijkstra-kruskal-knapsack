//Program 1 - Shortest Path.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <limits.h>
#include <stdio.h>
using namespace std;

const int NUM_OF_VERTICES = 10;
const int NUM_OF_EDGES = 18;

struct Planet
{
    string name;
    int x;
    int y;
    int z;
    int weight;
    int profit;

    int value()
    {
        return weight != 0 ? int(profit / weight) : 0;
    }

    int distanceTo(Planet *planet)
    {
        return sqrt(pow(planet->x - x, 2.0) + pow(planet->y - y, 2.0) + pow(planet->z - z, 2.0));
    }

    Planet(string name = "", int x = 0, int y = 0, int z = 0, int weight = 0, int profit = 0)
        : name(name), x(x), y(y), z(z), weight(weight), profit(profit)
    {
    }
};

struct Edge
{
    string v1;
    string v2;
    int distance;

    Edge(string v1 = "", string v2 = "", int distance = 0)
        : v1(v1), v2(v2), distance(distance)
    {
    }
};

Planet **planetArr = new Planet *[NUM_OF_VERTICES];
Edge **edgeArr = new Edge *[NUM_OF_EDGES];

// Function to convert the planet's name(last alphabet) to the array number that stores this planet in planetArr. For example: "A" -> 0
int convertStrToArrIndex(string str)
{
    return int(str[0]) - 65;
}

// Function to convert the array number in planetArr to the name of the planet(last alphabet) stored. For example: 0 -> "A"
string convertArrIndexToStr(int i)
{
    string s(1, char(i + 65));
    return s;
}

// Function to add Edge into edgeArr.
int arrLength = 0;
void addEdge(string v1, string v2)
{
    int i = convertStrToArrIndex(v1);
    int j = convertStrToArrIndex(v2);
    int distance = planetArr[i]->distanceTo(planetArr[j]);
    if (arrLength < NUM_OF_EDGES)
    {
        edgeArr[arrLength++] = new Edge(v1, v2, distance);
    }
    else
    {
        cout << "Number of edges exceeds 18. Cannot add more edges anymore" << endl;
    }
}

// Function to add edge into the matrix
void addEdgeToMatrix(int matrix[][NUM_OF_VERTICES])
{
    for (int i = 0; i < NUM_OF_EDGES; i++)
    {
        int a = convertStrToArrIndex(edgeArr[i]->v1);
        int b = convertStrToArrIndex(edgeArr[i]->v2);
        int d = edgeArr[i]->distance;
        matrix[a][b] = d;
        matrix[b][a] = d;
    }
}

// An utility function to find the vertex with minimum distance value,
// from the set of vertices not yet included in shortest path tree.
int minDistance(int dist[],
                bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < NUM_OF_VERTICES; v++)
        if (sptSet[v] == false &&
            dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print shortest path from source to j using parent array.
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == -1)
    {
        cout << convertArrIndexToStr(j);
        return;
    }
    printPath(parent, parent[j]);
    cout << " -> " << convertArrIndexToStr(j);
}

// An utility function to print the constructed distance array.
void printSolution(int dist[], int n,
                   int parent[], int src)
{
    string srcStr = convertArrIndexToStr(src);
    printf("Vertex\t\tShortest Distance\tPath");
    for (int i = 0; i < NUM_OF_VERTICES; i++)
    {
        string vertexStr = convertArrIndexToStr(i);
        cout << endl;
        cout << srcStr << " -> " << vertexStr << "\t\t" << dist[i] << "\t\t\t";
        printPath(parent, i);
    }
}

// Function that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[NUM_OF_VERTICES][NUM_OF_VERTICES], int src)
{

    // The output array dist[i] will hold the shortest distance from src to i.
    int dist[NUM_OF_VERTICES];

    // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized.
    bool sptSet[NUM_OF_VERTICES];

    // Parent array is used to store shortest path tree.
    // parent[i] will store the parent node of i.
    // parent[i] is -1 if i is the source.
    int parent[NUM_OF_VERTICES];

    // Initialize parent[src] as -1 since source doesn't have a parent node.
    // Initialize all distances as INFINITE(which is INT_MAX) and stpSet[] as false.
    for (int i = 0; i < NUM_OF_VERTICES; i++)
    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0.
    dist[src] = 0;

    // Find shortest path for all vertices.
    for (int count = 0; count < NUM_OF_VERTICES - 1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration since dist[src] is 0.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as true, meaning that it has processed.
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < NUM_OF_VERTICES; v++)

            // Update dist[v] only if
            // 1. is not in sptSet,
            // 2. there is an edge from u to v, and
            // 3. total weight of path from src to v through u is smaller than current value of dist[v].
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the solution (vertex, distance, and path)
    printSolution(dist, NUM_OF_VERTICES, parent, src);
}

int main()
{

    //change the path according to your own file location
    ifstream dataFile("A2planets.txt");

    //read data file, initialize Planet and put them in planetArr
    if (dataFile.is_open())
    {
        int count = 0;
        string line;
        while (getline(dataFile, line))
        {
            istringstream iss(line);
            string data_name;
            int data_x;
            int data_y;
            int data_z;
            int data_weight;
            int data_profit;
            if (!(iss >> data_name >> data_x >> data_y >> data_z >> data_weight >> data_profit))
            {
                break;
            } // error
            planetArr[count] = new Planet(data_name, data_x, data_y, data_z, data_weight, data_profit);
            count++;
        }
        dataFile.close();
    }
    else
    {
        cout << "Unable to open file";
        return 0;
    }

    addEdge("A", "D");
    addEdge("A", "F");
    addEdge("A", "H");
    addEdge("A", "J");
    addEdge("B", "D");
    addEdge("B", "E");
    addEdge("B", "G");
    addEdge("C", "E");
    addEdge("C", "F");
    addEdge("C", "I");
    addEdge("D", "J");
    addEdge("E", "G");
    addEdge("E", "I");
    addEdge("F", "H");
    addEdge("G", "I");
    addEdge("G", "J");
    addEdge("H", "I");
    addEdge("H", "J");

    int matrix[NUM_OF_VERTICES][NUM_OF_VERTICES] = {0};
    addEdgeToMatrix(matrix);

    dijkstra(matrix, 0);

    return 0;
}
