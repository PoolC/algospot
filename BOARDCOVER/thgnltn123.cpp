#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

bool** board;



struct StackNode
{
	bool** board;
	int remain;
	struct StackNode* next;
};

StackNode* stackTop;

int h;
int w;
int curRemain;
long long curResult;

struct pointNode
{
	int x;
	int y;

};


bool** makeNewBoard()
{
	bool** result= new bool*[h];
	for(int i=0; i<h; i++)
		result[i]=new bool[w];
	return result;
}

void deleteBoard(bool** target)
{
	for(int i=0; i<h; i++)
		delete[] target[i];
	delete[] target;
}


struct pointNode findNext(int startY, int startX)
{
	for(int y=startY; y<h; y++)
	{
		int x;
		if(y==startY)
			x=startX;
		else x=0;
		for(;x<w; x++)
			if(board[y][x]==true)
			{
				struct pointNode result;
				result.x=x;
				result.y=y;

				return result;

			}

	}


	printf("Error! no point to return\n");
	system("Pause");


}



void push()
{
	struct StackNode *newNode= (struct StackNode *)malloc(sizeof(StackNode));
	
	newNode->board=makeNewBoard();
	newNode->remain=curRemain;
	for(int i=0; i<h; i++)
		for(int j=0; j<w; j++)
			newNode->board[i][j]=board[i][j];


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
	struct StackNode* target;

	if(stackTop==NULL)
	{
		printf("stack underflow!=n");
		system("Pause");
	}

	target=stackTop;
	curRemain=target->remain;
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<w; j++)
			board[i][j]=target->board[i][j];
		delete[] target->board[i];
	}
	delete[] target->board;


	if(target->next!=NULL)
		stackTop=target->next;
	else
		stackTop=NULL;
	
	free(target);
}



void recurBoardFunc(int curH, int curW)
{
	/*case 1: 
	CO
	O
	*/
	

	
	if(curW!=w-1&&curH!=h-1&&board[curH][curW]==true&&board[curH+1][curW]==true&&board[curH][curW+1]==true)
	{
		if(curRemain==3)
		{
			curResult++;
			return;
		}
		else 
		{
			push();
			board[curH][curW]=false;
			board[curH+1][curW]=false;
			board[curH][curW+1]=false;
			curRemain-=3;
			struct pointNode next=findNext(curH, curW);
	
			recurBoardFunc(next.y, next.x);
			pop();
		}
	}

	/*case 2: 
	CO
	 O
	*/

	if(curW!=w-1&&curH!=h-1&&board[curH][curW]==true&&board[curH][curW+1]==true&&board[curH+1][curW+1]==true)
	{
		if(curRemain==3)
		{
			curResult++;
			return;
		}
		else
		{
			push();
			board[curH][curW]=false;
			board[curH][curW+1]=false;
			board[curH+1][curW+1]=false;
			curRemain-=3;
			struct pointNode next=findNext(curH, curW);

			recurBoardFunc(next.y, next.x);
			pop();
		}
	}


	/*case 3: 
	 C
	OO
	*/

	if(curW!=0&&curH!=h-1&&board[curH][curW]==true&&board[curH+1][curW]==true&&board[curH+1][curW-1]==true)
	{
		if(curRemain==3)
		{
			curResult++;
			return;
		}
		else
		{
			push();
			board[curH][curW]=false;
			board[curH+1][curW]=false;
			board[curH+1][curW-1]=false;
			curRemain-=3;
			struct pointNode next=findNext(curH, curW);

			recurBoardFunc(next.y, next.x);
			pop();
		}

	}

	/*case 4:
	C
	OO
	*/


	if(curW!=w-1&&curH!=h-1&&board[curH][curW]==true&&board[curH+1][curW]==true&&board[curH+1][curW+1]==true)
	{
		if(curRemain==3)
		{
			curResult++;
			return;
		}
		else
		{
			push();
			board[curH][curW]=false;
			board[curH+1][curW]=false;
			board[curH+1][curW+1]=false;
			curRemain-=3;
			struct pointNode next=findNext(curH, curW);

			recurBoardFunc(next.y, next.x);
			pop();
		}
	}

	return;

}



int main()
{
	int numOfCase;

	stackTop=NULL;

	scanf("%d", &numOfCase);

	

	for(int i=0;i<numOfCase;i++)
	{
		scanf("%d %d", &h, &w);
		char input[21];

		//initialize
		board=makeNewBoard();
		curRemain=0;
		curResult=0;

		for(int j=0; j<h; j++)
		{
			scanf("%s", &input);
			for(int k=0; k<w; k++)
			{
				if(input[k]=='#')
					board[j][k]=false;

				else if(input[k]=='.')
				{
					board[j][k]=true;
					curRemain++;
				}

				else
				{
					printf("Error Input!\n");
					system("Pause");
				}
			}
		}

		/*
		printf("for debug!\n");
		for(int j=0; j<h; j++)
		{
			for(int k=0; k<w; k++)
			{
				if(board[j][k]==false)
					printf("#");
				else 
					printf(".");
				
			}
			printf("\n");
		}
		*/


		//start
		struct pointNode next=findNext(0,0);
		recurBoardFunc(next.y, next.x);
		printf("%d\n", curResult);


		//printf("%d\n", curResult/fact(numOfPerson/2));


		
		deleteBoard(board);
	}




}
