#include"param.hpp"
#include<cstdio>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

NodeP::NodeP()
	:Lx(0), Ly(0), xb(0), xt(0), yb(0), yt(0), dx(0), dy(0), xnode(0), ynode(0), xelem(0), yelem(0), nnode(0), nelem(0)
{
	
	setNodeParam();
}
NodeP::NodeP(const NodeP& Np) {
	Lx = Np.Lx;
	Ly = Np.Ly;
	xb = Np.xb;
	xt = Np.xt;
	yb = Np.yb;
	yt = Np.yt;
	dx = Np.dx;
	dy = Np.dy;
	xnode = Np.xnode;
	ynode = Np.ynode;
	xelem = Np.xelem;
	yelem = Np.yelem;
	nnode = Np.nnode;
	nelem = Np.nelem;
}
NodeP& NodeP::operator=(const NodeP& Np) {
	Lx = Np.Lx;
	Ly = Np.Ly;
	xb = Np.xb;
	xt = Np.xt;
	yb = Np.yb;
	yt = Np.yt;
	dx = Np.dx;
	dy = Np.dy;
	xnode = Np.xnode;
	ynode = Np.ynode;
	xelem = Np.xelem;
	yelem = Np.yelem;
	nnode = Np.nnode;
	nelem = Np.nelem;

	return *this;
}
void NodeP::setNodeParam() {
	
	cout << "X軸左端: xb->";
	cin >> xb;
	cout << "X軸右端: xt->";
	cin >> xt;
	cout << "Y軸下端: yb->";
	cin >> yb;
	cout << "Y軸上端: yt->";
	cin >> yt;
	Lx = xt - xb;
	Ly = yt - yb;

	cout << "x方向要素数 ->";
	cin >> xelem;
	cout << "y方向要素数 ->";
	cin >> yelem;
	xnode = xelem + 1;
	ynode = yelem + 1;
	nnode = xnode * ynode;
	nelem = xelem * yelem;
	cout << "総節点数 -> 　" << nnode << "総要素数 ->" << nelem << endl;
	dx = Lx / (double)xelem;
	dy = Ly / (double)yelem;
	cout << "dx=" << dx << endl;
	cout << "dy=" << dy << endl;
}
double NodeP::getLx() {
	return Lx;
}
double NodeP::getLy() {
	return Ly;
}
double NodeP::getXb() {
	return xb;
}
double NodeP::getXt() {
	return xt;
}
double NodeP::getYb() {
	return yb;
}
double NodeP::getYt() {
	return yt;
}
double NodeP::getDx() {
	return dx;
}
double NodeP::getDy() {
	return dy;
}
int NodeP::getXnode() {
	return xnode;
}
int NodeP::getYnode() {
	return ynode;
}
int NodeP::getXelem() {
	return xelem;
}
int NodeP::getYelem() {
	return yelem;
}
int NodeP::getNnode() {
	return nnode;
}
int NodeP::getNelem() {
	return nelem;
}
TimeP::TimeP()
	:dt(0), nend(0), nsample(0) 
{
	//cout << "TimeP()" << endl;
	setTparam();
}
TimeP::TimeP(const TimeP& Tp) {
	dt = Tp.dt;
	nend = Tp.nend;
	nsample = Tp.nsample;
}
TimeP& TimeP::operator=(const TimeP& Tp) {
	dt = Tp.dt;
	nend = Tp.nend;
	nsample = Tp.nsample;

	return *this;
}
void TimeP::setTparam() {
	cout << "dt->";
	cin >> dt;
	cout << "終了ステップ->";
	cin >> nend;
	cout << "サンプルステップ数: nsample->";
	cin >> nsample;

}
double TimeP::getDt() {
	return dt;
}
int TimeP::getNend() {
	return nend;
}
int TimeP::getNsample () {
	return nsample;
}

Boundarycond::Boundarycond()
	:flagL(0), flagR(0), flagU(0), flagD(0)
{
	set_BC();
}
void Boundarycond::set_BC() {
	cout << "境界条件の設定" << endl;
	cout << "0:流入境界(diriclet),1:流出境界(neumann dv/dx=0)" << endl;
	/*
	cout << "上壁面の境界条件を決めてください" << endl;
	cin >> flagU;
	cout << "左壁面の境界条件を決めてください" << endl;
	cin >> flagL;
	cout << "右壁面の境界条件を決めてください" << endl;
	cin >> flagR;
	cout << "下壁面の境界条件を決めてください" << endl;
	cin >> flagD;
	*/
	cout << "上壁面の境界条件 ->1" << endl;
	flagU = 1;
	if (flagU == 0) {
		cout << "流入値->";
		cin >> dU;
	}
	cout << "左壁面の境界条件 ->0" << endl;
	flagL = 0;
	if (flagL == 0) {
		cout << "流入値->";
		cin >> dL;
	}
	cout << "右壁面の境界条件 ->1" << endl;
	flagR = 1;
	if (flagR == 0) {
		cout << "流入値->";
		cin >> dR;
	}
	cout << "下壁面の境界条件 ->0" << endl;
	flagL = 0;
	if (flagD == 0) {
		cout << "流入値->";
		cin >> dD;
	}
}
int Boundarycond::getBCflagL() {
	return flagL;
}
int Boundarycond::getBCflagR() {
	return flagR;
}
int Boundarycond::getBCflagU() {
	return flagU;
}
int Boundarycond::getBCflagD() {
	return flagD;
}
double Boundarycond::getdL() {
	return dL;
}
double Boundarycond::getdR() {
	return dR;
}
double Boundarycond::getdU() {
	return dU;
}
double Boundarycond::getdD() {
	return dD;
}
void Boundarycond::setdL(double dL_) {
	dL = dL_;
}
void Boundarycond::setdR(double dR_) {
	dR = dR_;
}
void Boundarycond::setdU(double dU_) {
	dU = dU_;
}
void Boundarycond::setdD(double dD_) {
	dD = dD_;
}
ADeq_param_2d::ADeq_param_2d(NodeP& Np, TimeP& Tp)
	:nparam(Np),tparam(Tp)
{


	set_param();
}
void ADeq_param_2d::set_param() {
	cout << "x方向定常流速cx->";
	cin >> cx;
	cout << "y方向定常流速cy->";
	cin >> cy;
	cout << "拡散係数　alpha->";
	cin >> alpha;
	courantx = cx * tparam.getDt() / nparam.getDx();
	couranty = cy * tparam.getDt() / nparam.getDy();
	diffusion = alpha * tparam.getDt() / (nparam.getDx() * nparam.getDy());
	cout << "x方向 courant数 Cx=" << courantx << endl;
	cout << "y方向 courant数 Cy=" << couranty << endl;
	cout << "拡散数 D=" << diffusion << endl;
	Pe = sqrt(cx * cx + cy * cy) * sqrt(nparam.getLx() * nparam.getLx() + nparam.getLy() * nparam.getLy()) / alpha;
	cout << "Peclet数 Pe=" << Pe << endl;

}
double ADeq_param_2d::get_alpha() {
	return alpha;
}
double ADeq_param_2d::get_cx() {
	return cx;
}
double ADeq_param_2d::get_cy() {
	return cy;
}
double ADeq_param_2d::get_couranx() {
	return courantx;
}
double ADeq_param_2d::get_courany() {
	return couranty;
}
double ADeq_param_2d::get_diffusion() {
	return diffusion;
}
double ADeq_param_2d::get_Pe() {
	return Pe;
}