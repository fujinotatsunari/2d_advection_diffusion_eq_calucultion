#pragma once
#include"output.hpp"
#include"mesh.hpp"
#include"value.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include<vector>
using namespace std;

class Outputdata {
private:
	int n;
	int scheme;

	vector<double> x;
	vector<double> y;
	vector<vector<double>> copy;
	Mesh2d& mesh;
	Time& t;
	ADeq_param_2d& adp;
	Boundarycond& BC;
	PHI& phi;


public:
	Outputdata(Mesh2d& Mesh, Time& T, PHI& phi, ADeq_param_2d& ADP, Boundarycond& BC, int Scheme);
	void output_result_csv(int N);
	//void output_condition();

};

string make_directories(string str1, string str2);
/*ディレクトリを作成したい場所の文字列を作る
親ディレクトリの名前str1と子ディレクトリの名前str2を
結合しディレクトリstr1/str2を作りリターンする*/


string directories_setup(int n, int scheme);
/*結果を保存するためのディレクトリを作成する*/
