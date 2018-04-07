#include <iostream>

int cache[30][30][15];

int w(int x, int y, int s)
{
	int res = 0;
	if (s == 0)
	{
		return (x == 0 && y == 0) ? 1 : 0;
	}

	if (cache[x + 15][y + 15][s] == 0)
	{
		res = w(x - 1, y - 1, s - 1) +
			w(x, y - 1, s - 1) +
			w(x + 1, y, s - 1) +
			w(x + 1, y + 1, s - 1) +
			w(x, y + 1, s - 1) +
			w(x - 1, y, s - 1);

		cache[x + 15][y + 15][s] = res;
	}
	else
	{
		res = cache[x + 15][y + 15][s];
	}
		
	return res;
}

int main()
{
	int testsCount = 0;
	std::cin >> testsCount;

	for (int i = 0; i < testsCount; ++i)
	{
		int steps = 0;
		std::cin >> steps;
		std::cout << w(0, 0, steps) << std::endl;
	}

	getchar();
	getchar();

	return 0;
}
