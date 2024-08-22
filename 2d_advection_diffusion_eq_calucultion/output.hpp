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
	vector<double> x;
	vector<double> y;
	vector<vector<double>> copy;
	Mesh2d& mesh;
	Time& t;
	ADeq_param_2d& adp;
	Boundarycond& BC;
	PHI& phi;


public:
	Outputdata(Mesh2d& Mesh, Time& T, PHI& phi, ADeq_param_2d& ADP, Boundarycond& BC);
	void output_result_csv(int N);//�v�Z����
	//void output_condition();//�v�Z�p�����[�^

};

string make_directories(string str1, string str2);
	/*�f�B���N�g����쐬�������ꏊ�̕��������
	�e�f�B���N�g���̖��Ostr1�Ǝq�f�B���N�g���̖��Ostr2��
	�������f�B���N�g��str1/str2���胊�^�[������*/
string directories_setup(int n);
	/*���ʂ�ۑ����邽�߂̃f�B���N�g����쐬����*/

