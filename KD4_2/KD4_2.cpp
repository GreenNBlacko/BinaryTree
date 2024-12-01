#include <iostream>
#include "GrayStl.h"

using namespace std;

int main() {
	int N, x, lastEven = 0;

	getValue(N, "N");

	List<int> list = List<int>(N, 0);

	for (int i = 0; i < N; i++) {
		getValue(list[i], "element " + to_string(i + 1));

		if (list[i] % 2 == 0)
			lastEven = i;
	}

	getValue(x, "x");

	list.insert(lastEven, x);

	printf("Resulting list: \n");
	list.display();

	return 0;
}