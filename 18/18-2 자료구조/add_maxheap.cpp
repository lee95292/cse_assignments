#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

int heap[MAX_SIZE];
int total_node= 0;
void add_heap(int item);

int main()
{
	int i;
	add_heap(10);
	add_heap(20);
	add_heap(5);
	add_heap(12);
	add_heap(40);
	add_heap(80);
	for(i=1;i<=total_node;i++)
		printf("%d ",heap[i]);
		
}

void add_heap(int item)
{
	int i;
	if(total_node>=MAX_SIZE-1)exit(1);
	i=++total_node;
	
	while((i!=1)&&(item>heap[i/2]))
	{
		heap[i]=heap[i/2];
		i/=2;
	}
	heap[i]=item;
}
