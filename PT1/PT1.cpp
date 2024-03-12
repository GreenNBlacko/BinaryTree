#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

int main() {
    int n, m;
    OneDirectionalList<int> firstList;
    OneDirectionalList<int> SecondList;

    getValue(n, "n");
    getValue(m, "m");

    for (int i = 0; i < n; i++) {
        int val;

        getValue(val, "element " + to_string(i));

        firstList.insertAtEnd(val);
    }
    

    for (int i = 0; i < m; i++) // Sm - S1
        SecondList.insertAtStart(firstList.elementAt(i));

    for (int i = m; i < n; i++) // Sm+1 - Sn
        SecondList.insertAtStart(firstList.elementAt(i));
}