

#include <iostream>
#include "GrayStl.h"

using namespace std;

int main()
{
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
}
