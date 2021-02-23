//Program 1 - Display and sort.

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <list>
#include <iterator>
#include <map>
#include <stdlib.h>
#include <time.h>
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
    string v1; //vertice 1 that connects with the edge
    string v2; //vertice 2 that connects with the edge
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

// Function to add Edge into the matrix
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

// Function to add Edge into the list
void addEdgeToAdjList(map<string, list<pair<string, int>>> &adjList)
{
    for (int i = 0; i < NUM_OF_EDGES; i++)
    {
        adjList[edgeArr[i]->v1].push_back(make_pair(edgeArr[i]->v2, edgeArr[i]->distance));
    }
}

// Function to display the matrix
void displayMatrix(int matrix[10][10])
{
    cout << endl
         << "The Matrix:" << endl;

    for (int i = -1; i < NUM_OF_VERTICES; i++)
    {
        for (int j = -1; j < NUM_OF_VERTICES; j++)
        {
            if (j == -1 && i == -1)
            {
                cout << "     ";
            }
            else if (i == -1)
            {
                printf("%2c   ", char(convertArrIndexToStr(j)[0]));
            }
            else if (j == -1)
            {
                printf("%2c   ", char(convertArrIndexToStr(i)[0]));
            }
            else
            {
                printf("%4d ", matrix[i][j]);
            }
        }
        cout << endl;
    }
}

// Function to display the list
void displayAdjList(map<string, list<pair<string, int>>> &adjList)
{
    cout << endl
         << "The Adjacency List:" << endl;
    for (auto &value : adjList)
    {
        string vertex = value.first;
        list<pair<string, int>> adjVertices = value.second;
        list<pair<string, int>>::iterator itr = adjVertices.begin();

        cout << "[" << vertex << "]";
        while (itr != adjVertices.end())
        {
            cout << " -> [" << (*itr).first << "]";
            printf("(%4d)", (*itr).second);
            ++itr;
        }

        cout << endl;
    }
}

// An utility function to swap two Edges
void swap(Edge *&a, Edge *&b)
{
    Edge *t = a;
    a = b;
    b = t;
}

/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot. 
This Overloading Function is for edgeArr. */
int partitionArr(Edge **edgeArr, int low, int high)
{
    Edge *pivot = edgeArr[high]; // pivot
    int i = low - 1;             // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    { // use j to go through whole array to find element that is smaller than the pivot
        // If current element is smaller than the pivot
        if (edgeArr[j]->distance < pivot->distance)
        {
            i++; // increment index of smaller element
            swap(edgeArr[i], edgeArr[j]);
        }
    }

    //place pivot right after a bunch of elements that are smaller than the pivot
    swap(edgeArr[i + 1], edgeArr[high]);
    return i + 1;
}

/* Generates Random Pivot, swaps pivot with
end element and calls the partition function
This Overloading Function is for edgeArr. */
int partitionArr_r(Edge **edgeArr, int low, int high)
{
    // Generate a random number in between low and high
    srand(time(NULL));
    int random = low + rand() % (high - low);

    // Swap edgeArrrandom] with edgeArr[high]
    swap(edgeArr[random], edgeArr[high]);

    return partitionArr(edgeArr, low, high);
}

/* This function implements QuickSort and sort edge's distance in ascending order. 
arr --> Array to be sorted,  
low --> Starting index,  
high --> Ending index.
This Overloading Function is for edgeArr. */
void quickSortArr(Edge **edgeArr, int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partitionArr_r(edgeArr, low, high);

        // Separately sort elements before partition and after partition
        quickSortArr(edgeArr, low, pi - 1);
        quickSortArr(edgeArr, pi + 1, high);
    }
}

// Function to print edgeArr
void printArray(Edge **edgeArr)
{
    cout << "No.\tEdge\tDistance\n";
    for (int i = 0; i < NUM_OF_EDGES; i++)
    {
        printf("%2d)\t", i + 1);
        cout << edgeArr[i]->v1 << " -- " << edgeArr[i]->v2 << "\t";
        printf("%4d\n", edgeArr[i]->distance);
    }
    cout << endl;
}

// An utility function to swap two Planets
void swap(Planet *&a, Planet *&b)
{
    Planet *t = a;
    a = b;
    b = t;
}

/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all greater (greater than pivot)  
to left of pivot and all smaller elements to right  
of pivot. 
This Overloading Function is for planetArr. */
int partitionArr(Planet **planetArr, int low, int high)
{
    Planet *pivot = planetArr[high]; // pivot

    int i = low - 1; // Index of greater element

    for (int j = low; j <= high - 1; j++)
    { // use j to go through whole array to find element that is greater than the pivot
        // If current element is greater than the pivot
        if (planetArr[j]->value() > pivot->value())
        {

            i++; // increment index of greater element
            swap(planetArr[i], planetArr[j]);
        }
    }

    //place pivot right after a bunch of elements that are greater than the pivot
    swap(planetArr[i + 1], planetArr[high]);
    return i + 1;
}

/* Generates Random Pivot, swaps pivot with
end element and calls the partition function
This Overloading Function is for planetArr. */
int partitionArr_r(Planet **planetArr, int low, int high)
{
    // Generate a random number in between low and high
    srand(time(NULL));
    int random = low + rand() % (high - low);

    // Swap planetArr[random] with planetArr[high]
    swap(planetArr[random], planetArr[high]);

    return partitionArr(planetArr, low, high);
}

/* This function implements QuickSort and sort planet's value in descending order.
arr --> Array to be sorted,  
low --> Starting index,  
high --> Ending index.
This Overloading Function is for planetArr. */
void quickSortArr(Planet **planetArr, int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partitionArr_r(planetArr, low, high);

        // Separately sort elements before partition and after partition
        quickSortArr(planetArr, low, pi - 1);
        quickSortArr(planetArr, pi + 1, high);
    }
}

// Function to print planetArr
void printArray(Planet **planetArr)
{
    cout << "No.\tPlanet\tValue\n";
    for (int i = 0; i < NUM_OF_VERTICES; i++)
    {
        printf("%2d)\t", i + 1);
        cout << convertArrIndexToStr(i) << "\t";
        printf("%2d\n", planetArr[i]->value());
    }
    cout << endl;
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
    addEdgeToMatrix(matrix); // Add Edges in edgeArr to the matrix
    displayMatrix(matrix);

    cout << endl;

    map<string, list<pair<string, int>>> adjList;
    addEdgeToAdjList(adjList); // Add Edges in edgeArr to the adjList
    displayAdjList(adjList);

    cout << endl;

    int sizeOfEdgeArr = NUM_OF_EDGES;
    quickSortArr(edgeArr, 0, sizeOfEdgeArr - 1);
    cout << "List of edges in ascending order of distance: " << endl;
    printArray(edgeArr);

    int sizeOfPlanetArr = NUM_OF_VERTICES;
    quickSortArr(planetArr, 0, sizeOfPlanetArr - 1);
    cout << "List of planets in descending order of value: " << endl;
    printArray(planetArr);

    return 0;
}