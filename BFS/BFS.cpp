// o(|v|^2) as it is done with a matrix, otherwise o(|v|+|e|) with adjacency list

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class graph {
private:
    vector<vector<int>> adjmatrix;       //two dimensional vector array
    

public:
    vector<string> color;  //white = unvisted, grey = visited, black = explored
    vector<int> distance;
    vector<int> parent;

    graph(int numvertices) {
        //numvertices intializes rows, the second argument initializes a one-dimensional vector of type int equal to size numofvertices, all initialized to 0
        // initializing to 0 means no edge in the start
        //vertices start at 0
        adjmatrix.resize(numvertices, vector<int>(numvertices, 0));
        color.resize(numvertices, "white");
        distance.resize(numvertices, INT_MAX);
        parent.resize(numvertices, -1);
    }

    void addedge(int u, int v) {
        adjmatrix[u][v] = 1;
        adjmatrix[v][u] = 1;    //undirected graph
    }

    void bfs(int s) {
        int numvertices = adjmatrix.size();     //used to set the initial values for each vertex
        
        color[s] = "grey";
        distance[s] = 0;
        parent[s] = -1;

        queue<int> q;
        q.push(s); //s is just an int,  not the whole vertex

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < numvertices; v++) {
                if ((adjmatrix[u][v] == 1) && (color[v] == "white")) {
                    q.push(v);
                    color[v] = "grey";
                    distance[v] = distance[u] + 1;
                    parent[v] = u;
                }
            }
            color[u] = "black";
        }

        for (int i = 0; i < numvertices; i++) {
            cout << "vertex " << i << ": distance = " << distance[i] << ", parent = " << parent[i] << endl;
        }
    }

    //prints the path to a vertex v from s, the starting vertex
    void printpath(int s, int v) {
        if (parent[v] == -1) {
            cout << "no path found from " << s << " to " << v << endl;
        }
        else {
            cout << "The path from " << s << " to " << v << " is: ";
            printpath2(s, v);
            cout << endl;
        }
    }

    void printpath2(int s, int v) {
        if (s == v) {
            cout << s << " ";
        }
        else {
            printpath2(s, parent[v]);
            cout << v << " ";
        }
    }
};

int main()
{
    graph g(5);
    g.addedge(0, 1);
    g.addedge(0, 2);
    g.addedge(1, 3);
    g.addedge(2, 3);
    g.addedge(3, 4);

    g.bfs(0);

    g.printpath(0, 4);
    return 0;
}