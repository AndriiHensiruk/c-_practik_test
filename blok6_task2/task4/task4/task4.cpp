// task4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

int main()
{
	std::cout << "Enter the size masiv";
	int siz;
	std::cin >> siz;

	int* arr = new int [siz];
	
	for (int row = 0; row < siz; row++)
			arr[row] = rand() % 100;

	for (int row = 0; row < siz; row++)
	{
			std::cout << arr[row] << "\t";
		std::cout << "\n";
	}

	int stk_row;
	for (int row = 1; row < siz; row++)
	{
		for (int colum = 0; colum < siz-row; colum++)
			if (arr[colum] > arr[colum + 1])
			{
				stk_row = arr[colum];
				arr[colum] = arr[colum + 1];
				arr[colum + 1] = stk_row;
			}
			
	}

	std::cout << "Sort masiv" << "\n";
	for (int row = 0; row < siz; row++)
	{
			std::cout << arr[row] << "\t";
		std::cout << "\n";
	}
		
		delete[]arr;
		return 0;
}