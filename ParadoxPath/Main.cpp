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
	const int startPos = idx(nStartX, nStartY), targetPos = idx(nTargetX, nTargetY);

	int discovered = 0; 
	int ExploredNodes = 0;
	std::vector<int> p(n), d(n, INT_MAX);
	std::priority_queue<std::tuple<int, int, int>,
	                    std::vector<std::tuple<int, int, int>>,
	                    std::greater<std::tuple<int, int, int>>> pq; // A* with tie breaking
	d[startPos] = 0;
	pq.push(std::make_tuple(0 + h(startPos), 0, startPos));
	while (!pq.empty()) 
	{
		int u = std::get<2>(pq.top()); pq.pop(); ExploredNodes++;
		for (auto e : { +1, -1, +nMapWidth, -nMapWidth }) 
		{
			int v = u + e;
			if ((e == 1 && (v % nMapWidth == 0)) || (e == -1 && (u % nMapWidth == 0)))
			{
				continue;
			}

			if (0 <= v && v < n && d[v] > d[u] + 1 && pMap[v]) 
			{
				p[v] = u;
				d[v] = d[u] + 1;
				if (v == targetPos)
				{
					goto end;
				}

				pq.push(std::make_tuple(d[v] + h(v), ++discovered, v));
			}
		}
	}
end:

	if (d[targetPos] == INT_MAX) 
	{
		return -1;
	}

	if (d[targetPos] <= nOutBufferSize) 
	{
		int curr = targetPos;
		for (int i = d[targetPos] - 1; i >= 0; i--) 
		{
			pOutBuffer[i] = curr;
			curr = p[curr];
		}
		return d[targetPos];
	}

	return d[targetPos]; // buffer size too small
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