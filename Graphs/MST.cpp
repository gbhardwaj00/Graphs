#include <iostream>
#include <vector>
#include <algorithm>
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



int main() {
	int n = 8;
	vector<Edge> edges = {Edge(0, 1, 25), Edge(0, 5, 5), Edge(1, 2, 12), Edge(1, 6, 10), Edge(2, 3, 8), Edge(3, 4, 16), Edge(3, 6, 14), Edge(4, 5, 20), Edge(4, 6, 18)};
	vector<Edge> mst = kruskal(edges, n);
	for (int i = 0; i < mst.size(); i++) {
		cout << mst[i].u << " - " << mst[i].v << " : " << mst[i].weight << "\n";
	}
	return 0;
	return 0;
}