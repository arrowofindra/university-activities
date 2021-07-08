// A C++ Program to find minimal spanning tree from a graph using Kruskal's Algorithm
#include <iostream>
#include "ReadFile.cpp" // program included to read graph data from a file
using namespace std;
Graph g;
// A structure to represent a weighted edge in graph
struct Edge {
    char src, dest; // source,destination edge
    int weight; // weight of the edge
};
// A structure to represent a subset
struct subset {
    int parent, rank;
};
// Sorting algorithm used for sorting edges according to their weights
void sortAlgo(Edge arr[], int n){
    int i, j, minIndex;
    for (i = 0; i < n-1; i++){
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j].weight < arr[minIndex].weight)
                minIndex = j;
        }
        swap(arr[minIndex], arr[i]);
    }
}
// A class to find the minimal spanning tree using Kruskal's Algorithm
class KruskalMST {
public:
    void readMatrix(int,Edge []);
    int findSet(subset subsets[], int);
    void unionSet(subset subsets[], int, int);
    void spawnMST();
    void printMST(int,Edge []);
};
// A function to arrange the graph data according to the Edge structure
void KruskalMST ::readMatrix(int m,Edge edge[]) {
    edge[m];
    int n = 0;
    for (int i = 0; i < g.v; i++) {
        for (int j = 0; j < g.v; j++) {
            if(g.arr[i][j] != 0){
                edge[n].src = g.vert[i];
                edge[n].dest = g.vert[j];
                edge[n].weight = g.arr[i][j];
                for (int k= 0; k < n; k++) {
                    // If same edge is repeated then discard it
                    if (edge[k].dest == edge[n].src and edge[k].src == edge[n].dest and edge[k].weight == edge[n].weight)
                        n--;
                }
                n++;
            }
        }
    }
}
// A function to find the set of an element
int KruskalMST ::findSet(subset *subsets, int i) {
    // find the root and make it parent of i
    if (subsets[i].parent != i)
        subsets[i].parent = findSet(subsets, subsets[i].parent);
    return subsets[i].parent;
}
// A function to perform union on two sets
void KruskalMST ::unionSet(subset *subsets, int x, int y) {
    int xRoot = findSet(subsets, x);
    int yRoot = findSet(subsets, y);
    // Attach the smaller rank tree under the root of high rank tree
    if (subsets[xRoot].rank < subsets[yRoot].rank)
        subsets[xRoot].parent = yRoot;
    else if (subsets[xRoot].rank > subsets[yRoot].rank)
        subsets[yRoot].parent = xRoot;
    // If ranks are same, then make one as root and increase its rank by one
    else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}
// A function to print the minimal spanning tree
void KruskalMST ::printMST(int n, Edge result[]) {
    cout << "The edges in the spawned MST are as follows :" << endl;
    int minCost = 0;
    for (int i = 0; i < n-1; i++){
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
        minCost = minCost + result[i].weight;
    }
    cout << "Minimum Cost Spanning Tree: " << minCost << endl;
}
// A function to find the minimal spanning tree using Kruskal's Algorithm
void KruskalMST ::spawnMST() {
    Edge edgeList[MAX_L];
    int vert = g.v,edge = g.e;
    Edge result[vert];
    readMatrix(edge,edgeList);
    int indexResult = 0,indexEdgeList = 0;
    subset* subsets = new subset[(vert * sizeof(subset))];
    for (int v = 0; v < vert; ++v){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    // Sort all the edges in increasing order of their weight
    sortAlgo(edgeList,edge);
    while (indexResult < vert - 1 && indexEdgeList < edge){
        // Pick the smallest edge and increment the index for next iteration
        Edge nextEdge = edgeList[indexEdgeList++];
        int x = findSet(subsets, int((nextEdge.src)-'A'));
        int y = findSet(subsets, int((nextEdge.dest)-'A'));
        // If including this edge doesn't cause cycle, include it in result
        // increment the index of result for next edge
        if (x != y) {
            result[indexResult++] = nextEdge;
            unionSet(subsets, x, y);
        }
        // Else discard it
    }
    printMST(vert,result);
    return;
}
// Driver function
int main(){
    g = readFile();
    KruskalMST mst;
    mst.spawnMST();
    return 0;
}
// Code Author :Indranil Das
// Roll No.: 16900119105
