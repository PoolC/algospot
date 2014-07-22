#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int numbers[500];
int stringLength;
int maxLength[500];

int DP()
{
	for(int i= stringLength-1; i>=0; i--)
	{
		int Length=1;
		
		for(int j=i+1; j<stringLength; j++)
		{
			if(numbers[i]<numbers[j]&&Length<maxLength[i]+maxLength[j])
				Length=maxLength[i]+maxLength[j];
		}
		maxLength[i]=Length;

	}

	int maximum=1;

	for(int i=0; i<stringLength; i++)
	{
		if(maxLength[i]>maximum) maximum=maxLength[i];
	}
	return maximum;
}


int main()
{
	int numOfCase;


	scanf("%d", &numOfCase);

	for(int i=0;i<numOfCase;i++)
	{
		scanf("%d", &stringLength);

		//initialize
		for(int j=0; j<stringLength; j++)
		{
			scanf("%d", &numbers[j]);	
			maxLength[j]=1;
		}
		int result=0;

		result = DP();
		
		printf("%d\n", result);
	}
}
