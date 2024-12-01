#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

int main() {
    int n, m;
    List<int> firstList;
    List<int> SecondList;

    getValue(n, "n");
    getValue(m, "m");

    for (int i = 0; i < n; i++) {
        int val;

        getValue(val, "element " + to_string(i + 1));

        firstList.push_back(val);
    }
    

    for (int i = 0; i < m; i++) // Sm - S1
        SecondList.push_front(firstList.at(i));

    for (int i = m; i < n; i++) // Sm+1 - Sn
        SecondList.push_front(firstList.at(i));
}