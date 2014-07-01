#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>



struct pair
{
	int a;
	int b;
	bool used;
	bool selected;
};




struct pairStackNode
{
	struct pair curPair[45];
	bool curPerson[10];
	struct pairStackNode* next;
};

pairStackNode* stackTop;

int numOfPair;
int numOfPerson;
bool curPerson[10];
struct pair curPair[45];
int curResult;


void push()
{
	int i;
	struct pairStackNode *newNode= (struct pairStackNode *)malloc(sizeof(pairStackNode));
	for(i=0; i<numOfPerson; i++)
	newNode->curPerson[i]=curPerson[i];
	for(i=0; i<numOfPair; i++)
	newNode->curPair[i]=curPair[i];


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
	int i;
	struct pairStackNode* target;

	if(stackTop==NULL)
	{
		printf("stack underflow!=n");
		system("Pause");
	}

	target=stackTop;
	if(target->next!=NULL)
	{
		for(i=0; i<numOfPerson; i++)
			curPerson[i]=target->curPerson[i];
		for(i=0; i<numOfPair; i++)
			curPair[i]=target->curPair[i];
		stackTop=target->next;
		free(target);
	}
	else
	{
		for(i=0; i<numOfPerson; i++)
			curPerson[i]=target->curPerson[i];
		for(i=0; i<numOfPair; i++)
			curPair[i]=target->curPair[i];
		stackTop=NULL;
		free(target);
	}
}

int fact(int n)
{
	if(n<=1)
		return 1;
	else
		return n*fact(n-1);

}


void recurFindPair(int startNumber)
{
	int i,j,k,a,b;
	struct pair* targetPair;

	for(i=startNumber; i<numOfPair; i++)
	{
		push();
		targetPair = &curPair[i];
		if(targetPair->used==false)
		{
			targetPair->used=true;
			targetPair->selected=true;
			a=targetPair->a;
			b=targetPair->b;
			curPerson[targetPair->a]=true;
			curPerson[targetPair->b]=true;

			for(j=0; j<numOfPair;j++)
			{
				targetPair = &curPair[j];
				if(targetPair->a==a||targetPair->b==a||targetPair->a==b||targetPair->b==b)
				{
					targetPair->used=true;
				}
			}

			recurFindPair(i+1);

			//test 
			for(j=0; j<numOfPerson; j++)
				if(curPerson[j]==false) break;
			if(j==numOfPerson)
				curResult++;
				/*
				printf("Selected List for Debug Mode!\n");

				for(j=0; j<numOfPair; j++)
				{
					targetPair = &curPair[j];
					if(targetPair->selected==true)
						printf("(%d, %d) ", targetPair->a, targetPair->b);

				}
				printf("\n");*/
		}
		pop();
	}
	return;

}



int main()
{
	int numOfCase;
	int i=0;
	int j;

	stackTop=NULL;

	scanf("%d", &numOfCase);

	

	while(i<numOfCase)
	{
		scanf("%d %d", &numOfPerson, &numOfPair);

		//initialize
		for(j=0; j<numOfPerson; j++)
		curPerson[j]=false;

		for(j=0; j<numOfPair; j++)
		{
			scanf("%d %d", &curPair[j].a, &curPair[j].b);
			curPair[j].used=false;
			curPair[j].selected=false;
		}
		/*
				printf("Total pair for debug!\n");

				for(j=0; j<numOfPair; j++)
				{

						printf("(%d, %d) ", curPair[j].a, curPair[j].b);

				}
				printf("\n");
				*/
		//start
		curResult=0;
		recurFindPair(0);

		//printf("%d\n", curResult/fact(numOfPerson/2));
		
		printf("%d\n", curResult);
		i++;




		

	}




}