// task5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
	std::cout << "Enter the size masiv";
	int siz;
	std::cin >> siz;
	srand(time(0));

	int** arr = new int* [siz];
	for (int i = 0; i < siz; i++)
		arr[i] = new int[siz];

	for (int row = 0; row < siz; row++)
		for (int colum = 0; colum < siz; colum++)
			arr[row][colum] = rand() % 10;

	for (int row = 0; row < siz; row++)
	{
		for (int colum = 0; colum < siz; colum++)
			std::cout << arr[row][colum] << "\t";
		std::cout << "\n";
	}

	//////////////////////////////////////////////////
	std::cout << "Massiv summ el. strok" << "\n";
	
	int *serd_sum=new int[siz];
	for (int row = 0; row < siz; row++)
	{
		int sum = 0;
		for (int colum = 0; colum < siz; colum++)
			sum = arr[row][colum]+sum;
		serd_sum[row] = sum/siz;	
	}

	for (int i = 0; i < siz; i++)
		std::cout << serd_sum[i] << "\n";

	/////////////////////////////////////////
	int* _s = new int[siz];
	int stk;
	for (int row = 0; row < siz; row++)
	{
		for (int colum = siz - 1; colum >= 1 + row; colum--)
			if (serd_sum[colum] < serd_sum[colum - 1])
			{
				stk = serd_sum[colum];
				serd_sum[colum] = serd_sum[colum - 1];
				serd_sum[colum - 1] = stk;
				//_s[row] = arr[colum];
			}
	}
	std::cout << "Otsortirovanniy massiv" << "\n";
	for (int i = 0; i < siz; i++)
		std::cout << serd_sum[i] << "\n";
		
	for (int i = 0; i < siz; i++)
	{
		std::cout << arr[i] << "\n";
	}

	//----------------------------------------------
	std::cout << "matrix" << "\n";
	int n;
	for (int row = 0; row < siz; row++)
	{
		n = _s[row];
		for (int colum = 0; colum < siz; colum++)
			std::cout << arr[n][colum] << "\t";
		std::cout << "\n";
	}
	for (int i = 0; i < siz; i++)
		delete[]arr[i];
	delete[]serd_sum;
	delete[]_s;
}