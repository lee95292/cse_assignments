#include"LandInfo.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

static char* rn[9] = { "금", "은", "다이아몬드", "루비", "사파이어", "에메랄드", "구리", "철", "석유" };//자원 이름들을 저장할 배열
static int rm[9] = { 1000, 100, 2000, 600, 500, 400, 50, 70, 300 };//자원 가치를 저장할 배열

LInfo* initLand()
{
	LInfo* info = malloc(sizeof(LInfo));//땅의 정보 생성

	srand(time(NULL));

	int n = rand() % 9;//무작위 자원 생성

	info->resource = malloc(sizeof(char)*(strlen(rn[n]) + 1));//자원 이름을 저장하기 위해서 공간 할당

	strcpy(info->resource, rn[n]);//자원 이름 대입
	info->price = rm[n];//자원의 턴당 수익 대입

	return info;
}