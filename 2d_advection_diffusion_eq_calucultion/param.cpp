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
	
	cout << "X-axis bottom: xb->";
	cin >> xb;
	cout << "X-axis top: xt->";
	cin >> xt;
	cout << "Y-axis bottom: yb->";
	cin >> yb;
	cout << "Y-axis top: yt->";
	cin >> yt;
	Lx = xt - xb;
	Ly = yt - yb;

	cout << "xelement ->";
	cin >> xelem;
	cout << "yelement ->";
	cin >> yelem;
	xnode = xelem + 1;
	ynode = yelem + 1;
	nnode = xnode * ynode;
	nelem = xelem * yelem;
	cout << "all nodes> 　" << nnode << "　all elements->" << nelem << endl;
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
	cout << "end step: nend->";
	cin >> nend;
	cout << "sample step: nsample->";
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
	cout << "Set boundary condition" << endl;
	cout << "0:inlet(diriclet),1:outlet(neumann dv/dx=0)" << endl;
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
	cout << "upper wall BC ->1" << endl;
	flagU = 1;
	if (flagU == 0) {
		cout << "upper wal inlet value->";
		cin >> dU;
	}
	cout << "left wall BC ->0" << endl;
	flagL = 0;
	if (flagL == 0) {
		cout << "left wall inlet value->";
		cin >> dL;
	}
	cout << "right wall BC ->1" << endl;
	flagR = 1;
	if (flagR == 0) {
		cout << "right wall inlet value->";
		cin >> dR;
	}
	cout << "downner wall BC ->0" << endl;
	flagL = 0;
	if (flagD == 0) {
		cout << "downner wall inlet value->";
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
	cout << "cx->";
	cin >> cx;
	cout << "cy->";
	cin >> cy;
	cout << "alpha->";
	cin >> alpha;
	courantx = cx * tparam.getDt() / nparam.getDx();
	couranty = cy * tparam.getDt() / nparam.getDy();
	diffusion = alpha * tparam.getDt() / (nparam.getDx() * nparam.getDy());
	cout << "x-axis courant Cx=" << courantx << endl;
	cout << "y-axis courant Cy=" << couranty << endl;
	cout << "diffusion number D=" << diffusion << endl;
	Pe = sqrt(cx * cx + cy * cy) * sqrt(nparam.getLx() * nparam.getLx() + nparam.getLy() * nparam.getLy()) / alpha;
	cout << "Peclet number Pe=" << Pe << endl;

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