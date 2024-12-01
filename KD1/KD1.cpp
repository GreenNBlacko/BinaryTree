

#include <iostream>
#include "GrayStl.h"

using namespace std;

int main()
{
	switch (selectionMenu("Select which task to run", { "First", "Second", "Third" })) {
		case 0: {
			int n;

			List<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.push_back((a % 2 == 0 ? a * 2 : a));
			}

			cout << "\nResulting list:\n";
			list.display();
			break;
		}
			
		case 1: {
			int n, x;

			List<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.push_back(a);
			}

			int lastEven = -1;

			for (int i = 0; i < n; i++) {
				int value = list.at(i);

				int mod = value % 2;

				if (mod == 0)
					lastEven = i;
			}

			if (lastEven != -1) {
				getValue(x, "x");
				list.insert(lastEven, x);

				cout << "\nResulting list:\n";
				list.display();
			}
			break;
		}

		case 2: {
			int n;

			List<int> list{};

			getValue(n, "n");

			for (int i = 0; i < n; i++) {
				int a;

				getValue(a, "element " + to_string(i + 1));

				list.push_back(a);
			}

			int _min = 0, _max = 0;

			for (int i = 0; i < n; i++) {
				int element = list.at(i);
				int minElement = list.at(_min);
				int maxElement = list.at(_max);

				if (element > maxElement)
					_max = i;

				if (element < minElement)
					_min = i;
			}

			list.remove(_min);
			list.remove(_max);

			cout << "\nResulting list:\n";
			list.display();
			break;
		}
	}

	if (selectionMenu("Continue?", { "No", "Yes" }) == 1)
		main();
}
