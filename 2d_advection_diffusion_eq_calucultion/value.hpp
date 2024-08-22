#pragma once
#include"value.hpp"
#include"Mesh.hpp"
#include<vector>

class Scalar2d {//�񎟌��X�J���[�ʃN���X
private:
	int no_;
	double x_, y_;//���W
	double v_;//�X�J���[��
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
class ScalarField2d {//�񎟌��X�J���[��N���X
	//Mesh2d��ŃX�J���[����߂�.

protected:
	Mesh2d& mesh_;
	Boundarycond& Bcond_;
	vector<Scalar2d> scalar_;
	vector<double> value;
public:
	
	ScalarField2d(Mesh2d& mesh, Boundarycond& BC);
	const double&  operator[](int i)const;
	double& operator[](int i);
};
class PHI :public ScalarField2d {//�ڗ��g�U�������̕�����phi
private:
	int size;//va�z��̑傫��nnode�ɑΉ�
public:
	PHI(Mesh2d& mesh, Boundarycond& BC);
	void setup();
	void initialize_default();//���[�Ɖ��[��1��^����
	//void initialize_deltafunc();//�f���^�֐��^�̏������(
	//void initialize_cosfunc();//cos�֐��^�̏������

};
