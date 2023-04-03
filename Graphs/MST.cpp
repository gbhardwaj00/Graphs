#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class DisjointSet {
private:
	//every disjoint set will have a single parent, initially number of disjoint sets is equal to vertices
	vector<int> parent, rank;
public:
	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	//finds parent of x
	int find(int x) {
		while (parent[x] != x) {
			x = parent[x];
		}
		return x;
	}

	void unionSet(int u, int v) {
		int x = find(u);
		int y = find(v);
		if (x == y) {
			return;
		}
		if (rank[x] < rank[y]) {
			parent[x] = y;
		}
		else if(rank[y] < rank[x]) {
			parent[y] = x;
		}
		else {
			parent[y] = x;
			rank[x]++;
		}
	}
};

class Edge {
public:
	int u, v, weight;
	Edge(int u, int v, int weight) {
		this->u = u;
		this->v = v;
		this->weight = weight;
	}
};


bool cmp(Edge e1, Edge e2) {
	return e1.weight < e2.weight;
}

vector<Edge> kruskal(vector<Edge> edges, int n) {
	sort(edges.begin(), edges.end(), cmp);
	DisjointSet set(n);
	vector<Edge> mst;
	for (int i = 0; i < edges.size(); i++) {
		int u = edges[i].u;
		int v = edges[i].v;
		if (set.find(u) != set.find(v)) {
			set.unionSet(u, v);
			mst.push_back(edges[i]);
		}
	}
	return mst;
}

class Vertex {
public:
	int id;
	int key;
	int parent;
	Vertex() {
		this->id = -1;
		this->key = -1;
		this->parent = -1;
	}
	Vertex(int i, int k, int p) {
		this->id = i;
		this->key = k;
		this->parent = p;
	}
};

vector<bool> visited;

struct compareKey {
	bool operator()(Vertex const& v1, Vertex const& v2) {
		return v1.key > v2.key;
	}
};

void prims(vector<Edge> edges, int n, int r) {
	visited.resize(n, false);
	vector<Vertex> vertices(n);
	for (int i = 0; i < n; i++) {
		vertices[i].id = i;
		vertices[i].key = INT_MAX;
		vertices[i].parent = -1;
	}
	vertices[r].key = 0;
	priority_queue<Vertex, vector<Vertex>, compareKey> Q;
	for (int i = 0; i < n; i++) {
		Q.push(vertices[i]);
	}
	vector<vector<pair<int, int>>> adjList(n);
	for (int i = 0; i < edges.size(); i++) {
		adjList[edges[i].u].push_back({ edges[i].v, edges[i].weight });
		adjList[edges[i].v].push_back({ edges[i].u, edges[i].weight });
	}
	while (!Q.empty()) {
		int u = Q.top().id;
		Q.pop();

		if (visited[u]) continue;
		visited[u] = true;

		for (int i = 0; i < adjList[u].size(); i++) {
			int v = adjList[u][i].first;
			int w = adjList[u][i].second;
			if (w < vertices[v].key && visited[v] == false) {
				vertices[v].key = w;
				vertices[v].parent = u;
				Q.push(vertices[v]);
			}
		}
	}

	printf("The edges in Prims MST are:\n");
	for (int i = 1; i < vertices.size(); ++i) {
		printf("%d - %d\n", vertices[i].parent, i);
	}
}

int main() {
	int n = 8;
	vector<Edge> edges = {Edge(0, 1, 25), Edge(0, 5, 5), Edge(1, 2, 12), Edge(1, 6, 10), Edge(2, 3, 8), Edge(3, 4, 16), Edge(3, 6, 14), Edge(4, 5, 20), Edge(4, 6, 18), Edge(4, 7, 12)};
	vector<Edge> mst = kruskal(edges, n);
	for (int i = 0; i < mst.size(); i++) {
		cout << mst[i].u << " - " << mst[i].v << " : " << mst[i].weight << "\n";
	}

	int s = 0; // source node
	prims(edges, n, s);

	return 0;
}