#include<iostream>
#include<algorithm>
#include<vector>
#include<array>
#include<string>
#include<functional>
using namespace std;

#ifdef LOCAL 
#include<fstream>
#include <chrono>
#include <ctime>
ifstream in("input.txt");
ostream& out = cout;
chrono::time_point<chrono::system_clock> tstart, tend;
auto NowTime = chrono::system_clock::now;
#else
istream& in = cin;
ostream& out = cout;
#endif

#define UINT_MAX 0xffffffff

typedef unsigned int num;

string PINumbers;
array<int, 10000> DynamicMemory;

static num CalDifficulty(const string& Numbers);

static num PI(const string& PInums);
static num PI(const string& PInums, size_t index);

int main() {
	size_t tCase;
	in >> tCase;
	while (tCase--) {
#ifdef LOCAL
		tstart = NowTime();
#endif
		fill(DynamicMemory.begin(), DynamicMemory.end(), -1);
		in >> PINumbers;
		out << PI(PINumbers) << endl;
#ifdef LOCAL
		tend = NowTime();
		out << "Operating time: " << chrono::duration_cast<std::chrono::milliseconds>(tend - tstart).count() << endl;
#endif
	}
	return 0;
}


static num CalDifficulty(const string& Numbers) {
	vector<int> Differs;
	for (size_t i = 1; i < Numbers.size(); i++){
		Differs.push_back(Numbers[i] - Numbers[i - 1]);
	}
	if (Differs[0] == 0) {
		for (size_t i = 1; i < Differs.size(); i++){
			if (Differs[i] != Differs[0]) {
				return 10;
			}
		}
		return 1;
	}
	else if ((Differs[0] == Differs[1]) &&(Differs[0] == 1 || Differs[0] == -1)) {
		for (size_t i = 1; i < Differs.size(); i++){
			if (Differs[i] != Differs[0]) {
				return 10;
			}
		}
		return 2;
	}
	else if (Differs[0] == -Differs[1]) {
		for (size_t i = 1; i < Differs.size(); i++) {
			if (Differs[i] != -Differs[i - 1]) {
				return 10;
			}
		}
		return 4;
	}
	else if (Differs[0] == Differs[1]) {
		for (size_t i = 1; i < Differs.size(); i++){
			if (Differs[i] != Differs[0]) {
				return 10;
			}
		}
		return 5;
	}
	else {
		return 10;
	}	
}

static num PI(const string& PInums) {
	return PI(PInums, 0);
}

static num PI(const string& PInums, size_t index) {	
	num minDifficulty = UINT_MAX;
	if (index >= PInums.size()) {
		return 0;
	}
	if (index + 3 > PInums.size()) {
		return minDifficulty;
	}
	string subnums;
	subnums = subnums + PInums[index] + PInums[index + 1];
	if (DynamicMemory[index] == -1) {
		for (size_t i = 3; i <= 5; i++) {
			if (index + i <= PInums.size()) {
				subnums += PInums[index + i - 1];

				num tmpDifficulty = PI(PInums, index + i);
				if (tmpDifficulty != UINT_MAX) {
					tmpDifficulty += CalDifficulty(subnums);					
				}
				if (minDifficulty > tmpDifficulty) {
					minDifficulty = tmpDifficulty;
				}
			}
		}
		DynamicMemory[index] = minDifficulty;
	}
	else {
		minDifficulty = DynamicMemory[index];
	}

	return minDifficulty;
}