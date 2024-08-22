#pragma once
#include"param.hpp"
#include<vector>
using namespace std;

class NodeP {//�v�Z�i�q�p�����[�^�N���X
private:
	double Lx, Ly;
	double xb, yb;
	double xt, yt;
	double dx, dy;

	int xnode, ynode;
	int xelem, yelem;
	int nnode, nelem;
public:
	NodeP();
	NodeP(const NodeP& Np);
	NodeP& operator=(const NodeP& Np);
	void setNodeParam();
	double getLx();
	double getLy();
	double getXb();
	double getXt();
	double getYb();
	double getYt();
	double getDx();
	double getDy();
	//double getDxDy();
	int getXnode();
	int getYnode();
	int getXelem();
	int getYelem();
	int getNnode();
	int getNelem();
};

class TimeP {//時間軸パラメータクラス
private:
	double dt;
	int nend;
	int nsample;

public:
	TimeP();
	TimeP(const TimeP& Tp);
	TimeP& operator=(const TimeP& Tp);
	double getDt();
	int getNend();
	int getNsample();
	void setTparam();
};
class Boundarycond {//境界条件クラス
private:
	int flagL, flagR, flagU, flagD;
	double dL, dR, dU, dD;//流入境界条件値
	//0:流入境界(diriclet),1:流出境界(neumann dv/dx=0)
public:
	Boundarycond();
	void set_BC();
	int getBCflagL();
	int getBCflagR();
	int getBCflagD();
	int getBCflagU();
	double getdL();
	double getdR();
	double getdU();
	double getdD();
	void setdL(double dL_);
	void setdR(double dR_);
	void setdU(double dU_);
	void setdD(double dD_);
};



class ADeq_param_2d {//一次元移流拡散方程式パラメータクラス
private:
	double cx;//定常流速x成分
	double cy;//定常流速x成分
	double alpha;//拡散係数
	double courantx;//クーラン数x方向
	double couranty;//クーラン数y方向
	double diffusion;//拡散数
	double Pe;//ペクレ数
	NodeP& nparam;
	TimeP& tparam;
public:
	//ADeq_param_2d();
	//ADeq_param_2d(TimeP& Tp);
	ADeq_param_2d(NodeP& Np, TimeP& Tp);
	void set_param();
	double get_cx();
	double get_cy();
	double get_alpha();
	double get_couranx();
	double get_courany();
	double get_diffusion();
	double get_Pe();
};



