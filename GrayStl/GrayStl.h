#pragma once

/*
	+ --------------------------------------------------------- +
	|					I wait for the day						|
	|				the memes will be noticed.					|
	|		Hopefully someone can find the humor in it.			|
	|					Just like I once did					|
	+ --------------------------------------------------------- +
*/

#include <string>
#include <iostream>
#include <cstddef>
#include <sstream>
#include <locale>
#include <unordered_map>

// ------------------- TYPE DECLARATIONS ------------------- \\

template<typename T>
class Sortable;

template <typename T>
class Vector;

template <typename T>
class List;

template <typename T>
class CyclicList;

template <typename T>
class Stack;

template <typename T>
class Queue;

template <typename T>
class BiList;

template <typename T>
class BiCyclicList; // Wait, no it's not a bicycle, what makes you think that?

template <typename T>
class DeQueue;

// ------------------- TYPE DECLARATIONS ------------------- \\

std::string formatNumberWithCommas(long long number) {
	// Get the default locale
	std::locale loc("");

	// Create a custom locale with grouping enabled
	struct myseps : std::numpunct<char> {
		char do_thousands_sep() const { return ','; }  // Separate with comma
		std::string do_grouping() const { return "\3"; }  // Groups of three digits
	};

	// Create a stringstream to format the number
	std::stringstream stream;
	stream.imbue(std::locale(loc, new myseps));
	stream << std::fixed << number;

	// Return the formatted number as a string
	return stream.str();
}


template <typename T>
struct ListItem {
	T value;
	ListItem<T>* nextValue;

	ListItem<T>(T _value) {
		value = _value;
		nextValue = nullptr;
	}
};

template <typename T>
struct List_iter {
	ListItem<T>* current;
	List_iter(ListItem<T>* current) : current(current) {}

	const List_iter& operator++() { current = current->nextValue; return *this; }
	List_iter operator++(int) {
		List_iter result = *this; ++(*this); return result;
	}

	List_iter operator+(int const right) {
		for (int i = 0; i < right && current != nullptr; i++) {
			current = current->nextValue;
		}

		return *this;
	}

	bool operator==(List_iter<T> right) {
		return current == right.node();
	}

	bool operator==(ListItem<T> right) {
		return current == right;
	}

	bool operator!=(List_iter<T> right) {
		return !(current == right.node());
	}

	bool operator!=(ListItem<T> right) {
		return !(current == right);
	}

	T& operator*() const {
		return current->value;
	}

	ListItem<T>* node() const {
		return current;
	}
};

template <typename T>
struct BiListItem {
	T value;
	BiListItem<T>* prevValue;
	BiListItem<T>* nextValue;

	BiListItem<T>(T _value) {
		value = _value;
		prevValue = nextValue = nullptr;
	}
};

template <typename T>
struct BiList_iter {
	BiListItem<T>* current;
	BiList_iter(BiListItem<T>* current) : current(current) {}

	const BiList_iter& operator++() { current = current->nextValue; return *this; }
	BiList_iter operator++(int) {
		BiList_iter result = *this; ++(*this); return result;
	}

	BiList_iter<T> operator+(int const& right) {
		for (int i = 0; i < right && current != nullptr; i++) {
			current = current->nextValue;
		}

		return *this;
	}

	const BiList_iter& operator--() { current = current->prevValue; return *this; }
	BiList_iter operator--(int) {
		BiList_iter result = *this; --(*this); return result;
	}

	BiList_iter<T> operator-(int const& right) {
		for (int i = 0; i < right && current != nullptr; i++) {
			current = current->prevValue;
		}

		return *this;
	}

	bool operator==(BiList_iter<T> right) {
		return current == right.node();
	}

	bool operator==(BiListItem<T>* right) {
		return current == right;
	}

	bool operator!=(BiList_iter<T> right) {
		return !(current == right.node());
	}

	bool operator!=(BiListItem<T>* right) {
		return !(current == right);
	}

	T& operator*() const {
		return current->value;
	}

	BiListItem<T>* node() const {
		return current;
	}
};

template <typename T>
struct TreeItem {
	T value;
	TreeItem<T>* left = nullptr;
	TreeItem<T>* right = nullptr;

	int height = 0;
};

template <typename T>
struct BTreeItem {
	Vector<T> keys;
	Vector<BTreeItem*> children;
	bool leaf;

	BTreeItem(bool _leaf = true) : leaf(_leaf) {}
};

template <typename T>
class Compare {
public:
	static int compare(T val1, T val2) {
		return (val1 == val2 ? 0 :
			(val1 > val2 ? -1 : 1));
	}
};

template<> static int Compare<std::string>::compare(std::string val1, std::string val2) {
	return val1.compare(val2);
}

// Oh yer a really funny one, ain't ya?
template<typename T>
class Sortable {
public:
	// THERE'S VIRTUAL STDs NOW???
	virtual std::size_t size() const = 0;

	// No need to ask I'm a smooth operator~𝆕
	virtual T& operator[](std::size_t index) = 0;

	bool empty() const { return size() == 0; }

	T& at(std::size_t index) {
		if (empty())
			throw std::out_of_range("Index out of bounds");

		return (*this)[index];
	}

	std::size_t indexOf(T value) {
		std::size_t i = 0;

		for (i = 0; i < size() && (*this)[i] != value; i++) {}

		if ((*this)[i] != value)
			return -1;

		return i;
	}

	T max() { // DO DO  DO DO   MAX VERSTAPEN
		if (empty())
			throw std::out_of_range("List is empty");

		T maxValue = (*this)[0];

		for (int i = 1; i < size(); i++) {
			maxValue = (Compare<T>::compare(maxValue, (*this)[i]) == -1 ? maxValue : (*this)[i]);
		}

		return maxValue;
	}

	T min() {
		if (empty())
			throw std::out_of_range("List is empty");

		T minValue = (*this)[0];

		for (int i = 1; i < size(); i++) {
			minValue = (Compare<T>::compare(minValue, (*this)[i]) == 1 ? minValue : (*this)[i]);
		}

		return minValue;
	}

	double avg() {
		double avg = 0;

		for (int i = 0; i < size(); i++)
			avg += (*this)[i];

		avg /= size();

		return avg;
	}

	void display() {
		display(0);
	}

	void display(int startIndex) {
		for (int i = startIndex; i < size(); i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void reverse() {
		for (std::size_t i = 0; i < size() / 2; i++) {
			T temp = (*this)[i];

			(*this)[i] = (*this)[size() - i - 1];
			(*this)[size() - i - 1] = temp;
		}
	}

	void insertionSort() {
		long long swaps = 0;

		for (int i = 1; i < size(); i++) {
			if (Compare<T>::compare((*this)[i], (*this)[i - 1]) == 1) {
				for (int o = 0; o < i; o++) {
					if (Compare<T>::compare((*this)[i], (*this)[o]) == 1) {
						T temp = (*this)[o];

						(*this)[o] = (*this)[i];
						(*this)[i] = temp;
					}
				}
			}
		}
	}

	// Get a room, you two
	void shellSort() { // offender #1
		int n = size();

		for (int gap = n / 2; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i++) {
				T temp = (*this)[i];
				int j;

				for (j = i; j >= gap && (*this)[j - gap] > temp; j -= gap) {
					(*this)[j] = (*this)[j - gap];
				}

				(*this)[j] = temp;
			}
		}
	}

	void mergeSort() { // offender #2
		mergeSort(*this);
	}

	void quickSort() {
		quickSort(0, size() - 1);
	}

	void quickSort(int low, int high) {
		if (low < high) {
			int pi = partition(*this, low, high);

			quickSort(low, pi - 1);
			quickSort(pi + 1, high);
		}
	}

	void bingoSort() {
		int n = size();
		if (n <= 1) return;

		// Find the maximum element in the array
		T max_val = (*this)[0];
		for (int i = 1; i < n; ++i) { // Or just use max(), I forgor ._.
			if ((*this)[i] > max_val) {
				max_val = (*this)[i];
			}
		}

		// - This is a bucket
		//						Oh no -
		// - But wait, there's more
		//					 Dear god -
		Vector<Vector<T>> buckets(max_val + 1);
		for (int i = 0; i < n; ++i) {
			buckets[(*this)[i]].push_back((*this)[i]);
		}

		// Concatenate elements from buckets
		std::size_t index = 0;
		for (int i = 0; i <= max_val; ++i) {
			for (int o = 0; o < buckets[i].size() && buckets[i][o] != NULL; o++) {
				(*this)[index++] = buckets[i][o];
			}
		}
	}

	void bubbleSort() {
		for (int i = 0; i < size() - 1; ++i) {
			for (int j = 0; j < size() - i - 1; ++j) {
				if ((*this)[j] > (*this)[j + 1]) {
					T temp = (*this)[j];

					(*this)[j] = (*this)[j + 1];
					(*this)[j + 1] = temp;
				}
			}
		}
	}

private:
	void mergeSort(Sortable<T>& arr) {
		if (arr.size() <= 1) {
			return;
		}

		int mid = arr.size() / 2;
		Vector<T> left;
		for (int i = 0; i < mid; i++) {
			left.push_back(arr[i]);
		}
		Vector<T> right;
		for (int i = mid; i < arr.size(); i++) {
			right.push_back(arr[i]);
		}

		mergeSort(left);
		mergeSort(right);
		merge(left, right, arr);
	}

	void merge(Sortable<T>& left, Sortable<T>& right, Sortable<T>& result) {
		int i = 0, j = 0, k = 0;
		while (i < left.size() && j < right.size()) {
			if (left[i] <= right[j]) {
				result[k++] = left[i++];
			}
			else {
				result[k++] = right[j++];
			}
		}
		while (i < left.size()) {
			result[k++] = left[i++];
		}
		while (j < right.size()) {
			result[k++] = right[j++];
		}
	}

	int partition(Sortable<T>& arr, int low, int high) {
		T pivot = arr[high];
		int i = low - 1;

		for (int j = low; j <= high - 1; j++) {
			if (arr[j] < pivot) {
				i++;
				std::swap(arr[i], arr[j]); // That did not go by plan, did it now?
			}
		}
		std::swap(arr[i + 1], arr[high]);
		return i + 1;
	}
};

template<> double Sortable<std::string>::avg() {
	throw "Collections of text cannot be averaged";
}

const int CACHE_SIZE = 10;
const int CACHE_THRESHOLD = 50;

template <typename T>
class Vector : public Sortable<T> {
	T* elements{};
	std::size_t _size = 0;
	std::size_t capacity = 0;

	void reserve(std::size_t new_capacity) {
		if (new_capacity > capacity) {
			T* new_elements = new T[new_capacity];
			for (std::size_t i = 0; i < _size; ++i) {
				new_elements[i] = elements[i];
			}
			delete[] elements;
			elements = new_elements;
			capacity = new_capacity;
		}
	}

public:
	// Define iterator and const_iterator types
	using iterator = T*;
	using const_iterator = const T*;

	// Iterator functions
	iterator begin() {
		return elements;
	}

	iterator end() {
		return elements + _size;
	}

	const_iterator begin() const {
		return elements;
	}

	const_iterator end() const {
		return elements + _size;
	}

	virtual std::size_t size() const override { return _size; }

	Vector() {
		reserve(0);
	}

	Vector(std::size_t capacity) {
		reserve(capacity);
	}

	Vector(std::size_t capacity, T value) {
		for (std::size_t i = 0; i < capacity; i++)
			push_back(value);
	}

	Vector(std::initializer_list<T> values) {
		for (const T value : values) {
			push_back(value);
		}
	}

	~Vector() {
		delete[] elements;
	}

	void insert(iterator pos, const T& value) {
		// Calculate the index corresponding to the iterator position
		std::size_t index = pos - begin();

		// Call the insert function with the index
		insert(index, value);
	}

	void insert(std::size_t index, const T& value) {
		if (_size >= capacity) {
			std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
			reserve(new_capacity);
		}

		elements[_size++] = value;

		for (int i = _size - 1; i > index - 1; i--) {
			T temp = elements[i];

			elements[i] = elements[i - 1];
			elements[i - 1] = temp;
		}
	}

	void push_back(const T& value) {
		if (_size >= capacity) {
			std::size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
			reserve(new_capacity);
		}
		elements[_size++] = value;
	}

	void remove(std::size_t index) {
		_size--;

		for (int i = index; i < _size; i++)
			elements[i] = elements[i + 1];
	}

	void pop_back() {
		if (_size > 0) {
			_size--;
		}
	}

	// Erase a single element at the specified index
	void erase(std::size_t index) {
		if (index >= _size) {
			// Index out of range
			return;
		}

		// Shift elements to the left to fill the gap
		for (std::size_t i = index; i < _size - 1; ++i) {
			elements[i] = elements[i + 1];
		}

		// Decrease the size
		--_size;
	}

	// Erase a range of elements specified by start and end iterators
	void erase(iterator start, iterator end) {
		std::size_t startIndex = start - begin();
		std::size_t endIndex = end - begin();

		if (startIndex >= _size || endIndex > _size || startIndex >= endIndex) {
			// Indices out of range, or invalid range
			return;
		}

		// Calculate the number of elements to erase
		std::size_t numToRemove = endIndex - startIndex;

		// Shift elements to the left to fill the gap
		for (std::size_t i = startIndex; i < _size - numToRemove; ++i) {
			elements[i] = elements[i + numToRemove];
		}

		// Adjust the size
		_size -= numToRemove;
	}

	void clear() {
		_size = 0;
	}

	// Assigns new content to the vector, replacing its current content, and modifying its size accordingly.
	void assign(std::size_t count, const T& value) {
		clear(); // Clear the existing elements

		// Reserve capacity if necessary
		if (count > capacity) {
			reserve(count);
		}

		// Insert 'count' number of elements with the specified value
		for (std::size_t i = 0; i < count; ++i) {
			push_back(value);
		}
	}

	void assign(iterator first, iterator last) {
		clear(); // Clear the vector before assigning new values
		for (auto it = first; it != last; ++it) {
			push_back(*it);
		}
	}

	virtual T& operator[](std::size_t index) override {
		return elements[index];
	}
};

/// <summary>
///	<para/>	It's sortable.
///	<para/>	'𝘑𝘶𝘴𝘵 𝘣𝘦𝘤𝘢𝘶𝘴𝘦 𝘺𝘰𝘶 𝘤𝘢𝘯, 𝘥𝘰𝘦𝘴𝘯'𝘵 𝘮𝘦𝘢𝘯 𝘺𝘰𝘶 𝘴𝘩𝘰𝘶𝘭𝘥'
///	<para/>						   - William C. Taylor
/// </summary>
template <typename T>
class List : public Sortable<T> {
	std::size_t _size = 0;

public:
	ListItem<T>* start = nullptr;
	ListItem<T>* stop = nullptr;

	List() {
		_size = 0;
	}

	List(std::size_t capacity) {
		assign(capacity, T());
	}

	List(std::size_t capacity, T value) {
		assign(capacity, std::move(value));
	}

	List(std::initializer_list<T> values) {
		for (const T& value : values) {
			push_back(std::move(value));
		}
	}

	virtual std::size_t size() const override { return _size; }

	List_iter<T> begin() { return List_iter<T>(start); }
	List_iter<T> end() { return List_iter<T>(stop); }

	void push_front(T value) {
		ListItem<T>* newValue = new ListItem<T>(value);

		newValue->nextValue = start;
		start = newValue;


		start = newValue;
		if (stop == nullptr)
			stop = newValue;

		_size++;
	}

	// Um 𝙖𝙠𝙨𝙝𝙪𝙖𝙡𝙡𝙮, you don't need temp for this
	void insert(std::size_t index, T value) {
		ListItem<T>* current = (begin() + index).node();

		if (current == start) {
			push_front(value);
			return;
		}
		else if (current == stop) {
			push_back(value);
			return;
		}

		ListItem<T>* newItem = new ListItem<T>(value);

		newItem->nextValue = current->nextValue;
		current->nextValue = newItem;

		_size++;
	}

	void push_back(T value) {
		ListItem<T>* newValue = new ListItem<T>(value);

		if (stop != nullptr) stop->nextValue = newValue;

		if (start == nullptr)
			start = newValue;
		stop = newValue;

		_size++;
	}

	void pop_front() {
		if (Sortable<T>::empty())
			throw std::out_of_range("List is empty");

		ListItem<T>* old = start;

		start = old->nextValue;

		free(old);

		_size--;
	}

	void remove(std::size_t index) {
		ListItem<T>* current = (begin() + index).node();

		if (current == start) {
			pop_front();

			return;
		}

		if (current == stop)
			throw std::out_of_range("Index out of range");

		if (current->nextValue == stop) {
			stop = current;
		}

		ListItem<T>* temp = current->nextValue;
		current->nextValue = temp->nextValue;
		current->value = temp->value;

		free(temp);

		_size--;
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(value);
	}

	void clear() {
		while (!Sortable<T>::empty())
			pop_front();
	}

private:
	std::unordered_map<int, ListItem<T>*> indexMap = std::unordered_map<int, ListItem<T>*>();

public:

	virtual T& operator[](std::size_t index) override {
		// Check if the index is out of range
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		// Check if the list item is already cached
		auto it = indexMap.find(index);
		if (it != indexMap.end()) {
			return it->second->value;
		}

		// Determine the starting point for traversal
		ListItem<T>* temp = nullptr;
		int startIndex = 0;

		// Find the last cached index and item
		int lastCachedIndex = -1;
		ListItem<T>* lastCachedItem = nullptr;
		for (const auto& entry : indexMap) {
			if (entry.first > lastCachedIndex && entry.first <= index) {
				lastCachedIndex = entry.first;
				lastCachedItem = entry.second;
			}
		}

		startIndex = 0;
		temp = start;

		// Start traversal from the cached element
		if (lastCachedItem != nullptr && index >= lastCachedIndex) {
			temp = lastCachedItem;
			startIndex = lastCachedIndex;
		}

		// Traverse to the desired index and store list items in the index map
		for (int i = startIndex; i < index; ++i) {
			if (indexMap.size() > 10) {
				// Remove the oldest entry from the indexMap
				indexMap.erase(indexMap.begin());
			}

			temp = temp->nextValue;
		}

		if (index >= CACHE_THRESHOLD && indexMap.empty() || std::abs((int)index - indexMap.end()->first) >= CACHE_THRESHOLD) {
			// Store the list item at the significant index in the index map
			indexMap[index] = temp;
		}

		return temp->value;
	}

};

template <typename T>
class CyclicList : public Sortable<T> {
private:
	List<T> list = List<T>();


public:
	CyclicList() {
		list = List<T>(0);
	}

	CyclicList(std::size_t capacity) {
		list = List<T>(capacity);
	}

	CyclicList(std::size_t capacity, T value) {
		list = List<T>(capacity, value);
	}

	virtual std::size_t size() const override { return list.size(); }

	List_iter<T> begin() { return list.begin(); }
	List_iter<T> end() { return list.end(); }

	void push_front(T value) {
		list.push_front(value);

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void insert(std::size_t index, T value) {
		list.insert(index, value);
	}

	void push_back(T value) {
		list.push_back(value);

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void pop_front() {
		list.pop_front();

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void remove(std::size_t index) {
		list.remove(index);
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(value);
	}

	void clear() {
		while (!Sortable<T>::empty())
			pop_front();
	}

	virtual T& operator[](std::size_t index) override {
		return list[index];
	}
};

template <typename T>
class Stack {
	std::size_t _size = 0;

public:
	ListItem<T>* _head;

	Stack() {
		_size = 0;
	}

	Stack(std::size_t capacity) {
		_size = 0;

		for (int i = 0; i < capacity; i++)
			push(T());
	}

	Stack(std::size_t capacity, T value) {
		_size = 0;

		for (int i = 0; i < capacity; i++)
			push(std::move(value));
	}

	~Stack() {
		clear();
	}

	// None for you, you can rest easy :]
	List_iter<T> head() { return List_iter<T>(_head); }

	std::size_t size() const { return _size; }

	bool empty() const { return _size == 0; }

	T& top() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		return _head->value;
	}

	// Yes please
	const T& top() const {
		if (empty())
			throw std::out_of_range("Stack is empty");

		return _head->value;
	}

	void push(T value) {
		ListItem<T>* newValue = new ListItem<T>(value);

		if (_head != nullptr)
			newValue->nextValue = _head;
		_head = newValue;

		_size++;
	}

	void pop() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		ListItem<T>* old = _head;

		_head = old->nextValue;

		free(old);

		_size--;
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push(value);
	}

	void clear() {
		while (!empty())
			pop();
	}

	void display() {
		display(0);
	}

	void display(int startIndex) {
		for (int i = startIndex; i < size(); i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}
};

template <typename T>
class Queue {
	std::size_t _size;

protected:
	ListItem<T>* start;
	ListItem<T>* stop;

public:

	Queue() {
		_size = 0;
	}

	Queue(std::size_t capacity) {
		for (int i = 0; i < capacity; i++)
			push(T());
	}

	Queue(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push(std::move(value));
	}

	List_iter<T> begin() { return List_iter<T>(start); }
	List_iter<T> end() { return List_iter<T>(stop); }

	std::size_t size() const { return _size; }
	bool empty() const { return _size == 0; }

	void push(T value) {
		ListItem<T>* newValue = new ListItem<T>(value); // create new node

		if (stop != nullptr) stop->nextValue = newValue; // if end exists, set its next element to the new node

		if (empty()) // if the end position is empty, set new node as end
			start = newValue;
		stop = newValue; // setting the new node as the end

		_size++;
	}

	// Cherry, anyone?
	void pop() {
		if (Sortable<T>::empty())
			throw std::out_of_range("Queue is empty");

		ListItem<T>* old = start; // we take the first element from the queue

		start = old->nextValue; // set start as the next element in the queue

		free(old); // delete the first node

		_size--;
	}

	T& front() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		return start->value;
	}

	const T& front() const {
		if (empty())
			throw std::out_of_range("Queue is empty");

		return start->value;
	}

	T& back() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		return stop->value;
	}

	const T& back() const {
		if (empty())
			throw std::out_of_range("Queue is empty");

		return stop->value;
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push(value);
	}

	// I prefer 𝓽𝓻𝓪𝓷𝓼𝓵𝓾𝓼𝓬𝓮𝓷𝓽
	void clear() {
		while (!empty())
			pop();
	}

	void display() {
		display(0);
	}

	void display(int startIndex) {
		List_iter<T> current = begin() + startIndex;

		for (int i = startIndex; i < _size; i++) {
			std::cout << (*current) << " ";
			current++;
		}

		std::cout << std::endl;
	}
};

// Don't get the wrong idea, by bi I mean 𝘣𝘪directional list
// Get your mind out of the gutter
template <typename T>
class BiList : public Sortable<T> {
	BiListItem<T>* start = nullptr;
	BiListItem<T>* stop = nullptr;

	std::size_t _size = 0;

public:
	BiList() {
		_size = 0;
	}

	BiList(std::size_t capacity) {
		for (int i = 0; i < capacity; i++)
			push_back(T());
	}

	BiList(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	virtual std::size_t size() const override { return _size; }

	BiList_iter<T> begin() { return BiList_iter<T>(start); }
	BiList_iter<T> end() { return BiList_iter<T>(stop); }

	void push_front(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (start == nullptr) {
			start = stop = newValue;

			_size++;

			return;
		}

		newValue->nextValue = start;
		start->prevValue = newValue;
		start = newValue;

		_size++;
	}

	// Why is the line that shows where I'm typing a box now??
	void insert(std::size_t index, T value) {
		BiList_iter<T> it = begin() + index;

		if (it == start) {
			push_front(value);
			return;
		}
		else if (it == stop) {
			push_back(value);
			return;
		}

		BiListItem<T>* current = it.node();
		BiListItem<T>* newValue = new BiListItem<T>(value);

		newValue->nextValue = current->nextValue;
		newValue->prevValue = current;
		current->nextValue->prevValue = newValue;
		current->nextValue = newValue;

		_size++;
	}

	void push_back(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (stop == nullptr) {
			start = stop = newValue;

			_size++;
			return;
		}

		newValue->prevValue = stop;
		stop->nextValue = newValue;
		stop = newValue;

		_size++;
	}

	void pop_front() {
		if (Sortable<T>::empty())
			throw std::out_of_range("List is empty"); // Oh no shit sherlock, thanks for telling me

		BiListItem<T>* old = start;

		start = old->nextValue;
		start->prevValue = nullptr;

		free(old);

		_size--;
	}

	void remove(std::size_t index) {
		BiListItem<T>* current = (begin() + index).node();

		if (current == start) {
			pop_front();
			return;
		}
		else if (current == stop) {
			pop_back();
			return;
		}

		current->prevValue->nextValue = current->nextValue;
		current->nextValue->prevValue = current->prevValue;

		free(current);

		_size--;
	}

	void pop_back() {
		if (Sortable<T>::empty())
			throw std::out_of_range("List is empty");

		BiListItem<T>* old = stop->prevValue;

		stop = old->prevValue;
		stop->nextValue = nullptr;

		free(old);

		_size--;
	}

	BiListItem<T>* findElement(T value) {
		BiList_iter<T> current = begin();

		while (current != nullptr && *current != value)
			current++;

		return current.node();
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(value);
	}

	void clear() {
		while (!Sortable<T>::empty())
			pop_front();
	}

	virtual T& operator[](std::size_t index) override {
		BiListItem<T>* temp = start;
		for (int i = 0; i < index && temp != nullptr; i++) {
			temp = temp->nextValue;
		}
		if (temp == nullptr) {
			throw std::out_of_range("Index out of range");
		}
		return temp->value;
	}
};

template <typename T>
class BiCyclicList : public Sortable<T> {
private:
	std::size_t _size = 0;

protected:
	BiListItem<T>* start = nullptr;
	BiListItem<T>* stop = nullptr;

public:
	BiCyclicList() {
		_size = 0;
	}

	BiCyclicList(std::size_t capacity) {
		for (int i = 0; i < capacity; i++)
			push_back(T());
	}

	BiCyclicList(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	std::size_t size() const override { return _size; }

	BiList_iter<T> begin() { return BiList_iter<T>(start); }
	BiList_iter<T> end() { return BiList_iter<T>(stop); }

	int indexOf(T value) {
		if (Sortable<T>::empty())
			return -1;

		int i = 0;

		for (i = 0; i < _size; i++) { if ((*this)[i] == value) break; }

		if (i == _size)
			return -1;

		return i;
	}

	void push_front(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (start == nullptr) {
			start = stop = newValue;

			newValue->nextValue = stop;
			newValue->prevValue = stop;

			_size++;

			return;
		}

		newValue->nextValue = start;
		newValue->prevValue = stop;
		start->prevValue = newValue;
		start = newValue;

		_size++;
	}

	void insert(std::size_t index, T value) {
		BiList_iter<T> it = begin() + index;

		if (it == start) {
			push_front(value);
			return;
		}
		else if (it == stop) {
			push_back(value);
			return;
		}

		BiListItem<T>* current = it.node();
		BiListItem<T>* newValue = new BiListItem<T>(value);

		newValue->nextValue = current->nextValue;
		newValue->prevValue = current;
		current->nextValue->prevValue = newValue;
		current->nextValue = newValue;

		_size++;
	}

	void push_back(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (stop == nullptr) {
			start = stop = newValue;

			newValue->nextValue = start;
			newValue->prevValue = start;

			_size++;
			return;
		}

		newValue->prevValue = stop;
		newValue->nextValue = start;
		stop->nextValue = newValue;
		stop = newValue;

		_size++;
	}

	void pop_front() {
		if (Sortable<T>::empty())
			throw std::out_of_range("List is empty");

		BiListItem<T>* old = start;

		start = old->nextValue;
		start->prevValue = stop;

		free(old);

		_size--;
	}

	void remove(std::size_t index) {
		BiListItem<T>* current = (begin() + index).node();

		if (current == start) {
			pop_front();
			return;
		}
		else if (current == stop) {
			pop_back();
			return;
		}

		current->prevValue->nextValue = current->nextValue;
		current->nextValue->prevValue = current->prevValue;

		free(current);

		_size--;
	}

	void pop_back() {
		if (Sortable<T>::empty())
			throw std::out_of_range("List is empty");

		BiListItem<T>* old = stop->prevValue;

		stop = old->prevValue;
		stop->nextValue = start;

		free(old);

		_size--;
	}

	BiListItem<T>* findElement(T value) {
		BiList_iter<T> current = begin();

		for (int i = 0; i < _size && *current != value; i++)
			current++;

		return current.node();
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(value);
	}

	void clear() {
		while (!Sortable<T>::empty())
			pop_front();
	}

	virtual T& operator[](std::size_t index) override {
		if (index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		BiListItem<T>* temp = start;
		for (int i = 0; i < index; i++) {
			temp = temp->nextValue;
		}
		return temp->value;
	}
};

template <typename T>
class Deque {
private:
	std::size_t _size = 0;

protected:
	BiListItem<T>* start;
	BiListItem<T>* stop;

public:
	Deque() {
		_size = 0;
	}

	Deque(std::size_t capacity) {
		assign(capacity, T());
	}

	Deque(std::size_t capacity, T value) {
		assign(capacity, value);
	}

	~Deque() {
		clear();
	}

	std::size_t size() const { return _size; }
	bool empty() const { return _size == 0; }

	BiList_iter<T> begin() { return BiList_iter<T>(start); }
	BiList_iter<T> end() { return BiList_iter<T>(stop); }

	void push_front(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (empty()) {
			start = stop = newValue; // if dequeue is empty, the new node becomes start and end

			_size++;

			return;
		}

		newValue->nextValue = start; // set the next value to the previous start value
		start->prevValue = newValue; // set the previous value of the start node to the new node
		start = newValue; // set the new node as the start

		_size++;
	}

	void push_back(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (empty()) {
			start = stop = newValue;

			_size++;

			return;
		}

		newValue->prevValue = stop;
		stop->nextValue = newValue;
		stop = newValue;

		_size++;
	}

	void pop_front() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		BiListItem<T>* old = start;

		start = start->nextValue;
		if (start != nullptr)
			start->prevValue = nullptr;
		else
			stop = nullptr;

		_size--;

		free(old);
	}

	void pop_back() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		BiListItem<T>* old = stop;

		stop = stop->prevValue;
		if (stop != nullptr)
			stop->nextValue = nullptr;
		else
			stop = nullptr;

		_size--;

		free(old);
	}

	T& front() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		return start->value;
	}

	const T& front() const {
		if (empty())
			throw std::out_of_range("Deque is empty");

		return start->value;
	}

	T& back() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		return stop->value;
	}

	const T& back() const {
		if (empty())
			throw std::out_of_range("Deque is empty");

		return stop->value;
	}

	void assign(std::size_t capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	void clear() {
		while (empty())
			pop_front();
	}

	void display() {
		display(0);
	}

	void display(int startIndex) {
		BiList_iter<T> current = begin() + startIndex;

		for (int i = startIndex; i < _size; i++) {
			std::cout << (*current) << " ";
			current++;
		}

		std::cout << std::endl;
	}
};

// UOOOOOHHH tree
template <typename T>
class BinaryTree {
public:
	TreeItem<T>* root;

	TreeItem<T>* insertItem(T value) {
		TreeItem<T>* newItem = new TreeItem<T>();
		newItem->value = value;

		// assign value to the root if tree is empty (rule 1)
		if (root == nullptr) {
			root = newItem;

			return newItem;
		}

		// rule 2
		TreeItem<T>* current = root;

		while (current != newItem) { // while the current node is not equal to the new node
			if (Compare<T>::compare(newItem->value, current->value) == 1) { // compare the values
				if (current->left == nullptr) { // if the spot is free, put the new node in its place
					current->left = newItem;
				}

				current = current->left; // go left
			}
			else {
				if (current->right == nullptr) {
					current->right = newItem;
				}

				current = current->right;
			}
		}

		return newItem;
	}

	TreeItem<T>* findItem(T value) {
		TreeItem<T>* current = root;

		while (Compare<T>::compare(current->value, value) != 0) {
			if (current == nullptr)
				return current;

			if (Compare<T>::compare(value, current->value) == 1) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

		return current;
	}

	void removeItem(T value) {
		TreeItem<T>* item = findItem(value); // find the node to delete

		TreeItem<T>* replaceWith = item->left; // go left

		// rule 1
		if (replaceWith == nullptr && item->right == nullptr) {
			free(item);
			return;
		}

		// rule 3(4)
		if (replaceWith == nullptr && item->right != nullptr) {
			replaceWith = item->right;

			item->value = replaceWith->value;
			item->left = replaceWith->left;
			item->right = replaceWith->right;

			free(replaceWith);
		}

		// rule 4
		if (replaceWith->right != nullptr) { // if we can go right
			while (replaceWith->right->right != nullptr) { // go as far right as possible
				replaceWith = replaceWith->right;
			}

			if (replaceWith->right->left != nullptr) { // if the best candidate has a child on their left
				// Everyone's asking 'what is temp?', 'why is temp here?'
				// But no one's asking '𝘩𝘰𝘸 is temp?'
				TreeItem<T>* temp = replaceWith->right;

				replaceWith->right = temp->left;

				replaceWith = temp;
			}
		}

		// rule 2
		item->value = replaceWith->value;

		free(replaceWith);
	}

	TreeItem<T>* maxItem(T ceil) { throw "Not yet implemented for this type"; }
	TreeItem<T>* minItem(T floor) { throw "Not yet implemented for this type"; }

	List<T> moreThan(T value) {
		List<T> list = List<T>();

		TreeItem<T>* item = minItem(value);

		if (Compare<T>::compare(item->value, value) == -1)
			list.push_back(item->value);

		addToList(list, item->right);

		return list;
	}

	List<T> lessThan(T value) {
		List<T> list = List<T>();

		TreeItem<T>* item = maxItem(value);

		addToList(list, item->left);

		if (Compare<T>::compare(item->value, value) == 1)
			list.push_back(item->value);

		return list;
	}

	void display() {
		display(root); // 𝘚𝘩𝘩𝘩𝘩.. 𝘕𝘰 𝘰𝘯𝘦 𝘩𝘢𝘴 𝘵𝘰 𝘬𝘯𝘰𝘸
	}

private:
	void display(TreeItem<T>* node) {
		if (node == nullptr)
			return;

		display(node->left);
		std::cout << node->value << " ";
		display(node->right);
	}

	void addToList(List<T>& list, TreeItem<T>* node) {
		if (node == nullptr)
			return;

		addToList(list, node->left);
		list.push_back(node->value);
		addToList(list, node->right);
	}
};

template<> TreeItem<int>* BinaryTree<int>::maxItem(int ceil) {
	for (int i = ceil; ; i--) {
		TreeItem<int>* element = findItem(i);

		if (element != nullptr)
			return element;
	}
}

template<> TreeItem<int>* BinaryTree<int>::minItem(int floor) {
	for (int i = floor; ; i++) {
		TreeItem<int>* element = findItem(i);

		if (element != nullptr)
			return element;
	}
}

// I HAVE NEVER SEEN SUCH GREATNESS BEFORE
template <typename T>
class AVLTree {
private:
	BinaryTree<T> tree;

	void balance(T value) {
		tree.root = balance(tree.root, value);
	}

	TreeItem<T>* balance(TreeItem<T>* node, T value) { // I really tried to find a better way to do this
		if (node == nullptr)
			return node;

		if (Compare<T>::compare(value, node->value) == 1) {
			node->left = balance(node->left, value);
		}
		else {
			node->right = balance(node->right, value);
		}

		// Just like riding a bicycle

		int bc = balanceCoeficient(node);

		if (bc > 1 && value < node->left->value)
			return RTurn(node);

		if (bc < -1 && value > node->right->value)
			return LTurn(node);

		if (bc > 1 && value > node->left->value) {
			node->left = LTurn(node->left);

			return RTurn(node);
		}

		if (bc < -1 && value < node->right->value) {
			node->right = RTurn(node->right);

			return LTurn(node);
		}

		return node;
	}

	// To the left
	TreeItem<T>* LTurn(TreeItem<T>* node) {
		if (node->right == nullptr)
			return node;

		TreeItem<T>* nextNode = node->right;

		node->right = nextNode->left;
		nextNode->left = node;

		node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
		nextNode->height = std::max(getHeight(nextNode->left), getHeight(nextNode->right)) + 1;

		return nextNode;
	}

	// Take it back now yo
	TreeItem<T>* RTurn(TreeItem<T>* node) {
		if (node->left == nullptr)
			return node;

		TreeItem<T>* nextNode = node->left;

		node->left = nextNode->right;
		nextNode->right = node;

		node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
		nextNode->height = std::max(getHeight(nextNode->left), getHeight(nextNode->right)) + 1;

		return nextNode;
	}

	// Cha cha real smooth
	int balanceCoeficient(TreeItem<T>* node) {
		if (node == nullptr)
			return 0;

		return getHeight(node->left) - getHeight(node->right);
	}

	int getHeight(TreeItem<T>* node) {
		if (node == nullptr)
			return 0;

		return node->height;
	}

public:
	TreeItem<T>* root() {
		return tree.root;
	}

	TreeItem<T>* insertItem(T value) {
		TreeItem<T>* newItem = new TreeItem<T>();
		newItem->value = value;

		// assign value to the root if tree is empty
		if (tree.root == nullptr) {
			tree.root = newItem;

			return newItem;
		}

		TreeItem<T>* node = tree.root;

		while (node != newItem) {
			node->height++;

			if (Compare<T>::compare(newItem->value, node->value) == 1) {
				if (node->left == nullptr) {
					node->left = newItem;
				}

				node = node->left;
			}
			else {
				if (node->right == nullptr) {
					node->right = newItem;
				}

				node = node->right;
			}
		}

		balance(value);

		return newItem;
	}

	TreeItem<T>* findItem(T value) {
		return tree.findItem(value);
	}

	void removeItem(T value) {
		tree.removeItem(value);
	}

	void display() {
		tree.display();
	}
};

// This is it. I can die in peace now
template <typename T>
class BTree {
private:
	BTreeItem<T>* root;
	int t; // Minimum degree
	std::size_t M;
	std::size_t MIN_KEYS;

	void split(BTreeItem<T>* parent, int index) {
		BTreeItem<T>* child = parent->children[index];
		BTreeItem<T>* new_child = new BTreeItem<T>();

		// Determine the midpoint of the keys
		int mid = child->keys.size() / 2;

		// Move keys and children from the full child to the new child
		new_child->keys.assign(child->keys.begin() + mid + 1, child->keys.end());
		child->keys.erase(child->keys.begin() + mid, child->keys.end());
		if (!child->leaf) {
			new_child->children.assign(child->children.begin() + mid + 1, child->children.end());
			child->children.erase(child->children.begin() + mid + 1, child->children.end());
		}

		// Insert the middle key into the parent node
		parent->keys.insert(parent->keys.begin() + index, child->keys[mid]);

		// Link the new child to the parent
		parent->children.insert(parent->children.begin() + index + 1, new_child); // Do WHAT

		// Update child properties
		child->keys.pop_back();
		new_child->leaf = child->leaf;

		// If child was an internal node, adjust its children pointers
		if (!child->leaf) {
			child->children.pop_back();
		}
	}

	void insert_non_full(BTreeItem<T>* node, const T& key) {
		int i = node->keys.size() - 1;
		if (node->leaf) {
			while (i >= 0 && key < node->keys[i]) {
				i--;
			}
			node->keys.insert((node->keys.begin() + i + 1), key);
		}
		else {
			while (i >= 0 && key < node->keys[i]) {
				i--;
			}
			i++;
			if (node->children[i]->keys.size() == M - 1) {
				split(node, i);
				if (key > node->keys[i]) {
					i++;
				}
			}
			insert_non_full(node->children[i], key);
		}
	}

	// Find the index of the key in the node, return -1 if not found
	int findIndexInNode(BTreeItem<T>* node, const T& key) {
		for (std::size_t i = 0; i < node->keys.size(); ++i) {
			if (node->keys[i] == key) {
				return i; // Key found at index i
			}
		}
		return -1; // Key not found
	}

	// Find the index of the child node to traverse to based on the key
	int findChildIndex(BTreeItem<T>* node, const T& key) {
		std::size_t i = 0;
		while (i < node->keys.size() && key > node->keys[i]) {
			++i;
		}
		return i;
	}

	// Merge the child node at index with its adjacent sibling
	void mergeNodes(BTreeItem<T>* parent, std::size_t index) {
		BTreeItem<T>* child = parent->children[index];
		BTreeItem<T>* sibling = parent->children[index + 1];

		// Move key from parent to child
		child->keys.push_back(parent->keys[index]);

		// Move keys and children from sibling to child
		for (std::size_t i = 0; i < sibling->keys.size(); ++i) {
			child->keys.push_back(sibling->keys[i]);
		}
		for (std::size_t i = 0; i < sibling->children.size(); ++i) {
			child->children.push_back(sibling->children[i]);
		}

		// Erase key and child pointer from parent
		parent->keys.erase(index);
		parent->children.erase(index + 1);

		// Delete the sibling node
		free(sibling); // WOOO BABYYYYY. THAT'S WHAT I'M TALKING ABOUT
		//							   - MoistKritical
	}

public:
	BTree(int _t) : root(nullptr), t(_t) {
		M = 2 * t + 1;
		MIN_KEYS = M / 2 - 1;
	}

	BTree(int _t, std::initializer_list<T> values) : root(nullptr), t(_t) {
		M = 2 * t + 1;
		MIN_KEYS = M / 2 - 1;

		for (const T& value : values) {
			insert(value);
		}
	}

	// Insert a key into the B-tree
	void insert(const T& key) {
		if (root == nullptr) {
			root = new BTreeItem<T>();
			root->keys.push_back(key);
		}
		else {
			if (root->keys.size() == M - 1) {
				BTreeItem<T>* new_root = new BTreeItem<T>();

				new_root->leaf = false;
				new_root->children.push_back(root);

				root = new_root;
				split(new_root, 0);
			}
			insert_non_full(root, key);
		}
	}

	// Search for a key in the B-tree
	bool search(const T& key) const {
		BTreeItem<T>* item = root;

		while (item != nullptr) {
			int i = 0;
			while (i < item->keys.size() && key > item->keys[i]) {
				i++;
			}
			if (i < item->keys.size() && key == item->keys[i]) {
				return true;
			}
			if (item->leaf) {
				break;
			}
			item = item->children[i];
		}

		return false;
	}

	// Remove a key from the B-tree
	void remove(const T& key) {
		if (root == nullptr)
			return; // B-tree is empty, nothing to remove

		// Search for the key in the B-tree
		BTreeItem<T>* node = root;
		int index;
		while (true) {
			index = findIndexInNode(node, key);
			if (index != -1) {
				break; // Key found in this node
			}
			else if (node->leaf) {
				return; // Key not found in leaf node
			}
			else {
				// Traverse to child node based on the key's position
				index = findChildIndex(node, key);
				node = node->children[index];
			}
		}

		// Key found, now remove it
		if (node->leaf) {
			// Key found in a leaf node, simply remove it
			node->keys.remove(index);
		}
		else {
			// Key found in an internal node, replace it with predecessor or successor
			if (node->children[index]->keys.size() >= MIN_KEYS) {
				// If the child containing the key has enough keys, replace it with predecessor
				BTreeItem<T>* predNode = node->children[index];
				while (!predNode->leaf) {
					predNode = predNode->children[predNode->keys.size()];
				}
				node->keys[index] = predNode->keys.back();
				remove(predNode->keys.back());
			}
			else if (node->children[index + 1]->keys.size() >= MIN_KEYS) {
				// If the next child has enough keys, replace it with successor
				BTreeItem<T>* succNode = node->children[index + 1]; // cOUldN'T yOU haVe nAMeD It beTteR? No. Succ it up, sissy b
				while (!succNode->leaf) {
					succNode = succNode->children[0];
				}
				node->keys[index] = succNode->keys.front();
				remove(succNode->keys.front());
			}
			else {
				// Merge child and its sibling, then remove key recursively
				mergeNodes(node, index);
				remove(key);
			}
		}
	}

	// Look ma!! No recursion!!!!
	void print() const {
		if (root == nullptr) {
			std::cout << "B-tree is empty" << std::endl;
			return;
		}

		Stack<std::pair<BTreeItem<T>*, int>> stack = Stack<std::pair<BTreeItem<T>*, int>>();
		stack.push({ root, 0 });

		while (!stack.empty()) {
			std::pair<BTreeItem<T>*, int> top = stack.top();
			BTreeItem<T>* item = top.first;
			int depth = top.second;
			stack.pop();

			for (int i = item->keys.size() - 1; i >= 0; i--) {
				if (!item->leaf) {
					stack.push({ item->children[i + 1], depth + 1 });
				}
				std::cout << std::string(depth, '-') << " " << item->keys[i] << std::endl;
			}

			if (!item->leaf) {
				stack.push({ item->children[0], depth + 1 });
			}
		}
	}
};

// NO!! You've 𝘎𝘖𝘛 to STOP DOING THIS, it's too much!!
class ExpressionTree {
private:
	TreeItem<std::string>* root;

	TreeItem<std::string>* createExpr(TreeItem<std::string>* node, std::string expr) {
		std::size_t opPos = std::string::npos;

		std::string ops = "(+-/*^";

		for (int i = 0; i < ops.size(); i++) {
			opPos = expr.find(ops[i]);

			if (opPos != std::string::npos)
				break;
		}

		if (opPos == std::string::npos) { // if expression is a simple integer, do not parse it, add it to the tree
			TreeItem<std::string>* item = new TreeItem<std::string>();

			item->value = expr;

			return item;
		}

		std::string left = expr.substr(0, opPos);
		std::string right = expr.substr(opPos + 1);

		if (expr[opPos] == '(') {
			std::size_t cpos = expr.find(')', expr.find('('));
			std::size_t tpos = expr.find(')', cpos + 1);

			while (tpos != std::string::npos) {
				cpos = tpos;
				tpos = expr.find(')', cpos + 1);
			}

			if (cpos != expr.size() - 1)
				return createOp(node, expr.substr(0, cpos + 1), expr.substr(cpos + 2), expr[cpos + 1]);

			left = expr.substr(0, opPos - 1);
			right = expr.substr(opPos + 1, cpos - opPos - 1);

			opPos--;
		}

		return createOp(node, left, right, expr[opPos]);
	}

	TreeItem<std::string>* createOp(TreeItem<std::string>* node, std::string left, std::string right, char op) {
		if (node == nullptr) {
			node = new TreeItem<std::string>();

			node->value = op;
		}

		node->left = createExpr(node->left, left);
		node->right = createExpr(node->right, right);

		return node;
	}

	double parse(TreeItem<std::string>* node) {
		double left;
		double right;

		try {
			left = std::stod(node->left->value);
		}
		catch (std::exception _) {
			left = parse(node->left);
		}

		try {
			right = std::stod(node->right->value);
		}
		catch (std::exception _) {
			right = parse(node->right);
		}

		switch (node->value[0])
		{
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '/':
			return left / right;
		case '*':
			return left * right;
		case '^':
			return pow(left, right);

		default:
			break;
		}
	}

public:
	ExpressionTree(std::string expr) {
		root = createExpr(root, expr);
	}

	double parse() {
		return parse(root);
	}
};

void getValue(int& value, std::string name) {
	std::cout << "Enter " << name << ": ";
	std::cin >> value;
}

int selectionMenu(std::string prompt, List<std::string> options) {
	int val;

	std::cout << prompt << std::endl;
	for (int i = 0; i < options.size(); i++) {
		printf("[%i] %s\n", i, options[i].c_str());
	}

	std::cout << "Your selection: ";
	std::cin >> val;

	while (val < 0 || val >= options.size()) {
		std::cout << "\nIncorrect selection, try again\nYour selection: ";
		std::cin >> val;
	}

	return val;
}

// Heh I made you look
// Now repost this to 3 other people in 2 hours 
// Or else you will be cursed with segfaults for the rest of your programming career