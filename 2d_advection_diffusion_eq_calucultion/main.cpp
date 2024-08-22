/*二次元移流拡散方程式有限要素法解析ソリューション*/
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
	cout <<"2d advection diffusion equation FEM solution" << endl;
	NodeP np;
	TimeP tp;
	Boundarycond BC;
	ADeq_param_2d ad(np, tp);
	Time T(tp);
	Mesh2d mesh(np, BC);


	PHI phi(mesh, BC);
	phi.initialize_default();
	int scheme;
	cout << "set Time scheme" << endl;
	cout << "0:Explicit, 1:Implicit" << endl;
	cin >> scheme;
	if (scheme == 0) {

		Explicit_FEM solution(mesh, T, phi, BC, ad);
		solution.do_expcalculation();
	}
	else if (scheme == 1) {
		Implicit_FEM solution(mesh, T, phi, BC, ad);
		solution.do_impcaluculation();
	}
	

}