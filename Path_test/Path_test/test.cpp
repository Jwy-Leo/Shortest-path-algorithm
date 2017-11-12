#include "3rdparty.h"
#include "parameter.h"
#include "My_map.h"
#include "ant.h"
using namespace std;
void randE_B(int*sx,int*sy,int*ex,int*ey);
void main()
{
	
	int sx,sy,ex,ey;
	randE_B(&sx,&sy,&ex,&ey);
	My_map MAP(POINT_N*POINT_D,POINT_N*POINT_D,CV_8UC3,sx,sy,ex,ey,900);
	ant person(sx,sy,ex,ey);
	
	state tempStateB;
	state tempStateE;
	fflush(stdin);
	imshow("©³ªO",MAP.get_map());
	for(int i=0;i<1300;i++)
	{

		if(kbhit())
			exit(0);
		MAP.graph();
		imshow("©³ªO",MAP.get_map());
		waitKey(100);
		//waitKey(60/POINT_N);
		if(i==0){
			MAP.put_S_state(archor);
			MAP.put_E_state(Fog);
		}
		else
			MAP.put_E_state(tempStateE);
		if(MAP.Chage_iteration())
			break;
		tempStateB=MAP.S_state();
		tempStateE=MAP.E_state();
		MAP.put_S_state(Begin);
		MAP.put_E_state(End);
	}
	waitKey(0);
}

void randE_B(int*sx,int*sy,int*ex,int*ey)
{
	srand(time(NULL));
	/*Start and End point generator*/
	/*random initial point*/
	*sx=rand()%POINT_N;
	*sy=rand()%POINT_N;
	while(1)
	{
		int temp_rand_nx=rand()%POINT_N;
		int temp_rand_ny=rand()%POINT_N;
		if(*sx!=temp_rand_nx||*sy!=temp_rand_ny)
		{
			*ex=temp_rand_nx;
			*ey=temp_rand_ny;
			break;
		}
	}
}