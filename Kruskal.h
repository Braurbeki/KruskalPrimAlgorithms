#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

class Kruskal
{
private:
	multimap<int, pair<int, int>>  Edges = { {4, {2,4}},
											 {4, {3,5}},
											 {5, {2,3}},
											 {6, {1,4}},
											 {7, {1,2}},
											 {8, {4,5}},
											 {9, {1,3}},
	};

	vector<pair<int, int>> tree;

	int* parent;

	bool TreeBuilt = false;

	int NumV;

	int FullWeight;

	int find_set(int v) {
		if (v == parent[v])
			return v;
		return find_set(parent[v]);
	}

	void union_set(int a, int b) {
		parent[b] = a;
	}

public:

	Kruskal()
	{
		FullWeight = 0;
		NumV = 5;
		parent = new int[NumV + 1];
		for (int i = 0; i <= NumV; i++) {
			parent[i] = i;
		}
	}

	void ChangeGraf()
	{
		Edges.clear();
		multimap<int, pair<int, int>> NewEdges;
		int NumEd, FirstVert, SecondVert, weight;
		cout << "Amount of edges: "; cin >> NumEd;
		cout << "Amount of vertexes: "; cin >> NumV;
		parent = new int[NumV + 1];
		for (int i = 0; i <= NumV; i++) {
			parent[i] = i;
		}
		for (int i = 0; i < NumEd; i++)
		{
			cout << "First vertex: "; cin >> FirstVert;
			cout << "Second vertex: "; cin >> SecondVert;
			cout << "Weight: "; cin >> weight;
			NewEdges.insert(pair<int, pair<int, int>>(weight, { FirstVert, SecondVert }));
		}

		for (auto const& edge : NewEdges)
		{
			Edges.insert(edge);
		}
		NewEdges.clear();
	}

	void BuildTree()
	{
		int i = 0, a, b;
		for (multimap<int, pair<int, int>>::iterator it = Edges.begin(); it != Edges.end(); it++)
		{
			a = find_set(it->second.first);
			b = find_set(it->second.second);
			if (a != b)
			{
				tree.push_back(it->second);
				FullWeight += it->first;
				union_set(a, b);
			}
		}

		TreeBuilt = true;
	}

	void ShowGraph()
	{
		cout << "Weight" << setw(7) << "Edges" << endl;
		for (multimap<int, pair<int, int>>::iterator it = Edges.begin(); it != Edges.end(); it++)
		{
			cout << it->first << setw(7) << it->second.first << "-" << it->second.second << endl;
		}
	}

	void ShowTree()
	{
		if (!TreeBuilt)
		{
			cout << "BuildTree function hasn't been called. Can't print the tree";
			return;
		}
		cout << "Kruskal summary time: " << clock() / 1000.0 << endl;
		cout << "Final tree: ";
		for (vector<pair<int, int>>::iterator it = tree.begin(); it != tree.end(); it++)
		{
			cout << '(' << it->first << '-' << it->second << ')' << " ";
		}
		cout << "\nFull weight: " << FullWeight << endl;
	}
};

