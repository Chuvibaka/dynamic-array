#include <iostream>
#include <stdexcept>
#include <sstream>


template <typename T>
class Vector
{
private:
	unsigned int size = 0;
	unsigned int capacity = 0;
	T* dinamycArray = nullptr;

	void resize()
	{
		unsigned int newCapacity = (capacity == 0) ? 1 : capacity * 2;
		T* newArray = new T[newCapacity];

		for (unsigned int i = 0; i < size; i++)
		{
			newArray[i] = dinamycArray[i];
		}

		delete[] dinamycArray;

		dinamycArray = newArray;
		capacity = newCapacity;
	}


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
		capacity = sizeOffArray;
		dinamycArray = new T[capacity];
	}

	Vector(const Vector& other)
	{
		size = other.size;
		capacity = other.capacity;
		dinamycArray = new T[capacity];

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
			capacity = other.capacity;
			dinamycArray = new T[capacity];

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

	void push_back(const T& value)
	{
		if (size == capacity)
		{
			resize();
		}

		dinamycArray[size] = value;
		++size;
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

	friend std::ostream& operator<<(std::ostream& out, const Vector& vector)
	{
		out << "[";

		for (unsigned int i = 0; i < vector.size; i++)
		{
			out << vector.dinamycArray[i];

			if (i != vector.size - 1)
			{
				out << ", ";
			}
		}

		out << "]";

		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector& vector)
	{
		unsigned int count = 0;
		in >> count;

		for (unsigned int i = 0; i < count; i++)
		{
			T value;
			in >> value;
			vector.push_back(value);
		}

		return in;
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

	unsigned int getSize() const
	{
		return size;
	}

	unsigned int getCapacity() const
	{
		return capacity;
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

	std::cout << "Before push_back: size = " << numbers.getSize()
		<< ", capacity = " << numbers.getCapacity() << "\n";

	numbers.push_back(444);
	std::cout << "After push_back(444): size = " << numbers.getSize()
		<< ", capacity = " << numbers.getCapacity() << "\n";

	numbers.push_back(555);
	std::cout << "After push_back(555): size = " << numbers.getSize()
		<< ", capacity = " << numbers.getCapacity() << "\n";


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

	Vector<int> growing;

	std::cout << "Growth from empty vector:\n";

	for (int i = 0; i < 5; i++)
	{
		growing.push_back(i);
		std::cout << "size = " << growing.getSize()
			<< ", capacity = " << growing.getCapacity() << "\n";
	}

	std::cout << "numbers: " << numbers << "\n";
	std::cout << "prices: " << prices << "\n";
	std::cout << "chained: " << numbers << " and " << prices << "\n";

	Vector<int> streamed;
	std::istringstream input("3 10 20 30");
	input >> streamed;

	std::cout << "Read from stream: " << streamed << "\n";
	std::cout << "size = " << streamed.getSize()
		<< ", capacity = " << streamed.getCapacity() << "\n";

	std::ostringstream output;
	output << streamed;
	std::cout << "Into ostringstream: " << output.str() << "\n";


	return 0;
}
