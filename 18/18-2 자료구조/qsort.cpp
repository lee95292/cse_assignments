/**
* Author :이명규  
* Date : 2018.10.07
* Description: 10개 이상의 배열 원소들에 대해, 퀵 정렬을 수행해주는 프로그램입니다. 
*/

#include<stdio.h>
#define comp 10

void qsort(int,int,int[]);

int main()
{
	int a[comp]={10,2,5,4,11,22,9,12,44,21};
	int i;
	
	printf("배열의 구성요소들을 입력하세요(%d개)\n",comp);
    
    for(i=0;i<comp;i++)
    {
      scanf("%d",&a[i]);	
	}printf("===================\n");
	qsort(0,comp-1,a);
}

void qsort(int l, int r,int data[])
{
	int piv=(l+r)/2;
	int lp=l,rp=r;
	int temp;

	do
	{
		
	
		while(data[lp]<data[piv])lp++;
		while(data[rp]>data[piv])rp--;
		
	  	if(lp<=rp)
	  	{
	  	//	printf("%d %d\n",lp,rp);
	  		for(int i=0;i<comp;i++)
			{
				printf("%d ",data[i]);
			}printf("\n");
	  		printf("data[%d]:%d <<>> data[%d]:%d\n\n",lp,data[lp],rp,data[rp]);
			temp=data[lp];
			data[lp]=data[rp];
			data[rp]=temp;
			lp++;
			rp--;
			
	  	}
		

	}while(lp<=rp);
	
	if(l<rp)
		qsort(l,rp,data);
	if(r>lp)
		qsort(lp,r,data);
}


