#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<cstring>

char name[100][11];
int edge[26][26][100];
int edgeCount[26][26];
int numOfEdge;
int start;
int end;
int size;

int resultOuted[26][26];
void recurFind(int cur, int oldPath[100])
{
	for(int i=0; i<26; i++)
	{
		while(edgeCount[cur][i]>0)
		{
			edgeCount[cur][i]--;
			recurFind(i, oldPath);
		}
	}
	oldPath[size++]=cur;
}

int main()
{
	int numOfCase;
	scanf("%d", &numOfCase);
	char buffer[11];
	for(int i=0; i<numOfCase; i++)
	{
		for(int j=0; j<26; j++)
			for(int k=0; k<26; k++)
			{
				edgeCount[j][k]=0;
				resultOuted[j][k]=0;

			}
		scanf("%d", &numOfEdge);

		for(int j=0; j<numOfEdge; j++)
		{
			scanf("%s", buffer);
			int strLength=strlen(buffer);
			int firstIndex=buffer[0]-'a';
			int lastIndex=buffer[strLength-1]-'a';
			
			for(int k=0; k<=strLength; k++)
				name[j][k]=buffer[k];
			
			edge[firstIndex][lastIndex][edgeCount[firstIndex][lastIndex]++]=j;
		}
		

		int resultPath[101];

		//circuit인지 테스트
		bool  isCircuit=true;
		for(int j=0; j<26; j++)
		{
			int jIn=0;
			int jOut=0;

			for(int z=0; z<26; z++)
			{
				jIn+=edgeCount[z][j];
				jOut+=edgeCount[j][z];
			}

			
			if(jOut!=jIn)
				isCircuit=false;

			if(isCircuit==false) break;
		}

		if(isCircuit==true)//circuit임. 
		{
			start=name[numOfEdge-1][0]-'a';
			end=start;

			size=0;
			recurFind(start, resultPath);
			if(size!=numOfEdge+1) printf("IMPOSSIBLE\n");
			else
			{
				for(int j=numOfEdge; j>0; j--)
				{
					if(j!=1)
						printf("%s ", name[edge[resultPath[j]][resultPath[j-1]][(resultOuted[resultPath[j]][resultPath[j-1]]++)]]);
					else printf("%s\n", name[edge[resultPath[j]][resultPath[j-1]][(resultOuted[resultPath[j]][resultPath[j-1]]++)]]);
				}
			}
		}

		else//start랑 end를 찾아야함
		{
			start=-1;
			end=-1;
			bool find=true;
			for(int j=0; j<26; j++)
			{
				int jIn=0;
				int jOut=0;

				for(int z=0; z<26; z++)
				{
					jIn+=edgeCount[z][j];
					jOut+=edgeCount[j][z];
				}

				if(jOut==jIn+1)
				{
					if(start==-1) start=j;
					else find=false;
				}

				else if(jOut==jIn-1)
				{
					if(end==-1) end=j;
					else find=false;
				}
				
				else if(jOut!=jIn)
					find=false;

				if(find==false) break;
			}

			if(find==true)
			{
				size=0;
				recurFind(start, resultPath);
				if(size!=numOfEdge+1) printf("IMPOSSIBLE\n");
				else
				{
					for(int j=numOfEdge; j>0; j--)
					{
						if(j!=1)
							printf("%s ", name[edge[resultPath[j]][resultPath[j-1]][(resultOuted[resultPath[j]][resultPath[j-1]]++)]]);
						else printf("%s\n", name[edge[resultPath[j]][resultPath[j-1]][(resultOuted[resultPath[j]][resultPath[j-1]]++)]]);
					}
				}

			}
			else printf("IMPOSSIBLE\n");	
		}
	}

}
