#include <iostream>
#include "GrayStl.h"

using namespace std;

void removeAllEven(TreeItem<int>* root, List<int>& list) {
	if (root == nullptr)
		return;

	removeAllEven(root->left, list);

	if (root->value % 2 == 0) {
		list.push_back(root->value);
	}

	removeAllEven(root->right, list);
}

List<int> removeAllEven(BinaryTree<int> tree) {
	List<int> a = List<int>();

	removeAllEven(tree.root, a);

	for (int i = 0; i < a.size(); i++) {
		tree.removeItem(a[i]);
	}

	return a;
}

int main() {
	BinaryTree<int> tree = BinaryTree<int>();
	Queue<int> queue = Queue<int>();
	Deque<int> deque = Deque<int>();

	List<List<int>> lst = List<List<int>>(5, List<int>(2, 5));

	start:

	switch (selectionMenu("Select the operation", { "Insert", "Search", "Display", "Remove", "Convert", "Quit" })) {
		case 0: { // Insert
			int value;

			getValue(value, "the number you want to insert");

			tree.insertItem(value);
			break;
		}

		case 1: { // Search
			int value;

			getValue(value, "the value you want to search");

			TreeItem<int>* item = tree.findItem(value);

			if (item == nullptr) {
				cout << "The value you have entered does not exist in the tree" << endl;
				break;
			}
		}

		case 2: { // Display
			tree.display();
		}

		case 3: { // Remove
			int value;

			getValue(value, "the value you want to remove");

			TreeItem<int>* item = tree.findItem(value);

			if (item == nullptr) {
				cout << "The value you have entered does not exist in the tree" << endl;
				break;
			}

			tree.removeItem(value);
		}

		case 4: { // Convert
			List<int> temp;

			// a
			temp = tree.moreThan(10);

			for (int i = 0; i < temp.size(); i++)
				deque.push_front(temp[i]);

			temp.clear();

			// b
			temp = tree.lessThan(5);

			for (int i = 0; i < temp.size(); i++)
				deque.push_back(temp[i]);

			temp.clear();

			// c
			temp = removeAllEven(tree);

			for (int i = 0; i < temp.size(); i++)
				queue.push(temp[i]);

			temp.clear();

			// d
			cout << "Resulting lists: \n";
			deque.display();
		}

		case 5: // Quit
			return 0;
	}

	goto start;
}
