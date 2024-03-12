

#include <iostream>
#include "GrayStl.h"

using namespace std;

int main()
{
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
}
