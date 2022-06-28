/**
* Author:이명규 (201716422)
* Date :18_09_21
* Description:
	하노이타워 규칙을 지키면서 원판들을 
	옮기는 방법을 기술한 프로그램입니다.
	원판번호 (1~n)과의 중복을 피하기 위해 초기값을
	from:A, using:B, to:C 로 하였습니다.
	n =3, n=4일때의 결과를 출력합니다. 
 
**/

#include<stdio.h>

void Hanoi(int, char,char,char);

int main()
{
	printf("----------n=3-----------\n");
	Hanoi(3,'A','C','B');
	printf("\n----------n=4----------\n");
	Hanoi(4,'A','C','B');
}

void Hanoi(int n,char from, char to,char use)
{
	
	if(n==1)
		printf("Move %d from %c to %c\n",n,from,to);
	else
	{
		Hanoi(n-1,from,use,to);
		printf("Move %d from %c to %c\n",n,from,to);
		Hanoi(n-1,use,to,from);
	}
}

