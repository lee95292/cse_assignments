#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncursesw/curses.h>
#include<locale.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"auction.h"
#include"LandInfo.h"
#include"draw.h"
#include"timer.h"
#include"board.h"
#include"playerInfo.h"


#define BUFFSIZ 256
extern int min;
int price;
int pid;
int status;
int phase = 1;//0이면 경매 1이면 보드선택
int isselected = 0;//보드 선택 완료
int pos[2] = { -1, -1 };// 보드판 위치

void drawline_h()//플레이어 금액 표시 영역을 가를 선
{
	attron(COLOR_PAIR(5));
	for (int i = 0; i < 30; i++)
	{
		mvprintw(20, i, " ");
		mvprintw(20, 110 + i, " ");
	}
}

void drawline_tb()//타이머와 보드 영역을 가를 선
{
	attron(COLOR_PAIR(5));
	for (int i = 0; i < 80; i++)
	{
		mvprintw(10, i + 30, " ");
		mvprintw(30, i + 30, " ");
	}
}

void auctionwindow()
{
	drawline_c(30);//경매창을 나눌 세로 줄 그리기
	drawline_c(110);
	drawline_h();
	drawline_tb();
	pplayerinfo();
	draw_map();
}