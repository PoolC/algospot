#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#ifdef LOCAL
#include<fstream>
#include<chrono>
#include<ctime>
ifstream in("input.txt");
ostream& out = cout;
#else
istream& in = cin;
ostream& out = cout;
#endif

typedef pair<int, int> pint;
typedef unsigned int num;

const int MaxCase = 30000000;
num Signals;
size_t sigbegin = 1;

short ConvertedSignals[MaxCase];

void Init() {
	Signals = 1983;
	ConvertedSignals[0] = 1984;
	for (int i = 1; i < MaxCase; i++) {
		Signals = Signals * 214013 + 2531011;
		ConvertedSignals[i] = Signals % 10000 + 1;
	}
}

void ReInit(num b) {
	for (int i = 0; i <= MaxCase - b; i++) {
		ConvertedSignals[i] = ConvertedSignals[b + i];
	}
	for (int i = MaxCase - b + 1; i < MaxCase; i++) {
		Signals = Signals * 214013 + 2531011;
		ConvertedSignals[i] = Signals % 10000 + 1;
	}
}

num ITES(const pint& obj);

int main() {
	size_t tCase;
	pint tmp;
	in >> tCase;
	while (tCase--) {
		if (sigbegin != 0) {
			Init();
		}
		in >> tmp.first >> tmp.second;
		out << ITES(tmp) << endl;
	}
	return 0;
}

num ITES(const pint& obj) {
	sigbegin = 0;
	size_t begin = 0, end = 0, con = MaxCase - sigbegin;
	num sum = ConvertedSignals[begin];
	num sol = 0;
	while (end < obj.second) {
		if (sum > obj.first) {
			sum -= ConvertedSignals[begin++ - sigbegin];
			if (begin > end) {
				sum += ConvertedSignals[++end - sigbegin];
			}
		}
		else if (sum < obj.first) {
			sum += ConvertedSignals[++end - sigbegin];
		}
		else {
			sol++;
			sum += ConvertedSignals[++end - sigbegin];
		}
		if (sigbegin == 0 && end >= con) {
			ReInit(begin);
			sigbegin = begin;
			con = MaxCase - sigbegin;
		}
	}
	return sol;
}