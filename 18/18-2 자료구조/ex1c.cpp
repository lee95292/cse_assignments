#include<stdio.h>
#include<stdlib.h>

int main()
{
	int* a= (int*)malloc(4*sizeof(int));
	printf("%d",sizeof(a));
	
	int c=2000000000;
	if(c<2100000000)
	printf("asd");
}
