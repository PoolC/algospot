#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

char numbers[10010];
int numberLength;

struct nodes
{
	bool alreadyDone[3];
	int value[3];
};

nodes DPdata[10010];
int DPvalue[10010];


int diffTest(int startIndex, int length)
{
	bool flag=true;
	for(int i=startIndex+1; i<length+startIndex; i++)
	{
		if(numbers[startIndex]!=numbers[i])
		{
			flag=false;
			break;
		}
	}
	if(flag==true) return 1;

	flag=true;
	for(int i=startIndex+1; i<length+startIndex; i++)
	{
		if(numbers[i-1]!=(numbers[i]-1))
		{
			flag=false;
			break;
		}
	}
	if(flag==true) return 2;


	flag=true;
	for(int i=startIndex+1; i<length+startIndex; i++)
	{
		if(numbers[i-1]!=(numbers[i]+1))
		{
			flag=false;
			break;
		}
	}
	if(flag==true) return 2;

	flag=true;
	for(int i=startIndex+2; i<length+startIndex; i++)
	{
		if(numbers[i]!=numbers[i-2])
		{
			flag=false;
			break;
		}
	}
	if(flag==true) return 4;


	flag=true;
	int sub = numbers[startIndex+1]-numbers[startIndex];
	for(int i=startIndex+2; i<length+startIndex; i++)
	{
		if(numbers[i]!=(numbers[i-1]+sub))
		{
			flag=false;
			break;
		}
	}
	if(flag==true) return 5;



	return 10;

}


int getDiff(int startIndex, int length)
{

	if(DPdata[startIndex].alreadyDone[length-3]==false)
	{
		DPdata[startIndex].value[length-3]=diffTest(startIndex, length);
		DPdata[startIndex].alreadyDone[length-3]=true;
	}

	return DPdata[startIndex].value[length-3];
}


int DP()
{
	DPvalue[2]=getDiff(0,3);
	DPvalue[3]=getDiff(0,4);
	DPvalue[4]=getDiff(0,5);
	DPvalue[5]=DPvalue[2]+getDiff(3,3);
	DPvalue[6]=DPvalue[2]+getDiff(3,4);
	int temp=DPvalue[3]+getDiff(4,3);
	if(DPvalue[6]>temp) DPvalue[6]=temp;


	for(int i=7; i<numberLength; i++)
	{
		DPvalue[i]=DPvalue[i-3]+getDiff(i-2,3);
		temp=DPvalue[i-4]+getDiff(i-3,4);
		if(DPvalue[i]>temp) DPvalue[i]=temp;
		temp=DPvalue[i-5]+getDiff(i-4,5);
		if(DPvalue[i]>temp) DPvalue[i]=temp;
	}

	return DPvalue[numberLength-1];
}



int main()
{
	int numOfCase;


	scanf("%d", &numOfCase);
	
	for(int i=0;i<numOfCase;i++)
	{
		numbers[0]=0;
		while(numbers[0]<'0' || numbers[0]>'9')
			scanf("%c", &numbers[0]);
		
		
		for(numberLength=1; ;numberLength++)
		{
			scanf("%c", &numbers[numberLength]);
			if(numbers[numberLength]==0||numbers[numberLength]==' '||numbers[numberLength]=='\n') break;
		}

		for(int i=0; i<numberLength; i++)
		{
			DPdata[i].alreadyDone[0]=false;
			DPdata[i].alreadyDone[1]=false;
			DPdata[i].alreadyDone[2]=false;
		}

		int result;
		int tempResult;

		printf("%d\n", DP());

	}
}
