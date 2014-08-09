#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <vector>


using namespace std;

#ifdef LOCAL
#include<fstream>
#include <exception>
ifstream in("input.txt");
ostream& out = cout;
#else
istream& in = cin;
ostream& out = cout;
#endif

int RUNNINGMEDIAN(int num, int a, int b);

int main() {
	int tCase;
	int tn, ta, tb;	
	in >> tCase;
	while (tCase--) {
		in >> tn >> ta >> tb;
		out << RUNNINGMEDIAN(tn - 1, ta, tb) << endl;
	}
}

int RUNNINGMEDIAN(int num, int a, int b) {
	
	int med = 1983, base = 1983, def, tmp;
	int result = 1983;
	priority_queue<int, vector<int>, less<int>> left;
	priority_queue<int, vector<int>, greater<int>> right;
	queue<int> tmpcontainer;
	while (num--) {
		base = (static_cast<long long>(base) * a + b) % 20090711;
		if (base > med) right.push(base);
		else left.push(base);
		def = left.size() - right.size();
		while (def != 0 && def != -1) {
			if (def > 0) {
				right.push(med);
				med = left.top();
				left.pop();
			}
			else {
				left.push(med);
				med = right.top();
				right.pop();
			}
			def = left.size() - right.size();
		}
		result = (result + med) % 20090711;
	}
	return result;
}