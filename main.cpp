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

	vector(const vector& other)
	{
		size = other.size;
		dinamycArray = new int[size];

		for (unsigned int i = 0; i < size; i++)
		{
			dinamycArray[i] = other.dinamycArray[i];
		}
	}

	vector& operator=(const vector& other)
	{
		if (this != &other)
		{
			delete[] dinamycArray;

			size = other.size;
			dinamycArray = new int[size];

			for (unsigned int i = 0; i < size; i++)
			{
				dinamycArray[i] = other.dinamycArray[i];
			}
		}

		return *this;
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

	int& operator[](unsigned int index)
	{
		return dinamycArray[index];
	}

	int operator[](unsigned int index) const
	{
		return dinamycArray[index];
	}

	bool operator==(const vector& other) const
	{
		if (size != other.size)
		{
			return false;
		}

		for (unsigned int i = 0; i < size; i++)
		{
			if (dinamycArray[i] != other.dinamycArray[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator!=(const vector& other) const
	{
		return !(*this == other);
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

	vector copyNumbers = numbers;

	copyNumbers[0] = 999;
	std::cout << "Copy array:\n";
	std::cout << copyNumbers[0] << "\n";
	std::cout << copyNumbers[1] << "\n";
	std::cout << copyNumbers[2] << "\n";
	std::cout << copyNumbers[3] << "\n";
	std::cout << copyNumbers[4] << "\n";

	std::cout << "Original array:\n";
	std::cout << numbers[0] << "\n";

	vector assigned(2);
	assigned = numbers;
	std::cout << "Assigned array:\n";
	std::cout << assigned[0] << "\n";
	std::cout << assigned[1] << "\n";
	std::cout << assigned[2] << "\n";
	std::cout << assigned[3] << "\n";
	std::cout << assigned[4] << "\n";

	assigned = assigned;
	std::cout << "Self-assigned array:\n";
	std::cout << assigned[0] << "\n";
	std::cout << assigned[1] << "\n";
	std::cout << assigned[2] << "\n";
	std::cout << assigned[3] << "\n";
	std::cout << assigned[4] << "\n";

	const vector constNumbers = numbers;
	std::cout << "Const array:\n";
	std::cout << constNumbers[0] << "\n";

	if (numbers == assigned)
	{
		std::cout << "numbers and assigned are equal\n";
	}
	else
	{
		std::cout << "numbers and assigned are not equal\n";
	}

	if (numbers != copyNumbers)
	{
		std::cout << "numbers and copyNumbers are not equal\n";
	}
	else
	{
		std::cout << "numbers and copyNumbers are equal\n";
	}

	assigned[1] = 888;
	std::cout << "After changing assigned[1] to 888:\n";
	std::cout << "numbers[1]: " << numbers[1] << "\n";
	std::cout << "assigned[1]: " << assigned[1] << "\n";

	return 0;
}
