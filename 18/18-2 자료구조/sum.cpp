#include<stdio.h>
int SUM(int);
int main()
{
	int a=0;
	scanf("%d",&a);
	printf("%d",SUM(a));
}

int SUM(int n)
{
	if(n<0)
		return 0;
	else if(1==n)
		return 1;
	else
		return n+SUM(n-1);		
}
