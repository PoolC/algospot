#include <cstdio>
#include <string>
#include <list>
#include <array>
#include <iterator>
#include <functional>

using namespace std;

list<int> numbers;
int record[50000];
int result[50000];
size_t recnum;

void INSERTION();

int main() {
	int tCase;
	scanf("%d", &tCase);
	while (tCase--) {
		numbers.clear();
		scanf("%d", &recnum);
		INSERTION();
	}
}

void INSERTION() {
	for (size_t i = 0; i < recnum; i++) {
		scanf("%d", &record[i]);
		numbers.push_back(i + 1);
	}
	for (int i = recnum - 1; i >= 0; i--) {
		list<int>::iterator pos;
		if (record[i] > recnum / 2)
			pos = prev(numbers.end(), record[i] + 1);
		else
			pos = next(numbers.begin(), i - record[i]);
		result[i] = *pos;
		numbers.erase(pos);
	}
	printf("%d", result[0]);
	for (size_t i = 1; i < recnum; i++) {
		printf(" %d", result[i]);
	}
	printf("\n");
}