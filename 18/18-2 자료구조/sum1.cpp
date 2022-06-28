#include<stdio.h>
int SUM1(int);
int main()
{
	int a=0;
	scanf("%d",&a);
	printf("%d",SUM1(a));
}

int SUM1(int n)
{
	if(0>=n)
		return 0;
	else if(1==n)
		return 1;
		
	else
	{
		return SUM1(n-1)+(n*(n+1))/2;  //= SUM(n)
	}
}
