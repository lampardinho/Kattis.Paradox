#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <functional>

int idx(int nMapWidth, int x, int y)
{
	return x + y * nMapWidth;
}

// lower bound distance to target from u
int costToTarget(int nMapWidth, int nTargetX, int nTargetY, int u)
{
	int x = u % nMapWidth, y = u / nMapWidth;
	return abs(x - nTargetX) + abs(y - nTargetY);
}

struct Node
{
	int x;
	int y;
};

struct NodePathfindingData
{
	int cost;
	Node parentNode;
	Node node;
};

bool operator <(const NodePathfindingData& left, const NodePathfindingData& right)
{
	return left.cost > right.cost;
}

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	const int n = nMapWidth * nMapHeight;
	const Node startPos = {nStartX, nStartY};
	const Node targetPos = {nTargetX, nTargetY};

	int discovered = 0; 
	int exploredNodesCount = 0;
	std::vector<int> parents(n);
	std::vector<int> costs(n, INT_MAX);
	std::priority_queue<NodePathfindingData> openedNodes; // A* with tie breaking
	costs[startPos] = 0;
	openedNodes.push({0 + costToTarget(nMapWidth, nTargetX, nTargetY, startPos), 0, startPos});
	while (!openedNodes.empty()) 
	{
		const int currentNode = openedNodes.top().node; 
		openedNodes.pop(); 
		exploredNodesCount++;

		if (currentNode == targetPos)
		{
			if (costs[targetPos] <= nOutBufferSize) 
			{
				NodePathfindingData curr = targetPos;
				for (int i = costs[targetPos] - 1; i >= 0; i--) 
				{
					pOutBuffer[i] = curr;
					curr = curr;
				}
				return costs[targetPos];
			}

			return costs[targetPos]; // buffer size too small
		}

		for (auto directions : { +1, -1, +nMapWidth, -nMapWidth }) 
		{
			int nearbyNode = currentNode + directions;
			if ((directions == 1 && (nearbyNode % nMapWidth == 0)) || (directions == -1 && (currentNode % nMapWidth == 0)))
			{
				continue;
			}

			const bool isTraversable = pMap[nearbyNode] == 1;
			if (nearbyNode >= 0 && nearbyNode < n && costs[nearbyNode] > costs[currentNode] + 1 && isTraversable) 
			{
				parents[nearbyNode] = currentNode;
				costs[nearbyNode] = costs[currentNode] + 1;				

				openedNodes.push({costs[nearbyNode] + costToTarget(nMapWidth, nTargetX, nTargetY, nearbyNode), ++discovered, nearbyNode});
			}
		}
	}

	return -1;		
}

int main()
{
	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[12];
	int res = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
	//FindPath must return 3, and the first three positions of pOutBuffer must be populated with {1, 5, 9}

//	unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
//	int pOutBuffer[7];
//	FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
	//For this input FindPath must return ?1
	
	std::cout << res << std::endl;

	for (int i = 0; i < res; ++i)
	{
		std::cout << pOutBuffer[i] << " ";
	}

	getchar();

	return 0;
}