#include "ant.h"


ant::ant(int S_x,int S_y,int E_x,int E_y)
{
	target.x=E_x;
	target.y=E_y;
	target.State=Fog;
	P_inf start_p;
	start_p.x=S_x;
	start_p.y=S_y;
	start_p.State=choose_path;
	start_p.score=0;
	archor_search_in_list(start_p);
	path.push(start_p);
}
/* virtual */
int ant::ant_choose_path()
{
	if(path_archor.empty()||(path.top().x==target.x&&path.top().y==target.y))
		return 0;
	/*現在先不新增前一個點的絕對關連性 跟一開始設計的一樣*/
	P_inf point_rem=path_archor.front();
	int index=0;
	int cnt=0;
	for(list<P_inf>::iterator i=path_archor.begin();i!=path_archor.end();i++,cnt++)
	{
		P_inf point=*i;
		if(point.score<point_rem.score)
		{
			point_rem=point;
			index=cnt;
		}
	}
	list<P_inf>::iterator i=path_archor.begin();
	while((index--)>0)
		i++;
	//cout<<i->x<<endl<<i->y<<endl;
	path_archor.erase(i);
	point_rem.State=choose_path;
	path.push(point_rem);
	
	archor_search_in_list(path.top());
	P_inf haha=path.top();
	return 1;
}
void ant::archor_search_in_list(P_inf center)
{
	int horizontal[2]={-1,1};
	int vertical[2]={-1,1};
	for(int i=0;i<2;i++)
	{
		queue<int> temp;
		int cnt=0;
		P_inf point;
		point.x=center.x+horizontal[i];
		point.y=center.y;
		
		for(list<P_inf>::iterator i=path_archor.begin();i!=path_archor.end();i++,cnt++)
			if(point.x==i->x&&point.y==i->y)
				temp.push(cnt);
		if(temp.empty())
		{
			point.State=archor;
			point.score=ant_path_score(center,point);
			path_archor.push_back(point);
		}
		else
		{
			int temp_score=10000;
			int temp_index=0;
			while(temp.empty())
			{
				list<P_inf>::iterator itemp=path_archor.begin();
				
				for(int temp_INT=temp.front();temp_INT>0;temp_INT--)
					itemp++;
				if(temp_score>itemp->score)
				{
					temp_score=itemp->score;
					temp_index=temp.front();
				}
				temp.pop();
			}
			if(temp_score>ant_path_score(center,point))
			{
				list<P_inf>::iterator itemp=path_archor.begin();
				while(temp_index<0)
				{
					itemp++;
					temp_index--;
				}
				itemp->score=ant_path_score(center,point);
			}
		}

		point.x=center.x;
		point.y=center.y+vertical[i];
		
		for(list<P_inf>::iterator i=path_archor.begin();i!=path_archor.end();i++,cnt++)
			if(point.x==i->x&&point.y==i->y)
				temp.push(cnt);
		if(temp.empty())
		{
			point.State=archor;
			point.score=ant_path_score(center,point);
			path_archor.push_back(point);
		}
		else
		{
			int temp_score=10000;
			int temp_index=0;
			while(temp.empty())
			{
				list<P_inf>::iterator itemp=path_archor.begin();
				
				for(int temp_INT=temp.front();temp_INT>0;temp_INT--)
					itemp++;
				if(temp_score>itemp->score)
				{
					temp_score=itemp->score;
					temp_index=temp.front();
				}
				temp.pop();
			}
			if(temp_score>ant_path_score(center,point))
			{
				list<P_inf>::iterator itemp=path_archor.begin();
				while(temp_index<0)
				{
					itemp++;
					temp_index--;
				}
				itemp->score=ant_path_score(center,point);
			}
		}


	}
}
int ant::ant_path_score(P_inf pre,P_inf current)
{
	//return pre.score+abs(current.x-target.x)+abs(current.y-target.y);
	return abs(current.x-target.x)+abs(current.y-target.y);
}
ant::~ant(void)
{
}

