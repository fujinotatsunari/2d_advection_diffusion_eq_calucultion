#pragma once
#include"FEM.hpp"
#include"value.hpp"
#include"Mesh.hpp"
#include"matrix.hpp"
#include<vector>

/*
class Jacobian : public ScalarField2d{
private:
	int size;////�z��̑傫��nnode�ɑΉ�
	vector<double> xi = { -1.0,1.0,1.0,-1.0 };//�v�Z��ԍ��Wxi���W
	vector<double> eta = { -1.0,-1.0,1.0,1.0 };//�v�Z��ԍ��Weta���W

public:
	Jacobian(Mesh2d& mesh, Boundarycond& BC);
	void setup();
	void calculate_jacobian();

};*/
class CofficientMatrix {//�v�f��W���s��N���X
protected:
	int node = 4;//�v�f��ߓ_��
	vector<Matrix> mat;//�}�g���N�X�{��:nelem��vector
	vector<double> xi = { -1.0,1.0,1.0,-1.0 };//�v�Z��ԍ��Wxi���W
	vector<double> eta = { -1.0,-1.0,1.0,1.0 };//�v�Z��ԍ��Weta���W
	Mesh2d& mesh_;

public:
	CofficientMatrix(Mesh2d& mesh);
	CofficientMatrix(Mesh2d& mesh, const vector<Matrix>& Mat);

	static CofficientMatrix generate(Mesh2d& mesh);
	virtual const Matrix& operator[](int ie)const;
	virtual Matrix& operator[](int ie);
	void view();

};


class Massmatrix :public CofficientMatrix {//���ʍs��
public:
	Massmatrix(Mesh2d& mesh);
	Massmatrix(Mesh2d& mesh, const vector<Matrix>& Mat);
	static Massmatrix generate_Mass(Mesh2d& mesh);
	const Matrix& operator[](int ie)const override;
	Matrix& operator[](int ie) override;
};
class Lumped_Massmatrix :public CofficientMatrix {//�W�������ʍs��
public:
	Lumped_Massmatrix(Mesh2d& mesh);
	Lumped_Massmatrix(Mesh2d& mesh, const vector<Matrix>& Mat);
	static Lumped_Massmatrix generate_Lmass(Mesh2d& mesh);
	const Matrix& operator[](int ie)const override;
	Matrix& operator[](int ie) override;
};
  
class Diffmatrix :public CofficientMatrix {//�g�U�s��
public:
	Diffmatrix(Mesh2d& mesh);
	Diffmatrix(Mesh2d& mesh, const vector<Matrix>& Mat);
	static Diffmatrix generate_Diff(Mesh2d& mesh);
	const Matrix& operator[](int ie)const override;
	Matrix& operator[](int ie) override;
};

class xAdvecmatrix :public CofficientMatrix{//x�����ڗ��s��N���X(���`)
public:
	xAdvecmatrix(Mesh2d& mesh);
	xAdvecmatrix(Mesh2d& mesh, const vector<Matrix>& Mat);
	static xAdvecmatrix generate_xAd(Mesh2d& mesh);
	const Matrix& operator[](int ie)const override;
	Matrix& operator[](int ie) override;
};
class yAdvecmatrix :public CofficientMatrix {//x�����ڗ��s��N���X(���`)
public:
	yAdvecmatrix(Mesh2d& mesh);
	yAdvecmatrix(Mesh2d& mesh, const vector<Matrix>& Mat);
	static yAdvecmatrix generate_yAd(Mesh2d& mesh);
	const Matrix& operator[](int ie)const override;
	Matrix& operator[](int ie) override;
};