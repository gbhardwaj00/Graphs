// O(|V|^2) for DFS and Topological Sort as it is done with a matrix, otherwise O(|V|+|E|) with adjacency list

#include <iostream>
#include <vector>
#include <list>
using namespace std;

//directed graph
class Graph {
private:
	vector<vector<int>> adjMatrix;
	vector<string> color;						//white = unvisted, grey = visited, black = explored
	vector<int> discovered;						//when we first discover a vertex
	vector<int> checked;						//when all edges of a vertex are explored
	vector<int> parent;
	vector<int> topSorted;
	int step = 1;

public:
	Graph(int numVertices) {
		adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
		color.resize(numVertices, "white");
		discovered.resize(numVertices, -1);
		checked.resize(numVertices, -1);
		parent.resize(numVertices, -1);//
		topSorted.resize(numVertices, -1);
	}

	void createTranspose(Graph g) {
		for (int u = 0; u < g.adjMatrix.size(); u++) {
			for (int v = 0; v < g.adjMatrix.size(); v++) {
				if (g.adjMatrix[u][v] == 1) {
					this->adjMatrix[v][u] = 1;
				}
			}
		}
	}

	void addEdge(int u, int v) {
		adjMatrix[u][v] = 1;					//directed graph
	}

	//graph doesn't have to connected
	//use for each vertex loop if G is not connected
	void DFS() {//
		for (int i = 0; i < adjMatrix.size(); i++) {
			DFSRecusrive(i);
		}
	}

	void DFSTranspose(Graph G) {
		int treeNum = 1;
		cout << "Strongly Connected Components are: \n";
		for (int i = 0; i < adjMatrix.size(); i++) {
			if (color[G.topSorted[i]] == "white") {
				cout << "Tree: " << treeNum << " is: ";
				treeNum++;
				DFSRecusrive(G.topSorted[i]);
				cout << "\n";
			}
		}
	}

	void DFSRecusrive(int s) {
		if (color[s] == "white") {
			cout << s << " ";
			color[s] = "grey";
			discovered[s] = step;
			for (int v = 0; v < adjMatrix.size(); v++) {
				if ((adjMatrix[s][v] == 1) && (color[v] == "white")) {
					parent[v] = s;
					step++;
					DFSRecusrive(v);
				}
			}
			color[s] = "black";
			step++;
			checked[s] = step;
			topologicalSort(s);
		}
	}
	
	void printDandC() {
		cout << endl;
		for (int i = 0; i < adjMatrix.size(); i++) {
			cout << "Vertex " << i << " with Parent " << parent[i] << " : Discovered in Step: " << discovered[i] << " Checked in Step: " << checked[i] << endl;
		}
	}

	void topologicalSort(int s) {
		topSorted.insert(topSorted.begin(), s);
	}

	void printTopSorted() {
		cout << "Topologically sorted list is: ";
		for (int i = 0; i < adjMatrix.size(); i++) {
			cout << topSorted[i] << " ";
		}
		cout << endl;
	}

	void printGraph() {
		cout << "Graph is as follows:\n";
		for (int u = 0; u < adjMatrix.size(); u++) {
			for (int v = 0; v < adjMatrix.size(); v++) {
				cout << adjMatrix[u][v] << " ";
			}
			cout << endl;
		}
		cout << "\n";
	}

	void findSCCs(Graph G) {
		Graph GT(G.adjMatrix.size());
		GT.createTranspose(G);
		GT.printGraph();
		GT.DFSTranspose(G);
	}
};

int main() {
	Graph G(6);
	G.addEdge(0, 2);
	G.addEdge(2, 1);
	G.addEdge(1, 0);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(3,5);
	G.addEdge(4, 3);

	G.DFS();

	//printing information about each vectors attributes
	G.printDandC();

	//printing topological sorted list
	G.printTopSorted();

	//finding strongly connected components

	cout << "Original graph G is: \n";
	G.printGraph();
	
	G.findSCCs(G);

	return 0;
}