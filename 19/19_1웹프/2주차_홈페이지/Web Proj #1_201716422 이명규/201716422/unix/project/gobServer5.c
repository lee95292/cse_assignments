#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/times.h>
#include <limits.h>
//#include<mysql/mysql.h>

#define PORTNUM 16969

#define MAX_CLIENT 24
#define MAX_ROOM 6

#define INST_SIZE 512
#define RES_SIZE 512
#define NAME_LEN 20

///////////////////////////////////////////////
typedef struct
{
    char resource[15];
	int price;																						   //턴당 획득 할 수 있는 돈
} LInfo;																							   //땅 속성
static char *rn[9] = {"금", "은", "다이아몬드", "루비", "사파이어", "에메랄드", "구리", "철", "석유"}; //자원 이름들을 저장할 배열
static int rm[9] = {1000, 100, 2000, 600, 500, 400, 50, 70, 300};									   //자원 가치를 저장할 배열

void initLand(LInfo *info)
{
	srand(time(NULL));
	int n = rand() % 9;											 //무작위 자원 생성
    strcpy(info->resource,rn[n]);
	info->price = rm[n];		   //자원의 턴당 수익 대입
}
typedef struct User
{
	int userNum;
	int roomNum;
	int myPrice;
	int x,y;
	char *userName;

} UserInfo;

typedef struct Room
{
	int roomNum;
	char *roomName;

	int goCheck;
	int priceRcheck;
	int maxPrice;
	int binded;
	int maxUserNum;
	
	int ncurUser;
	int curUser[4];
} RoomInfo;

void initUser(UserInfo *user[MAX_CLIENT]) //userNum은 1번부터 사용한다. room에서 userNum=0은 입장하지 않은 상태
{
	int i;
	for (i = 1; i <= MAX_CLIENT; i++)
	{
		user[i]->userName = (char *)malloc(sizeof(char) * NAME_LEN);
		user[i]->userNum = 0;
		user[i]->roomNum = 0;
		user[i]->myPrice=0;
		user[i]->x=0;
		user[i]->y=0;
		sprintf(user[i]->userName, "User_%d", i);
	}
}

int setUserName(UserInfo *user, char *instruction)
{
	char *tokPtr = strtok(instruction, " ");

	if (strlen(tokPtr) <= NAME_LEN) //userNum out bound
	{
		strcpy(user->userName, strtok(NULL, " "));
		return 1;
	}
	else
		return -1;
}

void initRoom(RoomInfo *room[MAX_CLIENT]) //모든 방 초기화, room은 1번방부터 쓴다. 유저에서 roomNum=0 은 입장하지 않은 상태
{
	int i, j;
	for (i = 0; i <= MAX_ROOM; i++)
	{
		room[i]->roomNum = 0;
		room[i]->roomName = (char *)malloc(sizeof(char) * NAME_LEN);
		room[i]->ncurUser = 0;
		sprintf(room[i]->roomName, "Room%d", i);
		room[i]->binded=0;
		room[i]->maxPrice=0;
		room[i]->maxUserNum=0;
		room[i]->goCheck = 0;
		room[i]->priceRcheck;
		for (j = 0; j < 4; j++)
		{
			room[i]->curUser[j] = 0; //초기 user : 0
		}
	}
}

int getNextRoomNum(RoomInfo *room[MAX_CLIENT])
{
    int i;
	for (i = 1; i <= MAX_CLIENT; i++)
	{
		if (room[i]->roomNum == 0)
		{
			return i;
		}
	}
	return -1; //최대 방생성개수 초과
}
int makeRoom(RoomInfo *room, char *instruction, int roomNum)
{
	char *tokPtr = strtok(instruction, " ");
	if (roomNum <= 0)
		return -1; //full house
	else if (room->roomNum == 0)
	{
		room->roomNum = roomNum;
		//room->roomName=strtok(NULL," ");
		strcpy(room->roomName, strtok(NULL, " "));
		printf("room name : %s", room->roomName);
		return roomNum;
	}
}
int enterRoom(UserInfo *user, RoomInfo *room) //방 입장 , 성공 시 방에서의 순서,풀 하우스의 경우 -1 리턴,	방에 이미 참가한 경우 -2
{
	int i, eflag = -1;
	if (user->roomNum != 0)
		return -2;

	for (i = 0; i < 4; i++)
	{
		if (room->curUser[i] == 0) //i번째 칸이 비었을 경우,
		{
			eflag = i;
			break;
		}
	}
	//++ 방에 있는 인원들에게 유저 이름 전송
	if (eflag == -1) //full house
		return -1;
	else
	{
		room->curUser[eflag] = user->userNum;
		room->ncurUser++;
		user->roomNum = room->roomNum;
		return eflag;
	}
}

int exitRoom(struct User *user, struct Room *room)
{

	if (room->roomNum > MAX_ROOM || user->userNum > MAX_CLIENT || room->roomNum < 1 || user->userNum < 1) // 0<userNum<=MAXUSER , 0<roomNum<=MAXRoom
		return -1;

	user->roomNum = 0;
    int i;
	for ( i = 0; i < 4; i++)
	{
		if (room->curUser[i] == user->userNum)
		{
			room->curUser[i] = 0;
			room->ncurUser--;
		}
	}
}
void setUMsg(char *response, RoomInfo *room,UserInfo* user[MAX_CLIENT+1])
{
	sprintf(response, "u");
	int i,b;
	for (i = 0; i < 4; i++)
	{
		b = room->curUser[i];
		if (b != 0)
		{
			sprintf(response, "%s %s", response, user[b]->userName);
		}
	}
}
///////////////////////////////////////////////////////////
struct tms rtime;
clock_t t1, t2;

int main()
{
	char response[RES_SIZE];
	struct sockaddr_in sin, cli;
	int sd, ns[MAX_CLIENT], clientlen = sizeof(cli), i;

	char *shmaddrp[MAX_CLIENT];
	char *shmaddrc;

	int clnum;
	time_t t;
	int tmp, b;
	char *tmpbuf;

	t1 = times(&rtime);

	// 쉐어메모리 선언 및 인덱싱_--------------------
	//int instShmId;		//instruction 통신용 쉐어메모리 아이디

	char instruction[INST_SIZE];
	//instruction = (char**)malloc(sizeof(char)*(MAX_CLIENT+1)*INST_SIZE);
	//instShmId = shmget(IPC_PRIVATE, sizeof(char)*(MAX_CLIENT+1)*INST_SIZE,IPC_CREAT|0644);
	//instruction = (char **)shmat(instShmId, NULL, 0);

	UserInfo *user[MAX_CLIENT + 1];
	int userShmId[MAX_CLIENT + 1]; //user 구조체 공유용 쉐어메모리 아이디
	for (i = 0; i <= MAX_CLIENT; i++)
	{
		user[i] = (UserInfo *)malloc(sizeof(UserInfo));
		userShmId[i] = shmget(IPC_PRIVATE, sizeof(UserInfo), IPC_CREAT | 0644);
		user[i] = (UserInfo *)shmat(userShmId[i], NULL, 0);
	}

	int roomShmId[MAX_CLIENT + 1]; //roomInfo 구조체 공유용 쉐어메모리 아이디
	RoomInfo *roomInfo[MAX_CLIENT + 1];
	for (i = 0; i <= MAX_CLIENT; i++)
	{
		roomInfo[i] = (RoomInfo *)malloc(sizeof(RoomInfo));
		roomShmId[i] = shmget(IPC_PRIVATE, sizeof(RoomInfo), IPC_CREAT | 0644);
		roomInfo[i] = (RoomInfo *)shmat(roomShmId[i], NULL, 0);
	}

	int landShmId; //LInfo 구조체 공유용 쉐어메모리 아이디
	LInfo *landInfo;
	landInfo = (LInfo *)malloc(sizeof(LInfo));
	landShmId = shmget(IPC_PRIVATE, sizeof(RoomInfo), IPC_CREAT | 0644);
	landInfo = (LInfo *)shmat(landShmId, NULL, 0);

	int pidsShmid;
	int *pids;
	pids = (int *)malloc(sizeof(int) * (MAX_CLIENT + 1));
	pidsShmid = shmget(IPC_PRIVATE, sizeof(pids), IPC_CREAT | 0644);
	pids = (int *)shmat(pidsShmid, NULL, 0);

	// int userIndexShmId; 	//접속한 클라이언트에 순서 부여되는 순서 | 공유메모리
	// int* uis;
	// uis = malloc(sizeof(int)*(MAX_CLIENT+1));
	// userIndexShmId= shmger(IPC_PRIVATE, sizeof(int)*(MAX_CLIENT+1), IPC_CREAT|0644);
	// uis =(int*) shmat(userIndexShmId, NULL, 0);

	// --------------------쉐어메모리 선언 및 인덱싱
	initRoom(roomInfo);
	initUser(user);
	initLand(landInfo);
	int uisIdx = 0;

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("bind");
		exit(1);
	}

	if (listen(sd, MAX_CLIENT))
	{
		perror("listen");
		exit(1);
	}

	printf("..wait for client..\n");
	while (1)
	{
		for (i = 1; i <= MAX_CLIENT; i++) //유저 생성 및 자식서버 넘버 설정
		{
			if (user[i]->userNum == 0)
			{
				user[i]->userNum = i;
				uisIdx = i; //uisIdx : 클라이언트 넘버 (= 유저 넘버)
				break;
			}
		}
		if ((ns[uisIdx] = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
		{
			perror("accept");
			exit(1);
		}
		/*
			유저 입장부분 작성 : 현재 shmi로 쓰이고 있는 유저 인덱싱 알고리즘 개발
			: 배열에서 쭉 진행하다가 0인 값 발견하면 userNum으로 알려주기
		*/
		if ((pids[uisIdx] = fork()) == 0)
		{
			close(sd);
			char *tokPtr;
			int nextRidx = 0, entered = 0, maked = 0;
			for (i = 1; i <= MAX_CLIENT; i++) //공유메모리 참조
			{
				roomInfo[i] = (RoomInfo *)shmat(roomShmId[i], NULL, 0);
				user[i] = (UserInfo *)shmat(userShmId[i], NULL, 0);
			}
			landInfo = (LInfo *)shmat(landShmId, NULL, 0);
			pids = (int *)shmat(pidsShmid, NULL, 0);
			//instruction = (char *)shmat(instShmId, NULL, 0);
			printf("Client Entered : User %d\n", uisIdx);
			strcpy(response, "Welcome to Server");
			if (send(ns[uisIdx], response, INST_SIZE, 0) == -1)
			{
				perror("send");
				exit(1);
			}

			while ((b = recv(ns[uisIdx], instruction, INST_SIZE, 0)) > 0)
			{
				printf("From User %d request: <%s>\n", uisIdx,instruction);
				switch (instruction[0])
				{
				case 's':
					/*
							set UserInfo, 
							req: "s usrName"
							res : ok - "accept" 
								fail - "e errInfo"
						*/
					if (setUserName(user[uisIdx], instruction) == 1)
						sprintf(response, "accept : user name : %s", user[uisIdx]->userName);
					else
						sprintf(response, "e userName out Bound");

					send(ns[uisIdx], response, RES_SIZE, 0); //response send
					break;
				case 'm':
					/*
							make room
							req : "m roomName"
							res : "m roomNumber"
							fail : "e errinfo"
							1. 유저가 방에 참가하지 않았을 경우 
						*/

					nextRidx = getNextRoomNum(roomInfo);
					maked = makeRoom(roomInfo[nextRidx], instruction, nextRidx);
					entered = enterRoom(user[uisIdx], roomInfo[nextRidx]);

					if (nextRidx > 0 && maked > 0 && entered >= 0) //if success
					{
						sprintf(response, "m %d", nextRidx);
					}
					else if (nextRidx == -1) //if fail
					{
						sprintf(response, "e Num Max Room outbounded");
					}
					else if (entered == -1)
					{
						sprintf(response, "e it's Full house");
					}
					else if (entered == -2)
					{
						sprintf(response, "e user already entered");
					}
					else
					{
						sprintf(response, "e Unkown Error: Maked : %d / Entered : %d / nextRidx: %d", maked, entered, nextRidx);
					}
					send(ns[uisIdx], response, RES_SIZE, 0);

					if ((b = recv(ns[uisIdx], instruction, INST_SIZE, 0)) > 0) //f 받기
					{
						printf("From User %d request: <%s>\n", uisIdx, instruction);
						sprintf(response, "f %d %s", uisIdx, user[uisIdx]->userName);

						send(ns[uisIdx], response, RES_SIZE, 0);
						printf("To   User %d response : <%s>\n", uisIdx, response); //test
					}

					if ((b = recv(ns[uisIdx], instruction, INST_SIZE, 0)) > 0) //u 받기
					{
						printf("From User %d request: <%s>\n", uisIdx, instruction);

						char *tokPtr = strtok(instruction, " ");
						tokPtr = strtok(NULL, " ");
						if (atoi(tokPtr) != 0)
							setUMsg(response, roomInfo[atoi(tokPtr)],user);
						else
							sprintf(response, "e roomnumber set err");

						send(ns[uisIdx], response, RES_SIZE, 0);
						printf("To   User %d response : <%s>\n", uisIdx, response); //test
					}
					printf("User %d wailt for enter User..\n", uisIdx);
					b = roomInfo[maked]->ncurUser;
					while (roomInfo[maked]->ncurUser <= 4)
					{
						printf("User %d workding\n", uisIdx);
						if (roomInfo[maked]->ncurUser != b)
						{
							b = roomInfo[maked]->ncurUser;
							setUMsg(response, roomInfo[maked],user);
							printf("To   User %d response : <%s>\n", uisIdx, response); //test
							send(ns[uisIdx], response, RES_SIZE, 0);
						}
						if (roomInfo[maked]->ncurUser == 4)
						{
							printf("All User Entered \n");
							break;
						}
						sleep(1);
					}
					break;
				case 'i':
					/*
							room info 
							req : "i"
							res : "i num1 1name ... "
						*/
					sprintf(response, "i");
					for (i = 0; i < MAX_CLIENT; i++)
					{
						if (roomInfo[i]->roomNum != 0)
						{
							printf("%s", roomInfo[i]->roomName);
							sprintf(response, "%s %d %s %d", response, roomInfo[i]->roomNum, roomInfo[i]->roomName, roomInfo[i]->ncurUser);
						}
					}

					send(ns[uisIdx], response, RES_SIZE, 0); //response send
					break;

				case 'r':
					/*
							enter room 
							req : "r roomnum"
							if usr can enter room
								res: "r roomnum "
							if usr cant enter room
								res: "e errinfo"
						*/
					tokPtr = strtok(instruction, " ");
					if ((tmp = atoi(strtok(NULL, " "))) >= 0 && tmp <= MAX_ROOM) //tmp==roomNum
					{
						if (enterRoom(user[uisIdx], roomInfo[tmp]) < 0)
						{
							sprintf(response, "e enterroom error");
						}
						else
							sprintf(response, "r %d", tmp);
					}
					else
						sprintf(response, "e request error");
					printf("To   User %d response : <%s>\n", uisIdx, response); //test
					send(ns[uisIdx], response, RES_SIZE, 0);

					if ((b = recv(ns[uisIdx], instruction, INST_SIZE, 0)) > 0) //f 받기
					{
						printf("From User %d request: <%s>\n", uisIdx, instruction);
						sprintf(response, "f %d %s", uisIdx, user[uisIdx]->userName);

						send(ns[uisIdx], response, RES_SIZE, 0);
						printf("To   User %d response : <%s>\n", uisIdx, response); //test
					}

					if ((b = recv(ns[uisIdx], instruction, INST_SIZE, 0)) > 0) //u 받기
					{
						printf("From User %d request: <%s>\n", uisIdx, instruction);

						char *tokPtr = strtok(instruction, " ");
						tokPtr = strtok(NULL, " ");
						if (atoi(tokPtr) != 0)
							setUMsg(response, roomInfo[atoi(tokPtr)],user);
						else
							sprintf(response, "e roomnumber set err");

						send(ns[uisIdx], response, RES_SIZE, 0);
						printf("To   User %d response : <%s>\n", uisIdx, response); //test
					}

					//입장정보 처리중..
					b = roomInfo[tmp]->ncurUser;
					while (roomInfo[tmp]->ncurUser <= 4)
					{
						printf("User %d workding\n", uisIdx);
						if (roomInfo[tmp]->ncurUser != b)
						{
							b = roomInfo[tmp]->ncurUser;
							setUMsg(response, roomInfo[tmp],user);
							printf("To   User %d response : <%s>\n", uisIdx, response); //test
							send(ns[uisIdx], response, RES_SIZE, 0);
						}
						if (roomInfo[tmp]->ncurUser == 4)
						{
							printf("All user entered : %d \n", uisIdx);
							break;
						}
						sleep(1);
					}
					break;

				case 'f':
					/*
						show user info
						req: "f"
						res : "f usrNum usrName"
						if usrname null: set usrName
					*/
					if (user[uisIdx]->userName == NULL)
						sprintf(response, "e set userName");
					else
						sprintf(response, "f %d %s", user[uisIdx]->userNum, user[uisIdx]->userName);
					send(ns[uisIdx], response, RES_SIZE, 0);
					break;
				case 'u':
					/*
						user in room
						req: "u roomnum"
						res: "u user1Name '''"
						fail: "e errInfo"
					*/
					tokPtr = strtok(instruction, " ");
					tokPtr = strtok(NULL, " "); // u 뒤에 나오는 숫자
					if (atoi(tokPtr) != 0)
					{
						setUMsg(response, roomInfo[atoi(tokPtr)],user); //현재 방의 방정보를 세팅
					}
					else
						sprintf(response, "e userInfo service error");
					send(ns[uisIdx], response, RES_SIZE, 0);
					break;
				case 'g':
                    b = user[uisIdx]->roomNum;
					
					roomInfo[b]->maxPrice=0;							//다음 턴을 위해 최대경매가 초기화
					user[uisIdx]->myPrice=0;
                    roomInfo[b]->priceRcheck=0;

                    sleep(2);
					roomInfo[b]->binded=0;

					roomInfo[b]->goCheck++;
					
					sprintf(response, "g %s %d", landInfo->resource, landInfo->price);
					send(ns[uisIdx], response, RES_SIZE, 0);
					break;
				case 'p':
					/*
						나의 입찰가를 받아서 최대 입찰가를 전송해라
					*/
					tokPtr= strtok(instruction," ");
				
					b=roomInfo[user[uisIdx]->roomNum]->goCheck;
					if(b!=0) roomInfo[user[uisIdx]->roomNum]->goCheck=0;				//b는 gocheck 4로 지정된 go Check 초기화
					
					b=user[uisIdx]->roomNum;											//b는 룸넘버
					UserInfo* maxUser;
					user[uisIdx]->myPrice=atoi(strtok(NULL," "));						//나의 입찰가

					if(user[uisIdx]->myPrice > roomInfo[b]->maxPrice)					//myprice > maxprice
					{
						roomInfo[b]->maxPrice = user[uisIdx]->myPrice;
						maxUser = user[uisIdx];
						roomInfo[b]->maxUserNum=maxUser->userNum;
					}
						roomInfo[b]->priceRcheck++;
					//c=roomInfo[b]->priceRcheck;
					while(roomInfo[b]->priceRcheck < 4)		//최댓값 입력이 덜되었다.
					{
						//if(roomInfo[b]->priceRcheck!=c)printf("priceInfo changed");
						printf("User %d wait Other Client pri Check:%d\n",uisIdx,roomInfo[b]->priceRcheck);
						sleep(1);
					}
					printf("All price input :User%d\n",uisIdx);

					sprintf(response,"p %s %d",user[roomInfo[b]->maxUserNum]->userName,roomInfo[b]->maxPrice);
					printf("To User%d Response : <%s>\n",uisIdx,response);
					send(ns[uisIdx], response, RES_SIZE, 0);
					
					while(user[uisIdx]->myPrice != roomInfo[b]->maxPrice)		//최댓값 처리하는 유저가 아니면 반복
					{
						printf("User %d wait for tender pick area.. binded = %d ,roomNum : %d\n",uisIdx,roomInfo[b]->binded,roomInfo[b]->roomNum);
						sleep(1);
						if(roomInfo[b]->binded==1) 							// 최대입찰자의 b메시지 처리 후, 최대입찰자의 정보 전송
						{													
							sleep(1);
							printf("tender pickied ared.. User%d wait for chosing\n",uisIdx);
							b=roomInfo[user[uisIdx]->roomNum]->maxUserNum;

							sprintf(response,"b %s %d %d",user[b]->userName,user[b]->y,user[b]->x);
							send(ns[uisIdx], response, RES_SIZE, 0);
							break;								
						}
					}
					break;

				case 'b':					
					b=roomInfo[user[uisIdx]->roomNum]->maxUserNum;
					printf("instruction in b opt::%s, maxUserNum:%d \n",instruction,b);
					
					tokPtr=strtok(instruction," ");
					user[b]->y=atoi(strtok(NULL," "));
					user[b]->x=atoi(strtok(NULL," "));
					roomInfo[user[uisIdx]->roomNum]->binded=1;
					
                    initLand(landInfo);
					
					sprintf(response,"b %s %d %d",user[b]->userName,user[b]->y,user[b]->x);
					send(ns[uisIdx], response, RES_SIZE, 0);
					break;
					//					default:
				}
				printf("To   User %d response : <%s>\n", uisIdx, response); //test
				sprintf(response, " "); //message execueted
				fflush(stdout);
			}

			exit(0);
		}

		close(ns[uisIdx]);
	}
}
