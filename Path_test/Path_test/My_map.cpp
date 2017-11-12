#include "My_map.h"
My_map::My_map(int col,int row,int Cvtype,int sx,int sy,int ex,int ey,int obstacal_num)
{
	Mat temp(col,row,Cvtype,Scalar(0, 0, 0));
	
	temp.copyTo(map);
	/* Create Global Set*/
	for(float i=0;i<POINT_N;i++)
		for(float j=0;j<POINT_N;j++)
		{
			P_inf point_inf;
			point_inf.x=j;
			point_inf.y=i;
			point_inf.State=Fog;
			point_inf.score=0;
			GSet.push_back(point_inf);
		}
	/*obstacal list Do Once*/
	OBS_G(obstacal_num);
	Start_p_x=sx;
	Start_p_y=sy;
	End_p_x=ex;
	End_p_y=ey;
	GSet[sy*POINT_N+sx].State=Begin;
	GSet[ey*POINT_N+ex].State=End;
}
void My_map::OBS_G(int num)
{
	/*Generate*/
	srand(time(NULL));
	queue <P_inf> object;
	for(int i=0;i<num;i++)//POINT_N*POINT_N/10;i++)
	{
		P_inf temp_object_g;
		temp_object_g.x=rand()%POINT_N;
		temp_object_g.y=rand()%POINT_N;
		object.push(temp_object_g);
	}
	/*modify*/
	while(!object.empty())
	{
		GSet[object.front().y*POINT_N+object.front().x].State=fuck_object;
		object.pop();
	}	
}
void My_map::graph()
{
	for(int i=0;i<GSet.size();i++)
	{
		Point center=Point(GSet[i].x*POINT_D+POINT_B,GSet[i].y*POINT_D+POINT_B);
		switch(GSet[i].State)
		{
		case choose_path:
			circle(map, center, POINT_R, Scalar(0,255,255),-1);
			break;
		case archor:
			circle(map, center, POINT_R, Scalar(255,32,160),3);
			break;
		case Fog:
			circle(map, center, POINT_R, Scalar(0,0,0),-1);
			break;
		case Begin:
			circle(map, center, POINT_R, Scalar(0,255,0),-1);
			break;
		case End:
			circle(map, center, POINT_R, Scalar(0,0,255),-1);
			break;
		case fuck_object:
			rectangle(map,center-Point(3,3),center+Point(3,3),Scalar( 105, 128, 112),-1);
			//circle(map, center, POINT_R, Scalar(105,128,112),-1);
			break;
		default:
			circle(map, center, POINT_R, Scalar(0,0,0),-1);
		}
	}
}
int My_map::Chage_iteration()
{
	int score=100000;
	int x=0;
	int y=0;
	queue<P_inf> temp;
	queue<P_inf> op_temp;
	for(int i=0;i<GSet.size();i++)
		if(GSet[i].State==archor)
		{
			assign_score(GSet[i],End_p_x,End_p_y,Start_p_x,Start_p_y);
			temp.push(GSet[i]);
		}
	/*search ¾÷¨î*/
	/*assign score*/
	while(!temp.empty())
	{
		P_inf temp_p=temp.front();
		if(temp_p.x==End_p_x&&temp_p.y==End_p_y)
			return 1;
		if(temp_p.State==archor)
			if(score>temp_p.score)
			{
				x=temp_p.x;
				y=temp_p.y;
				score=temp_p.score;
			}
		//List[temp_p.y*POINT_N+temp_p.x].State=done;
		//FILL(&List,temp_p);
		temp.pop();
	}
	/**/
	if(GSet[y*POINT_N+x].State==archor){
		GSet[y*POINT_N+x].State=choose_path;
		FILL(GSet[y*POINT_N+x]);
	}	
	return 0;
}

void My_map::assign_score(P_inf front,int endx,int endy,int sx,int sy)
{
	/* If in_set => should update the minimal cost*/
	for(int i=front.y-1;i<=front.y+1;i++)
		for(int j=front.x-1;j<=front.x+1;j++)
		{
			int D=0;
			if(!(i*POINT_N+j>=POINT_N*POINT_N||i*POINT_N+j<0))
			if(((i)>=0&&(j)<POINT_N)&&((j)>=0&&(j)<POINT_N)){
				if((front.x+1==j||front.x-1==j)&&front.y==i)
					D=abs(sy-endy)*abs(sy-endy);
				if(front.x==j&&(front.y+1==i||front.y-1==i))
					D=abs(sx-endx)*abs(sx-endx);
				if((front.x+1==j||front.x-1==j)&&(front.y+1==i||front.y-1==i))
					//D=floor(sqrt((float)abs(sx-endx)*abs(sx-endx)+abs(sy-endy)*abs(sy-endy)));
					D=abs(sy-endy)*abs(sx-endx);
				D=0;
			if(GSet[i*POINT_N+j].State==Fog)
				//L[i*POINT_N+j].score=front.score+D+abs(j-endx)*10+abs(i-endy)*10;
				//L[i*POINT_N+j].score=front.score+D+abs(j-endx)+abs(i-endy);
				//L[i*POINT_N+j].score=front.score+D+abs(j-endx)*abs(j-endx)+abs(i-endy)*abs(i-endy);
				//L[i*POINT_N+j].score=front.score+D+abs(j-endx)*abs(i-endy);
				//L[i*POINT_N+j].score=front.score+D+abs(j-endx)+abs(i-endy);
				GSet[i*POINT_N+j].score=D+abs(j-endx)+abs(i-endy);
			}
		}
}
void My_map::FILL(P_inf P)
{
	int x_move[2]={-1,1};
	int y_move[2]={-1,1};
	for(int i=0;i<2;i++)
	{
		if(!(P.y*POINT_N+(P.x+x_move[i])>=POINT_N*POINT_N||P.y*POINT_N+(P.x+x_move[i])<0))
			if((P.y>=0&&P.y<POINT_N)&&((P.x+x_move[i])>=0&&(P.x+x_move[i])<POINT_N))
				if(GSet[P.y*POINT_N+(P.x+x_move[i])].State==Fog)
					GSet[P.y*POINT_N+(P.x+x_move[i])].State=archor;
		if(((P.y+y_move[i])>=0&&(P.y+y_move[i])<POINT_N)&&(P.x>=0&&P.x<POINT_N))
			if(GSet[(P.y+y_move[i])*POINT_N+P.x].State==Fog)
					GSet[(P.y+y_move[i])*POINT_N+P.x].State=archor;
	}
}
Mat My_map::get_map()
{
	return map;
}
vector <P_inf> My_map::get_P_inf()
{
	return GSet;
}
My_map::~My_map(void)
{
	map.release();
}


state My_map::E_state()
{
	return GSet[End_p_y*POINT_N+End_p_x].State;
}
state My_map::S_state()
{
	return GSet[Start_p_y*POINT_N+Start_p_x].State;
}
void  My_map::put_E_state(state in)
{
	GSet[End_p_y*POINT_N+End_p_x].State=in;
}
void My_map::put_S_state(state in)
{
	 GSet[Start_p_y*POINT_N+Start_p_x].State=in;
}

	