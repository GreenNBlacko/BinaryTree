#include <iostream>
#include <GrayStl.h>

using namespace std;

int main() {
    BTree<int> tree(2, { 1, 5, 10, 2, 5, 3, 4, 7, 6, 25, 82, 14, 34, 264, 14, 25, 36, 274, 26, 49, 25, 348, 654 });

    tree.print();

    return 0;
}
