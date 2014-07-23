#include<cstdio>
int t,n,i,d[100]{1,2};int main(){scanf("%d",&t);for(i=2;i<100;i++)d[i]=(d[i-1]+d[i-2])%1000000007;while(t--){scanf("%d",&n);printf("%d\n",d[n-1]);}return 0;}