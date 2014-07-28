#include <iostream>
#include<string>

using namespace std;

#ifdef LOCAL
#include<fstream>
ifstream in("input.txt");
ostream& out = cout;
#else
istream& in = cin;
ostream& out = cout;
#endif

char bStack[10000];
int top;
bool answer;

bool BracketPush(char obj);

int main() {
	size_t tCase;
	in >> tCase;
	while (tCase--) {
		top = -1;
		answer = true;
		string Input;
		in >> Input;
		for (int i = 0; i < Input.length(); i++){
			if (!BracketPush(Input[i])) {
				answer = false;
				break;
			}
		}
		if (answer && top == -1) {
			out << "YES" << endl;
		}
		else {
			out << "NO" << endl;
		}
	}
	return 0;
}

bool BracketPush(char obj) {
	switch (obj) {
	case '(':
	case '{':
	case '[':
		bStack[++top] = obj;
		break;
	case ')':
		if (bStack[top--] != '(') return false;
		break;
	case '}':
		if (bStack[top--] != '{') return false;
		break;
	case ']':
		if (bStack[top--] != '[') return false;		
		break;
	}
	return true;
}
