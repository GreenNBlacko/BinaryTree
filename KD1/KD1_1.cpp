

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

        list.insertAtEnd((a % 2 == 0 ? a * 2 : a));
    }

    cout << "\nResulting list:\n";
    list.display();
}
