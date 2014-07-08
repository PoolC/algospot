#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int clocks[16];
int selectedNumber[10];
int curRecursion;

bool done;


struct StackNode
{
	int clocks[16];
	int selectedNumber[10];
	int curRecursion;
	struct StackNode* next;
};

StackNode* stackTop;

void clockSwitch(int switchNumber)
{
	curRecursion--;
	selectedNumber[switchNumber]++;
	switch(switchNumber)
	{
	case 0:
		clocks[0]=(clocks[0]+1)%4;
		clocks[1]=(clocks[1]+1)%4;
		clocks[2]=(clocks[2]+1)%4;
		break;

	case 1:
		clocks[3]=(clocks[3]+1)%4;
		clocks[7]=(clocks[7]+1)%4;
		clocks[9]=(clocks[9]+1)%4;
		clocks[11]=(clocks[11]+1)%4;
		break;

	case 2:
		clocks[4]=(clocks[4]+1)%4;
		clocks[10]=(clocks[10]+1)%4;
		clocks[14]=(clocks[14]+1)%4;
		clocks[15]=(clocks[15]+1)%4;
		break;

	case 3:
		clocks[0]=(clocks[0]+1)%4;
		clocks[4]=(clocks[4]+1)%4;
		clocks[5]=(clocks[5]+1)%4;
		clocks[6]=(clocks[6]+1)%4;
		clocks[7]=(clocks[7]+1)%4;
		break;

	case 4:
		clocks[6]=(clocks[6]+1)%4;
		clocks[7]=(clocks[7]+1)%4;
		clocks[8]=(clocks[8]+1)%4;
		clocks[10]=(clocks[10]+1)%4;
		clocks[12]=(clocks[12]+1)%4;
		break;

	case 5:
		clocks[0]=(clocks[0]+1)%4;
		clocks[2]=(clocks[2]+1)%4;
		clocks[14]=(clocks[14]+1)%4;
		clocks[15]=(clocks[15]+1)%4;
		break;

	case 6:
		clocks[3]=(clocks[3]+1)%4;
		clocks[14]=(clocks[14]+1)%4;
		clocks[15]=(clocks[15]+1)%4;
		break;

	case 7:
		clocks[4]=(clocks[4]+1)%4;
		clocks[5]=(clocks[5]+1)%4;
		clocks[7]=(clocks[7]+1)%4;
		clocks[14]=(clocks[14]+1)%4;
		clocks[15]=(clocks[15]+1)%4;
		break;

	case 8:
		clocks[1]=(clocks[1]+1)%4;
		clocks[2]=(clocks[2]+1)%4;
		clocks[3]=(clocks[3]+1)%4;
		clocks[4]=(clocks[4]+1)%4;
		clocks[5]=(clocks[5]+1)%4;
		break;

	case 9:
		clocks[3]=(clocks[3]+1)%4;
		clocks[4]=(clocks[4]+1)%4;
		clocks[5]=(clocks[5]+1)%4;
		clocks[9]=(clocks[9]+1)%4;
		clocks[13]=(clocks[13]+1)%4;
		break;


	}

}

bool isDone()
{
	for(int i=0; i<16; i++)
		if(clocks[i]!=0) return false;
	return true;
	

}


void push()
{
	struct StackNode *newNode= (struct StackNode *)malloc(sizeof(StackNode));
	
	for(int i=0; i<16; i++)
	{
		newNode->clocks[i]=clocks[i];
		if(i<10)
			newNode->selectedNumber[i]=selectedNumber[i];
	}
	newNode->curRecursion=curRecursion;

	if(stackTop==NULL)
	{
		stackTop=newNode;
		newNode->next=NULL;
	}
	else
	{
		newNode->next=stackTop;
		stackTop=newNode;
	}

}

void pop()
{
	struct StackNode* target;

	if(stackTop==NULL)
	{
		printf("stack underflow!=n");
		system("Pause");
	}

	target=stackTop;

	for(int i=0; i<16; i++)
	{
		clocks[i]=target->clocks[i];
		if(i<10)
			selectedNumber[i]=target->selectedNumber[i];
	}
	curRecursion=target->curRecursion;


	if(target->next!=NULL)
		stackTop=target->next;
	else
		stackTop=NULL;
	
	free(target);
}



void recurClockFunc(int startNumber)
{
	for(int i=startNumber; i<10; i++)
	{
		if(selectedNumber[i]<3)
		{
			push();

			clockSwitch(i);
		
			if(curRecursion==0)
			{

				if(isDone())
					done=true;
			}
			else
				recurClockFunc(i);

			pop();
		}

		if(done==true) return;
	}
}



int main()
{
	int numOfCase;

	stackTop=NULL;

	scanf("%d", &numOfCase);

	for(int i=0;i<numOfCase;i++)
	{
		//initialize
		done=false;
		for(int j=0; j<10; j++)
			selectedNumber[j]=0;

	
		for(int j=0; j<16; j++)
		{
			scanf("%d", &clocks[j]);
			clocks[j]/=3;
			if(clocks[j]==4)
				clocks[j]=0;
		}
		
		
		if(isDone()) printf("0\n");
		else
			for(curRecursion=1; curRecursion<31; curRecursion++)
			{
				recurClockFunc(0);
				if(done==true)
				{
					printf("%d\n", curRecursion);
					break;
				}
			}
		
		if(done==false) printf("-1\n");
	}
}
