#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef LOCAL
#include<fstream>
ifstream in("input.txt");
ostream& out = cout;
#else
istream& in = cin;
ostream& out = cout;
#endif

array<int, 5051> DynamicMemory;
int TriCount;

inline int SumSigma(const int obj) {
	return obj * (obj + 1) / 2;
}

int TRIPATHCNT(vector<int>& Triangle, int mlevel);
int TRIPATHCNT(vector<int>& Triangle, int index, int level);
void BottomBuild(vector<int>& Triangle);

int main() {
	size_t tCase;
	in >> tCase;
	while (tCase--) {
		fill(DynamicMemory.begin(), DynamicMemory.end(), 0);
		vector<int> Triangle(1, 1);
		in >> TriCount;
		Triangle[0] = TriCount;
		int TotalNum = SumSigma(TriCount);
		for (int i = 1; i <= TotalNum; i++) {
			in >> TriCount;
			Triangle.push_back(TriCount);
		}
		out << TRIPATHCNT(Triangle, TotalNum) << endl;
	}
}

int TRIPATHCNT(vector<int>& Triangle, int mlevel) {
	BottomBuild(Triangle);
	return TRIPATHCNT(Triangle, 1, 1);
}
int TRIPATHCNT(vector<int>& Triangle, int index, int level) {
	int maxPCase(1);
	if (DynamicMemory[index] != 0) {
		maxPCase = DynamicMemory[index];
	}
	else {
		if (level == Triangle[0]){
			DynamicMemory[index] = maxPCase;
		}
		else {
			int LeftCase(0), RightCase(0);
			if (Triangle[index + level] > Triangle[index + level + 1]) 	LeftCase = TRIPATHCNT(Triangle, index + level, level + 1);
			else if (Triangle[index + level] < Triangle[index + level + 1]) RightCase = TRIPATHCNT(Triangle, index + level + 1, level + 1);
			else {
				LeftCase = TRIPATHCNT(Triangle, index + level, level + 1);
				RightCase = TRIPATHCNT(Triangle, index + level + 1, level + 1);
			}
			maxPCase = LeftCase + RightCase;
			DynamicMemory[index] = maxPCase;
		}
	}
	return maxPCase;
}

void BottomBuild(vector<int>& Triangle) {
	for (int i = Triangle[0] - 1; i > 0; i--) {
		for (int j = 1 + SumSigma(i - 1); j <= SumSigma(i); j++){
			Triangle[j] += (Triangle[j + i] > Triangle[j + i + 1]) ? Triangle[j + i] : Triangle[j + i + 1];
		}
	}
}