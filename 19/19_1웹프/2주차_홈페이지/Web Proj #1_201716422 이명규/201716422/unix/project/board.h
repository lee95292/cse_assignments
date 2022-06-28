int board[5][5];//게임 보드 판
void init_board();//보드판 초기화
void giveinfo(int r, int c, int n);//(r,c)에 n번째 플레이어가 토지를 획득한 정보를 보드판에 저장
// 소유권 정보를 송수신 할때 문자열은 이렇게 되어 있다
// 보드의 행 r/ 보드의 열 c/ n번째 플레이어 n