#include"output.hpp"
#include <string>
#include <time.h>
#include <direct.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

using namespace std;
Outputdata::Outputdata(Mesh2d& Mesh, Time& T, PHI& Phi, ADeq_param_2d& ADP, Boundarycond& bc, int Scheme) 
	:n(0),mesh(Mesh),t(T),phi(Phi),adp(ADP),BC(bc),scheme(Scheme)
{

	
	x.resize(mesh.xnode());
	y.resize(mesh.ynode());
	copy.resize(mesh.xnode());
	for (int i = 0; i < copy.size(); i++) {
		copy[i].resize(mesh.ynode());
	}
	for (int j = 0; j < mesh.ynode(); j++) {
		for (int i = 0; i < mesh.xnode(); i++) {
			int np = i + mesh.xnode() * j; 
			copy[i][j] = phi[np];

			if (i == 0) {
				y[j] = mesh.y(np);
			}
			if (j == 0) {
				x[i] = mesh.x(np);
			}
		}
	}
}
void Outputdata::output_result_csv(int N) {
	n = N;
	string str;
	string str1;//makedirectoriesで帰ってくるパス
	string str2;
	string str3;

	str1 = directories_setup(n, scheme);//C:///.../data_(i)
	str2 = "result_csv";
	str3 = make_directories(str1, str2);//C:/..../data_(i)/result_csv
	str = str3 + "/" + "t = " + to_string(t.ntime(n)) + "_" + "phi.csv";

	ofstream outputfile(str);
	outputfile << ",";
	for (int i = 0; i < x.size(); i++) {
		outputfile << x[i] << ",";
	}
	outputfile << "\n";
	for (int j = 0; j < y.size(); j++) {
		outputfile << y[j] << ",";
		for (int i = 0; i < x.size(); i++) {
			outputfile << copy[i][j] << ",";
		}
		outputfile << "\n";
	}
	outputfile.close();
}
string make_directories(string str1, string str2) {
	/*ディレクトリを作成したい場所の文字列を作る
	親ディレクトリの名前str1と子ディレクトリの名前str2を
	結合しディレクトリstr1/str2を作りリターンする*/
	string str;
	str = str1 + "/" + str2;
	struct stat statBuf;
	if (stat(str.c_str(), &statBuf) != 0) {
		if (_mkdir(str.c_str()) == 0) {
			//成功
			cout << str << "���쐬����܂���" << endl;
			return str;
		}
		else {
			// 失敗
			cout << str << "�̍쐬�Ɏ��s���܂���" << endl;
			exit(-1);
		}
	}
	else {

		//cout << str << "�͂��łɂ���܂�" << endl;
		return str;
	}

}
string directories_setup(int n) {
	string dirname0 = "C:";
	string dirname1 = "Result";
	string dirname2 = "2d_advection_diffusion_eq_calculation";
	
	string dirname3 = "FEM_explicit";
	string dirname4 = "result";
	string str;
	string str1;

	string year;
	string month;
	string day;

	time_t timer;
	struct tm local_time;
	timer = time(NULL);
	localtime_s(&local_time, &timer);
	struct stat statBuf;

	str = make_directories(make_directories(make_directories(make_directories(dirname0, dirname1), dirname2), dirname3), dirname4);

	year = to_string(local_time.tm_year + 1900);
	month = to_string(local_time.tm_mon + 1);
	day = to_string(local_time.tm_mday);

	str1 = year + month + day;
	str = make_directories(str, str1);//C:/..../day

	int check = 0;

	if (n == 0) {//時間ステップが0(初回呼び出し時)
		for (int i = 0; check == 0; i++) {
			str1 = str + "/" + "data" + to_string(i);//C:/../data_i
			if (stat(str1.c_str(), &statBuf) != 0) {
				//C:/../data_iがそんざいしないとき
				str1 = "data" + to_string(i);//存在しないのでつくる
				str = make_directories(str, str1);
				check = 1;
				return str;//C:/../data_i
			}
			else {
				//C:/../data_iがそんざいするとき
			}
		}
	}
	else {//時間ステップが0じゃない(初回ではない)
		for (int i = 0; check == 0; i++) {
			str1 = str + "/" + "data" + to_string(i);//C:/../data_i
			if (stat(str1.c_str(), &statBuf) != 0) {
				//C:/../data_iがそんざいしないとき
				str1 = "data" + to_string(i);
				str = make_directories(str, str1);
				check = 1;
				return str;
			}
			else {
				//str1がそんざいするとき
				int j = i + 1;
				str1 = str + "/" + "data" + to_string(j);//C:/../data_(i+1)
				if (stat(str1.c_str(), &statBuf) != 0) {
					//data(i+1)が存在しない<=>dataiが最後<=>dataiへ保存
					str1 = "data" + to_string(i);
					str = make_directories(str, str1);
					check = 1;
					return str;
				}
				else {
					//data(i+1)が存在
				}
			}

		}
	}

}
string directories_setup(int n, int scheme) {
	string dirname0 = "C:";
	string dirname1 = "Result";
	string dirname2 = "2d_advection_diffusion_eq_calculation";
	string dirname3;
	if (scheme == 0) {//陽解法
		dirname3 = "FEM_explicit";
	}
	else if (scheme == 1) {//陰解法
		dirname3 = "FEM_implicit";
	}
	
	string dirname4 = "result";
	string str;
	string str1;

	string year;
	string month;
	string day;

	time_t timer;
	struct tm local_time;
	timer = time(NULL);
	localtime_s(&local_time, &timer);
	struct stat statBuf;

	str = make_directories(make_directories(make_directories(make_directories(dirname0, dirname1), dirname2), dirname3), dirname4);

	year = to_string(local_time.tm_year + 1900);
	month = to_string(local_time.tm_mon + 1);
	day = to_string(local_time.tm_mday);

	str1 = year + month + day;
	str = make_directories(str, str1);//C:/..../day

	int check = 0;

	if (n == 0) {//時間ステップが0(初回呼び出し時)
		for (int i = 0; check == 0; i++) {
			str1 = str + "/" + "data" + to_string(i);//C:/../data_i
			if (stat(str1.c_str(), &statBuf) != 0) {
				//C:/../data_iがそんざいしないとき
				str1 = "data" + to_string(i);//存在しないのでつくる
				str = make_directories(str, str1);
				check = 1;
				return str;//C:/../data_i
			}
			else {
				//C:/../data_iがそんざいするとき
			}
		}
	}
	else {//時間ステップが0じゃない(初回ではない)
		for (int i = 0; check == 0; i++) {
			str1 = str + "/" + "data" + to_string(i);//C:/../data_i
			if (stat(str1.c_str(), &statBuf) != 0) {
				//C:/../data_iがそんざいしないとき
				str1 = "data" + to_string(i);
				str = make_directories(str, str1);
				check = 1;
				return str;
			}
			else {
				//str1がそんざいするとき
				int j = i + 1;
				str1 = str + "/" + "data" + to_string(j);//C:/../data_(i+1)
				if (stat(str1.c_str(), &statBuf) != 0) {
					//data(i+1)が存在しない<=>dataiが最後<=>dataiへ保存
					str1 = "data" + to_string(i);
					str = make_directories(str, str1);
					check = 1;
					return str;
				}
				else {
					//data(i+1)が存在
				}
			}

		}
	}


}
/*
void out_put(int n, double time, int xelem, int yelem, double* phi, double* x, double* y) {
	int xnode = xelem + 1;
	int ynode = yelem + 1;


	output_csv(n, time, xelem, yelem, x, y, phi);
	//output_inp(n, time, xelem, yelem, x, y, phi);



}
void output_csv(int n, double time, int xelem, int yelem, double* x, double* y, double* phi) {

	int xnode = xelem + 1;
	int ynode = yelem + 1;
	double* X = new double[xnode];
	double* Y = new double[ynode];
	double** output_phi;



	output_phi = new double* [xnode];
	for (int i = 0; i < xnode; i++) {
		output_phi[i] = new double[ynode];
	}
	for (int j = 0; j < ynode; j++) {
		for (int i = 0; i < xnode; i++) {
			int np = i + xnode * j; //�ߓ_�ԍ�

			output_phi[i][j] = phi[np];
			if (i == 0) {
				Y[j] = y[np];
			}
			if (j == 0) {
				X[i] = x[np];
			}
		}
	}

	std::string str;
	std::string str1;//makedirectories�ŋA���Ă���p�X
	std::string str2;
	std::string str3;

	str1 = directories_setup(n);//C:///.../data_(i)
	str2 = "result_csv";
	str3 = make_directories(str1, str2);//C:/..../data_(i)/result_csv
	str = str3 + "/" + "t = " + to_string(time) + "_" + "phi.csv";

	ofstream outputfile(str);
	outputfile << ",";
	for (int i = 0; i < xnode; i++) {
		outputfile << X[i] << ",";
	}
	outputfile << "\n";
	for (int j = 0; j < ynode; j++) {
		outputfile << Y[j] << ",";
		for (int i = 0; i < xnode; i++) {
			outputfile << output_phi[i][j] << ",";
		}
		outputfile << "\n";
	}
	outputfile.close();


	delete[] X;
	delete[] Y;
	for (int i = 0; i < xnode; i++) {
		delete[] output_phi[i];
	}

}

void output_inp(int n, double time, int xelement, int yelement, double* x, double* y, double* phi) {
	int xnode = xelement + 1;
	int ynode = yelement + 1;
	int nelem = xelement * yelement;
	int nnode = xnode * ynode;

	int** nbool1;   //nbool[�v�f�ԍ�][�Ǐ��ߓ_�ԍ�] = �S�̐ߓ_�ԍ�
	nbool1 = new int* [nelem];
	nbool1[0] = new int[nelem * NODE];

	for (int ie = 0; ie < nelem; ie++) {
		nbool1[ie] = nbool1[0] + ie * NODE;
	}
	for (int j = 0; j < yelement; j++) {
		for (int i = 0; i < xelement; i++) {
			int ie = i + xelement * j;
			int np1 = i + xnode * j;
			int np2 = np1 + 1;
			int np4 = np1 + xnode;
			int np3 = np4 + 1;


			nbool1[ie][0] = np1;
			nbool1[ie][1] = np2;
			nbool1[ie][2] = np3;
			nbool1[ie][3] = np4;
		}
	}


	std::string str;
	std::string str1;//makedirectories�ŋA���Ă���p�X
	std::string str2;
	std::string str3;

	str1 = directories_setup(n);//C:///.../data_(i)
	str2 = "result_csv";
	str3 = make_directories(str1, str2);//C:/..../data_(i)/result_csv
	str = str3 + "/" + "t=" + to_string(time) + "_" + "phi.inp";
	ofstream outputfile(str);

	outputfile << "# 2d square domain 4-node quadrilateral grids\n";
	outputfile << "1\n";
	outputfile << "data\n";
	outputfile << "step" << n << " t=" << time << "\n";
	outputfile << nnode << " " << nelem << "\n";
	for (int i = 0; i < nnode; i++) {       //�ߓ_�ԍ� x,y,z���W
		//2�������z=0
		outputfile << i << " " << x[i] << " " << y[i] << " " << 0.0 << "\n";

	}
	for (int ie = 0; ie < nelem; ie++) {        //�v�f�ԍ��@�ގ��ԍ��@�v�f��ށ@�v�f�\��

		outputfile << ie << " " << 1 << " " << "quad";
		for (int i = 0; i < 4; i++) {
			outputfile << nbool1[ie][i];
		}
		outputfile << "\n";
	}
	outputfile << 1 << " " << 0 << "\n";
	outputfile << 1 << " " << 1 << "\n";
	outputfile << "Temperature, _\n";
	for (int i = 0; i < nnode; i++) {   //�ߓ_�ԍ��@�ߓ_�f�[�^�l
		outputfile << i << " " << phi[i] << "\n";
	}
	outputfile.close();
	delete[] nbool1[0]; delete[] nbool1;
}
*/