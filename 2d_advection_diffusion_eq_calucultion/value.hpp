#pragma once
#include"value.hpp"
#include"Mesh.hpp"
#include<vector>

class Scalar2d {//二次元スカラー量クラス
private:
	int no_;
	double x_, y_;//座標
	double v_;//スカラー量
public:
	Scalar2d();
	void setNo(int no);
	int getNo();
	void setX(double x);
	double getX();
	void setY(double y);
	double getY();
	void setV(double v);
	double getV();

};
class ScalarField2d {//二次元スカラー場クラス
	//Mesh2d上でスカラー場を定める.

protected:
	Mesh2d& mesh_;
	Boundarycond& Bcond_;
	vector<Scalar2d> scalar_;
	vector<double> value;
public:

	ScalarField2d(Mesh2d& mesh, Boundarycond& BC);
	const double& operator[](int i)const;
	double& operator[](int i);
};
class PHI :public ScalarField2d {//移流拡散方程式の物理量phi
private:
	int size;//va配列の大きさnnodeに対応
public:
	PHI(Mesh2d& mesh, Boundarycond& BC);
	void setup();
	void initialize_default();//左端と下端に1を与える
	//void initialize_deltafunc();//デルタ関数型の初期条件(
	//void initialize_cosfunc();//cos関数型の初期条件

};