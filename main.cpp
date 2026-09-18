#include <iostream>
#include <stdexcept>

template <typename T>
class Vector
{
private:
	unsigned int size = 0;
	T* dinamycArray = nullptr;

	void checkIndex(unsigned int index) const
	{
		if (index >= size)
		{
			throw std::out_of_range("Index out of range");
		}
	}

public:
	Vector() = default;
	Vector(int sizeOffArray)
	{
		size = sizeOffArray;
		dinamycArray = new T[size];
	}

	Vector(const Vector& other)
	{
		size = other.size;
		dinamycArray = new T[size];

		for (unsigned int i = 0; i < size; i++)
		{
			dinamycArray[i] = other.dinamycArray[i];
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			delete[] dinamycArray;

			size = other.size;
			dinamycArray = new T[size];

			for (unsigned int i = 0; i < size; i++)
			{
				dinamycArray[i] = other.dinamycArray[i];
			}
		}

		return *this;
	}

	~Vector()
	{
		delete[] dinamycArray;
	}

	void resize(int newSize)
	{
		T* newArray = new T[newSize];

		for (unsigned int i = 0; i < size; i++)
		{
			newArray[i] = dinamycArray[i];
		}

		size = newSize;

		delete[] dinamycArray;
		dinamycArray = newArray;
	}

	T& operator[](unsigned int index)
	{
		checkIndex(index);
		return dinamycArray[index];
	}

	const T& operator[](unsigned int index) const
	{
		checkIndex(index);
		return dinamycArray[index];
	}

	bool operator==(const Vector& other) const
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

	bool operator!=(const Vector& other) const
	{
		return !(*this == other);
	}

	explicit operator bool() const
	{
		return size > 0;
	}

	void set(int index, const T& newValue)
	{
		checkIndex(index);
		dinamycArray[index] = newValue;
	}

	const T& get(int index) const
	{
		checkIndex(index);
		return dinamycArray[index];
	}
};

int main()
{
	Vector<int> numbers(3);

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

	Vector<int> copyNumbers = numbers;

	copyNumbers[0] = 999;
	std::cout << "Copy array:\n";
	std::cout << copyNumbers[0] << "\n";
	std::cout << copyNumbers[1] << "\n";
	std::cout << copyNumbers[2] << "\n";
	std::cout << copyNumbers[3] << "\n";
	std::cout << copyNumbers[4] << "\n";

	std::cout << "Original array:\n";
	std::cout << numbers[0] << "\n";

	Vector<int> assigned(2);
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

	const Vector<int> constNumbers = numbers;
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

	try
	{
		numbers.get(10);
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Caught exception: " << e.what() << "\n";
	}

	Vector<int> empty(0);
	if (empty)
	{
		std::cout << "Empty vector is not empty\n";
	}
	else
	{
		std::cout << "Empty vector is empty\n";
	}

	if (numbers)
	{
		std::cout << "Numbers vector is not empty\n";
	}
	else
	{
		std::cout << "Numbers vector is empty\n";
	}

	if (numbers && !empty)
	{
		std::cout << "logical operators work too\n";
	}

	bool hasData = static_cast<bool>(numbers);
	std::cout << "static_cast<bool>(numbers): " << hasData << "\n";

	Vector<int> defaultNumbers;
	if (defaultNumbers)
	{
		std::cout << "Default vector is not empty\n";
	}
	else
	{
		std::cout << "Default vector is empty\n";
	}

	Vector<double> prices(3);
	prices.set(0, 1.5);
	prices.set(1, 2.25);
	prices.set(2, 10.0);

	std::cout << "Double vector:\n";
	std::cout << prices.get(0) << "\n";
	std::cout << prices.get(1) << "\n";
	std::cout << prices.get(2) << "\n";

	prices[1] = 99.99;
	std::cout << "After prices[1] = 99.99: " << prices[1] << "\n";

	Vector<double> pricesCopy = prices;

	if (prices == pricesCopy)
	{
		std::cout << "prices and pricesCopy are equal\n";
	}
	else
	{
		std::cout << "prices and pricesCopy are not equal\n";
	}

	return 0;
}
