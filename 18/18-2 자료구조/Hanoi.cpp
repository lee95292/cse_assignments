/**
* Author:�̸�� (201716422)
* Date :18_09_21
* Description:
	�ϳ���Ÿ�� ��Ģ�� ��Ű�鼭 ���ǵ��� 
	�ű�� ����� ����� ���α׷��Դϴ�.
	���ǹ�ȣ (1~n)���� �ߺ��� ���ϱ� ���� �ʱⰪ��
	from:A, using:B, to:C �� �Ͽ����ϴ�.
	n =3, n=4�϶��� ����� ����մϴ�. 
 
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

