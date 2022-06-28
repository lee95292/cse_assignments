#include<stdio.h>
int FACT_SUM(int);
int FACT(int);
int main()
{
	int a=0;
	scanf("%d",&a);
	printf("%d",FACT_SUM(a));
}

int FACT_SUM(int n)
{
	if(0>=n)
		return -1;
	else if(1==n)
		return 1;
	else
	{
		return FACT_SUM(n-1) + FACT(n);	
	}
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
