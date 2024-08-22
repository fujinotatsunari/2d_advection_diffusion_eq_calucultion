#include"value.hpp"
#include"Mesh.hpp"
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;
# define PI 3.14159265359

Scalar2d::Scalar2d() 
	:no_(0),x_(0),y_(0),v_(0) 
{

}

void Scalar2d::setNo(int no) {
	no_ = no;
}
int Scalar2d::getNo() {
	return no_;
}
void Scalar2d::setX(double x) {
	x_ = x;
}
double Scalar2d::getX() {
	return x_;
}
void Scalar2d::setY(double y) {
	y_ = y;
}
double Scalar2d::getY() {
	return y_;
}
void Scalar2d::setV(double v) {
	v_ = v;
}
double Scalar2d::getV() {
	return  v_;
}

ScalarField2d::ScalarField2d(Mesh2d& mesh, Boundarycond& BC)
	:mesh_(mesh), Bcond_(BC)
{
	scalar_.resize(mesh_.nnode());
	value.resize(mesh_.nnode());

	for (int j = 0; j < mesh_.ynode(); j++) {
		for (int i = 0; i < mesh_.xnode(); i++) {
			int np = i + mesh_.xnode() * j;
			scalar_[np].setNo(i);
			scalar_[np].setX(mesh_.x(np));
			scalar_[np].setY(mesh_.y(np));
			scalar_[np].setV(0.0);
			value[np] = scalar_[np].getV();
		}
	}

}

double& ScalarField2d::operator[](int i) {
	return value[i];

}
const double& ScalarField2d::operator[](int i)const {
	return value[i];
}
PHI::PHI(Mesh2d& mesh, Boundarycond& BC)
	:ScalarField2d(mesh, BC)
{
	setup();
}
void PHI::setup() {
	scalar_.resize(mesh_.nnode());
	value.resize(mesh_.nnode());
	for (int i = 0; i < scalar_.size(); i++) {
		scalar_[i].setNo(i);
		scalar_[i].setX(mesh_.x(i));
		scalar_[i].setY(mesh_.y(i));
		scalar_[i].setV(0.0);
		value[i] = scalar_[i].getV();
	}
}
void PHI::initialize_default() {
	//初期条件の設定
	for (int j = 0; j < mesh_.ynode(); j++) {
		for (int i = 0; i < mesh_.xnode(); i++) {
			int np = i + mesh_.xnode() * j;

			if (i == 0) {//左端
				value[np] = Bcond_.getdL();;
				scalar_[np].setV(value[np]);
			}
			else if (j == 0) {//下端
				value[np] = Bcond_.getdD();
				scalar_[np].setV(value[np]);
			}
			else {
				value[np] = 0.0;
				scalar_[np].setV(value[np]);
			}
			//cout << "value[" << np << "]=" << value[np] << endl;
		}
	}
	//境界条件の設定
	/*
	for (int j = 0; j < mesh_.ynode(); j++) {
		for (int i = 0; i < mesh_.xnode(); i++) {
			int np = i + mesh_.xnode() * j;
			if (mesh_.ncond(np) == 1) {//dirichlet境界条件
				if (i == 0) {//左壁面
					value[np] = Bcond_.getdL();
					scalar_[np].setV(value[np]);
				}
				if (j == 0) {//下壁面
					value[np] = Bcond_.getdD();
					scalar_[np].setV(value[np]);
				}
				if (i == mesh_.xnode() - 1) {//右壁面
					//value[np] = Bcond_.getdR();
					//scalar_[np].setV(value[np]);
				}
				if (j == mesh_.ynode() - 1) {//上壁面
					//value[np] = Bcond_.getdU();
					//scalar_[np].setV(value[np]);
				}

			}
		}
	}
	*/
}
