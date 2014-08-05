#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define QUEUEMAX 5000000


int cQueue[QUEUEMAX];
int start;
int end;
int queueSum;

int main()
{
	int numOfCase;
	int inputs[20][2];

	

	scanf("%d", &numOfCase);
		
	for(int i=0;i<numOfCase;i++)
		scanf("%d %d", &inputs[i][0], &inputs[i][1]);

	int findMax=0;
	for(int i=0;i<numOfCase;i++)
		if(inputs[i][1]>findMax) findMax=inputs[i][1];

	
	/*	A[i] = (A[i-1] * 214013 + 2531011) % ((long long)1024*1024*1024*4) ;*/
	
	
	

	for(int i=0; i<numOfCase; i++)
	{
		queueSum=0;
		start=0;
		end=0;
		int sum=inputs[i][0];
		int length=inputs[i][1];
		long long result=0;

		long long A=1983;
		for(int j=0; j<length; j++)
		{
			int signal=A%10000+1;
			cQueue[end]=signal;

			end=(end+1)%QUEUEMAX;

			queueSum+=signal;
			if(queueSum==sum)
				result++;

			else if(queueSum>sum)
			{
				for(int k=start; k!=(end==0)?(QUEUEMAX-1):(end-1); k=(k+1)%QUEUEMAX)
				{
					queueSum-=cQueue[k];
					start=(start+1)%QUEUEMAX;
					if(queueSum<=sum) break;

				}

				if(queueSum==sum)
					result++;
			}
			A=(A * 214013 + 2531011) % ((long long)1024*1024*1024*4) ;
		}
		printf("%lld\n", result);
	}
}
