#include <iostream>

int cache[30][30][15];

template<int x, int y, size_t steps>
struct cachedSteps : std::integral_constant< size_t, 
	cachedSteps<x-1, y-1, steps-1>::value + 
	cachedSteps<x, y-1, steps-1>::value + 
	cachedSteps<x+1, y, steps-1>::value + 
	cachedSteps<x+1, y+1, steps-1>::value + 
	cachedSteps<x, y+1, steps-1>::value + 
	cachedSteps<x-1, y, steps-1>::value >
{
	cachedSteps()
	{
		cache[x+15][y+15][steps] = 2;//this->value;
	}
};

template<> struct cachedSteps<0, 0, 0> : std::integral_constant<size_t, 1> {};
template<int x, int y> struct cachedSteps<x, y, 0> : std::integral_constant<size_t, 0> {};

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

//		cache[x + 15][y + 15] = res;
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
			for ( int k = 0; k < 30; ++k )
			{
//				cache[i][j][k] = cachedSteps<i, j, k>::value;
			}
		}
	}
}

template<> struct cachedSteps<0, 0, 14>{};


int FIB[21];

template <int x, int y, size_t steps> struct Fib { static const int VAL; };
template <int x, int y, size_t steps> const int Fib<x, y, steps>::VAL =
	cache[x][y][steps] =
	Fib<x-1, y-1, steps-1>::VAL/* + 
	Fib<x, y-1, steps-1>::VAL + 
	Fib<x+1, y, steps-1>::VAL + 
	Fib<x+1, y+1, steps-1>::VAL + 
	Fib<x, y+1, steps-1>::VAL + 
	Fib<x-1, y, steps-1>::VAL*/;

template <> struct Fib<0, 0, 0> { static const int VAL; };
const int Fib<0, 0, 0>::VAL = cache[0][0][0] = 1;

template <int x, int y> struct Fib<x, y, 0> { static const int VAL; };
template <int x, int y> const int Fib<x, y, 0>::VAL = cache[x][y][0]=0;

template struct Fib<0, 0, 10>; //explicit template instantiation

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
//		std::cout << cachedSteps<0, 0, tests[i]>::value << std::endl;
//		std::cout << cache[0][0][tests[i]] << std::endl;
		std::cout << cache[0][0][tests[i]] << std::endl;
	}
	
	getchar();
	getchar();

	return 0;
}
