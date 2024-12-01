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
	BiList<int> firstList{};

	int val;

	start:

	switch ((operations)selectionMenu("Select operation", { "Insert", "Remove", "Print", "Search", "Convert", "Quit"})) {
		case Insert:
			cout << endl;

			getValue(val, "value");

			switch (selectionMenu("Where do you want to insert", { "At start", "At end", "At i" })) {
				case 0:
					firstList.push_front(val);
					break;

				case 1:
					firstList.push_back(val);
					break;

				case 2:
					int i;

					getValue(i, "i");

					firstList.insert(i, val);
					break;
			}
			break;

		case Remove:
			cout << endl;

			switch (selectionMenu("Where do you want to remove", { "At start", "At end", "At i" })) {
			case 0:
				firstList.pop_front();
				break;

			case 1:
				firstList.pop_back();
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

			BiListItem<int>* item = firstList.begin().node();

			switch (selectionMenu("How do you want to search", { "By index", "By value" })) {
			case 0:
				int i;

				getValue(i, "i");

				item = (firstList.begin() + i).node();
				break;

			case 1:
				getValue(val, "value");

				item = firstList.findElement(val);
				break;
			}

			cout << "\nValue: " << item->value
				 << "\nPrevious value: " << (item->prevValue != nullptr ? to_string(item->prevValue->value) : "None")
				 << "\nNext value: " << (item->nextValue != nullptr ? to_string(item->nextValue->value) : "None")
				 << endl;
			break;
		}

		case Convert: {
			cout << endl;

			CyclicList<int> secondList{};

			for (int i = 0; i < firstList.size(); i++) {
				secondList.push_back(firstList[i]);
			}

			cout << "Converted list:\n";
			secondList.display();
			break;
		}

		default:
			return 0;
	}

	cout << endl;

	goto start;
}