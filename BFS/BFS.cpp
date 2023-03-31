// O(|V|^2) as it is done with a matrix, otherwise O(|V|+|E|) with adjacency list

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;       //two dimensional vector array
    

public:
    vector<string> color;  //white = unvisted, grey = visited, black = explored
    vector<int> distance;
    vector<int> parent;

    Graph(int numVertices) {
        //numVertices intializes rows, the second argument initializes a one-dimensional vector of type int equal to size numOfVertices, all initialized to 0
        // initializing to 0 means no edge in the start
        //vertices start at 0
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
        color.resize(numVertices, "white");
        distance.resize(numVertices, INT_MAX);
        parent.resize(numVertices, -1);
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;    //undirected graph
    }

    void BFS(int s) {
        int numVertices = adjMatrix.size();     //used to set the initial values for each vertex
        
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

    //Prints the Path to a vertex v from s, the starting vertex
    void printPath(int s, int v) {
        if (parent[v] == -1) {
            cout << "No path found from " << s << " to " << v << endl;
        }
        else {
            cout << "Path from " << s << " to " << v << " is: ";
            printPath2(s, v);
            cout << endl;
        }
    }

    void printPath2(int s, int v) {
        if (s == v) {
            cout << s << " ";
        }
        else {
            printPath2(s, parent[v]);
            cout << v << " ";
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

    G.printPath(0, 4);
    return 0;
}