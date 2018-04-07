#include <iostream>

int tests[100][100];
int colSum[100];
int rowSum[100];

int best(int w, int h)
{
	uint32_t bestRow = ~0;
	for (int r = 0; r < w; r++) 
	{
		uint32_t sum = 0;

		for (int c = 0; c < h; c++)
		{
			sum += r > c ? (r - c)*rowSum[c] : (c - r)*rowSum[c];
		}

		if (sum < bestRow)
		{
			bestRow = sum;
		}
	}

	uint32_t bestCol = ~0;
	for (int c = 0; c < h; c++) 
	{
		uint32_t sum = 0;

		for (int r = 0; r < w; r++)
		{
			sum += c > r ? (c - r)*colSum[r] : (r - c)*colSum[r];
		}

		if (sum < bestCol)
		{
			bestCol = sum;
		}
	}

	return bestRow + bestCol;
}

int main()
{
	int testsCount = 0;
	std::cin >> testsCount;
	
	for (int i = 0; i < testsCount; ++i)
	{
		int w = 0;
		int h = 0;
		std::cin >> w >> h;
		
		for (int x = 0; x < w; ++x)
		{
			for (int y = 0; y < h; ++y)
			{
				std::cin >> tests[x][y];

				colSum[y] += tests[x][y];
				rowSum[x] += tests[x][y];
			}
		}

		std::cout << best(w, h) << " blocks" << std::endl;
	}

	getchar();
	getchar();

	return 0;
}