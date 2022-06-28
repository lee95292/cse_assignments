#include <stdio.h>
#define N 8         /* 정점의 수 */
#define M 9999
int a[N+1][N+1]={{0,0,0,0,0,0,0,0,0}, /* 인접행렬 */
                 {0,0,1,7,2,M,M,M,M},
                 {0,1,0,M,M,2,4,M,M},
                 {0,7,M,0,M,M,2,3,M},
                 {0,2,M,M,0,M,M,5,M},
                 {0,M,2,M,M,0,1,M,M},
                 {0,M,4,2,M,1,0,M,6},
                 {0,M,M,3,5,M,M,0,2},
                 {0,M,M,M,M,M,6,2,0}};
int main(int argc, char* argv[])
{
    int j,k,p,start,min,
        leng[N+1],              /* 정점까지의 거리 */
        v[N+1];                 /* 확정 플래그 */
    printf("시작점 : ");
 scanf("%d",&start);
    for (k=1;k<=N;k++) {
        leng[k]=M;v[k]=0;
    }
    leng[start]=0;
    for (j=1;j<=N;j++) {
        min=M;          /* 최소인 정점을 찾는다 */
        for (k=1;k<=N;k++) {
            if (v[k]==0 && leng[k]<min) {
                p=k; min=leng[k];
            }
        }
        v[p]=1;            /* 최소인 정점을 확정한다 */
        if (min==M) {
            printf("그래프가 연결되어 있지 않다.\n");
            return 1;
        }
        /* p를 경유해서 k에 이르는 거리가 지금까지의 최단경로보다 작으면 갱신 */
        for (k=1;k<=N;k++) {
            if((leng[p]+a[p][k])<leng[k])
                leng[k]=leng[p]+a[p][k];
        }
    }
    for (j=1;j<=N;j++)
        printf("%d -> %d : %d\n",start,j,leng[j]);
}

