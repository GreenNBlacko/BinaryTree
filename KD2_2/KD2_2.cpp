#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

enum operations {
	Insert,
	Remove,
	Print,
	Search,
	Convert,
	Quit
};

int main() {
	List<int> firstList{};

	int val;

start:

	switch ((operations)selectionMenu("Select operation", new string[6]{ "Insert", "Remove", "Print", "Search", "Convert", "Quit" }, 6)) {
	case Insert:
		cout << endl;

		getValue(val, "value");

		switch (selectionMenu("Where do you want to insert", new string[4]{ "At start", "At end", "Before i", "After i" }, 4)) {
		case 0:
			firstList.push_front(val);
			break;

		case 1:
			firstList.push_back(val);
			break;

		case 2:
			int i;

			getValue(i, "i");

			firstList.insert(i - 1, val);
			break;

		case 3:
			getValue(i, "i");

			firstList.insert(i, val);
			break;
		}
		break;

	case Remove:
		cout << endl;

		switch (selectionMenu("Where do you want to remove", new string[2]{ "At start", "At i" }, 2)) {
			case 0:
				firstList.pop_front();
				break;

			case 2:
				int i;

				getValue(i, "i");

				firstList.remove(i);
				break;
		}
		break;

	case Print:
		cout << endl;

		firstList.display();
		break;

	case Search: {
		cout << endl;

		ListItem<int>* item = firstList.begin().node();

		switch (selectionMenu("How do you want to search", new string[4]{ "By index", "By value", "Max value", "Min Value" }, 4)) {
			case 0:
				int i;

				getValue(i, "i");

				item = (firstList.begin() + i).node();
				break;

			case 1:
				getValue(val, "value");

				item = (firstList.begin() + firstList.indexOf(val)).node();
				break;

			case 2:
				item = (firstList.begin() + firstList.indexOf(firstList.max())).node();
				break;

			case 3:
				item = (firstList.begin() + firstList.indexOf(firstList.min())).node();
				break;
		}

		cout << "\nValue: " << item->value
			<< "\nNext value: " << (item->nextValue != nullptr ? to_string(item->nextValue->value) : "None")
			<< endl;
		break;
	}

	case Convert: {
		cout << endl;

		BiList<int> secondList{};

		double avg = 0;

		for (int i = 0; i < firstList.size(); i++) {
			avg += firstList[i];
		}

		avg /= firstList.size();

		cout << "Average of all elements: " << avg << endl;

		int count = 0;

		for (int i = 0; i < firstList.size(); i++) {
			if (firstList[i] > avg) {
				secondList.push_back(firstList[i]);

				count++;
			}
		}

		cout << "Resulting list: " << endl;
		secondList.display();

		int pairs = 0;

		for (int i = 0; i < secondList.size() - 1; i++) {
			if ((secondList[i] * secondList[i + 1]) % 5 == 0)
				pairs++;
		}

		cout << "Number of pairs divisible by 5: " << pairs << endl;

		int lastValue = secondList[secondList.size() - 1];

		cout << "Last value of the bidirectional list: " << lastValue << endl;

		for (int i = 0; i < secondList.size(); i++) {
			int value = secondList[i];

			if (value >= lastValue)
				continue;

			secondList.remove(i);
			cout << "Removed " << value << endl;

			i--;
		}

		cout << "Resulting list:\n";
		secondList.display();
		break;
	}

	default:
		return 0;
	}

	cout << endl;

	goto start;
}
