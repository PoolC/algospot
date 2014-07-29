#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MOD 1000000007

int DPresult[101];

int main()
{
	int numOfCase;

	scanf("%d", &numOfCase);
		
	for(int i=0;i<numOfCase;i++)
	{
		int n;
		scanf("%d", &n);
		
		long long result=0;

		int garo;
		int sero;

		DPresult[1]=1;
		DPresult[2]=2;
		DPresult[3]=3;

		for(int i=4; i<=n; i++)
			DPresult[i]=(DPresult[i-1]+DPresult[i-2])%MOD;

		printf("%lld\n", DPresult[n]);
	}
}
