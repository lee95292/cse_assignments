#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<ncursesw/curses.h>
#include<locale.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"auction.h"
#include"LandInfo.h"
#include"draw.h"
#include"timer.h"
#include"board.h"
#include"playerInfo.h"
#include"client.h"

#define PORTNUM 13246
#define BUFF_SIZ 512

extern int min;
int n, x, y = 2;//getch로 입력 받는 키, 현재 커서 x, y 좌표

void drawmenu()
{
	char buff[BUFF_SIZ];

	sprintf(buff, "경매의 신");

	mvprintw(10, 70 - strlen(buff) / 2, "%s", buff);// 게임 제목 출력

	refresh();

	
	WINDOW* select = newwin(5, 14, 17, 62);//선택 창 생성
	wborder(select, '*', '*', '*', '*', '*', '*', '*', '*');//구분 선 그리기

	sprintf(buff, "시작");
	mvwprintw(select, 1, 8 - strlen(buff) / 2, "%s", buff);//시작버튼 출력
	sprintf(buff, "도움말");
	mvwprintw(select, 2, 8 - strlen(buff) / 2, "%s", buff);//도움말 버튼 출력
	sprintf(buff, "종료");
	mvwprintw(select, 3, 8 - strlen(buff) / 2, "%s", buff);//종료버튼 출력
	mvwprintw(select, 1, 2, "*");
	wmove(select, 1, 2);
	wrefresh(select);
	
	while (n = getch())
	{
		getyx(select, y, x);
		switch (n)
		{
		case KEY_UP:
			if (y > 1)
			{
				mvwprintw(select, y, x, " ");
				mvwprintw(select, y - 1, x, "*");
				wmove(select, y - 1, x);
			}
			break;
		case KEY_DOWN:
			if (y < 3)
			{
				mvwprintw(select, y, x, " ");
				mvwprintw(select, y + 1, x, "*");
				wmove(select, y + 1, x);
			}
			break;
		}

		if (n == '\n')
			break;

		wrefresh(select);
	}

	delwin(select);
}

void drawmenu2()
{
	char buff[BUFF_SIZ];

	refresh();

	WINDOW* select = newwin(8, 20, 15, 58);//선택 창 생성
	wborder(select, '*', '*', '*', '*', '*', '*', '*', '*');//구분 선 그리기

	sprintf(buff, "내 이름 설정");
	mvwprintw(select, 1, 12 - strlen(buff) / 2, "%s", buff);//이름 설정 버튼 출력
	sprintf(buff, "내 정보 보기");
	mvwprintw(select, 2, 12 - strlen(buff) / 2, "%s", buff);//이름 정보 버튼 출력
	sprintf(buff, "방 생성");
	mvwprintw(select, 3, 12 - strlen(buff) / 2, "%s", buff);//방 생성 버튼 출력
	sprintf(buff, "방 입장");
	mvwprintw(select, 4, 12 - strlen(buff) / 2, "%s", buff);//방 입장 버튼 출력
	sprintf(buff, "방 정보");
	mvwprintw(select, 5, 12 - strlen(buff) / 2, "%s", buff);//방 정보 버튼 출력
	sprintf(buff, "게임 종료");
	mvwprintw(select, 6, 12 - strlen(buff) / 2, "%s", buff);//종료 버튼 출력
	mvwprintw(select, 1, 2, "*");
	wmove(select, 1, 2);
	wrefresh(select);

	while (n = getch())
	{
		getyx(select, y, x);
		switch (n)
		{
		case KEY_UP:
			if (y > 1)
			{
				wmove(select, y, 2);
				wprintw(select, " ");
				wmove(select, y - 1, 2);
				wprintw(select, "*");
			}
			break;
		case KEY_DOWN:
			if (y < 6)
			{
				wmove(select, y, 2);
				wprintw(select, " ");
				wmove(select, y + 1, 2);
				wprintw(select, "*");
			}
			break;
		}

		if (n == '\n')
			break;

		wrefresh(select);
	}

	getyx(select, y, x);
	n = y;

	delwin(select);
}

int main()
{
	char buf[BUFF_SIZ];
	char* tmpbuf;// recv로 받은 문자열 분해
	struct sockaddr_in sin;
	int sd, readBytes;
	int pid;

	int rn;//방 번호

	int shmid;//공유 메모리 식별자
	char* shmaddr;//공유 메모리

	pinfo me;//내 정보
	int mynum;//내 순서

	setlocale(LC_ALL, "ko_KR.UTF-8");
	initscr();
	init_board();
	start_color();
	init_drawColor();
	curs_set(0);						//커서를 보이지 않게 한다.
	noecho();							//입력된 키를 화면에 보이지 않게 한다.
	cbreak();							//엔터가 불필요한 입력은 사용하지 않는다.
	keypad(stdscr, TRUE); 				//커서키를 사용가능하게 한다.

	while (y == 2)
	{
		clear();
		drawmenu();

		switch (y)
		{
		case 1://게임 시작
			break;
		case 2://도움말
			clear();
			do
			{
				sprintf(buf, "경매의 신 게임 진행 방식은 다음과 같습니다.");
				mvprintw(4, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "1. 방에 입장하면 다른 플레이어들이 다 입장할 때 까지 기다립니다.");
				mvprintw(6, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "2. 다른 플레이어가 다 입장하면 게임을 시작합니다.");
				mvprintw(8, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "3. 30초동안 상단에 타이머가 작동되는데 이 시간동안 경매를 진행합니다.");
				mvprintw(10, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "4. 숫자를 입력하면 입찰가가 갱신 됩니다.");
				mvprintw(12, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "1은 입찰가가 1 증가되고 2는 10, 3은 100, 4는 1000이 증가합니다.");
				mvprintw(13, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "0을 입력하면 현재 입찰가가 초기화 됩니다.");
				mvprintw(14, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "5. 타이머가 종료되면 가장 높은 입찰가를 입력한 플레이어가 승리합니다.");
				mvprintw(16, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "승리한 플레이어는 보드판에 자신의 영토를 둘수 있게 됩니다.");
				mvprintw(17, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "패배한 플레이어는 승리한 플레이어가 영토를 둘 때 까지 대기합니다.");
				mvprintw(18, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "6. 영토를 두면 다시 게임을 진행합니다.");
				mvprintw(20, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "7. 보드판이 다 차면 게임이 종료됩니다.");
				mvprintw(22, 80 - strlen(buf) / 2, "%s", buf);
				sprintf(buf, "가장 많은 영토를 확보한 플레이어가 승리합니다.");
				mvprintw(23, 80 - strlen(buf) / 2, "%s", buf);
				touchwin(stdscr);
			} while (!getch());
			break;
		case 3://게임 종료
			endwin();
			exit(1);
			break;
		}
	}

	clear();//화면 지우기

	y = x = 1;// 서버가 보낸 메시지 표시하기 위해서 위치 초기화
	
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		endwin();
		exit(1);
	}

	if (connect(sd, (struct sockaddr*)&sin, sizeof(sin)))
	{
		perror("connect");
		endwin();
		exit(1);
	}

	if (recv(sd, buf, BUFF_SIZ, 0) == -1)
	{
		perror("recv");
		endwin();
		exit(1);
	}

	mvprintw(10, 70 - strlen(buf) / 2 - 1, "%s", buf);

	refresh();

	sprintf(buf, "f");
	send(sd, buf, BUFF_SIZ, 0);// 유저 이름 요청
	recv(sd, buf, BUFF_SIZ, 0);// 내 이름 받음
	tmpbuf = strtok(buf, " ");
	if (tmpbuf[0] == 'f')
	{
		tmpbuf = strtok(NULL, " ");//유저 번호 분리
		tmpbuf = strtok(NULL, " ");//유저 이름 분리
		strcpy(me.pname, tmpbuf);//이름 저장
	}

	shmid = shmget(IPC_PRIVATE, BUFF_SIZ, IPC_CREAT | 0644);
	shmaddr = (char *)shmat(shmid, (char *)NULL, 0);
	shmaddr[0] = '0';

	if ((pid = fork()) == 0)
	{
		while (1)//recv로 받아 출력만 해줄 프로세스
		{
			if (recv(sd, buf, BUFF_SIZ, 0) < 0)
			{
				exit(1);
				break;
			}

			clear();
			wmove(stdscr, 1, 1);
			getyx(stdscr, y, x);

			tmpbuf = strtok(buf, " ");
			n = tmpbuf[0];//뭘 보내왔나 해독

			switch (n)
			{
			case 'i'://열려있는 모든 방 정보를 보여줌
				while (tmpbuf != NULL)
				{
					tmpbuf = strtok(NULL, " ");
					if (tmpbuf != NULL)
					{
						wmove(stdscr, y, 1);
						wprintw(stdscr, " %s", tmpbuf);//방 번호
						tmpbuf = strtok(NULL, " ");
						wprintw(stdscr, " %s", tmpbuf);//사람 수
						tmpbuf = strtok(NULL, " ");
						wprintw(stdscr, " %s", tmpbuf);//방 이름
						y++;
					}
					else
					{
						wmove(stdscr, y, 1);
						wprintw(stdscr, "%d개 만큼 방이 열려있습니다.                  ", y - 1);//방 번호
						y++;
					}
				}
				refresh();//화면 갱신
				break;
			case 's'://유저 이름 설정
				tmpbuf = strtok(NULL, " ");
				wmove(stdscr, y, 1);
				wprintw(stdscr, " %s", tmpbuf);//성공 메시지 출력
				y++;
				refresh();
				break;
			case 'm'://방을 생성
				tmpbuf = strtok(NULL, " ");
				wmove(stdscr, y, 1);
				wprintw(stdscr, " %s", tmpbuf);//방 번호 출력
				y++;
				sprintf(buf, "%d %s", 1, tmpbuf);//공유 메모리에 저장
				strcpy(shmaddr, buf);//방 입장 성공을 알려줌
				refresh();
				break;
			case 'f'://유저 이름 설정
				tmpbuf = strtok(NULL, " ");
				wmove(stdscr, y, 1);
				wprintw(stdscr, " %s", tmpbuf);//유저 번호 출력
				tmpbuf = strtok(NULL, " ");
				wprintw(stdscr, " %s", tmpbuf);
				y++;
				refresh();
				break;
			case 'r'://방 입장
				tmpbuf = strtok(NULL, " ");
				wmove(stdscr, y, 1);
				wprintw(stdscr, " %s", tmpbuf);//방 번호 출력
				y++;
				sprintf(buf, "%d %s", 1, tmpbuf);//공유 메모리에 저장
				strcpy(shmaddr, buf);//방 입장 성공을 알려줌
				refresh();
				break;
			case 'e'://에러 메시지
				wmove(stdscr, y, 1);
				wprintw(stdscr, " %s", tmpbuf);//에러 메시지 출력
				y++;
				refresh();
				break;
			}
			if (shmaddr[0] == '1')
				exit(1);
			y++;
		}
	}
	else//send만 관리할 프로세스
	{
		while (1)
		{
			drawmenu2();// 서버 통신 메뉴 출력
			clear();
			touchwin(stdscr);
			wmove(stdscr, 1, 60);
			getyx(stdscr, y, x);
			y++;
			buf[0] = '\0';
			char buff[BUFF_SIZ];
			switch (n)
			{
			case 1://유저 이름 세팅인 경우
				clear();
				wmove(stdscr, 1, 1);
				wprintw(stdscr, "내 유저 이름을 입력하세요                       ");
				wmove(stdscr, 2, 1);
				echo();//쓴 문자열을 보여줌
				getstr(buff);//이름 받음
				strcpy(me.pname, buff);// 유저 이름 복사
				sprintf(buf, "s %s", buff);
				break;
			case 2://유저 정보 요청
				sprintf(buf, "f");//보통의 경우 명령어를 보내줌
				break;
			case 3://방 생성인 경우
				clear();
				wmove(stdscr, 1, 1);
				wprintw(stdscr, "방 이름을 입력하세요                      ");
				wmove(stdscr, 2, 1);
				echo();//쓴 문자열을 보여줌
				getstr(buff);//방 이름 받음
				sprintf(buf, "m %s", buff);
				break;
			case 4://방 입장
				clear();
				wmove(stdscr, 1, 1);
				wprintw(stdscr, "방 번호를 입력하세요                   ");
				wmove(stdscr, 2, 1);
				echo();//쓴 문자열을 보여줌
				getstr(buff);//방 번호 받음
				sprintf(buf, "r %s", buff);
				break;
			case 5://방 정보 요청
				sprintf(buf, "i");
				break;
			case 6://게임 종료 버튼
				endwin();
				send(sd, "q", BUFF_SIZ, 0);
				close(sd);
				kill(pid, SIGKILL);	
				exit(1);//게임 종료
				break;
			}
			noecho();//쓴 문자열 안보여줌			
			if (send(sd, buf, BUFF_SIZ, 0) < 0)
			{
				endwin();
				close(sd);
				exit(1);
			}
			touchwin(stdscr);
			sleep(1);

			if (shmaddr[0] == '1')
				break;//방 입장에 성공 했으면 게임 창 출력
		}
		
		int price;//여기부터는 경매 진행 코드다
		int status;
		int phase = 0;//0이면 경매 1이면 보드선택
		int isselected = 0;//보드 선택 완료 여부
		int pos[2] = { -1, -1 };// 보드판에서 어느 좌표를 선택 했는가
		clear();
		initpinfo();
		tmpbuf = strtok(shmaddr, " ");
		tmpbuf = strtok(NULL, " ");//방 번호 분리함
		rn = atoi(tmpbuf);//방 번호 저장

		sprintf(buf, "f");//내 이름 알아오기
		if (send(sd, buf, BUFF_SIZ, 0) <= 0)
		{
			endwin();
			perror("send");
			exit(1);
		}
		if (recv(sd, buf, BUFF_SIZ, 0) <= 0)
		{
			endwin();
			perror("recv");
			exit(1);
		}

		tmpbuf = strtok(buf, " ");
		tmpbuf = strtok(NULL, " ");//내 번호
		tmpbuf = strtok(NULL, " ");//내 이름
		strcpy(me.pname, tmpbuf);//내 이름 저장

		sprintf(buf, "u %d", rn);//방에 존재하는 사람 이름 요청
		send(sd, buf, BUFF_SIZ, 0);//서버에 요청
		int k = 1;//바로 밑의 while문 조건용

		while (k)
		{
			if (recv(sd, buf, BUFF_SIZ, 0) < 0)
			{
				endwin();
				perror("recv");
				exit(1);
			}
			tmpbuf = strtok(buf, " ");
			k = 0;
			for (int i = 0; i < 4; i++)//현재 접속된 유저 이름 저장
			{
				tmpbuf = strtok(NULL, " ");
				if (tmpbuf == NULL)
				{
					gvname(i, "없음");
					k = 1;//한명이라도 접속자수가 모자라면 다시 루프를 돈다.
				}
				else
				{
					gvname(i, tmpbuf);// 이름 설정
					if (!strcmp(tmpbuf, me.pname))//내 이름이라면 순서 저장
						mynum = i;
				}
			}

			me.money = parr[mynum].money;//내 돈 저장
			me.tmoney = parr[mynum].tmoney;

			auctionwindow();
			touchwin(stdscr);
		}

		LInfo* land = malloc(sizeof(LInfo));//경매 물품
		land->resource = malloc(sizeof(char) * 20);
		char* tmp = malloc(sizeof(char) * BUFF_SIZ);

		auctionwindow();// 창에 줄 그리기
		touchwin(stdscr);
		int t = 1;
		sprintf(tmp, "g");
		send(sd, tmp, BUFF_SIZ, 0);//g메시지를 보냄
		while (1)//게임 시작
		{
			attron(COLOR_PAIR(6));
			if (phase == 0)//경매 대기중
			{
				while (1)
				{
					int p;//경매 승리한 플레이어 번호 변수
					recv(sd, tmp, BUFF_SIZ, 0);//승리자의 정보 또는 게임 시작 정보를 받아옴
					n = tmp[0];//첫번째 글자 갖고옴
					tmpbuf = strtok(tmp, " ");

					switch (n)
					{
					case 'b'://보드판 좌표를 받은 경우
						tmpbuf = strtok(NULL, " ");//유저 이름
						p = findpnum(tmpbuf);
						giveinfo(atoi(strtok(NULL, " ")), atoi(strtok(NULL, " ")), p + 1);//보드판 반영
						draw_map();
						touchwin(stdscr);
						attron(COLOR_PAIR(6));
						t = 0;//아직 안차있는 보드가 있나
						for (int i = 0; i < 4; i++)//턴 골드만큼 수익 획득
						{
							updateinfo(i, parr[i].tmoney, 0);
						}
						me.money += parr[mynum].tmoney;
						int pb[4] = { 0,0,0,0 };
						for (int i = 0; i < 5; i++)
						{
							for (int j = 0; j < 5; j++)
							{
								switch (board[i][j])
								{
								case 1:
									pb[0]++;
									break;
								case 2:
									pb[1]++;
									break;
								case 3:
									pb[2]++;
									break;
								case 4:
									pb[3]++;
									break;
								default:
									t = 1;
									break;
								}
							}
						}
						if (!t)//보드가 다 차있다면
						{
							int tmpi = 0;
							int max = 0;
							for (int i = 0; i < 4; i++)
							{
								if (max < pb[i])
								{
									max = pb[i];
									tmpi = i;
								}
							}
							attron(COLOR_PAIR(6));
							sprintf(tmp, "%s 플레이어의 승리!", parr[tmpi].pname);
							mvprintw(21, 70 - strlen(tmp) / 2, "%s", tmp);
							sprintf(tmp, "게임을 종료하려면 아무 키나 누르세요");
							mvprintw(22, 70 - strlen(tmp) / 2, "%s", tmp);
							touchwin(stdscr);
						}
						else
						{
							sprintf(tmp, "g");//게임 시작 메시지를 서버에 보냄
							send(sd, tmp, BUFF_SIZ, 0);
						}
						break;
					case 'g':
						strcpy(land->resource, strtok(NULL, " "));//자원 이름
						land->price = atoi(strtok(NULL, " "));//자원 가치						
						attron(COLOR_PAIR(6));
						sprintf(tmp, "소지 자원 : %s", land->resource);
						int s = strlen(tmp);
						mvprintw(19, 70 - s / 2, tmp);//자원 문자열 출력
						sprintf(tmp, "턴당 추가수익 : %d", land->price);
						s = strlen(tmp);
						mvprintw(20, 70 - s / 2, tmp);//수익 문자열 출력
						pplayerinfo();
						touchwin(stdscr);
						break;
					}
					if (n == 'g' || !t)
						break;//게임 시작이나 종료이면 루프 탈출
				}
			}
			if (!t)
			{
				while (!getch())
					continue;
				endwin();
				sprintf(buf, "q");
				send(sd, buf, BUFF_SIZ, 0);
				exit(1);
				break;//게임이 종료 됬으므로 게임을 종료한다.
			}
			if ((pid = fork()) == 0)//타이머 스타트
			{
				timer_t timerid;

				createTimer(&timerid, 30);

				while (1)
				{
					usleep(200);
					if (min < 0)
					{
						attron(COLOR_PAIR(6));
						timer_delete(&timerid);
						break;
					}
				}

				exit(1);
			}
			else//경매 진행
			{
				n = 0;
				price = 0;
				attron(COLOR_PAIR(6));
				do
				{
					if (waitpid(pid, &status, WNOHANG) == 0)//경매중
						phase = 0;
					else//보드 선택
					{
						if (!phase)//보드 선택할 차례라면
						{
							sprintf(buf, "p %d", price);
							send(sd, buf, BUFF_SIZ, 0);//가격을 보냄
							recv(sd, buf, BUFF_SIZ, 0);//최대 입찰자 정보를 받음
							tmpbuf = strtok(buf, " ");
							tmpbuf = strtok(NULL, " ");//이름
							if (!strcmp(tmpbuf, me.pname))
								phase = 1;//내가 승리했으니 보드판에서 선택
							else
								phase = 0;
							mvwprintw(stdscr, 26, 70 - strlen(tmpbuf) / 2, "%s", tmpbuf);
							if (mynum == findpnum(tmpbuf))
							{
								me.money -= -(atoi(tmpbuf = strtok(NULL, " ")));
								me.tmoney += land->price;
							}
							updateinfo(findpnum(tmpbuf), -(atoi(tmpbuf))/*경매가*/, land->price);//경매 승리자의 정보 업데이트
							
							pplayerinfo();
							wprintw(stdscr, " %s", tmpbuf);
							touchwin(stdscr);
							if (phase == 0)
								break;//루프를 나가서 승리자의 보드 선택 정보가 올 때 까지 대기
						}
					}
					switch (n)
					{
					case '0':
						if (!phase)
							price = 0;
						else
						{
							if (pos[0] == -1)
								pos[0] = 0;
							else
							{
								pos[1] = 0;
								isselected = 1;//선택 완료
							}
						}
						break;
					case '1':
						if (!phase)
							price += 1;
						else
						{
							if (pos[0] == -1)
								pos[0] = 1;
							else
							{
								pos[1] = 1;
								isselected = 1;//선택 완료
							}
						}
						break;
					case '2':
						if (!phase)
							price += 10;
						else
						{
							if (pos[0] == -1)
								pos[0] = 2;
							else
							{
								pos[1] = 2;
								isselected = 1;//선택 완료
							}
						}
						break;
					case '3':
						if (!phase)
							price += 100;
						else
						{
							if (pos[0] == -1)
								pos[0] = 3;
							else
							{
								pos[1] = 3;
								isselected = 1;//선택 완료
							}
						}
						break;
					case '4':
						if (!phase)
							price += 1000;
						else
						{
							if (pos[0] == -1)
								pos[0] = 4;
							else
							{
								pos[1] = 4;
								isselected = 1;//선택 완료
							}
						}
						break;
					case 8:
						if (phase)
						{
							pos[0] = -1;
							pos[1] = -1;
							isselected = 0;
						}
						break;
					case 127:
						if (phase)
						{
							pos[0] = -1;
							pos[1] = -1;
							isselected = 0;
						}
						break;
					default:
						break;
					}
					if (!phase)
					{
						if (price > me.money)
							price = me.money;
						sprintf(tmp, "입찰가 : %d      ", price);
					}
					else
					{
						attron(COLOR_PAIR(6));
						mvprintw(27, 50, "                    ");
						sprintf(tmp, "%d, %d   ", pos[0], pos[1]);
					}
					mvprintw(27, 70 - strlen(tmp) / 2, "%s", tmp);
					if (isselected&&n == '\n'&&board[pos[0]][pos[1]] == 7)//선택 완료이므로, 보드판 출력
					{
						//giveinfo(pos[0], pos[1], mynum);//플레이어의 소유권으로 둠
						sprintf(tmp, "b %d %d", pos[0], pos[1]);//서버에 선택 정보 전송
						send(sd, tmp, BUFF_SIZ, 0);
						phase = 0;
						break;//루프 탈출
					}
					else if(isselected&&n == '\n'&&board[pos[0]][pos[1]] != 7)//잘못 선택한 경우
					{
						pos[0] = -1;
						pos[1] = -1;
						isselected = 0;
						attron(COLOR_PAIR(6));
						mvprintw(25, 50, "다른 플레이어의 영토를 선택하셨습니다. 다시 선택해 주세요.");
					}
					move(5, 70);
					refresh();
				} while (n = getch());
			}
		}
	}

	return 0;
	
}