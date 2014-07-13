#include<iostream>
#include<string>
#include<stack>
#include<array>

using namespace std;

//#include<fstream>
//ifstream in("input.txt");

istream& in = cin;

/*
https://algospot.com/judge/submission/detail/213464
이승민,ElenesGu
*/

class QuadTree {
private:
	string InputTree;
	string OutputTree;

	int index;
	int level;

	char pick;
	stack<string> SStack;

	const array<int, 4> Order{{ 2, 3, 0, 1 }};
	static const int QuadCount = 4;
public:
	QuadTree() {};
	QuadTree(string Input);
	~QuadTree() {};
	void DoTest();
};


int main() {
	unsigned int tCase;
	string Input;

	in >> tCase;
	while (tCase--) {
		in >> Input;
		QuadTree Case(Input);
		cout << endl;
	}
	return 0;
}

QuadTree::QuadTree(string Input) 
	:InputTree(Input), index(0), level(0) {
	pick = InputTree[index++];
	if (pick == 'w' || pick == 'b') {
		cout << pick;
	}
	else {
		OutputTree += pick;
		DoTest();
		OutputTree += SStack.top();
		cout << OutputTree;
	}
}

void QuadTree::DoTest() {
	// 스택을 이용해서 아랫부분부터 쌓아 올린다.
	/*
	x
		wwwb
		wbww push
	x
		w
		x
			wbbb
			bbwb push
		w
		w

		wwwx(pop->bbwb) push
	x
		x
			x
				wwbb
				bbww push
			b
			w
			w
			wwx(pop->bbww)b push
		w
		w
		b
		wbx(pop->wwxbbwwb)w push
	b
	스택구조의 이미지화
	*/
	level++;
	string Sum;
	string parts[4];
	char picks[4];
	for (int i = 0; i < QuadCount; i++) {
		pick = InputTree[index++];
		picks[i] = pick;
		if (pick == 'x') {
			DoTest();
		}

	}
	/* 
		모두 x일 경우를 생각해보자.
		x[i]는 i번째 x의 서브스트링이다.
		스택에섯
		x[0] x[1] x[2] x[3]순서로 쌓여있다. (왼쪽이 탑)
		그러나 실제로 배치되는 순서는
		x[2] x[3] x[0] x[1] 이다. 
		즉, 연속적인 팝을 하면 순서대로 서브스트링이 x에 알맞게 들어가지 못하게 된다.
		따라서, 먼저 뒤에서부터 pop을 해 서브스트링을 구현한 뒤,
		다음 for문에서 올바르게 배치한다.
	*/
	for (int i = QuadCount - 1; i >= 0; i--){
		pick = picks[i];
		if (pick == 'x') {
			parts[i] = pick;
			parts[i] += SStack.top();
			SStack.pop();
		}
		else {
			parts[i] += pick;
		}
	}

	for (int i = 0; i < QuadCount; i++) {
		Sum += parts[Order[i]];
	}
	SStack.push(Sum);
	level--;
}