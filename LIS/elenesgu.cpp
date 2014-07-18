#include<iostream>
#include<array>
#include<vector>

using namespace std;

#ifdef LOCAL 
#include<fstream>
ifstream in("input.txt");
#else
istream& in = cin;
#endif

array<int, 500> DynamicMemory;
vector<int> SequenceNumber;
unsigned int Seqnum;
int MaxResult = -1;

int LIS(const vector<int> &SequenceNum, const size_t index);

int main() {
	size_t tCase;
	int tmp;
	in >> tCase;
	while (tCase--) {
		MaxResult = 0;
		SequenceNumber.clear();
		fill(DynamicMemory.begin(), DynamicMemory.end(), -1);
		in >> Seqnum;
		for (size_t i = 0; i < Seqnum;i ++) {
			in >> tmp;
			SequenceNumber.push_back(tmp);
		}
		for (size_t i = 0; i < Seqnum; i++) {
			if (DynamicMemory[i] == -1) LIS(SequenceNumber, i);
		}
		for (size_t i = 0; i < Seqnum; i++) {
			if (DynamicMemory[i] == -1) break;
			if (DynamicMemory[i] > MaxResult) {
				MaxResult = DynamicMemory[i];
			}
		}
		cout << MaxResult << endl;
	}

	return 0;
}

int LIS(const vector<int> &SequenceNum, const size_t index) {
	int Inum = 1;
	size_t i;
	if (index >= Seqnum) {
		return Inum;
	}
	if (DynamicMemory[index] == -1) {
		for (i = index + 1; i < Seqnum; i++) {
			if (SequenceNum[index] < SequenceNum[i]) {
				int tmp = LIS(SequenceNum, i) + 1;
				Inum = (tmp > Inum)? tmp: Inum;
				DynamicMemory[index] = Inum;
			}
		}
		if (i >= Seqnum) {
			DynamicMemory[index] = Inum;
		}
	}
	return DynamicMemory[index];	
}