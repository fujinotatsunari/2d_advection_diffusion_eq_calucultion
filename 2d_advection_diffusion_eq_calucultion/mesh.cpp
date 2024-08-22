#include"mesh.hpp"
#include"param.hpp"
#include<vector>
#include<iostream>
Node2d::Node2d():no(0),x(0),y(0)
{

}
void Node2d::setNo(int no_) {
	no = no_;
}
int Node2d::getNo() {
	return no;
}
void Node2d::setX(double x_) {
	x = x_;
}
double Node2d::getX() {
	return x;
}
void Node2d::setY(double y_) {
	y = y_;
}
double Node2d::getY() {
	return y;
}
Element2d::Element2d() :no(0),x(0),y(0),Se(0) 
{

}
void Element2d::setNo(int no_) {
	no = no_;
}
int Element2d::getNo() {
	return no;
}
void Element2d::setX(double x_) {
	x = x_;
}
double Element2d::getX() {
	return x;
}
void Element2d::setY(double y_) {
	y = y_;
}
double Element2d::getY() {
	return y;
}
void Element2d::setSe(double Se_) {
	Se = Se_;
}
double Element2d::getSe() {
	return Se;
}
Time::Time(TimeP& Tp) :ntime_(0), dt_(0), nend_(0),nsample_(0), tparam(Tp) {
	setup();
}
void Time::setup() {
	dt_ = tparam.getDt();
	nend_ = tparam.getNend();
	nsample_ = tparam.getNsample();
	t.resize(nend_ + 1, 0);
	for (int n = 0; n < t.size(); n++) {
		t[n] = 0.0 + (double)n * dt_;
	}
}
double Time::ntime(int n) {
	ntime_ = 0.0 + (double)n * dt_;
	return ntime_;
}
double Time::dt() {
	return dt_;
}
int Time::nend() {
	return nend_;
}
int Time::nsample() {
	return nsample_;
}
double const& Time::operator[](int n)const {
	return t[n];
}
double& Time::operator[](int n) {
	return t[n];
}
Mesh2d::Mesh2d(NodeP& NP, Boundarycond& BC)
	:nparam_(NP), Bcond_(BC), Lx_(0), Ly_(0), xb_(0), xt_(0), yb_(0), yt_(0), dx_(0), dy_(0), xnode_(0), ynode_(0), xelem_(0), yelem_(0), nnode_(0), nelem_(0)
{
	setup();
	generate_uniform_grid();
}
Mesh2d& Mesh2d::operator=(const Mesh2d& mesh) {
	nparam_ = mesh.nparam_;
	Bcond_ = mesh.Bcond_;
	node_ = mesh.node_;
	elem_ = mesh.elem_;
	ncond_ = mesh.ncond_;
	nbool1_ = mesh.nbool1_;
	nbool3_ = mesh.nbool3_;
	xb_ = mesh.xb_;
	xt_ = mesh.xt_;
	yb_ = mesh.yb_;
	yt_ = mesh.yt_;
	dx_ = mesh.dx_;
	dy_ = mesh.dy_;
	Lx_ = mesh.Lx_;
	Ly_ = mesh.Ly_;
	xnode_ = mesh.xnode_;
	ynode_ = mesh.ynode_;
	nnode_ = mesh.nnode_;

	xelem_ = mesh.xelem_;
	yelem_ = mesh.yelem_;
	nelem_ = mesh.nelem_;

	return *this;
}
Mesh2d::Mesh2d(const Mesh2d& mesh) 
	:nparam_(mesh.nparam_),Bcond_(mesh.Bcond_)
{

	node_ = mesh.node_;
	elem_ = mesh.elem_;
	ncond_ = mesh.ncond_;
	nbool1_ = mesh.nbool1_;
	nbool3_ = mesh.nbool3_;
	xb_ = mesh.xb_;
	xt_ = mesh.xt_;
	yb_ = mesh.yb_;
	yt_ = mesh.yt_;
	dx_ = mesh.dx_;
	dy_ = mesh.dy_;
	Lx_ = mesh.Lx_;
	Ly_ = mesh.Ly_;
	xnode_ = mesh.xnode_;
	ynode_ = mesh.ynode_;
	nnode_ = mesh.nnode_;

	xelem_ = mesh.xelem_;
	yelem_ = mesh.yelem_;
	nelem_ = mesh.nelem_;
}
void Mesh2d::setup() {
	xb_ = nparam_.getXb();
	xt_ = nparam_.getXt();
	yb_ = nparam_.getYb();
	yt_ = nparam_.getYt();
	dx_ = nparam_.getDx();
	dy_ = nparam_.getDy();
	Lx_ = nparam_.getLx();
	Ly_ = nparam_.getLy();

	xnode_ = nparam_.getXnode();
	ynode_ = nparam_.getYnode();
	nnode_ = nparam_.getNnode();

	xelem_ = nparam_.getXelem();
	yelem_ = nparam_.getYelem();
	nelem_ = nparam_.getNelem();

	int N = 4;//��v�f�̐ߓ_��
	nbool1_.resize(nelem_);
	for (int ie = 0; ie < nbool1_.size(); ie++) {
		nbool1_[ie].resize(N,0);
	}
	int M = 4;//1�v�f�ɗאڂ���v�f��
	nbool3_.resize(nelem_);
	for (int ie = 0; ie < nbool3_.size(); ie++) {
		nbool3_[ie].resize(M, 0);
	}

	ncond_.resize(nnode_);
	node_.resize(nnode_);
	elem_.resize(nelem_);
}
void Mesh2d::generate_uniform_grid() {
	//�ߓ_���W�̌v�Z
	for (int j = 0; j < ynode_; j++) {
		for (int i = 0; i < xnode_; i++) {
			int np = i + xnode_ * j;
			node_[np].setNo(i);//�ߓ_�ԍ��̐ݒ�
			node_[np].setX(dx_ * (double)i + xb_);//�ߓ_���Wx�̐ݒ�
			node_[np].setY(dy_ * (double)j + yb_);//�ߓ_���Wy�̐ݒ�

			if (i == 0) node_[np].setX(xb_);//x���[�̕␳
			if (i == xnode_ - 1) node_[np].setX(xt_);//x�E�[�̕␳
			if (j == 0) node_[np].setY(yb_);//y���[�̕␳
			if (j == ynode_ - 1) node_[np].setY(yt_);//y��[�̕␳
		}
	}
	//nbool1��nbool3�̊���
	for (int j = 0; j < yelem_; j++) {
		for (int i = 0; i < xelem_; i++) {
			int ie = i + xelem_ * j;

			int i1 = i + xnode_ * j;//�v�f�̍����_�̐ߓ_�ԍ�
			int i2 = i1 + 1;//�v�f�̉E���_�̐ߓ_�ԍ�
			int i4 = i1 + xnode_;//�v�f�̍���_�̐ߓ_�ԍ�
			int i3 = i4 + 1;//�v�f�̉E��_�̐ߓ_�ԍ�

			nbool1_[ie][0] = i1;
			nbool1_[ie][1] = i2;
			nbool1_[ie][2] = i3;
			nbool1_[ie][3] = i4;
			
			nbool3_[ie][2] = ie + xelem_;//�㑤�v�f
			if (j == yelem_ - 1) nbool3_[ie][2] = -1;//�̈��[

			nbool3_[ie][0] = ie - xelem_;//�����v�f
			if (j == 0) nbool3_[ie][0] = -1;//�̈扺�[

			nbool3_[ie][3] = ie - 1;//�����v�f
			if (i == 0) nbool3_[ie][3] = -1;//�̈捶�[

			nbool3_[ie][1] = ie + 1;//�E���v�f
			if (i == xelem_ - 1) nbool3_[ie][1] = -1;//�̈�E�[
		}
	}

	//�v�f���W�̐ݒ�
	for (int j = 0; j < yelem_; j++) {
		for (int i = 0; i < xelem_; i++) {
			int ie = i + xelem_ * j;
			elem_[ie].setNo(ie);
			int i1 = nbool1_[ie][0];
			int i2 = nbool1_[ie][1];
			int i3 = nbool1_[ie][2];
			int i4 = nbool1_[ie][3];

			elem_[ie].setX((node_[i1].getX() + node_[i2].getX() + node_[i3].getX() + node_[i4].getX()) / 4);//�v�f�d�S��x���W
			elem_[ie].setY((node_[i1].getY() + node_[i2].getY() + node_[i3].getY() + node_[i4].getY()) / 4);//�v�f�d�S��y���W
			double S;
			S = ((node_[i3].getX() - node_[i1].getX()) * (node_[i4].getY() - node_[i2].getY()) 
				- (node_[i4].getX() - node_[i2].getX()) * (node_[i3].getY() - node_[i1].getY())) / 4;//�v�f�l�p�`�̖ʐς���߂�

			elem_[ie].setSe(S);

		}
	}

	//���E����t���O�̐ݒ�
	//ncond:  0:���,1:�������E���,2:���o���E���
	for (int j = 0; j < ynode_; j++) {
		for (int i = 0; i < xnode_; i++) {
			int np = i + xnode_ * j;
			if (i == 0) {//���ǖ�
				if (Bcond_.getBCflagL() == 0) {//�������E���
					ncond_[np] = 1;

				}
				else if (Bcond_.getBCflagL() == 1) {//���o���E���
					ncond_[np] = 2;
				}
				else {

				}
			}
			else if (j == 0) {//���ǖ�
				if (Bcond_.getBCflagD() == 0) {//�������E���
					ncond_[np] = 1;
				}
				else if (Bcond_.getBCflagD() == 1) {//���o���E���
					ncond_[np] = 2;
				}
				else {

				}
			}
			else if (i == xnode_ - 1) {//�E�ǖ�
				if (Bcond_.getBCflagR() == 0) {//�������E���
					ncond_[np] = 1;
				}
				else if (Bcond_.getBCflagR() == 1) {//���o���E���
					ncond_[np] = 2;
				}
				else {

				}
			}
			else if (j == ynode_ - 1) {//��ǖ�
				if (Bcond_.getBCflagU() == 0) {//�������E���
					ncond_[np] = 1;
				}
				else if (Bcond_.getBCflagU() == 1) {//���o���E���
					ncond_[np] = 2;
				}
				else {

				}
			}
			else {//����ȊO�̗̈�
				ncond_[np] = 0;
			}
		}
	}

}
double Mesh2d::xb() {
	return xb_;
}
double Mesh2d::xt() {
	return xt_;
}
double Mesh2d::yb() {
	return yb_;
}
double Mesh2d::yt() {
	return yt_;
}
double Mesh2d::dx() {
	return dx_;
}
double Mesh2d::dy() {
	return dy_;
}
double Mesh2d::Lx() {
	return Lx_;
}
double Mesh2d::Ly() {
	return Ly_;
}
double Mesh2d::x(int i) {
	return node_[i].getX();
}
double Mesh2d::y(int i) {
	return node_[i].getY();
}
double Mesh2d::eX(int ie) {
	return elem_[ie].getX();
}
double Mesh2d::eY(int ie) {
	return elem_[ie].getY();
}
double Mesh2d::Se(int ie) {
	return elem_[ie].getSe();
}
int Mesh2d::xnode() {
	return xnode_;
}
int Mesh2d::ynode() {
	return ynode_;
}
int Mesh2d::xelem() {
	return xelem_;
}
int Mesh2d::yelem() {
	return yelem_;
}
int Mesh2d::nnode() {
	return nnode_;
}
int Mesh2d::nelem() {
	return nelem_;
}
int Mesh2d::i1(int ie) {
	return nbool1_[ie][0];
}
int Mesh2d::i2(int ie) {
	return nbool1_[ie][1];
}
int Mesh2d::i3(int ie) {
	return nbool1_[ie][2];
}
int Mesh2d::i4(int ie) {
	return nbool1_[ie][3];
}
int Mesh2d::nbool1(int ie, int np) {
	return nbool1_[ie][np];
}
int Mesh2d::e1(int ie) {
	return nbool3_[ie][0];
}
int Mesh2d::e2(int ie) {
	return nbool3_[ie][1];
}
int Mesh2d::e3(int ie) {
	return nbool3_[ie][2];
}
int Mesh2d::e4(int ie) {
	return nbool3_[ie][3];
}
int Mesh2d::nbool3(int ie, int np) {
	return nbool3_[ie][np];
}
int Mesh2d::ncond(int i) {
	return ncond_[i];
}