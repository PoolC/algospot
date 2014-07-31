#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#ifdef LOCAL
#include<fstream>
ifstream in("input.txt");
ostream& out = cout;
#else
istream& in = cin;
ostream& out = cout;
#endif

#define INT_MAX 0x7fffffff

struct Coord2{
	int x, y;

	Coord2(int ax, int ay) : x(ax), y(ay) {}
	Coord2(const Coord2& obj) : Coord2(obj.x, obj.y) {}
	Coord2() : Coord2(-1, -1) {}
	~Coord2() {}
};

class Circle {
public:
	Coord2 Center;
	int Radius;
	static bool isInclude(const Circle& fircircle, const Circle& seccircle);

	Circle() : Center(), Radius(0){}
	Circle(int ax, int ay, int ar) : Center(ax, ay), Radius(ar) {}
	Circle(const Circle& obj) : Circle(obj.Center.x, obj.Center.y, obj.Radius) {}
	~Circle() {}
};

class Fortress {
public:
	Circle value;
	vector<Fortress> SubFortress;

	Fortress() : value() {}
	Fortress(int ax, int ay, int ar) : value(ax, ay, ar){}
	Fortress(const Circle& obj) : Fortress(obj, 0) {}
	~Fortress() {}

	void NewFortress(const Circle newfort);
	int FindResult();
	int GetMaxDistance();
};

Fortress OutFortress(0, 0, INT_MAX);
vector<Circle> record;

int main() {
	size_t tCase, FortNum;
	in >> tCase;
	int tmpx, tmpy, tmpr;
	while (tCase--) {
		in >> FortNum;
		record.clear();
		OutFortress.SubFortress.clear();
		while (FortNum--) {
			in >> tmpx >> tmpy >> tmpr;
			record.push_back(Circle(tmpx, tmpy, tmpr));
		}
		sort(record.begin(), record.end(), [](const Circle& a, const Circle& b) {
			return a.Radius > b.Radius;
		});
		for_each(record.begin(), record.end(), [](const Circle& a) {
			OutFortress.NewFortress(a);
		});
		out << OutFortress.FindResult() << endl;
	}
	return 0;
}

#pragma region CircleFunc

bool Circle::isInclude(const Circle& fircircle, const Circle& seccircle) {
	const Circle* Bigger;
	const Circle* Smaller;
	if (fircircle.Radius > seccircle.Radius) {
		Bigger = &fircircle;
		Smaller = &seccircle;
	}
	else {
		Bigger = &seccircle;
		Smaller = &fircircle;
	}
	return (hypot(static_cast<double> (fircircle.Center.x - seccircle.Center.x),
		static_cast<double>(fircircle.Center.y - seccircle.Center.y)) + static_cast<double>(Smaller->Radius))
			 <
		static_cast<double>(Bigger->Radius);
}

#pragma endregion

#pragma region FortressFunc

void Fortress::NewFortress(const Circle newfort) {
	if (SubFortress.empty()) {
		SubFortress.push_back(Fortress(newfort));
		return;
	}
	size_t index;
	for (index = 0; index < SubFortress.size(); index++) {
		if (Circle::isInclude(SubFortress[index].value, newfort)) {
			SubFortress[index].NewFortress(newfort);
			return;
		}
	}	
	SubFortress.push_back(Fortress(newfort));
}

int Fortress::FindResult() {
	vector<int> nums;
	if (SubFortress.empty()){
		return 0;
	}
	for (size_t i = 0; i < SubFortress.size(); i++) {
		nums.push_back(SubFortress[i].GetMaxDistance());
	}
	int maxnum, anothernum;
	if (nums.size() == 1) {
		maxnum = nums[0] - 1;
	}
	else {
		sort(nums.begin(), nums.end(), greater<int>());
		maxnum = nums[0] + nums[1];
	}	
	
	for (size_t i = 0; i< nums.size(); i++) {
		anothernum = SubFortress[i].FindResult();
		if (anothernum > maxnum) {
			maxnum = anothernum;
		}
	}
	return maxnum;
}

int Fortress::GetMaxDistance() {
	int max = 1, tmpmax = 1, curmax;
	if (!SubFortress.empty()){
		for (size_t i = 0; i < SubFortress.size(); i++) {
			curmax = SubFortress[i].GetMaxDistance();
			if (tmpmax < curmax) {
				tmpmax = curmax;
			}
		}
		max += tmpmax;
	}
	return max;
}

#pragma endregion