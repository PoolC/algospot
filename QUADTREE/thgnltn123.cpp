#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<cstring>

struct indexPair
{
	int start;
	int end;
};

char curString[1001];


int nodeNumber;
int stringIndex;


indexPair recurFunc()
{
	indexPair result;
	if(curString[stringIndex]=='b'||curString[stringIndex]=='w')
	{
		result.start=stringIndex;
		result.end=stringIndex;
		stringIndex++;
	}
	else
	{
		indexPair curPair[4];
		stringIndex++;
		for(int i=0; i<4; i++)
		{
			curPair[i]=recurFunc();
		}

		char tempString[1001];
		result.start=curPair[0].start;
		result.end=curPair[3].end;

		int tempLength=result.end-result.start+1;
		int k=0;
		for(int i=2; i<4; i++)
			for(int j=curPair[i].start; j<=curPair[i].end; j++)
				tempString[k++]=curString[j];
		for(int i=0; i<2; i++)
			for(int j=curPair[i].start; j<=curPair[i].end; j++)
				tempString[k++]=curString[j];

		
		for(int i=0; i<tempLength; i++)
			curString[i+result.start]=tempString[i];

		result.start--;
	}
	return result;
}

int main()
{
	int numOfCase;


	scanf("%d", &numOfCase);

	for(int i=0;i<numOfCase;i++)
	{
		nodeNumber=0;

		scanf("%s", curString);
		stringIndex=0;

		recurFunc();
		printf("%s\n", curString);
	}
}
