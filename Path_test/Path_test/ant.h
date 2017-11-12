#pragma once
#include "3rdparty.h"
#include "parameter.h"
using namespace cv;
using namespace std;
class ant
{
	/*variable*/
	list <P_inf> path_archor;	
	stack <P_inf> path;	
	P_inf target;
protected:
	void virtual archor_search_in_list(P_inf);
	int virtual ant_path_score(P_inf,P_inf);
public:
	ant(int S_x,int S_y,int E_x,int E_y);
	list <P_inf> get_archor(){return path_archor;};
	stack <P_inf> get_path(){return path;};
	int virtual ant_choose_path();
	~ant(void);
};

