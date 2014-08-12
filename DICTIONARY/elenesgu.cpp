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
#define rchar_for(x) for(char x = 'z'; x >= 'a'; x--)

struct node {
	int ine = 0;
	int oute = 0;
	bool visited = false;
	vector<char> next;
};

class letterarray : public array<node, 26U> {
public:
	node& operator[](const char obj) {
		return this->at(obj - 'a');
	}
};

 string _DICTIONARY(int cnum);
 void MakeGraph(size_t index, unsigned int level);
 bool Tsort(const vector<char>& vn);

static letterarray letters;
static vector<string> records;
static vector<char> result;
static int num;
static string tmp;
static const string errormsg("INVALID HYPOTHESIS\n");
static const node empty;

int main() {
	int tCase;
	in >> tCase;
	while (tCase--) {
		result.clear();
		records.clear();
		letters.fill(empty);
		in >> num;
		out << _DICTIONARY(num);
	}

}

string _DICTIONARY(int cnum) {
	vector<char> validnode;
	while (cnum--) {
		in >> tmp;
		records.push_back(tmp);
	}
	for (size_t index = 0; index < records.size() - 1; index++) {
		MakeGraph(index, 0);
	}
	char_for(i) {
		if ((letters[i].ine + letters[i].oute) != 0) {
			validnode.push_back(i);
		}
	}
	if (Tsort(validnode)) {
		for (char obj : result) out << obj;
		char_for(x) {
			if (!letters[x].visited) {
				out << x;
			}
		}
	}
	else return errormsg;
	return "\n";
}

void MakeGraph(size_t index, unsigned int level) {
	if (records[index].size() > level) {
		if (records[index + 1].size() <= level) {
			return;
		}
		char fc = records[index].at(level);
		char sc = records[index + 1].at(level);
		if (fc != sc) {
			bool a_in = false;
			for (char obj : letters[fc].next) {
				if (sc == obj) {
					a_in = true;
					break;
				}
			}
			if(!a_in) {
				letters[fc].next.push_back(sc);
				letters[fc].oute++;
				letters[sc].ine++;
			}
		}
		else {
			MakeGraph(index, level + 1);
		}
	}
}

bool Tsort(const vector<char>& vn) {
	char next = 0, cur;
	const size_t vsize = vn.size();
	
	for (int i = 0; i < vsize; i++) {
		if (!next) {
			for (char j : vn) {
				if (!letters[j].ine && !letters[j].visited) {
					next = j;
					break;
				}
			}
		}
		if (!next) {
			return false;
		}
		letters[next].visited = true;
		result.push_back(next);
		cur = next;
		next = 0;
		for (char j : letters[cur].next) {
			letters[j].ine--;
			if (!letters[j].ine) {
				next = j;
			}				 
		}
	}
	return true;
}