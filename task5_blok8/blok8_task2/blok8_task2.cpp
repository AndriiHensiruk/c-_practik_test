// Task2

#include <iostream>
#include <conio.h>
#include <string>
#include <list>

class Vector
{
private:
	int v_x, v_y;
	std::list<Vector>myvector;

public:

	Vector* point;
	Vector(Vector* point)
	{
		this->point = point;
	}

	Vector(int x, int y)
	{
		v_x = x;
		v_y = y;

	}
	Vector()
	{

	}

	void delVektor(int index)
	{

		std::list<Vector>::iterator iterator = myvector.begin();
		std::advance(iterator, index);
		myvector.erase(iterator);


	}

	void addVektor(Vector& vector)
	{
		myvector.push_back(vector);

	}

	void printVector()
	{
		std::cout << "RECEIVED LIST " << "\n";
		for (auto vector : myvector)
			std::cout << vector.v_x << "  " << vector.v_y << "\t" << "\n";

	}

};

int main() {
	int cord_x, cord_y, n;

	std::cout << "Enter nambers of coordenats";
	std::cin >> n;

	Vector vector;

	for (int i = 0; i < n; i++)
	{
		std::cout << "Coordenata x : ";
		std::cin >> cord_x;
		std::cout << "Coordenata y : ";
		std::cin >> cord_y;
		Vector* point = new Vector(cord_x, cord_y);
		vector.Vector::addVektor(*point);
	}

	vector.printVector();
	int deln;
	std::cout << "Enter namber of coordenats if you nid to delet it";
	std::cin >> deln;
	vector.delVektor(deln);

	vector.printVector();



	return 0;
}