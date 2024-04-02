#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

enum operations {
	Insert,
	Remove,
	Print,
	Search,
	AddToStackFromMax,
	AddToStackUntilNegative,
	Quit
};

int main() {
	CyclicList<int> cyclicList = CyclicList<int>();
	Stack<int> stack = Stack<int>();

	int val;

start:

	switch ((operations)selectionMenu("Select operation", new string[7]{ "Insert", "Remove", "Print", "Search", "Add to stack from max", "Add to stack upto first negative", "Quit"}, 7)) {
	case Insert:
		cout << endl;

		getValue(val, "value");

		switch (selectionMenu("Where do you want to insert", new string[4]{ "At start", "At end", "Before i", "After i"}, 4)) {
			case 0:
				cyclicList.push_front(val);
				break;

			case 1:
				cyclicList.push_back(val);
				break;

			case 2:
				int i;

				getValue(i, "i");

				cyclicList.insert(i - 1, val);
				break;

			case 3:
				getValue(i, "i");

				cyclicList.insert(i, val);
				break;
		}
		break;

	case Remove:
		cout << endl;

		switch (selectionMenu("Where do you want to remove", new string[2]{ "At start", "At i" }, 2)) {
		case 0:
			cyclicList.pop_front();
			break;

		case 2:
			int i;

			getValue(i, "i");

			cyclicList.remove(i);
			break;
		}
		break;

	case Print:
		cout << endl;

		if (stack.empty()) {
			cout << "Stack is empty\n";
			break;
		}

		while (!stack.empty()) {
			int el = stack.pop();

			cout << el << " ";
		}
		cout << endl;
		break;

	case Search: {
		cout << endl;

		ListItem<int>* item = cyclicList.begin().node();

		switch (selectionMenu("How do you want to search", new string[4]{ "By index", "By value", "Max value", "Min Value"}, 4)) {
			case 0:
				int i;

				getValue(i, "i");

				item = (cyclicList.begin() + i).node();
				break;

			case 1:
				getValue(val, "value");

				item = (cyclicList.begin() + cyclicList.indexOf(val)).node();
				break;

			case 2:
				item = (cyclicList.begin() + cyclicList.indexOf(cyclicList.max())).node();
				break;

			case 3:
				item = (cyclicList.begin() + cyclicList.indexOf(cyclicList.min())).node();
				break;
		}

		cout << "\nValue: " << item->value
			<< "\nNext value: " << (item->nextValue != nullptr ? to_string(item->nextValue->value) : "None")
			<< endl;
		break;
	}

	case AddToStackFromMax: {
		cout << endl;

		for (int i = cyclicList.indexOf(cyclicList.max()); i < cyclicList.size(); i++)
			stack.push(cyclicList[i]);
		break;
	}

	case AddToStackUntilNegative: {
		cout << endl;

		for (int i = 0; i < cyclicList.size() && cyclicList[i] > -1; i++) {
			stack.push(cyclicList[i]);
			cyclicList.remove(i);
			i--;
		}
		break;
	}

	default:
		return 0;
	}

	cout << endl;

	goto start;
}