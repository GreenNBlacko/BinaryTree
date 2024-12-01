#include <iostream>
#include "GrayStl.h"

using namespace std;

enum operations {
	Insert,
	Remove,
	Max,
	a,
	b,
	c,
	Display,
	Quit
};

enum insertOps {
	insertAtStart,
	insertBefore_i,
	insertAfter_i,
	insertAtEnd
};

enum removeOps {
	removeAtStart,
	removeAt_i,
	removeAtEnd
};

int main() {
	BiCyclicList<int> list = BiCyclicList<int>();
	CyclicList<int> secondList = CyclicList<int>();

resume:
	switch ((operations)selectionMenu("Select operation", { "Insert", "Remove", "Find max", "Task a", "Task b", "Task c", "Display", "Quit"})) {
		case Insert: {
			int val;

			getValue(val, "the value you want to insert");

			insertOps op = (insertOps)selectionMenu("Where do you want to insert?", { "At start", "Before i", "After i", "At end" });

			switch (op) {
				case insertAtStart: {
					list.push_front(val);
					break;
				}

				case insertAtEnd: {
					list.push_back(val);
					break;
				}

				case insertBefore_i:
				case insertAfter_i: {
					int i;

					getValue(i, "i");

					if (op == insertAfter_i)
						++i;

					list.insert(val, i);
					break;
				}
			}
			break;
		}

		case Remove: {
			switch ((removeOps)selectionMenu("Select operation", { "At start", "At i", "At end" })) {
				case removeAtStart:
					list.pop_front();
					break;

				case removeAtEnd:
					list.pop_back();
					break;

				case removeAt_i:
					int i;

					getValue(i, "i");

					list.remove(i);
					break;
			}
		}

		case Max: {
			printf("Biggest element in list: %d\n", list.max());
			break;
		}

		case a: {
			int last0 = 0;

			for (int i = 0; i < list.size(); i++)
				if (list[i] == 0)
					last0 = i;

			for (int i = last0; i < list.size(); i++)
				secondList.push_back(list[i]);

			printf("Contents of the cyclic list:\n");
			secondList.display();
			break;
		}

		case b: {
			double avg = list.avg();
			int count = 0;

			printf("Average: %f\n", avg);

			for (int item : secondList)
				if (item > avg)
					count++;

			printf("Count of elements larger than average: %d\n", count);
			break;
		}

		case c: {
			while (secondList.size() > 4) {
				printf("Removed %d\n", secondList[3]);

				secondList.remove(3);
			}

			printf("Resulting list:\n");
			secondList.display();
			break;
		}

		case Display:
			list.display();
			break;

		case Quit:
			return 0;
	}

	goto resume;
}