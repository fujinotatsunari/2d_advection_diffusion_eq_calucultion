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

class TimeP {//���Ԏ��p�����[�^�N���X
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
class Boundarycond {//���E����N���X
private:
	int flagL, flagR, flagU, flagD;
	double dL, dR, dU, dD;//�������E����l
	//0:�������E(diriclet),1:���o���E(neumann dv/dx=0)
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
/*
class Constparam {//�萔�p�����[�^�N���X
protected:
	NodeP nparam;
public:
	Constparam();
	Constparam(NodeP& Np);
};
*/
/*
class NSeq_param2d :public Constparam {//Navier-Stokes�������p�����[�^(���x�E�S��������ԂɈˑ����Ȃ�(�ړ����E�Ȃ��@)
private:
	double Crho;//���x
	double Cmu;//�S��
	double Cnu;//���S��
	int type;//���̂̎��
public:
	NSeq_param2d();
	//NSeq_param2d(NodeP& Np, TimeP& Tp);
	NSeq_param2d(NodeP& Np);
	void setParam();
	void setType();
	double getCrho();
	double getCmu();
	double getCmu();
};
class NDNSeq_param2d :public Constparam {//��������Navier-Stokes�������p�����[�^
private:
	double Re;
public:
	NDNSeq_param2d();
	//NDNSeq_param2d(NodeP& Np, TimeP& Tp);
	NDNSeq_param2d(NodeP& Np);
	void setParam();
	double getRe();
};*/

class ADeq_param_2d  {//�ꎟ���ڗ��g�U�������p�����[�^�N���X
private:
	double cx;//��헬��x����
	double cy;//��헬��x����
	double alpha;//�g�U�W��
	double courantx;//�N�[������x����
	double couranty;//�N�[������y����
	double diffusion;//�g�U��
	double Pe;//�y�N����
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



