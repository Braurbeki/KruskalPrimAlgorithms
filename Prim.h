#include <iostream>
#include<vector>
#include<map>

using namespace std;

class Prim
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

	bool TreeBuilt = false;

	int FullWeight, CurrentEdge, NumVert = 5;

	bool* passed;

	int FindEdge(int frst, int sec)
	{
		multimap<int, pair<int, int>>::iterator it = Edges.begin();

		while (it != Edges.end())
		{
			if (it->second.first == frst && it->second.second == sec)
			{
				for (vector<pair<int, int>>::iterator itV = tree.begin(); itV != tree.end(); itV++)
				{
					if (itV->first == frst && itV->second == sec) goto ret;
					else if (itV->first == sec && itV->second == frst) goto ret;
				}
				return it->first;
			}

			if (it->second.first == sec && it->second.second == frst)
			{
				for (vector<pair<int, int>>::iterator itV = tree.begin(); itV != tree.end(); itV++)
				{
					if (itV->first == sec && itV->second == frst) goto ret;
					else if (itV->first == frst && itV->second == sec) goto ret;
				}
				return it->first;
			}

			it++;
		}
	ret: return 0;
	}

public:

	Prim()
	{
		FullWeight = 0;
		tree.clear();
	}

	void ChangeGraf()
	{
		Edges.clear();
		multimap<int, pair<int, int>> NewEdges;
		int NumEd, FirstVert, SecondVert, weight;
		cout << "Amount of edges: "; cin >> NumEd;
		cout << "Amount of vertexes: "; cin >> NumVert;
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
	}

	void BuildTree()
	{
		TreeBuilt = true;

		CurrentEdge = 0;
		int NumEdges = Edges.size();

		passed = new bool[NumEdges];
		multimap<int, pair<int, int>>::iterator it = Edges.begin();
		for (int i = 0; i <= NumEdges; i++)
		{
			passed[i] = false;
		} passed[it->second.first] = true;


		int firstParam = 0, secondParam = 0;
		while (CurrentEdge < NumEdges - 1)
		{
			int min = 0xfffffff; // ~infinity
			for (int i = 0; i < NumEdges; i++)
			{
				if (passed[i])
				{
					for (int j = 0; j < NumEdges; j++)
					{
						int tmp = FindEdge(i, j);
						if (!passed[j] && tmp != 0)
						{
							if (min > tmp)
							{
								min = tmp;
								secondParam = j;
								firstParam = i;
							}
						}
					}
				}

			}
			if (FindEdge(firstParam, secondParam) != 0)
			{
				FullWeight += FindEdge(firstParam, secondParam);
				tree.push_back(pair<int, int>(firstParam, secondParam));
			}
			passed[secondParam] = true;
			CurrentEdge++;
		}

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
		cout << "Prim summary time: " << clock() / 1000.0 << endl;
		cout << "Final tree: ";
		for (vector<pair<int, int>>::iterator it = tree.begin(); it != tree.end(); it++)
		{
			cout << '(' << it->first << '-' << it->second << ')' << " ";
		}
		cout << "\nFull weight: " << FullWeight << endl;
	}
};

