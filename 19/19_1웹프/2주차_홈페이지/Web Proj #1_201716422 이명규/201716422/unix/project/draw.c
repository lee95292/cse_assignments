#include <locale.h>
#include <ncursesw/curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "draw.h"
#include "board.h"

void init_drawColor()
{
	init_pair(5, COLOR_BLACK, COLOR_WHITE);//선그리기
	init_pair(1, COLOR_RED, COLOR_RED);//게임 보드에서 플레이어 1 영토
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW);//플레이어 2 영토
	init_pair(3, COLOR_GREEN, COLOR_GREEN);//플레이어 3 영토
	init_pair(4, COLOR_BLUE, COLOR_BLUE);//플레이어 4 영토
	init_pair(6, COLOR_WHITE, COLOR_BLACK);//글자 출력 용 색
	init_pair(7, COLOR_CYAN, COLOR_CYAN);//무소유
}


void draw_map()//board 정보에 따라 출력
{
	attron(COLOR_PAIR(5));
	mvprintw(32, 63, "  ");
	for (int i = 0; i < 5; i++)
	{
		mvprintw(32, i * 2 + 65, "%d ", i);//열 표시
		mvprintw(33 + i, 63, " %d", i);//행 표시
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			attron(COLOR_PAIR(board[i][j]));
			mvaddch(i + 33, j*2 + 65, ACS_BLOCK);
			addch(ACS_BLOCK);
		}
	}
	refresh();
}

void drawline_r(int n)
{
	attron(COLOR_PAIR(5));//선은 흰색으로
	for (int i = 0; i < 140; i++)
	{
		mvprintw(n, i, "\t");//선그리기
	}
}

void drawline_c(int n)
{
	attron(COLOR_PAIR(5));
	for (int i = 0; i < 40; i++)
	{
		mvprintw(i, n, "\t");
	}
}

void main_init()
{
	setlocale(LC_ALL, "ko_KR.UTF-8");
	initscr();
	init_board();
	start_color();
	init_drawColor();
	curs_set(0);						//커서를 보이지 않게 한다.
	noecho();							//입력된 키를 화면에 보이지 않게 한다.
	cbreak();							//엔터가 불필요한 입력은 사용하지 않는다.
	keypad(stdscr, TRUE); 				//커서키를 사용가능하게 한다.

	return;
}