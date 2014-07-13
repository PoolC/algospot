#include<iostream>
#include<array>

using namespace std;

#define UINT_MAX 0xffffffff

#ifdef LOCAL 
#include<fstream>
ifstream in("input.txt");
#else
istream& in = cin;
#endif


typedef array<unsigned int, 20000> Fence;

Fence Fences;

unsigned int calcFENCE(const Fence& Fences, size_t fStart, size_t fEnd);

inline size_t FindMinIndex(const Fence& Fences, size_t fStart, size_t fEnd) {
	
	size_t minIndex = fStart;
	for (size_t i = fStart; i <= fEnd; i++) {
		if (Fences[i] < Fences[minIndex]) {
			minIndex = i;
		}
	}
	return minIndex;
}

int main() {
	int tCase;
	int fSize;
	int tmp;

	in >> tCase;
	while(tCase--) {
		in >> fSize;
		for (int i = 0; i < fSize; i++){
			in >> tmp;
			Fences[i] = tmp;
		}
		
		cout << calcFENCE(Fences, 0, fSize - 1) << endl;
	}

	return 0;
}

unsigned int calcFENCE(const Fence& Fences, size_t fStart, size_t fEnd) {
	if (fStart == fEnd) {
		return Fences[fStart];
	}

	size_t MinIndex = FindMinIndex(Fences, fStart, fEnd);
	unsigned int localmaxCase = Fences[MinIndex] * (fEnd - fStart + 1);
	unsigned int tempmaxCase = 0;
	if (MinIndex > fStart) {
		tempmaxCase = calcFENCE(Fences, fStart, MinIndex - 1);
		localmaxCase = (localmaxCase > tempmaxCase) ? localmaxCase : tempmaxCase;
	}
	if (MinIndex < fEnd) {
		tempmaxCase = calcFENCE(Fences, MinIndex + 1, fEnd);
		localmaxCase = (localmaxCase > tempmaxCase) ? localmaxCase : tempmaxCase;
	}
	return localmaxCase;
}