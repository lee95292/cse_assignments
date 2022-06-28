#include<stdio.h>
int FACT(int);
int main()
{
	int a=0;
	scanf("%d",&a);
	printf("%d",FACT(a));
}

int FACT(int n)
{
	if(0>=n)
		return -1;
	else if(1==n)
		return 1;
	else
		return n*FACT(n-1);
}
