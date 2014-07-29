#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct node
{
	int maxNumber;
	int count;
};


node DPResult[100][100];

int numbers[100][100];

int main()
{
	int numOfCase;

	scanf("%d", &numOfCase);
		
	for(int i=0;i<numOfCase;i++)
	{
		int length;

		scanf("%d", &length);

		for(int j=0; j<length; j++)
			for(int k=0; k<=j; k++)
			{
				scanf("%d", &numbers[j][k]);
				DPResult[j][k].maxNumber=0;
				DPResult[j][k].count=0;
			}
	
		DPResult[0][0].maxNumber=numbers[0][0];
		DPResult[0][0].count=1;

		for(int j=1; j<length; j++)
			for(int k=0; k<=j; k++)
			{
				int localSum=0;
				if(j!=k)//자기 위 조건
				{
					localSum=DPResult[j-1][k].maxNumber+numbers[j][k];
					if(DPResult[j][k].maxNumber<localSum)
					{
						DPResult[j][k].maxNumber=localSum;
						DPResult[j][k].count=DPResult[j-1][k].count;
					}
					else if(DPResult[j][k].maxNumber==localSum)
						DPResult[j][k].count+=DPResult[j-1][k].count;
				}

				if(k>0)//자기 왼쪽 위 조건
				{
					localSum=DPResult[j-1][k-1].maxNumber+numbers[j][k];
					if(DPResult[j][k].maxNumber<localSum)
					{
						DPResult[j][k].maxNumber=localSum;
						DPResult[j][k].count=DPResult[j-1][k-1].count;
					}
					else if(DPResult[j][k].maxNumber==localSum)
						DPResult[j][k].count+=DPResult[j-1][k-1].count;
				}
			}
		
		int result=0;
		int maxNumber=0;
		for(int j=0; j<length; j++)
		{
			if(maxNumber<DPResult[length-1][j].maxNumber)
			{
				maxNumber=DPResult[length-1][j].maxNumber;
				result=DPResult[length-1][j].count;
			}
			else if(maxNumber==DPResult[length-1][j].maxNumber)
				result+=DPResult[length-1][j].count;
		}

		printf("%d\n", result);

	}
}
