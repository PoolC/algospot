#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

char stack[10001];
int top;


int main()
{
	int numOfCase;
	scanf("%d", &numOfCase);
		
	char str[10001];
	gets(str);//??
	for(int i=0; i<numOfCase; i++)
	{
		gets(str);
		int size;
		for(size=0; size<10001; size++)
			if(str[size]==0) break;
		
		top=-1;
		bool success=true;
		for(int j=0; j<size; j++)
		{
			//여기까징 오면 스택이 비어있진 않음
			switch(str[j])
			{
			case '[':
			case '(':
			case '{':
				top++;
				stack[top]=str[j];
				break;
			case ']':
				if(stack[top]=='[')
					top--;
				else
					success=false;
				break;
			case ')':
				if(stack[top]=='(')
					top--;
				else
					success=false;
				break;
			case '}':
				if(stack[top]=='{')
					top--;
				else
					success=false;
				break;
			}

			if(success==false) break;
		}
		if(success==true && top==-1) printf("YES\n");
		else printf("NO\n");

	}

}
