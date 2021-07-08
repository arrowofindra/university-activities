// A C++ program to read graph data from a file
// The inputs are in the format of --
// no. of vertices
// vertex names
// adjacency matrix of the graph
#include<iostream>
#include<fstream>
#define MAX_L 20
using namespace std;
// A structure to represent the directed graph
struct Graph{
    int v,e; // no. of vertices and edges
    int arr[MAX_L][MAX_L]; // adjacency matrix
    char vert[MAX_L]; // vertex names
};
// A function to read data from the file
Graph readFile() {
    Graph graph;
    int count = 0;
    fstream infile;
    // Enter the correct file path where the file to read is located
    infile.open("GraphData1.txt", ios::in);
    if (!infile) {
        cout << endl << "Error to open the file" << endl;
        exit(1);
    }
    infile >> graph.v; // Input for no. of vertices
    int i, j;
    // Input for vertex names
    for(i = 0;i < graph.v; i++)
        infile >> graph.vert[i];
    // Input for adjacency matrix
    for(i = 0;i < graph.v; i++){
        for(j = 0; j < graph.v; j++){
            infile >> graph.arr[i][j];
            if (graph.arr[i][j] != 0)
                count ++;
        }
    }
    graph.e = count; // Input for no. of edges
    infile.close();
    return graph;
}
