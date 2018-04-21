#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

struct NodePathLenght
{
	int node;
	int pathLenght;
};

bool operator <(const NodePathLenght& left, const NodePathLenght& right)
{
	return left.pathLenght > right.pathLenght;
}

int distanceToTarget(int nMapWidth, int nTargetX, int nTargetY, int node)
{
	const int x = node % nMapWidth;
	const int y = node / nMapWidth;
	return abs(x - nTargetX) + abs(y - nTargetY);
}

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	const int startNode = nStartX + nMapWidth * nStartY;
	const int targetNode = nTargetX + nMapWidth * nTargetY;

	const int nodesCount = nMapWidth * nMapHeight;
	std::vector<int> parents(nodesCount);
	std::vector<int> distances(nodesCount, INT_MAX);
	
	std::priority_queue<NodePathLenght> openedNodes;
	std::set<int> closedNodes;

	distances[startNode] = 0;
	openedNodes.push( {startNode, distanceToTarget(nMapWidth, nTargetX, nTargetY, startNode)} );
	while (!openedNodes.empty()) 
	{
		const int currentNode = openedNodes.top().node; 
		openedNodes.pop(); 

		closedNodes.emplace(currentNode);
		
		if (currentNode == targetNode)
		{
			const int distanceToTarget = distances[targetNode];

			if (distanceToTarget <= nOutBufferSize)
			{
				int pathNode = targetNode;
				for (int i = distanceToTarget - 1; i >= 0; i--) 
				{
					pOutBuffer[i] = pathNode;
					pathNode = parents[pathNode];
				}
			}

			return distanceToTarget;
		}

		const int right = 1;
		const int left = -1;
		const int up = -nMapWidth;
		const int down = nMapWidth;
		for (int direction : { right, left, down, up }) 
		{
			const int neighbourNode = currentNode + direction;

			if (neighbourNode < 0 || neighbourNode >= nodesCount)
			{
				continue;
			}

			if ((direction == right && neighbourNode % nMapWidth == 0) || 
				(direction == left && currentNode % nMapWidth == 0))
			{
				continue;
			}
			
			if (closedNodes.find(neighbourNode) != closedNodes.cend())
			{
				continue;
			}

			const bool isTraversable = pMap[neighbourNode] == 1;
			const int newDistanceToNode = distances[currentNode] + 1;
			if (isTraversable && distances[neighbourNode] > newDistanceToNode) 
			{
				parents[neighbourNode] = currentNode;
				distances[neighbourNode] = newDistanceToNode;

				const int pathLenght = newDistanceToNode + distanceToTarget(nMapWidth, nTargetX, nTargetY, neighbourNode);
				openedNodes.push( {neighbourNode, pathLenght} );
			}
		}
	}

	return -1;		
}

int main()
{
	unsigned char pMap1[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer1[12];
	const int res1 = FindPath(0, 0, 1, 2, pMap1, 4, 3, pOutBuffer1, 12);
	//FindPath must return 3, {1, 5, 9}

	std::cout << res1 << ": ";
	if (res1 > 0)
	{
		for (int i = 0; i < res1; ++i)
		{
			std::cout << pOutBuffer1[i] << " ";
		}
	}
	std::cout << "\n";

	unsigned char pMap2[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
	int pOutBuffer2[7];
	const int res2 = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);
	//For this input FindPath must return -1
	
	std::cout << res2 << ": ";
	if (res2 > 0)
	{
		for (int i = 0; i < res2; ++i)
		{
			std::cout << pOutBuffer2[i] << " ";
		}
	}
	std::cout << "\n";

	unsigned char pMap3[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer3[12];
	const int res3 = FindPath(0, 0, 1, 2, pMap3, 4, 3, pOutBuffer3, 2);
	//FindPath must return 3, {1, 5, 9}

	std::cout << res3 << ": ";
	if (res3 > 0)
	{
		for (int i = 0; i < res3; ++i)
		{
			std::cout << pOutBuffer3[i] << " ";
		}
	}
	std::cout << "\n";

	getchar();

	return 0;
}