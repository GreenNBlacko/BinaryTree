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
	BidirectionalList<int> firstList{};

	int val;

	start:

	switch ((operations)selectionMenu("Select operation", new string[6]{ "Insert", "Remove", "Print", "Search", "Convert", "Quit"}, 6)) {
		case Insert:
			cout << endl;

			getValue(val, "value");

			switch (selectionMenu("Where do you want to insert", new string[3]{ "At start", "At end", "At i" }, 3)) {
				case 0:
					firstList.InsertIntoStart(val);
					break;

				case 1:
					firstList.InsertIntoEnd(val);
					break;

				case 2:
					int i;

					getValue(i, "i");

					firstList.insertAt(i, val);
					break;
			}
			break;

		case Remove:
			cout << endl;

			switch (selectionMenu("Where do you want to remove", new string[3]{ "At start", "At end", "At i" }, 3)) {
			case 0:
				firstList.RemoveFromStart();
				break;

			case 1:
				firstList.RemoveFromEnd();
				break;

			case 2:
				int i;

				getValue(i, "i");

				firstList.RemoveAt(i);
				break;
			}
			break;

		case Print:
			cout << endl;

			firstList.display();
			break;

		case Search: {
			cout << endl;

			BidirectionalListItem<int>* item = *firstList.begin();

			switch (selectionMenu("How do you want to search", new string[2]{ "By index", "By value" }, 2)) {
			case 0:
				int i;

				getValue(i, "i");

				item = firstList.elementAt(i);
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

			for (BidirectionalListItem_iter<int> it = firstList.begin(); *it != nullptr; it++) {
				secondList.insertAtEnd((*it)->value);
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