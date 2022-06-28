#include<stdio.h>
#include"board.h"

void init_board()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board[i][j] = 7;//모두 0으로 초기화
		}
	}

	board[0][0] = 1;//플레이어 1 시작지점
	board[0][4] = 2;//플레이어 2 시작지점
	board[4][0] = 3;//플레이어 3 시작지점
	board[4][4] = 4;//플레이어 4 시작지점
}


void giveinfo(int r, int c, int n)
{
	board[r][c] = n;//플레이어 n의 소유권 놓음.
}