#include <iostream>
#include <bitset>

int main()
{
	uint32_t num = 0;
	std::cin >> num;

	char arr[32];
	int i = 0;
	while (num != 0)
	{
		arr[i++] = num & 1 ? '1' : '0';
		num >>= 1;
	}

	std::bitset<32> rbits(0);
	int k = 0;
	for (int j = i - 1; j >= 0; j--)
	{
		rbits[k++] = arr[j] == '1' ? true : false;
	}
	
	std::cout << rbits.to_ulong();

	return 0;
}
