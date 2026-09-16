#include <iostream>

class vector
{
private:
	unsigned int size = 0;
	int* dinamycArray = nullptr;

public:
	vector(int sizeOffArray)
	{
		size = sizeOffArray;
		dinamycArray = new int[size];
	}

	~vector()
	{
		delete[] dinamycArray;
	}

	void resize(int newSize)
	{
		int* newArray = new int[newSize];

		for (unsigned int i = 0; i < size; i++)
		{
			newArray[i] = dinamycArray[i];
		}

		size = newSize;

		delete[] dinamycArray;
		dinamycArray = newArray;
	}

	void set(int index, int newValue)
	{
		dinamycArray[index] = newValue;
	}

	int get(int index) const
	{
		return dinamycArray[index];
	}
};

int main()
{
	vector numbers(3);

	numbers.set(0, 111);
	numbers.set(1, 222);
	numbers.set(2, 333);

	std::cout << "Array before resize:\n";
	std::cout << numbers.get(0) << "\n";
	std::cout << numbers.get(1) << "\n";
	std::cout << numbers.get(2) << "\n";

	numbers.resize(5);

	numbers.set(3, 444);
	numbers.set(4, 555);

	std::cout << "Array after resize:\n";
	std::cout << numbers.get(0) << "\n";
	std::cout << numbers.get(1) << "\n";
	std::cout << numbers.get(2) << "\n";
	std::cout << numbers.get(3) << "\n";
	std::cout << numbers.get(4) << "\n";

	return 0;
}
