#include<iostream>
#include<vector>
#include<array>
#include<list>
#include<algorithm>
#include<iterator>

using namespace std;

istream& in = cin;

enum CTime { TWELVEN = 0, ZERO = 0, THREE = 1, SIX = 2, NINE = 3 };

typedef array< list<int>, 10> CSwitch;
typedef array<int, 16> CClock;
typedef array<int, 10> Variables;

CSwitch Cswitches = {
	 list<int>() = { 0, 1, 2 } ,
	 list<int>() = { 3, 7, 9, 11 } ,
	 list<int>() = { 4, 10, 14, 15 },
	 list<int>() = { 0, 4, 5, 6, 7 },
	 list<int>() = { 6, 7, 8, 10, 12 },
	 list<int>() = { 0, 2, 14, 15 },
	 list<int>() = { 3, 14, 15 },
	 list<int>() = { 4, 5, 7, 14, 15 },
	 list<int>() = { 1, 2, 3, 4, 5 } ,
	 list<int>() = { 3, 4, 5, 9, 13 }
};

Variables ResultNums;

inline int ToeCTIME(int target) {
	switch (target) {
	case 12:
		return 0;
	case 3:
		return 1;
	case 6:
		return 2;
	case 9:
		return 3;
	default:
		return -1;
	}
}

int ClockSync(CClock& Clocks, vector<bool>& Clicked, int level);
int ClickSwitch(CClock& Clocks, int SwitchIndex, int Time);

int main() {
	CClock Clocks;
	vector<bool> SwitchClicked(16);

	size_t tCase;
	in >> tCase;

	while (tCase--) {
		fill(begin(SwitchClicked), end(SwitchClicked), false);
		for (size_t i = 0; i < Clocks.size(); i++) {
			int tmp;
			in >> tmp;
			Clocks[i] = ToeCTIME(tmp);
		}
		cout << ClockSync(Clocks, SwitchClicked, 1) << endl;
	}
	return 0;
}


int ClockSync(CClock& Clocks, vector<bool>& Clicked,int level) {

	fill(begin(ResultNums), end(ResultNums), 0);

	if (Clocks[8] != Clocks[12]) {
		return -1;
	}
	ResultNums[4] = (4 - Clocks[8]) % 4;
	ClickSwitch(Clocks, 4, ResultNums[4]);

	ResultNums[1] = (4 - Clocks[11]) % 4;
	ClickSwitch(Clocks, 1, ResultNums[1]);

	ResultNums[9] = (4 - Clocks[13]) % 4;
	ClickSwitch(Clocks, 9, ResultNums[9]);

	if (Clocks[9] != 0) {
		return -1;
	}

	ResultNums[2] = (4 - Clocks[10]) % 4;
	ClickSwitch(Clocks, 2, ResultNums[2]);

	ResultNums[3] = (4 - Clocks[6]) % 4;
	ClickSwitch(Clocks, 3, ResultNums[3]);

	ResultNums[7] = (4 - Clocks[7]) % 4;
	ClickSwitch(Clocks, 7, ResultNums[7]);

	ResultNums[8] = (4 - Clocks[4]) % 4;
	ClickSwitch(Clocks, 8, ResultNums[8]);

	if (Clocks[5] != 0) {
		return -1;
	}

	ResultNums[0] = (4 - Clocks[1]) % 4;
	ClickSwitch(Clocks, 0, ResultNums[0]);

	ResultNums[5] = (4 - Clocks[0]) % 4;
	ClickSwitch(Clocks, 5, ResultNums[5]);

	if (Clocks[2] != 0) {
		return -1;
	}

	ResultNums[6] = (4 - Clocks[3]) % 4;
	ClickSwitch(Clocks, 6, ResultNums[6]);

	if (Clocks[14] != 0 || Clocks[15] != 0) {
		return -1;
	}

	int result = 0;

	for (size_t i = 0; i < ResultNums.size(); i++) {
		result += ResultNums[i];
	}
	return result;
}

int ClickSwitch(CClock& Clocks, int SwitchIndex, int Time) {
	for (auto itr = Cswitches[SwitchIndex].begin(); itr != Cswitches[SwitchIndex].end(); itr++) {
		Clocks[*itr] += Time;
		Clocks[*itr] %= 4;
	}
	return 0;
}