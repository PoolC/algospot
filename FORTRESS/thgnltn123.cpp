#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct node
{
	struct node* next;
	struct node* childStart;
	int x;
	int y;
	int r;
};

struct myResult
{
	int depth;
	int result;
};


node* root;

bool isIn(int x, int y, int fx, int fy, int fr)
{
	return((x-fx)*(x-fx)+(y-fy)*(y-fy)<=fr*fr)?true:false;
}

node* recurFind(int x, int y, int r, node* target)
{
	if(!isIn(x,y,target->x, target->y, target->r)) return NULL;

	node* current;
	for(current=target->childStart; current!=NULL; current=current->next)
	{
		if(!isIn(x,y,current->x,current->y,current->r)) continue;
		node* result=recurFind(x, y, r, current);
		if(result!=NULL) return result;
	}
	
	return target;

}

void recurDelete(node* target)
{

	for(node* current=target->childStart; current!=NULL; )
	{
		node* next=current->next;
		recurDelete(current);
		current=next;

	}
	free(target);
	return;
}

int findDepth(node* target)
{
	int max=0;
	if(target->childStart==NULL) return 1;
	for(node* current=target->childStart; current!=NULL; current=current->next)
	{
		int tempResult=findDepth(current);
		if(max<tempResult) max=tempResult;
	}
	return max+1;

}

myResult recurResult(node* target)
{
	if(target->childStart==NULL)
	{
		myResult temp;
		temp.depth=0;
		temp.result=0;
		return temp;
	}


	int maxResult=0;
	int maxDepth1=0;
	int maxDepth2=0;
	for(node* current=target->childStart; current!=NULL; current=current->next)
	{
		myResult temp=recurResult(current);
		if(temp.depth>maxDepth1)
		{
			maxDepth2=maxDepth1;
			maxDepth1=temp.depth;
		}
		else if(temp.depth>maxDepth2)
			maxDepth2=temp.depth;
		if(temp.result>maxResult) maxResult=temp.result;
	}

	if(target->childStart->next!=NULL&&(maxDepth1+maxDepth2+2)>maxResult) maxResult=(maxDepth1+maxDepth2+2);
	if(maxDepth1+1>maxResult) maxResult=maxDepth1+1;

	myResult tempResult;
	tempResult.depth=maxDepth1+1;
	tempResult.result=maxResult;
	return tempResult;
	
}



int main()
{
	int numOfCase;
	scanf("%d", &numOfCase);
	int inputs[100][3];
	for(int i=0; i<numOfCase; i++)
	{
		int numOfInput;
		scanf("%d", &numOfInput);
		
		int inputSize;
		for(inputSize=0; inputSize<numOfInput; inputSize++)
			scanf("%d %d %d", &inputs[inputSize][0], &inputs[inputSize][1], &inputs[inputSize][2]);

		root=(node*)malloc(sizeof(node));
		root->x=inputs[0][0];
		root->y=inputs[0][1];
		root->r=inputs[0][2];
		root->next=NULL;
		root->childStart=NULL;

		//일단 사이즈별로 정렬
		for(int j=1; j<inputSize; j++)
		{
			for(int k=1; k<inputSize-j; k++)
			{
				if(inputs[k][2]<inputs[k+1][2])
				{
					int temp=inputs[k][0];
					inputs[k][0]=inputs[k+1][0];
					inputs[k+1][0]=temp;

					temp=inputs[k][1];
					inputs[k][1]=inputs[k+1][1];
					inputs[k+1][1]=temp;

					temp=inputs[k][2];
					inputs[k][2]=inputs[k+1][2];
					inputs[k+1][2]=temp;
				}
			}
		}

		

		for(int j=1; j<inputSize; j++)
		{
			
			if(root->childStart==NULL)
			{
				node* newNode=(node*)malloc(sizeof(node));
				newNode->childStart=NULL;
				newNode->next=NULL;
				newNode->x=inputs[j][0];
				newNode->y=inputs[j][1];	
				newNode->r=inputs[j][2];
				root->childStart=newNode;
			}
			else
			{
				node* target=recurFind(inputs[j][0], inputs[j][1], inputs[j][2], root);

				node* newNode=(node*)malloc(sizeof(node));
				newNode->childStart=NULL;
				newNode->next=target->childStart;
				newNode->x=inputs[j][0];
				newNode->y=inputs[j][1];	
				newNode->r=inputs[j][2];
				target->childStart=newNode;
			}
		}

		printf("%d\n", recurResult(root).result);

		//다되면 삭제해야됨
		recurDelete(root);
	}
}
