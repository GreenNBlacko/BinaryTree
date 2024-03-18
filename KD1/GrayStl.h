#pragma once

#include <string>
#include <iostream>

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
struct BidirectionalListItem {
	T value;
	BidirectionalListItem<T>* prevValue;
	BidirectionalListItem<T>* nextValue;
};

template <typename T>
struct OneDirectionalListItem {
	T value;
	OneDirectionalListItem<T>* nextValue;
};

template <typename T>
struct OneDirectionalListItem_iter {
	OneDirectionalListItem<T>* current;
	OneDirectionalListItem_iter(OneDirectionalListItem<T>* current) : current(current) {}

	const OneDirectionalListItem_iter& operator++() { current = current->nextValue; return *this; }
	OneDirectionalListItem_iter operator++(int) {
		OneDirectionalListItem_iter result = *this; ++(*this); return result;
	}

	OneDirectionalListItem_iter& operator+(int const& right) { 
		for (int i = 0; i < right && current != nullptr; i++) {
			current = current->nextValue; 
		} 

		return *this; 
	}

	OneDirectionalListItem<T>* operator*() { return current; }
};

template <typename T>
struct BidirectionalListItem_iter {
	BidirectionalListItem<T>* current;
	BidirectionalListItem_iter(BidirectionalListItem<T>* current) : current(current) {}

	const BidirectionalListItem_iter& operator++() { current = current->nextValue; return *this; }
	BidirectionalListItem_iter operator++(int) {
		BidirectionalListItem_iter result = *this; ++(*this); return result;
	}

	BidirectionalListItem_iter<T> operator+(int const& right) {
		for (int i = 0; i < right && current != nullptr; i++) { 
			current = current->nextValue; 
		} 

		return *this; 
	}

	const BidirectionalListItem_iter& operator--() { current = current->prevValue; return *this; }
	BidirectionalListItem_iter operator--(int) {
		BidirectionalListItem_iter result = *this; --(*this); return result;
	}

	BidirectionalListItem_iter<T> operator-(int const& right) {
		for (int i = 0; i < right && current != nullptr; i++) { 
			current = current->prevValue; 
		} 

		return *this; 
	}

	BidirectionalListItem<T>* operator*() { return current; }
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
		return 0;
	}
};

template<> static int Compare<int>::compare(int val1, int val2) {
	return (val1 == val2 ? 0 :
		(val1 > val2 ? -1 : 1));
}

template<> static int Compare<char>::compare(char val1, char val2) {
	return (val1 == val2 ? 0 :
		(val1 > val2 ? -1 : 1));
}

template<> static int Compare<double>::compare(double val1, double val2) {
	return (val1 == val2 ? 0 :
		(val1 > val2 ? -1 : 1));
}

template<> static int Compare<float>::compare(float val1, float val2) {
	return (val1 == val2 ? 0 :
		(val1 > val2 ? -1 : 1));
}

template<> static int Compare<std::string>::compare(std::string val1, std::string val2) {
	return val1.compare(val2);
}

template <typename T>
class OneDirectionalList {
public:
	OneDirectionalListItem<T>* start = nullptr;
	OneDirectionalListItem<T>* stop = nullptr;

	OneDirectionalListItem_iter<T> begin()	{ return OneDirectionalListItem_iter<T>(start); }
	OneDirectionalListItem_iter<T> end()	{ return OneDirectionalListItem_iter<T>(stop);	}

	T elementAt(int index) {
		OneDirectionalListItem<T>* current = start;

		if (current == nullptr)
			throw "Index out of bounds";

		for (int i = 0; i < index; i++) {
			current = current->nextValue;

			if (current == nullptr)
				throw "Index out of bounds";
		}

		return current->value;
	}

	void insertAtStart(T value) {
		OneDirectionalListItem<T>* newValue = new OneDirectionalListItem<T>();

		newValue->value = value;
		newValue->nextValue = start;
		start = newValue;


		start = newValue;
		if (stop == nullptr)
			stop = newValue;
	}

	void insertAt(int index, T value) {
		OneDirectionalListItem<T>* current = start;

		if (current == nullptr)
			throw "Index out of bounds";

		for (int i = 0; i < index; i++) {
			current = current->nextValue;

			if (current == nullptr)
				throw "Index out of bounds";
		}

		if (current == start) {
			insertAtStart(value);
			return;
		}
		else if (current == stop) {
			insertAtEnd(value);
			return;
		}

		OneDirectionalListItem<T>* newItem = new OneDirectionalListItem<T>();

		newItem->value = value;
		newItem->nextValue = current->nextValue;
		current->nextValue = newItem;
	}

	void insertAtEnd(T value) {
		OneDirectionalListItem<T>* newValue = new OneDirectionalListItem<T>();

		newValue->value = value;
		if (stop != nullptr) stop->nextValue = newValue;

		if (start == nullptr)
			start = newValue;
		stop = newValue;
	}

	void removeFromStart() {
		if (start == nullptr)
			return;

		OneDirectionalListItem<T>* old = start;

		start = old->nextValue;

		free(old);
	}

	void removeAt(int index) {
		OneDirectionalListItem<T>* current = start;

		if (current == nullptr)
			throw "Index out of bounds";

		for (int i = 0; i < index - 2; i++) {
			current = current->nextValue;

			if (current == nullptr)
				throw "Index out of bounds";
		}

		if (current == start) {
			removeFromStart();

			return;
		}

		if (current->nextValue == stop) {
			stop = current;
		}

		OneDirectionalListItem<T>* temp = current->nextValue;
		current->nextValue = temp->nextValue;

		free(temp);
	}

	void display() {
		OneDirectionalListItem_iter<T> current = begin();

		while (*current != nullptr) {
			std::cout << *current->value << " ";
			current++;
		}

		std::cout << std::endl;
	}
};

template <typename T>
class CyclicList {
private: 
	OneDirectionalList<T> list{};


public:
	OneDirectionalListItem_iter<T> begin() { return list.begin(); }
	OneDirectionalListItem_iter<T> end() { return list.end(); }

	T elementAt(int index) {
		return list.elementAt(index);
	}

	void insertAtStart(T value) {
		list.insertAtStart(value);

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void insertAt(int index, T value) {
		list.insertAt(index, value);
	}

	void insertAtEnd(T value) {
		list.insertAtEnd(value);

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void removeFromStart() {
		list.removeFromStart();

		if (list.stop != nullptr)
			list.stop->nextValue = list.start;
	}

	void removeAt(int index) {
		list.removeAt(index);
	}

	void display() {
		OneDirectionalListItem_iter<T> current = begin();

		while (*current != list.stop) {
			std::cout << (*current)->value << " ";
			current++;
		}

		std::cout << (*current)->value << " ";

		std::cout << std::endl;
	}
};

template <typename T>
class Stack {
	OneDirectionalListItem<T>* head;

	void push(T value) {
		OneDirectionalListItem<T>* newValue = new OneDirectionalListItem<T>();

		newValue->value = value;
		newValue->nextValue = head;
		head = newValue;
	}

	T pop() {
		if (head == nullptr)
			throw "Stack is empty";

		OneDirectionalListItem<T>* old = head;
		T value = old->value;

		head = old->nextValue;

		free(old);

		return value;
	}

	void display() {
		OneDirectionalListItem<T>* current = head;

		while (current != nullptr) {
			std::cout << current->value << " ";
			current = current->nextValue;
		}

		std::cout << std::endl;
	}
};

template <typename T>
class Queue {
public:
	OneDirectionalListItem<T>* start;
	OneDirectionalListItem<T>* end;
	int size;

	void InsertValue(T value) {
		OneDirectionalListItem<T>* newValue = new OneDirectionalListItem<T>();

		newValue->value = value;
		if (end != nullptr) end->nextValue = newValue;

		if (size == 0)
			start = newValue;
		end = newValue;

		size++;
	}

	T ShiftValue() {
		if (size == 0)
			return "";

		OneDirectionalListItem<T>* old = start;
		T value = old->value;

		start = old->nextValue;

		free(old);

		size--;

		return value;
	}

	void display() {
		OneDirectionalListItem<T>* current = start;

		while (current != nullptr) {
			std::cout << current->value << " ";
			current = current->nextValue;
		}

		std::cout << std::endl;
	}
};

template <typename T>
class BidirectionalList {
	BidirectionalListItem<T>* start = nullptr;
	BidirectionalListItem<T>* stop = nullptr;

public:
	BidirectionalListItem_iter<T> begin() { return BidirectionalListItem_iter<T>(start); }
	BidirectionalListItem_iter<T> end() { return BidirectionalListItem_iter<T>(stop); }

	void InsertIntoStart(T value) {
		BidirectionalListItem<T>* newValue = CreateElement(value);

		if (start == nullptr) {
			start = stop = newValue;
			return;
		}

		newValue->nextValue = start;
		start->prevValue = newValue;
		start = newValue;
	}

	void insertAt(int index, T value) {
		BidirectionalListItem_iter<T> it = begin();

		if (*it == nullptr)
			throw "Index out of bounds";

		for (int i = 0; i < index; i++) {
			it++;

			if (*it == nullptr)
				throw "Index out of bounds";
		}

		if (*it == start) {
			InsertIntoStart(value);
			return;
		}
		else if (*it == stop) {
			InsertIntoEnd(value);
			return;
		}

		BidirectionalListItem<T>* current = *it;
		BidirectionalListItem<T>* newItem = new BidirectionalListItem<T>();

		newItem->value = value;
		newItem->nextValue = current->nextValue;
		newItem->prevValue = current;
		current->nextValue->prevValue = newItem;
		current->nextValue = newItem;
	}

	void InsertIntoEnd(T value) {
		BidirectionalListItem<T>* newValue = CreateElement(value);

		if (stop == nullptr) {
			start = stop = newValue;
			return;
		}

		newValue->prevValue = stop;
		stop->nextValue = newValue;
		stop = newValue;
	}

	void RemoveFromStart() {
		if (start == nullptr)
			throw "List is empty";

		BidirectionalListItem<T>* old = start;

		start = old->nextValue;
		start->prevValue = nullptr;

		free(old);
	}

	void RemoveAt(int index) {
		BidirectionalListItem<T>* current = elementAt(index);

		current->prevValue->nextValue = current->nextValue;
		current->nextValue->prevValue = current->prevValue;

		free(current);
	}

	void RemoveFromEnd() {
		if (stop == nullptr)
			throw "List is empty";

		BidirectionalListItem<T>* old = stop->prevValue;

		stop = old->prevValue;
		stop->nextValue = nullptr;

		free(old);
	}

	BidirectionalListItem<T>* elementAt(int index) {
		return *(begin() + index);
	}

	BidirectionalListItem<T>* findElement(T value) {
		BidirectionalListItem_iter<T> current = begin();

		while (*current != nullptr && (*current)->value != value)
			current++;

		return *current;
	}

	void display() {
		for (BidirectionalListItem_iter<T> it = begin(); *it != nullptr; it++) {
			std::cout << (*it)->value << " ";
		}

		std::cout << std::endl;
	}

private:
	BidirectionalListItem<T>* CreateElement(T value) {
		BidirectionalListItem<T>* item = new BidirectionalListItem<T>();

		item->value = value;

		item->nextValue = item->prevValue = nullptr;

		return item;
	}
};

template <typename T>
class DeQueue {
public:
	DeQueue() {
		begin = CreateElement(NULL);
		stop = CreateElement(NULL);

		begin->nextValue = stop;
		stop->prevValue = begin;
	}

	BidirectionalListItem<T>* begin;
	BidirectionalListItem<T>* stop;

	void InsertIntoStart(T value) {
		BidirectionalListItem<T>* newValue = CreateElement(value);

		newValue->nextValue = begin->nextValue;
		newValue->prevValue = begin;
		begin->nextValue->prevValue = newValue;
		begin->nextValue = newValue;
	}

	void InsertIntoEnd(T value) {
		BidirectionalListItem<T>* newValue = CreateElement(value);

		newValue->prevValue = stop->prevValue;
		newValue->nextValue = stop;
		stop->prevValue->nextValue = newValue;
		stop->prevValue = newValue;
	}

	T ShiftFromStart() {
		if (begin->nextValue == stop)
			return "";

		BidirectionalListItem<T>* old = begin->nextValue;
		T value = old->value;

		begin->nextValue = old->nextValue;
		begin->nextValue->prevValue = begin;

		free(old);

		return value;
	}

	T ShiftFromEnd() {
		if (stop->prevValue == begin)
			return NULL;

		BidirectionalListItem<T>* old = stop->prevValue;
		T value = old->value;

		stop->prevValue = old->prevValue;
		stop->prevValue->nextValue = stop;

		free(old);

		return value;
	}

	void display() {
		BidirectionalListItem<T>* current = begin;

		while (current->nextValue != stop) {
			current = current->nextValue;
			std::cout << current->value << std::endl;
		}
	}

private:
	BidirectionalListItem<T>* CreateElement(T value) {
		BidirectionalListItem<T>* item = new BidirectionalListItem<T>();

		item->value = value;

		item->nextValue = item->prevValue = nullptr;

		return item;
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