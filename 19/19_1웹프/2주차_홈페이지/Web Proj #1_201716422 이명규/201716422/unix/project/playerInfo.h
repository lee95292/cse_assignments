typedef struct
{
	char pname[20];//플레이어 이름
	int money;//소지금
	int tmoney;//턴당 소득
}pinfo;

pinfo parr[4];//플레이어 정보 배열

void initpinfo();//배열 초기화 함수
void gvname(int pnum, char* name);//플레이어 이름 부여
void updateinfo(int pnum, int m, int t);//소지금, 턴 소득 변화
void pplayerinfo();
int findpnum(char* name);//입력된 이름을 가진 플레이어 번호를 return