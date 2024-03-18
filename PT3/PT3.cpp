#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

int main() {
    int n;
    OneDirectionalList<int> firstList;
    BidirectionalList<int> SecondList;

    getValue(n, "n");

    for (int i = 0; i < n; i++) {
        int val;

        getValue(val, "element " + to_string(i + 1));

        firstList.insertAtEnd(val);
    }

    for (int i = 0; i < n; i++) {
        int val = firstList.elementAt(i);

        if(SecondList.findElement(val) == nullptr)
            SecondList.InsertIntoEnd(val);
    }

    cout << "Resulting list:\n";
    SecondList.display();
}