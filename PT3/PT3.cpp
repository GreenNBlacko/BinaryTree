#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

int main() {
    int n;

    getValue(n, "n");

    List<int> firstList = List<int>(n);
    BiList<int> SecondList;

    for (int i = 0; i < firstList.size(); i++) {
        getValue(firstList[i], "element " + to_string(i + 1));
    }

    for (int i = 0; i < firstList.size(); i++) {
        if (SecondList.indexOf(firstList[i]) == -1)
            SecondList.push_back(firstList[i]);
    }

    cout << "Resulting list:\n";
    SecondList.display();

    firstList.quicksort();

    cout << "Sorted list:\n";
    firstList.display();
}