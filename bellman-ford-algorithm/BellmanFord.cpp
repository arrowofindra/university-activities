// A C++ program for finding single source shortest path using Bellman-Ford's algorithm.
#include <iostream>
#include "ReadFile.cpp" // program included to read graph data from a file
Graph g;
using namespace std;
// A structure to represent a weighted edge in graph
struct Edge {
    char src, dest, pre; //source, destination, predecessor edge
    int weight,dist; // weight, distance from source
};
// A class to find the shortest path using Bellman-Ford's algorithm
class singleSourceShortestPath{
public:
    void readMatrix(int,Edge []);
    void printPath(int,Edge []);
    void algoBellmanFord(int,Edge []);
    void updateEdge(char,char,int,int,Edge []);
};
// A function to arrange the graph data according to the Edge structure
void singleSourceShortestPath ::readMatrix(int m,Edge edge[]) {
    edge[m];
    int n = 0;
    for (int i = 0; i < g.v; i++) {
        for (int j = 0; j < g.v; j++) {
            if(g.arr[i][j] != 0){
                edge[n].src = g.vert[i];
                edge[n].dest = g.vert[j];
                edge[n].weight = g.arr[i][j];
                edge[n].dist = INT_MAX;
                n++;
            }
        }
    }
}
// A function used to print the solution
void singleSourceShortestPath ::printPath(int n, Edge result[]) {
    cout << "The required solution for the given graph is: " << endl;
    for (int i = 0; i < n; i++){
            cout << g.vert[i] << " -- " << result[i].dist << endl;
    }
}

// A function to find the shortest path from source to all other vertices using Bellman-Ford algorithm
void singleSourceShortestPath:: algoBellmanFord(int src,Edge edgeList[]){
    int vert = g.v, edge = g.e;
    // Initialise the distance from source to itself
    for (int i = 0; i < edge; i++){
        if (edgeList[i].src == src)
            edgeList[i].dist = 0;
    }
    // Relax all edges |vert| - 1 times
    // A simple shortest path from source to any other vertex can have at-most |vert| - 1 edges
    for (int i = 1; i <= vert - 1; i++) {
        for (int j = 0; j < edge; j++) {
            int u = findPos(edge,g.vert,edgeList[j].src);
            int v = findPos(edge,g.vert,edgeList[j].dest);
            int weight = edgeList[j].weight;
            if (edgeList[u].dist != INT_MAX && edgeList[u].dist + weight < edgeList[v].dist) {
                edgeList[v].dist = edgeList[u].dist + weight;
                edgeList[v].pre = edgeList[j].src;
            }
        }
    }

    // Check for negative-weight cycles
    // If we obtain a shorter path than the path obtained in previous step
    // Then a negative weight cycle is present in the graph
    for (int i = 0; i < edge; i++) {
        int u = findPos(edge,g.vert,edgeList[i].src);
        int v = findPos(edge,g.vert,edgeList[i].dest);
        int weight = edgeList[i].weight;
        if (edgeList[u].dist != INT_MAX && edgeList[u].dist + weight < edgeList[v].dist) {
            cout << "The given graph contains negative weight cycle" << endl;
            return;
        }
    }
    printPath(vert,edgeList);
    return;
}
// A function to update the weight of a specific edge if desired
void singleSourceShortestPath ::updateEdge(char src, char dest, int n,int w, Edge edge[]) {
    for (int i = 0; i < n; i++) {
        if(edge[i].src == src and edge[i].dest == dest)
            edge[i].weight = w;
    }
}
// Driver function
int main(){
    Edge edgeList[MAX_L];
    g = readFile();
    singleSourceShortestPath ssp;
    ssp.readMatrix(g.e, edgeList);
    ssp.algoBellmanFord('S',edgeList);
    cout << "After updating edge 'AE': " << endl;
    ssp.updateEdge('A','E',g.e,-5,edgeList);
    ssp.algoBellmanFord('S',edgeList);
    return 0;
}
// Code Author :Indranil Das
// Roll No.: 16900119105
