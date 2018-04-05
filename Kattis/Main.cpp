#include <iostream>

int cache[30][30];
// https://stackoverflow.com/questions/22645551/calculate-the-fibonacci-number-recursive-approach-in-compile-time-constexpr
template<size_t x, size_t y, size_t steps>
struct cachedSteps : std::integral_constant< size_t, cachedSteps<x-1, y-1, steps-1>{} + cachedSteps<x, y-1, steps-1>{} + cachedSteps<x+1, y, steps-1>{} + cachedSteps<x+1, y+1, steps-1>{} + cachedSteps<x, y+1, steps-1>{} + cachedSteps<x-1, y, steps-1>{} >{};

template<> struct cachedSteps<0, 0, 0> : std::integral_constant<size_t, 1> {};
template<> struct cachedSteps<0, 1, 0> : std::integral_constant<size_t, 0> {};
template<> struct cachedSteps<1, 0, 0> : std::integral_constant<size_t, 0> {};
template<> struct cachedSteps<1, 1, 0> : std::integral_constant<size_t, 0> {};

int w(int x, int y, int s)
{
	int res = 0;
	if (s == 0)
	{
		return (x == 0 && y == 0) ? 1 : 0;
	}

	//if (cache[x + 15][y + 15] == -1)
	//{
		res = w(x-1, y-1, s-1) +
			w(x, y-1, s-1) +
			w(x+1, y, s-1) +
			w(x+1, y+1, s-1) +
			w(x, y+1, s-1) +
			w(x-1, y, s-1);

		cache[x + 15][y + 15] = res;
//	}
//	else
//	{
//		res = cache[x + 15][y + 15];
//	}
//	
	return res;
}

void clearCache()
{
	for ( int i = 0; i < 30; ++i )
	{
		for ( int j = 0; j < 30; ++j )
		{
			cache[i][j] = -1;
		}
	}
}

int main()
{
	int testsCount = 0;
	std::cin >> testsCount;

	int tests[1000];
	for ( int i = 0; i < testsCount; ++i )
	{
		std::cin >> tests[i];
	}

	for ( int i = 0; i < testsCount; ++i )
	{
		clearCache();
		std::cout << ( cachedSteps<0, 0, tests[i]>{} ) << std::endl;
	}
	
	getchar();
	getchar();

	return 0;
}
