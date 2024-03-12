

#include <iostream>
#include "GrayStl.h"

using namespace std;

int main()
{
	switch (selectionMenu("Select which task to run", new string[3]{ "First", "Second", "Third" }, 3)) {
		case 0: {
			int n;

			OneDirectionalList<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.insertAtEnd((a % 2 == 0 ? a * 2 : a));
			}

			cout << "\nResulting list:\n";
			list.display();
			break;
		}
			
		case 1: {
			int n, x;

			OneDirectionalList<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.insertAtEnd(a);
			}

			int lastEven = -1;

			for (int i = 0; i < n; i++) {
				int value = list.elementAt(i);

				int mod = value % 2;

				if (mod == 0)
					lastEven = i;
			}

			if (lastEven != -1) {
				getValue(x, "x");
				list.insertAt(lastEven, x);

				cout << "\nResulting list:\n";
				list.display();
			}
			break;
		}

		case 2: {
			int n;

			OneDirectionalList<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.insertAtEnd(a);
			}

			int _min = 0, _max = 0;

			for (int i = 0; i < n; i++) {
				int element = list.elementAt(i);
				int minElement = list.elementAt(_min);
				int maxElement = list.elementAt(_max);

				if (element > maxElement)
					_max = i;

				if (element < minElement)
					_min = i;
			}

			list.removeAt(_min);
			list.removeAt(_max);

			cout << "\nResulting list:\n";
			list.display();
			break;
		}
	}

	if (selectionMenu("Continue?", new string[2]{ "No", "Yes" }, 2) == 1)
		main();
}
