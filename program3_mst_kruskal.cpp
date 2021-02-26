#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility> 
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

const int NUM_OF_VERTICES = 10;     //A,B,C,D,E,F,G,H,I,J
const int NUM_OF_EDGES = 18;

vector<pair<int, pair<int, int>>> graph, mst;
int N, E;       //vertices, edges

//find the vertices
int root(int n, int *parent) {
    while(n != parent[n]) {
        n = parent[n];
    }
    return n;
}

//find mst
int kruskal() {
    int total = 0;    
    int parent[100];
    
    for(int i=0; i<N; i++) {
        parent[i] = i;
    }
    
    //use Introsort to minimize running time, O(n log n)
    sort(graph.begin(), graph.end()); 
   
    //find the weight of each edge of path chosen
    for(int i=0; i<graph.size(); i++) {
        
        int ru = root(graph[i].second.first, parent);       //origin planet
        int rv = root(graph[i].second.second, parent);      //destination planet
        
        if(ru != rv) {                                      //not the same planet
            mst.push_back(graph[i]);                        //put chosen path in mst
            parent[ru] = parent[rv];                            
            total += graph[i].first;                        //add the weight/distance
        }        
    }      
    return total;                                           //output mst weight
}

//for reading the input data (A2planets.txt)
struct Planet{
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

//initialize planet
Planet **planetArr = new Planet *[NUM_OF_VERTICES];

//add planets & distances between each path to the graph
int arrLength = 0;
void addEdge(string v1, string v2){
    int i = v1[0] - 'A';    //convert planet name to int
    int j = v2[0] - 'A';    //convert planet name to int
    int distance = planetArr[i]->distanceTo(planetArr[j]);      //calculate the distance
    if (arrLength < NUM_OF_EDGES)
    {
        graph.push_back( make_pair(distance, make_pair(i,j) ) );
    }
    else
    {
        cout << "Number of edges exceeds 18. Cannot add more edges anymore" << endl;
    }
}

int main()
{
    cout << "<<<Minimum Spanning Tree using Kruskal's Algorithm>>>\n\n";

    ifstream dataFile;
    dataFile.open("A2planets.txt");

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
        cout << "Unable to open file.";
        return 0;
    }

    N = NUM_OF_VERTICES;    //10
    E = NUM_OF_EDGES;       //18

    //to be added into graph
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

    int totalWeight = kruskal();          //find mst, output: mst weight
    
    cout << "The minimum spanning tree path: " << endl;
    for(int i=0; i<mst.size(); i++) {
        printf("%c %s %c %s %d\n", mst[i].second.first+'A', "-->", mst[i].second.second+'A', ", distance:", mst[i].first);
    }
    printf("Total weight of the MST: %i\n\n", totalWeight);
    
    mst.clear();        //clear the mst
    
    return 0;
}