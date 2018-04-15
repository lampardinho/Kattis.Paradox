#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <functional>

int FindPath(const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	auto idx = [nMapWidth](int x, int y) 
	{
		return x + y * nMapWidth;
	};

	auto h = [=](int u) -> int 
	{ // lower bound distance to target from u
		int x = u % nMapWidth, y = u / nMapWidth;
		return abs(x - nTargetX) + abs(y - nTargetY);
	};

	const int n = nMapWidth * nMapHeight;
	const int startPos = idx(nStartX, nStartY);
	const int targetPos = idx(nTargetX, nTargetY);

	int discovered = 0; 
	int exploredNodesCount = 0;
	std::vector<int> parents(n);
	std::vector<int> distance(n, INT_MAX);
	std::priority_queue<std::tuple<int, int, int>,
	                    std::vector<std::tuple<int, int, int>>,
	                    std::greater<std::tuple<int, int, int>>> openedNodes; // A* with tie breaking
	distance[startPos] = 0;
	openedNodes.push(std::make_tuple(0 + h(startPos), 0, startPos));
	while (!openedNodes.empty()) 
	{
		const int currentNode = std::get<2>(openedNodes.top()); 
		openedNodes.pop(); 
		exploredNodesCount++;

		if (currentNode == targetPos)
		{
			if (distance[targetPos] <= nOutBufferSize) 
			{
				int curr = targetPos;
				for (int i = distance[targetPos] - 1; i >= 0; i--) 
				{
					pOutBuffer[i] = curr;
					curr = parents[curr];
				}
				return distance[targetPos];
			}

			return distance[targetPos]; // buffer size too small
		}

		for (auto directions : { +1, -1, +nMapWidth, -nMapWidth }) 
		{
			int nearbyNode = currentNode + directions;
			if ((directions == 1 && (nearbyNode % nMapWidth == 0)) || (directions == -1 && (currentNode % nMapWidth == 0)))
			{
				continue;
			}

			const bool isTraversable = pMap[nearbyNode] == 1;
			if (nearbyNode >= 0 && nearbyNode < n && distance[nearbyNode] > distance[currentNode] + 1 && isTraversable) 
			{
				parents[nearbyNode] = currentNode;
				distance[nearbyNode] = distance[currentNode] + 1;				

				openedNodes.push(std::make_tuple(distance[nearbyNode] + h(nearbyNode), ++discovered, nearbyNode));
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
	
	std::cout << res << std::endl;

	getchar();

	return 0;
}