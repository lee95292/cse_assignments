
#include <stdio.h>
#define node 8  
#define m 9999   

int d[node]; 
int p[node]; 

int cost[node][node] = {
{ m,2,m,5,m,m,m,m },
{ m,m,11,m,6,m,m,m },
{ m,m,m,m,4,m,m,14 },
{ m,m,7,m,m,9,m,m },
{ m,m,m,m,m,m,10,m },
{ m,m,m,m,1,m,2,m },
{ m,m,m,m,m,m,m,8 },
{ m,m,m,m,m,m,m,m }
};


int checkVisit(int d[], int n, int p[])
{
	
	int i, min, check;
	min = m;
	check = -1;

	for (i = 0; i < n; i++)
	{
		if (d[i] < min && p[i] == 0)
		{
			min = d[i];
			check = i;
		}
	}
	return check;
}

void distance(int n)
{
	int i, vst, j;
	for (i = 0; i < n; i++)
	{
		d[i] = cost[0][i]; 
		p[i] = 0;
	}
	p[0] = 1;
	d[0] = 1;

	for (i = 0; i < n - 1; i++) 
	{
		vst = checkVisit(d, n, p);
		p[vst] = 1;

		for (j = 0; j < n; j++)
		{
			if (p[j] == 0)
			{
				if (d[vst] + cost[vst][j] < d[j])
				{
					d[j] = d[vst] + cost[vst][j];
				}
			}
		}
	}

	printf("노드 1에서 노드 8까지의 최단거리는 %d\n", d[node-1]);
}

void main()
{
	distance(node);
}

