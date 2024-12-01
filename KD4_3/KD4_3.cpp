#include <iostream>
#include "GrayStl.h"

using namespace std;

int main() {
	int N, x;

	getValue(N, "N");

	List<int> list = List<int>(N, 0);

	for (int i = 0; i < N; i++) {
		getValue(list[i], "element " + to_string(i + 1));
	}

	list.remove(list.indexOf(list.max()));
	list.remove(list.indexOf(list.min()));

	printf("Resulting list: \n");
	list.display();

	return 0;
}