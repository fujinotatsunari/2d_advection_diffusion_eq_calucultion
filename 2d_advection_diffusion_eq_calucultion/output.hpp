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
	int Filestage;
	vector<double> x;
	vector<double> y;
	vector<vector<double>> copy;
	Mesh2d& mesh;
	Time& t;
	ADeq_param_2d& adp;
	Boundarycond& BC;	
	PHI& phi;
	string dir;//保存場所


public:
	Outputdata(Mesh2d& Mesh, Time& T, PHI& phi, ADeq_param_2d& ADP, Boundarycond& BC, int Scheme);
	Outputdata(Mesh2d& Mesh, Time& T, PHI& phi, ADeq_param_2d& ADP, Boundarycond& BC, int Scheme, int filestage, int nstep);
	void output_result_csv(int N);//Nステップでのcsvの出力
	void output_condition();//パラメータファイルの出力

};
class OutputData {
private:
	int scheme;//計算スキームのフラグ
	int Filestage;//保存場所を作成したか否かのフラグ
	//0:未作成,1:作成済み
	vector<double> x;
	vector<double> y;
	vector<vector<double>> copy;
	Mesh2d& mesh;
	Time& t;
	ADeq_param_2d& adp;
	Boundarycond& BC;
	PHI& phi;
	string dir;//ディレクトリdata_nの位置

public:
	OutputData(Mesh2d& Mesh, Time& T, PHI& Phi, ADeq_param_2d& ADP, Boundarycond& Bc);
	void set_scheme(int Scheme);
	void set_Filestage(int filestage);
	int get_scheme(void);
	int get_Filestage(void);
	string directory_setup();//下におけるdata_nを返す
	/*
	* C:-//--|result|----|data0|-----|cond|
	*           |            |
	*           |             -------|resultcsv|
	*           |-------|data1|
	*           |-------|data2|
	*/
	void output_result_csv(int N);//Nステップでのcsvの出力
	void output_condition();//パラメータファイルの出力
	void data_update(PHI& Phi);//データの更新
	string get_dir();
};

class Outputdir {
	/*
	* C:-//--|result|----|data0|-----|cond|
	*           |            |
	*           |             -------|resultcsv|
	*           |-------|data1|
	*           |-------|data2|
	*/
private:
	string dir;//上のresultに該当
	string datadir;//data_nに該当, 1回の解析で1個

	
};
string make_directories(string str1, string str2);
/*ディレクトリを作成したい場所の文字列を作る
親ディレクトリの名前str1と子ディレクトリの名前str2を
結合しディレクトリstr1/str2を作りリターンする*/


//string directories_setup(int n, int scheme);
/*結果を保存するためのディレクトリを作成する*/

