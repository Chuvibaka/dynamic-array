#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>


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

	class Iterator
	{
	private:
		T* ptr = nullptr;

	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		Iterator(T* ptr = nullptr)
			: ptr(ptr)
		{
		}

		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }

		Iterator& operator++() { ++ptr; return *this; }
		Iterator operator++(int) { Iterator temp = *this; ++ptr; return temp; }

		Iterator& operator--() { --ptr; return *this; }
		Iterator operator--(int) { Iterator temp = *this; --ptr; return temp; }

		Iterator& operator+=(difference_type n) { ptr += n; return *this; }
		Iterator& operator-=(difference_type n) { ptr -= n; return *this; }

		Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
		Iterator operator-(difference_type n) const { return Iterator(ptr - n); }

		difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }

		reference operator[](difference_type n) const { return ptr[n]; }

		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		bool operator<(const Iterator& other) const { return ptr < other.ptr; }
		bool operator>(const Iterator& other) const { return ptr > other.ptr; }
		bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
		bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }
	};

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

	void swap(Vector& other)
	{
		T* tempArray = other.dinamycArray;
		other.dinamycArray = dinamycArray;
		dinamycArray = tempArray;

		unsigned int tempSize = other.size;
		other.size = size;
		size = tempSize;

		unsigned int tempCapacity = other.capacity;
		other.capacity = capacity;
		capacity = tempCapacity;
	}


	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			Vector temp(other);
			swap(temp);
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

	Iterator begin()
	{
		return Iterator(dinamycArray);
	}

	Iterator end()
	{
		return Iterator(dinamycArray + size);
	}


};

template <typename T>
void insertion_sort(Vector<T>& arr)
{
	for (int i = 1; i < static_cast<int>(arr.getSize()); ++i)
	{
		T value = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > value)
		{
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = value;
	}
}


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

	Vector<int> unsorted;
	unsorted.push_back(5);
	unsorted.push_back(2);
	unsorted.push_back(9);
	unsorted.push_back(1);
	unsorted.push_back(5);
	unsorted.push_back(6);

	std::cout << "Before insertion_sort: " << unsorted << "\n";
	insertion_sort(unsorted);
	std::cout << "After insertion_sort:  " << unsorted << "\n";

	Vector<double> unsortedPrices;
	unsortedPrices.push_back(10.5);
	unsortedPrices.push_back(2.25);
	unsortedPrices.push_back(99.9);
	unsortedPrices.push_back(0.5);

	std::cout << "Before insertion_sort: " << unsortedPrices << "\n";
	insertion_sort(unsortedPrices);
	std::cout << "After insertion_sort:  " << unsortedPrices << "\n";

	Vector<int> reversed;
	reversed.push_back(4);
	reversed.push_back(3);
	reversed.push_back(2);
	reversed.push_back(1);

	insertion_sort(reversed);
	std::cout << "Reversed after sort:   " << reversed << "\n";

	Vector<int> single;
	single.push_back(42);
	insertion_sort(single);
	std::cout << "Single after sort:     " << single << "\n";

	Vector<int> nothing;
	insertion_sort(nothing);
	std::cout << "Empty after sort:      " << nothing << "\n";

	Vector<int> iterable;
	iterable.push_back(30);
	iterable.push_back(10);
	iterable.push_back(20);

	std::cout << "Iterator loop: ";
	for (Vector<int>::Iterator it = iterable.begin(); it != iterable.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n";

	std::sort(iterable.begin(), iterable.end());
	std::cout << "After std::sort: " << iterable << "\n";


	return 0;
}
