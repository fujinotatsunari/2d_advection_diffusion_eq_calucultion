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
	cout <<"二次元移流拡散方程式有限要素法解析ソリューション" << endl;
	NodeP np;
	TimeP tp;
	Boundarycond BC;
	ADeq_param_2d ad(np, tp);
	Time T(tp);
	Mesh2d mesh(np, BC);


	PHI phi(mesh, BC);
	phi.initialize_default();
	int scheme;
	cout << "時間進行スキームの設定" << endl;
	cout << "0:陽解法, 1:陰解法" << endl;
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