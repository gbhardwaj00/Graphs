#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;       //two dimensional vector array

public:
    Graph(int numVertices) {
        //numVertices intializes rows, the second argument initializes a one-dimensional vector of type int equal to size numOfVertices, all initialized to 0
        // initializing to 0 means no edge in the start
        //vertices start at 0
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));  
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;    //undirected graph
    }

    void BFS(int s) {
        int numVertices = adjMatrix.size();     //used to set the initial values for each vertex

        vector<string> color(numVertices, "white");  //white = unvisted, grey = visited, black = explored
        vector<int> distance(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        color[s] = "grey";
        distance[s] = 0;
        parent[s] = -1;

        queue<int> Q;
        Q.push(s); //s is just an int,  not the whole vertex

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v = 0; v < numVertices; v++) {
                if ((adjMatrix[u][v] == 1) && (color[v] == "white")) {
                    Q.push(v);
                    color[v] = "grey";
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                }
            }
            color[u] = "black";
        }

        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ": distance = " << distance[i] << ", parent = " << parent[i] << endl;
        }
    }
};

int main()
{
    Graph G(5);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(1, 3);
    G.addEdge(2, 3);
    G.addEdge(3, 4);

    G.BFS(0);
    return 0;
}