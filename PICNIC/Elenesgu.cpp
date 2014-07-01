#include<stdio.h>
#include<stdlib.h>

int testcase(int* sel, int** rel, int* fnum);


int main () {
	int test_case, friendnum,relationnum;
	int* selected;
	int** relation;
	int i, j;
	int a, b;
	scanf("%d", &test_case);

	while(test_case) {
		scanf("%d %d", &friendnum, &relationnum);
		relation = (int**)malloc(friendnum * sizeof(int*));
		selected = (int*)malloc(friendnum * sizeof(int));
		for(i = 0; i < friendnum; i++) {
			relation[i] = (int*) malloc(friendnum * sizeof(int));
			for(j = 0 ; j < friendnum ; j++) {
				relation[i][j] = 0;
			}
			selected[i] = 0;
		}

		for(i = 0 ; i < relationnum ; i++) {
			scanf("%d %d", &a, &b);
			relation[a][b] = 1;
			relation[b][a] = 1;

		}

		printf("%d\n", testcase(selected, relation, &friendnum));
		for(i = 0; i < friendnum ; i++) {
			free(relation[i]);
		}
		free(relation);
		free(selected);
		test_case--;
	}
	return 0;
}


int testcase(int* sel, int** rel, int* fnum) {
	int result = 0;
	int i;
	int cur = -1;
	for(i = 0 ; i < *fnum ; i++) {
		if(sel[i] == 0) {
			cur = i;
		}
	}

	if(cur == -1) {
		return 1;
	}

	for(i = 0 ; i < *fnum ; i++) {
		if(sel[i] == 0 && rel[cur][i] == 1) {
			sel[i] = sel[cur] = 1;
			result += testcase(sel, rel, fnum);
			sel[i] = sel[cur] = 0;
		}

	}
	return result;
}