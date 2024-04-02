#pragma once

#include <string>
#include <iostream>
#include <cstddef>

void getValue(int& value, std::string name) {
	std::cout << "Enter " << name << ": ";
	std::cin >> value;
}

int selectionMenu(std::string prompt, std::string* options, int size) {
	int val;

	std::cout << prompt << std::endl;
	for (int i = 0; i < size; i++) {
		printf("[%i] %s\n", i, options[i].c_str());
	}

	std::cout << "Your selection: ";
	std::cin >> val;

	while (val < 0 || val >= size) {
		std::cout << "\nIncorrect selection, try again\nYour selection: ";
		std::cin >> val;
	}

	return val;
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
		return current == *right;
	}

	bool operator==(List_iter<T>* right) {
		return current == right;
	}

	bool operator!=(List_iter<T> right) {
		return !(this == right);
	}

	bool operator!=(List_iter<T>* right) {
		return !(this == right);
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
		return !(this == right);
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

// ------------------- TYPE DECLARATIONS ------------------- \\

template<typename T>
class Sortable;

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
class DeQueue;

// ------------------- TYPE DECLARATIONS ------------------- \\

template<typename T>
class Sortable {
public:
	virtual std::size_t size() = 0;

	virtual T& operator[](int index) = 0;

	void insertionSort() {
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

	void mergeSort() {
		bool set = false;

		for (int i = 0; i < size(); i++) { // dumb check, if array is sorted, no need to sort it again, save processing power
			if (i == size() - 1 && !set) // if we've gone through the whole array and not found a single issue, no need to sort, exit out of the function
				return;

			if (Compare<T>::compare((*this)[i], (*this)[i + 1]) == -1) // if an element is found out of place, commence setting the flag
				set = true;

			if (set) // if flag is set, stop the loop and proceed with sorting the list
				break;
		}

		List<List<T>> split;
		split.assign(1, List<T>(size(), 0)); // initializing the split list

		for (int i = 0; i < size(); i++) {
			split[0][i] = (*this)[i];
		}

		for (int n = (*this).size() / 2; n >= 1; n /= 2) { // incrementally increasing the number of split elements
			int subSplitSize = (*this).size() / n;

			List<List<T>> newSplit;
			for (int i = 0; i < n; i++)
				newSplit.push_back(List<T>(subSplitSize, T()));

			for (int i = 0; i < n; i++) {
				int lastLowest = -1; // by default when the cycle begins, there is no last lowest element

				for (int o = 0; o < subSplitSize; o++) {
					int currentLowest = subSplitSize * i;

					for (int p = i * subSplitSize; p < (subSplitSize + subSplitSize * i) % ((i + 1) * subSplitSize + 1); p++) { // find the smallest element to put into the position
						if (p == lastLowest || p == currentLowest) // skip the value if it has already been used or is currently contending to be used
							continue;

						// the reason for different lists is we cannot be sure of which list the element will be in, and not figuring that out could lead to garbage in garbage out
						int currentLowestList = (currentLowest / split[0].size());
						int lastLowestList = lastLowest != -1 ? (lastLowest / split[0].size()) : 0;
						int list = (p / split[0].size());

						// store the values to compact down the if statement below
						T currentLowestVal = split[currentLowestList][currentLowest % split[0].size()];
						T lastLowestVal = split[lastLowestList][lastLowest % split[0].size()];
						T currentVal = split[list][p % split[0].size()];
						T lastVal = o > 0 ? newSplit[i][o - 1] : NULL; // if it's the first element in the sub split, there is no last value, therefor attributed to null

						if (currentVal == lastVal) { // print repeating values
							split[lastLowestList][lastLowest % split[0].size()] = newSplit[0][0];

							currentLowest = p;

							break;
						}

						// if the last lowest element exists and is bigger or equal to the current lowest or the current value is less than the current lowest value
						// and it is currently trying to insert into the first sub split element or the current value is more or equal to the last value 
						if ((lastLowest != -1 && currentLowestVal <= lastLowestVal || currentVal < currentLowestVal) && (o == 0 || currentVal >= lastVal))
							currentLowest = p; // set the lowest element to the current element																									   
					}

					int insertList = (currentLowest / split[0].size()); // get the list which to insert from 

					newSplit[i][o] = split[insertList][currentLowest % split[0].size()]; // insert the value into the new sub split

					lastLowest = currentLowest; // set the current lowest value to the last for the next cycle
				}
			}

			split = newSplit; // assign the just created split to be merged further
		}

		for (int i = 0; i < size(); i++) {
			(*this)[i] = split[0][i];
		}
	}

	void quicksort() {
		quicksort(0, size() - 1);
	}

	void quicksort(int low, int high) {
		if (low < high) {
			int pi = partition(low, high);

			quicksort(low, pi - 1);
			quicksort(pi + 1, high);
		}
	}

private:
	int partition(int low, int high) {
		T pivot = (*this)[high]; // Choose the last element as the pivot
		int i = low - 1; // Index of the smaller element

		for (int j = low; j < high; j++) {
			if ((*this)[j] < pivot) {
				i++;
				T temp = (*this)[i];
				(*this)[i] = (*this)[j];
				(*this)[j] = temp;
			}
		}

		T temp = (*this)[i + 1];
		(*this)[i + 1] = (*this)[high];
		(*this)[high] = temp;
		return i + 1;
	}
};

template <typename T>
class List : public Sortable<T> {
	std::size_t _size = 0;

public:
	ListItem<T>* start = nullptr;
	ListItem<T>* stop = nullptr;

	List() {
		_size = 0;
	}

	List(int capacity) {
		assign(capacity, T());
	}

	List(int capacity, T value) {
		assign(capacity, value);
	}

	bool empty() const { return _size == 0; }

	virtual std::size_t size() override { return _size; }

	List_iter<T> begin() { return List_iter<T>(start); }
	List_iter<T> end() { return List_iter<T>(stop); }

	T elementAt(int index) {
		if (empty())
			throw std::out_of_range("Index out of bounds");

		ListItem<T>* current = start;

		for (int i = 0; i < index; i++) {
			current = current->nextValue;

			if (current == nullptr)
				throw std::out_of_range("Index out of bounds");
		}

		return current->value;
	}

	int indexOf(T value) {
		int i = 0;

		for (i = 0; i < _size && (*this)[i] != value; i++) {}

		if ((*this)[i] != value)
			return -1;

		return i;
	}

	T max() {
		if (empty())
			throw std::out_of_range("List is empty");

		T maxValue = (*this)[0];

		for (int i = 1; i < _size; i++) {
			maxValue = (Compare<T>::compare(maxValue, (*this)[i]) == -1 ? maxValue : (*this)[i]);
		}

		return maxValue;
	}

	T min() {
		if (empty())
			throw std::out_of_range("List is empty");

		T minValue = (*this)[0];

		for (int i = 1; i < _size; i++) {
			minValue = (Compare<T>::compare(minValue, (*this)[i]) == 1 ? minValue : (*this)[i]);
		}

		return minValue;
	}

	void push_front(T value) {
		ListItem<T>* newValue = new ListItem<T>(value);

		newValue->nextValue = start;
		start = newValue;


		start = newValue;
		if (stop == nullptr)
			stop = newValue;

		_size++;
	}

	void insert(int index, T value) {
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
		if (empty())
			throw std::out_of_range("List is empty");

		ListItem<T>* old = start;

		start = old->nextValue;

		free(old);

		_size--;
	}

	void remove(int index) {
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

	void display() {
		for (int i = 0; i < _size; i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	void clear() {
		while (!empty())
			pop_front();
	}

	virtual T& operator[](int index) override {
		ListItem<T>* temp = start;
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
class CyclicList : public Sortable<T> {
private:
	List<T> list = List<T>();


public:
	CyclicList() {
		list = List<T>(0);
	}

	CyclicList(int capacity) {
		list = List<T>(capacity);
	}

	CyclicList(int capacity, T value) {
		list = List<T>(capacity, value);
	}

	bool empty() const { return list.empty(); }

	virtual std::size_t size() override { return list.size(); }

	List_iter<T> begin() { return list.begin(); }
	List_iter<T> end() { return list.end(); }

	int indexOf(T value) {
		return list.indexOf(value);
	}

	T elementAt(int index) {
		return list.elementAt(index);
	}

	void push_front(T value) {
		list.push_front(value);

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void insert(int index, T value) {
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

	void remove(int index) {
		list.remove(index);
	}

	T max() {
		return list.max();
	}

	T min() {
		return list.min();
	}

	void display() {
		return list.display();
	}

	void display(int startIndex) {
		for (int i = startIndex; i < size(); i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	void clear() {
		while (!empty())
			pop_front();
	}

	virtual Sortable<T> copy() override {
		CyclicList<T> t = CyclicList<T>();

		for (int i = 0; i < size(); i++) {
			t.push_back(std::move(list[i]));
		}

		return t;
	}

	virtual T& operator[](int index) override {
		return list[index];
	}
};

template <typename T>
class Stack : public Sortable<T> {
	std::size_t _size = 0;

public:
	ListItem<T>* _head;

	Stack() {
		_size = 0;
	}

	Stack(int capacity) {
		_size = 0;

		for (int i = 0; i < capacity; i++)
			push(T());
	}

	Stack(int capacity, T value) {
		assign(capacity, value);
	}

	List_iter<T> head() { return List_iter<T>(_head); }

	bool empty() const { return _size == 0; }

	virtual std::size_t size() override { return _size; }

	void push(T value) {
		ListItem<T>* newValue = new ListItem<T>(value);

		if (_head != nullptr)
			newValue->nextValue = _head;
		_head = newValue;

		_size++;
	}

	T pop() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		ListItem<T>* old = _head;
		T value = old->value;

		_head = old->nextValue;

		free(old);

		_size--;

		return value;
	}

	void display() {
		for (int i = 0; i < _size; i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push(std::move(value));
	}

	void clear() {
		while (!empty())
			pop();
	}

	virtual T& operator[](int index) override {
		ListItem<T>* temp = _head;
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
class Queue : public Sortable<T> {
	std::size_t _size;

public:
	ListItem<T>* start;
	ListItem<T>* stop;

	Queue() {
		_size = 0;
	}

	Queue(int capacity) {
		for (int i = 0; i < capacity; i++)
			push(T());
	}

	Queue(int capacity, T value) {
		assign(capacity, value);
	}

	List_iter<T> begin() { return List_iter<T>(start); }
	List_iter<T> end() { return List_iter<T>(stop); }

	bool empty() const { return _size == 0; }

	virtual std::size_t size() override { return _size; }

	void push(T value) {
		ListItem<T>* newValue = new ListItem<T>();

		newValue->value = value;
		if (end != nullptr) end->nextValue = newValue;

		if (empty())
			start = newValue;
		end = newValue;

		_size++;
	}

	T shift() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		ListItem<T>* old = start;
		T value = old->value;

		start = old->nextValue;

		free(old);

		_size--;

		return value;
	}

	void display() {
		for (int i = 0; i < _size; i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push(std::move(value));
	}

	void clear() {
		while (!empty())
			shift();
	}

	virtual T& operator[](int index) override {
		ListItem<T>* temp = start;
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
class BiList : public Sortable<T> {
	BiListItem<T>* start = nullptr;
	BiListItem<T>* stop = nullptr;

	std::size_t _size = 0;

public:
	BiList() {
		_size = 0;
	}

	BiList(int capacity) {
		for (int i = 0; i < capacity; i++)
			push_back(T());
	}

	BiList(int capacity, T value) {
		assign(capacity, value);
	}

	bool empty() const { return _size == 0; }

	virtual std::size_t size() override { return _size; }

	BiList_iter<T> begin() { return BiList_iter<T>(start); }
	BiList_iter<T> end() { return BiList_iter<T>(stop); }

	int indexOf(T value) {
		if (empty())
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

			_size++;

			return;
		}

		newValue->nextValue = start;
		start->prevValue = newValue;
		start = newValue;

		_size++;
	}

	void insert(int index, T value) {
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
		if (empty())
			throw std::out_of_range("List is empty");

		BiListItem<T>* old = start;

		start = old->nextValue;
		start->prevValue = nullptr;

		free(old);

		_size--;
	}

	void remove(int index) {
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
		if (empty())
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

	void display() {
		for (int i = 0; i < _size; i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	void clear() {
		while (!empty())
			pop_front();
	}

	virtual T& operator[](int index) override {
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
class DeQueue : public Sortable<T> {
	std::size_t _size = 0;

public:
	DeQueue() {
		_size = 0;
	}

	DeQueue(int capacity) {
		for (int i = 0; i < capacity; i++)
			push(T());
	}

	DeQueue(int capacity, T value) {
		assign(capacity, value);
	}

	BiListItem<T>* start;
	BiListItem<T>* stop;

	bool empty() const { return _size == 0; }

	virtual std::size_t size() override { return _size; }

	BiList_iter<T> begin() { return BiList_iter<T>(start); }
	BiList_iter<T> end() { return BiList_iter<T>(stop); }

	void push_front(T value) {
		BiListItem<T>* newValue = new BiListItem<T>(value);

		if (empty()) {
			start = stop = newValue;

			_size++;

			return;
		}

		newValue->nextValue = start;
		start->prevValue = newValue;
		start = newValue;

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

	T shift_front() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		BiListItem<T>* old = start->nextValue;
		T value = old->value;

		start = start->next;
		if (start != nullptr)
			start->prevValue = nullptr;
		else
			stop = nullptr;

		_size--;

		free(old);

		return value;
	}

	T shift_back() {
		if (empty())
			throw std::out_of_range("Deque is empty");

		BiListItem<T>* old = stop;
		T value = old->value;

		stop = stop->prevValue;
		if (stop != nullptr)
			stop->nextValue = nullptr;
		else
			stop = nullptr;

		_size--;

		free(old);

		return value;
	}

	void display() {
		for (int i = 0; i < _size; i++)
			std::cout << (*this)[i] << " ";

		std::cout << std::endl;
	}

	void assign(int capacity, T value) {
		for (int i = 0; i < capacity; i++)
			push_back(std::move(value));
	}

	void clear() {
		while (!empty())
			shift_front();
	}

	virtual T& operator[](int index) override {
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
class BinaryTree {
public:
	TreeItem<T>* root;

	TreeItem<T>* insertItem(T value) {
		TreeItem<T>* newItem = new TreeItem<T>();
		newItem->value = value;

		// assign value to the root if tree is empty
		if (root == nullptr) {
			root = newItem;

			return newItem;
		}

		TreeItem<T>* current = root;

		while (current != newItem) {
			if (Compare<T>::compare(newItem->value, current->value) == 1) {
				if (current->left == nullptr) {
					current->left = newItem;
				}

				current = current->left;
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
		TreeItem<T>* item = findItem(value);

		TreeItem<T>* replaceWith = item->left;
		if (replaceWith->right != nullptr) {
			while (replaceWith->right->right != nullptr) {
				replaceWith = replaceWith->right;
			}

			if (replaceWith->right->left != nullptr) {
				TreeItem<T>* temp = replaceWith->right;

				replaceWith->right = temp->left;

				replaceWith = temp;
			}
		}

		item->value = replaceWith->value;

		free(replaceWith);
	}

	void display() {
		display(root);
	}

private:
	void display(TreeItem<T>* node) {
		if (node == nullptr)
			return;

		display(node->left);
		std::cout << node->value << " ";
		display(node->right);
	}
};

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

		// now the painful part

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

class Math {
private:
	TreeItem<std::string>* root;

	TreeItem<std::string>* createExpr(TreeItem<std::string>* node, std::string expr) {
		std::size_t opPos = std::string::npos;

		for (int i = 0; i < 5; i++) {
			opPos = expr.find("+-/*^"[i]);

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
		int left;
		int right;

		try {
			left = std::stoi(node->left->value);
		} catch (std::exception _) {
			left = parse(node->left);
		}

		try {
			right = std::stoi(node->right->value);
		} catch (std::exception _) {
			right = parse(node->right);
		}

		switch (node->value[0])
		{
		case '+':
			return (double)left + (double)right;
		case '-':
			return (double)left - (double)right;
		case '/':
			return (double)left / (double)right;
		case '*':
			return (double)left * (double)right;
		case '^':
			return std::pow((double)left, (double)right);

		default:
			break;
		}
	}

public:
	Math(std::string expr) {
		root = createExpr(root, expr);
	}

	int parse() {
		return parse(root);
	}
};