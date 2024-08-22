/*�񎟌��ڗ��g�U���������l��̓\�����[�V����*/
#include"param.hpp"
#include"mesh.hpp"
#include"value.hpp"
#include"solution.hpp"
#include<cstdio>
#include<cmath>
#include<vector>
#include<iostream>
using namespace std;

int main(void) {
	NodeP np;
	TimeP tp;
	Boundarycond BC;
	ADeq_param_2d ad(np, tp);
	Time T(tp);
	Mesh2d mesh(np, BC);


	PHI phi(mesh, BC);
	phi.initialize_default();
	for (int j = 0; j < mesh.ynode(); j++) {
		for (int i = 0; i < mesh.xnode(); i++) {
			int np = i + mesh.xnode()*j;
			cout << "x[" << np << "]=" << mesh.x(np) << "  y[" << np << "]=" << mesh.y(np) << endl;
			cout << phi[np] << endl;
		}
	}
	Explicit_FEM solution(mesh, T, phi, BC, ad);
	solution.do_expcalculation();

}