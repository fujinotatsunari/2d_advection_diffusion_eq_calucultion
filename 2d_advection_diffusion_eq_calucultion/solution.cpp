#include"solution.hpp"
#include"output.hpp"
#include"FEM.hpp"
#include"value.hpp"
#include"Mesh.hpp"
#include"param.hpp"
#include"matrix.hpp"
#include<vector>
#include<iostream>

using namespace std;

Explicit_FEM::Explicit_FEM(Mesh2d& mesh_, Time& t_, PHI& phi_, Boundarycond& BC_, ADeq_param_2d& adp)
	:mesh(mesh_), t(t_), phi(phi_), BC(BC_),ADP(adp)
{

}

void Explicit_FEM::do_expcalculation() {
	
	Lumped_Massmatrix Fm(mesh);//�W�������ʍs��
	xAdvecmatrix Amx(mesh);//�ڗ��s��x����
	yAdvecmatrix Amy(mesh);//�ڗ��s��y����
	Diffmatrix Dm(mesh);//�g�U�s��
	/*
	cout << "viewFm" << endl;
	Fm.view();
	cout << "viewAmx" << endl;
	Amx.view();
	cout << "viewAmy" << endl;
	Amy.view();
	cout << "viewDm" << endl;
	Dm.view();
	*/
	vector<double> phib;//1step�O�̕�����
	phib.resize(mesh.nnode());
	vector<double> dd;//�g�U���������ݕϐ�
	dd.resize(mesh.nnode());
	vector<double> uu;//�ڗ����������ݕϐ�
	uu.resize(mesh.nnode());
	vector<double> nn;//���E���������ݕϐ�
	nn.resize(mesh.nnode());
	vector<double> ff;//�W�������ʍs��̐ߓ_�ւ̊�^
	ff.resize(mesh.nnode());

	vector<int> nx;//���E��̒P�ʖ@���x�N�g��x����
	nx.resize(mesh.nnode());
	vector<int> ny;//���E��̒P�ʖ@���x�N�g��x����
	ny.resize(mesh.nnode());

	for (int j = 0; j < mesh.ynode(); j++) {
		for (int i = 0; i < mesh.xnode(); i++) {
			int np = i + mesh.xnode() * j;
			nx[np] = 0;
			ny[np] = 0;
			if (i == 0) {
				nx[np] = -1;//���E�@���P�ʃx�N�g��
			}
			if (i == mesh.xnode() - 1) {
				nx[np] = 1;
			}
			if (j == 0) {
				ny[np] = -1;
			}
			if (j == mesh.ynode() - 1) {
				ny[np] = 1;
			}
		}
	}

	//���Ԑi�s
	for (int n = 0; n <= t.nend() + 1; n++) {
		output(n);

		cout << "time=" << t.ntime(n) << endl;
		for (int j = 0; j < mesh.ynode(); j++) {
			for (int i = 0; i < mesh.xnode(); i++) {
				int np = i + mesh.xnode() * j;
				
				phib[np] = phi[np];
				dd[np] = 0.0;
				uu[np] = 0.0;
				nn[np] = 0.0;
			}
		}
		for (int j = 0; j < node; j++) {//�Ǐ��ߓ_���[�v
			for (int ie = 0; ie < mesh.nelem(); ie++) {//�v�f���[�v
				int np= mesh.nbool1(ie, j);
				int i1 = mesh.i1(ie);
				int i2 = mesh.i2(ie);
				int i3 = mesh.i3(ie);
				int i4 = mesh.i4(ie);

				dd[np] = dd[np] - ADP.get_alpha() * (Dm[ie][j][0] * phi[i1] + Dm[ie][j][1] * phi[i2] + Dm[ie][j][2] * phi[i3] + Dm[ie][j][3] * phi[i4]);//�g�U��
				uu[np] = uu[np] - ADP.get_cx() * (Amx[ie][j][0] * phi[i1] + Amx[ie][j][1] * phi[i2] + Amx[ie][j][2] * phi[i3] + Amx[ie][j][3] * phi[i4])//�ڗ���
					- ADP.get_cy() * (Amy[ie][j][0] * phi[i1] + Amy[ie][j][1] * phi[i2] + Amy[ie][j][2] * phi[i3] + Amy[ie][j][3] * phi[i4]);
				ff[np] = ff[np] + Fm[ie][j][j];
				double dphidx = 0.0;
				double dphidy = 0.0;
				if (mesh.ncond(np) == 2) {
					nn[np] = nn[np] + ADP.get_alpha() * (nx[np] * dphidx + ny[np] * dphidy);//����͗��o�݂̂�������̂ŋ��E����0
				}
	
	
			}
		}
		
		for (int j = 0; j < mesh.ynode(); j++) {
			for (int i = 0; i < mesh.xnode(); i++) {
				int np = i + mesh.xnode() * j;
				if (mesh.ncond(np) == 0) {//���
					phi[np] = phib[np] + t.dt() * (dd[np] + uu[np]) / ff[np];

				}
				else if (mesh.ncond(np) == 1) {//dirichlet���E���
					phi[np] = phib[np];
				}
				else if (mesh.ncond(np) == 2) {//neumann���E���
					phi[np] = phib[np] + t.dt() * (dd[np] + uu[np] + nn[np]) / ff[np];

				}
				else {

				}
				cout << "phi[" << np << "]=" << phi[np] << endl;
			}
		}
	}
}

void Explicit_FEM::output(int n) {
	if (n % t.nsample() == 0) {
		Outputdata output(mesh, t, phi, ADP, BC);
		output.output_result_csv(n);
	}
}