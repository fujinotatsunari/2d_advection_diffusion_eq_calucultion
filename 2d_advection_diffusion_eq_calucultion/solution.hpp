#pragma once
#include"solution.hpp"
#include"output.hpp"
#include"FEM.hpp"
#include"value.hpp"
#include"Mesh.hpp"
#include"param.hpp"
#include"matrix.hpp"
#include<vector>

class Explicit_FEM {
private:
	Mesh2d& mesh;
	Boundarycond& BC;
	Time& t;
	PHI& phi;
	ADeq_param_2d& ADP;
	int node = 4;
public:
	Explicit_FEM(Mesh2d& mesh_, Time& t_, PHI& phi_, Boundarycond& BC_, ADeq_param_2d& adp_);
	void output(int n);
	void do_expcalculation();//¿—ÊW’†‰»‚ğ—p‚¢‚éŒvZ
};

