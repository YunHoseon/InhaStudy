// 0814_Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 

#define I 90000
#define NodeNum 8

int EdgeCost[NodeNum][NodeNum] =
{
	{ 0, 2, I, I, I, 3, I, I },
	{ 2, 0, 4, 1, I, I, I, I },
	{ I, 4, 0, I, 3, I, I, I },
	{ I, 1, I, 0, 3, I, 2, I },
	{ I, I, 3, 3, 0, I, I, 4 },
	{ 3, I, I, I, I, 0, 6, I },
	{ I, I, I, 2, I, 6, 0, 4 },
	{ I, I, I, I, 4, I, 4, 0 }
};

vector<int> selectList;
vector<int> roadList;
vector<int> tmpList;

int main()
{
	int startNode, endNode, finalCost;
	
	int min = 0;
	int sum = 0;

	while (1)
	{
		cout << "시작 노드 : ";
		cin >> startNode;
		cout << "끝 노드 : ";
		cin >> endNode;

		roadList.push_back(startNode);

		for (int i = startNode; i < endNode - 1; i++)
		{
			if (EdgeCost[startNode - 1][i] != I)
				selectList.push_back(i);
		}


	}
    return 0;
}