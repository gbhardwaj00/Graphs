// O(|V|^2) as it is done with a matrix, otherwise O(|V|+|E|) with adjacency list

#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
	vector<vector<int>> adjMatrix;
	vector<string> color;						//white = unvisted, grey = visited, black = explored
	vector<int> discovered;						//when we first discover a vertex
	vector<int> checked;						//when all edges of a vertex are explored
	vector<int> parent;

	int step = 1;

public:
	Graph(int numVertices) {
		adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
		color.resize(numVertices, "white");
		discovered.resize(numVertices, -1);
		checked.resize(numVertices, -1);
		parent.resize(numVertices, -1);
	}

	void addEdge(int u, int v) {
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1;					//undirected graph
	}

	//only works if G is connected
	//use for each vertex loop if G is not connected
	void DFS(int s) {
		if (color[s] == "white") {
			cout << s << " ";
			color[s] = "grey";
			discovered[s] = step;
			for (int v = 0; v < adjMatrix.size(); v++) {
				if ((adjMatrix[s][v] == 1) && (color[v] == "white")) {
					parent[v] = s;
					step++;
					DFS(v);
				}
			}
			color[s] = "black";
			step++;
			checked[s] = step;
		}
	}
	
	void printDandC() {
		cout << endl;
		for (int i = 0; i < adjMatrix.size(); i++) {
			cout << "Vertex " << i << " with Parent " << parent[i] << " : Discovered in Step: " << discovered[i] << " Checked in Step: " << checked[i] << endl;
		}
	}
};

int main() {
	Graph G(6);
	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(1, 3);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(3,5);

	G.DFS(5);

	G.printDandC();

	return 0;
}