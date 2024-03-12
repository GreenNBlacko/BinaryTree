#include <iostream>
#include <iomanip>
#include "GrayStl.h"

using namespace std;

int main() {
    OneDirectionalList<int> list{};

    int n;

    getValue(n, "saraso elementu skaiciu");

    for (int i = 0; i < n; i++) {
        int x;

        getValue(x, to_string(i + 1) + "-aji elementa");

        list.insertAtEnd(x);
    }

    int _max = 0;

    for (int i = 0; i < n; i++) {
        int element = list.elementAt(i);
        int maxElement = list.elementAt(_max);

        if (element > maxElement)
            _max = i;
    }

    int x;
    getValue(x, "skaiciu, kuri norite iterpti po didziausio");
    list.insertAt(_max, x);

    cout << "Sarasas:" << endl;
    list.display();
    cout << endl;

    return 0;
}