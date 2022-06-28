#include"playerInfo.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ncursesw/curses.h>

void initpinfo()
{
	for (int i = 0; i < 4; i++)
	{
		strcpy(parr[i].pname, "\0");
		parr[i].money = 10000;
		parr[i].tmoney = 500;
	}
}

void updateinfo(int pnum, int m, int t)
{
	parr[pnum].money += m;
	parr[pnum].tmoney += t;
}

void gvname(int pnum, char* name)
{
	strcpy(parr[pnum].pname, name);
}

void pplayerinfo()//플레이어 정보 출력
{
	attron(COLOR_PAIR(6));
	char tmp[256];
	sprintf(tmp, "%s 소지금 : %d", parr[0].pname, parr[0].money);
	mvprintw(9, 15 - strlen(tmp) / 2, "%s", tmp);
	sprintf(tmp, "%s 수익 : %d", parr[0].pname, parr[0].tmoney);
	mvprintw(10, 15 - strlen(tmp) / 2, "%s", tmp);

	sprintf(tmp, "%s 소지금 : %d", parr[2].pname, parr[2].money);
	mvprintw(29, 15 - strlen(tmp) / 2, "%s", tmp);
	sprintf(tmp, "%s 수익 : %d", parr[2].pname, parr[2].tmoney);
	mvprintw(30, 15 - strlen(tmp) / 2, "%s", tmp);

	sprintf(tmp, "%s 소지금 : %d", parr[1].pname, parr[1].money);
	mvprintw(9, 125 - strlen(tmp) / 2, "%s", tmp);
	sprintf(tmp, "%s 수익 : %d", parr[1].pname, parr[1].tmoney);
	mvprintw(10, 125 - strlen(tmp) / 2, "%s", tmp);

	sprintf(tmp, "%s 소지금 : %d", parr[3].pname, parr[3].money);
	mvprintw(29, 125 - strlen(tmp) / 2, "%s", tmp);
	sprintf(tmp, "%s 수익 : %d", parr[3].pname, parr[3].tmoney);
	mvprintw(30, 125 - strlen(tmp) / 2, "%s", tmp);

	refresh();
}

int findpnum(char* name)
{
	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(name, parr[i].pname))//플레이어 이름에 해당하는 번호 return
			return i;
	}
}