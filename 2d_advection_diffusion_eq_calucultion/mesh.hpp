#pragma once
#include"mesh.hpp"
#include"param.hpp"
#include<vector>


class Node2d {//計算格子上の節点
private:
	int no;//節点番号
	double x;//座標x成分
	double y;//座標y成分
public:
	Node2d();
	void setNo(int no_);
	int getNo();
	void setX(double x_);
	double getX();
	void setY(double y_);
	double getY();

};

class Element2d {//計算格子上の要素
private:
	int no;//要素番号
	double x;//要素重心座標x成分
	double y;//要素重心座標y成分
	double Se;//要素面積
public:
	Element2d();
	void setNo(int no_);
	int getNo();
	void setX(double x_);
	double getX();
	void setY(double y_);
	double getY();
	void setSe(double Se_);
	double getSe();
};


class Time {//時間軸
private:
	double ntime_;//nステップでの時刻
	double dt_;//時間刻み幅
	int nend_;//終了ステップ
	int nsample_;//サンプルステップ
	vector<double> t;
	TimeP& tparam;
public:
	Time(TimeP& TP);
	//ゲッタ
	double ntime(int n);
	void setup();
	double dt();
	int nend();
	int nsample();
	double const& operator[](int n)const;
	double& operator[](int n);

};
class Mesh2d {//計算格子
	//1: 配列を与えるのではなく, 入力のインデックスに対応する配列の中身を与えるようにする
	//2:このクラスの役割は計算する空間を定義し, その空間上で物理量の計算を走らせるための諸変数の提供である
private:

	NodeP& nparam_;
	Boundarycond& Bcond_;
	vector<Node2d> node_;
	vector<Element2d> elem_;
	vector<int> ncond_;//節点境界フラグ
	//境界条件フラグの設定
	//ncond:  0:内部,1:流入境界条件,2:流出境界条件
	vector<vector<int>> nbool1_;//nbool[要素番号][要素内節点番号]=全体節点番号
	vector<vector<int>> nbool3_;//nbool3[要素番号][ローカルな要素番号]=全体要素番号 ::ある要素に隣接する要素の番号
	double xb_, xt_, yb_, yt_, dx_, dy_, Lx_, Ly_;
	int xnode_, ynode_, xelem_, yelem_, nnode_, nelem_;
public:

	Mesh2d(NodeP& NP, Boundarycond& BC);
	Mesh2d& operator=(const Mesh2d& mesh);
	Mesh2d(const Mesh2d& mesh);
	//ゲッタ
	double xb();
	double xt();
	double yb();
	double yt();
	double dx();
	double dy();
	double Lx();
	double Ly();
	double x(int i);//節点番号に対応するx座標
	double y(int i);//節点番号に対応するy座標
	double eX(int ie);//要素番号に対応するx座標
	double eY(int ie);//要素番号に対応するy座標
	double Se(int ie);//要素番号に対応する要素面積
	int xnode();
	int ynode();
	int xelem();
	int yelem();
	int nnode();
	int nelem();

	int nbool1(int ie, int np);
	int i1(int ie);//nbool1[ie][0]に対応する節点
	int i2(int ie);//nbool1[ie][1]に対応する節点
	int i3(int ie);//nbool1[ie][2]に対応する節点
	int i4(int ie);//nbool1[ie][3]に対応する節点
	int nbool3(int ie, int np);
	int e1(int ie);//nbool3[ie][0]に対応する要素
	int e2(int ie);//nbool3[ie][1]に対応する要素
	int e3(int ie);//nbool3[ie][2]に対応する要素
	int e4(int ie);//nbool3[ie][3]に対応する要素
	int ncond(int i);

	void setup();//初期化
	void generate_uniform_grid();//等間隔グリッドの作成(デフォルトで呼び出される)
	//void generate_cylinder_grid();//円柱周りグリッドの作成

};
