#pragma once
#include"mesh.hpp"
#include"param.hpp"
#include<vector>


class Node2d {//�v�Z�i�q��̐ߓ_
private:
	int no;//�ߓ_�ԍ�
	double x;//���Wx����
	double y;//���Wy����
public:
	Node2d();
	void setNo(int no_);
	int getNo();
	void setX(double x_);
	double getX();
	void setY(double y_);
	double getY();

};

class Element2d {//�v�Z�i�q��̗v�f
private:
	int no;//�v�f�ԍ�
	double x;//�v�f�d�S���Wx����
	double y;//�v�f�d�S���Wy����
	double Se;//�v�f�ʐ�
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


class Time {//���Ԏ�
private:
	double ntime_;//n�X�e�b�v�ł̎���
	double dt_;//���ԍ��ݕ�
	int nend_;//�I���X�e�b�v
	int nsample_;//�T���v���X�e�b�v
	vector<double> t;
	TimeP& tparam;
public:
	Time(TimeP& TP);
	//�Q�b�^
	double ntime(int n);
	void setup();
	double dt();
	int nend();
	int nsample();
	double const& operator[](int n)const;
	double& operator[](int n);

};
class Mesh2d {//�v�Z�i�q
	//1: �z���^����̂ł͂Ȃ�, ���͂̃C���f�b�N�X�ɑΉ�����z��̒��g��^����悤�ɂ���
	//2:���̃N���X�̖���͌v�Z�����Ԃ��`��, ���̋�ԏ�ŕ����ʂ̌v�Z�𑖂点�邽�߂̏��ϐ��̒񋟂ł���
private:

	NodeP& nparam_;
	Boundarycond& Bcond_;
	vector<Node2d> node_;
	vector<Element2d> elem_;
	vector<int> ncond_;//�ߓ_���E�t���O
	//���E����t���O�̐ݒ�
	//ncond:  0:���,1:�������E���,2:���o���E���
	vector<vector<int>> nbool1_;//nbool[�v�f�ԍ�][�v�f��ߓ_�ԍ�]=�S�̐ߓ_�ԍ�
	vector<vector<int>> nbool3_;//nbool3[�v�f�ԍ�][���[�J���ȗv�f�ԍ�]=�S�̗v�f�ԍ� ::����v�f�ɗאڂ���v�f�̔ԍ�
	double xb_, xt_, yb_, yt_, dx_, dy_, Lx_, Ly_;
	int xnode_, ynode_, xelem_, yelem_, nnode_, nelem_;
public:

	Mesh2d(NodeP& NP, Boundarycond& BC);
	Mesh2d& operator=(const Mesh2d& mesh);
	Mesh2d(const Mesh2d& mesh);
	//�Q�b�^
	double xb();
	double xt();
	double yb();
	double yt();
	double dx();
	double dy();
	double Lx();
	double Ly();
	double x(int i);//�ߓ_�ԍ��ɑΉ�����x���W
	double y(int i);//�ߓ_�ԍ��ɑΉ�����y���W
	double eX(int ie);//�v�f�ԍ��ɑΉ�����x���W
	double eY(int ie);//�v�f�ԍ��ɑΉ�����y���W
	double Se(int ie);//�v�f�ԍ��ɑΉ�����v�f�ʐ�
	int xnode();
	int ynode();
	int xelem();
	int yelem();
	int nnode();
	int nelem();

	int nbool1(int ie, int np);
	int i1(int ie);//nbool1[ie][0]�ɑΉ�����ߓ_
	int i2(int ie);//nbool1[ie][1]�ɑΉ�����ߓ_
	int i3(int ie);//nbool1[ie][2]�ɑΉ�����ߓ_
	int i4(int ie);//nbool1[ie][3]�ɑΉ�����ߓ_
	int nbool3(int ie, int np);
	int e1(int ie);//nbool3[ie][0]�ɑΉ�����v�f
	int e2(int ie);//nbool3[ie][1]�ɑΉ�����v�f
	int e3(int ie);//nbool3[ie][2]�ɑΉ�����v�f
	int e4(int ie);//nbool3[ie][3]�ɑΉ�����v�f
	int ncond(int i);

	void setup();//������
	void generate_uniform_grid();//���Ԋu�O���b�h�̍쐬(�f�t�H���g�ŌĂяo�����)
	//void generate_cylinder_grid();//�~������O���b�h�̍쐬

};
