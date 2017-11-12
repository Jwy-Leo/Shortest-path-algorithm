#pragma once
#include "3rdparty.h"
#include "parameter.h"
using namespace cv;
using namespace std;
class My_map
{
	/*variable*/
	Mat map;
	vector <P_inf> GSet;	//Global set
	int Start_p_x;
	int Start_p_y;
	int End_p_x;
	int End_p_y;
	/*function*/
	/*obstacle_generate*/
	void OBS_G(int num);
public:

	My_map(int col,int row,int Cvtype,int sx,int sy,int ex,int ey,int obstacal_num);
	Mat get_map();
	vector <P_inf> get_P_inf();
	void FILL(P_inf P);
	void assign_score(P_inf front,int endx,int endy,int sx,int sy);
	void D_C_MODE_SWITCH();
	int Chage_iteration();
	void graph();
	state E_state();
	state S_state();
	void  put_E_state(state);
	void put_S_state(state);
	~My_map(void);
};

