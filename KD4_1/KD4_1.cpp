#include <iostream>
#include "GrayStl.h"

using namespace std;

int main() {
	int N;

	getValue(N, "N");

	List<int> list = List<int>(N, 0);

	for (int i = 0; i < N; i++) {
		getValue(list[i], "element " + to_string(i + 1));
	}

	for (int i = 0; i < N; i++) {
		if (list[i] % 2 == 0)
			list[i] *= 2;
	}

	printf("Resulting list: \n");
	list.display();

	return 0;
}