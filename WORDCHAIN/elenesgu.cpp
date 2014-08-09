#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iterator>

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

#define char_for(x) for(char x = 'a'; x <= 'z'; x++)

void WORDCHAIN(int tCase);
void DFS(char start);

struct edge {
	string value;
	int point;
	bool visit;
	edge(string av, int ap) : value(av), point(ap), visit(false) {}
};
struct node {
	vector<edge> edges;
	int oute = 0, ine = 0;
};

class letterarray : public array<node, 26U> {
public:
	node& operator[](const char obj) {
		return this->at(obj - 'a');
	}
};

static node empty;
static const string errormsg("IMPOSSIBLE\n");

letterarray letters;
int mc;
vector<string> result;
array<char, 2U> ones;

int main() {
	int tCase;
	in >> tCase;
	while (tCase--) {
		letters.fill(empty);
		ones.fill(0);
		result.clear();
		in >> mc;
		WORDCHAIN(mc);
	}

}

void WORDCHAIN(int tCase) {
	string tmp;
	while (tCase--) {
		in >> tmp;
		letters[tmp.front()].edges.push_back(edge(tmp, tmp.back()));
		letters[tmp.front()].oute++;
		letters[tmp.back()].ine++;
	}
	char_for(i) {
		int d = letters[i].oute - letters[i].ine;
		if (d == 1) {
			if (ones[0] == 0) {
				ones[0] = i;
			}
			else {
				out << errormsg;
				return;
			}
		}
		if (d == -1) {
			if (ones[1] == 0) {
				ones[1] = i;
			}
			else {
				out << errormsg;
				return;
			}
		}
	}
	if (ones[0] == 0 && ones[1] == 0) {
		char_for(i) if(letters[i].edges.size()) DFS(i);
	}
	else if (ones[0] != 0 && ones[1] != 0) {
		DFS(ones[0]);
	}
	else {
		out << errormsg;
		return;
	}
	if (result.size() != mc) {
		out << errormsg;
		return;
	}
	for (reverse_iterator<vector<string>::iterator> itr = result.rbegin(); itr != result.rend(); itr++) {
		out << *itr << ' ';
	}
	out << endl;
}

void DFS(char start) {
	for (edge& obj : letters[start].edges) {
		if (!obj.visit) {
			obj.visit = true;
			DFS(obj.point);
			result.push_back(obj.value);
		}
	}
}