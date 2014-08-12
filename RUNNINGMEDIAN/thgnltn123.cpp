#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<cstring>

#define MOD 20090711


struct node
{
	node* left;
	node* right;
	int value;
};

int main()
{
	int numOfCase;
	scanf("%d", &numOfCase);
	for(int i=0; i<numOfCase; i++)
	{
		int num, a, b;
		scanf("%d %d %d", &num, &a, &b);

		int A=1983;

		int sum=1983;
		node* mid;

		mid=(node*)malloc(sizeof(node));
		mid->value=A;
		mid->left=NULL;
		mid->right=NULL;
		
		for(int j=1; j<num; j++)
		{
			A=((long long)A*a+b)%MOD;
			
			//insert
			node* target=mid;

			while(1)
			{
				if(A<target->value)
				{
					if(target->left==NULL)
					{
						target->left=(node*)malloc(sizeof(node));
						target->left->left=NULL;
						target->left->right=NULL;
						target->left->value=A;
						break;
					}
					else
					{
						target=target->left;
						continue;
					}
				}

				{
					if(target->right==NULL)
					{
						target->right=(node*)malloc(sizeof(node));
						target->right->left=NULL;
						target->right->right=NULL;
						target->right->value=A;
						break;
					}
					else
					{
						target=target->right;
						continue;
					}
				}
			}

			if(j%2==1&&A<mid->value)
			{
				node* newMid=mid->left;
				node* newMidParent=mid;
				while(newMid->right!=NULL)
				{
					newMidParent=newMid;
					newMid=newMid->right;
				}
		
				newMid->right=mid;

				
				if(newMidParent!=mid)
				{
					node* newLeftMost=newMid;
					while(newLeftMost->left!=NULL)
						newLeftMost=newLeftMost->left;
					newLeftMost->left=mid->left;
					newMidParent->right=NULL;
				}
				mid->left=NULL;
				mid=newMid;
			}

			else if(j%2==0&&A>mid->value)
			{
				node* newMid=mid->right;
				node* newMidParent=mid;

				
				while(newMid->left!=NULL)
				{
					newMidParent=newMid;
					newMid=newMid->left;
				}
		
				newMid->left=mid;

				
				if(newMidParent!=mid)
				{
					node* newRightMost=newMid;
					while(newRightMost->right!=NULL)
						newRightMost=newRightMost->right;
					newRightMost->right=mid->right;
					newMidParent->left=NULL;
				}
				mid->right=NULL;
				mid=newMid;
			}
			sum=((long long)sum+mid->value)%MOD;
		}
		printf("%d\n", sum);
	}

	
}
