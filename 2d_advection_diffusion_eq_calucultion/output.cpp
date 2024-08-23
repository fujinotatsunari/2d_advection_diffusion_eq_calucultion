#include"output.hpp"
#include <string>
#include <time.h>
#include <direct.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

using namespace std;
string make_directories(string str1, string str2) {

	string str;
	str = str1 + "/" + str2;
	struct stat statBuf;
	if (stat(str.c_str(), &statBuf) != 0) {
		if (_mkdir(str.c_str()) == 0) {
			// 成功
			cout << str << "が作成されました" << endl;
			return str;
		}
		else {
			// 失敗
			cout << str << "の作成に失敗しました" << endl;
			exit(-1);
		}
	}
	else {
		return str;
	}

}
OutputData::OutputData(Mesh2d& Mesh, Time& T, PHI& Phi, ADeq_param_2d& ADP, Boundarycond& Bc)
	:mesh(Mesh), t(T), phi(Phi), adp(ADP), BC(Bc), scheme(-1), Filestage(0)
{
	//dir = directory_setup();
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
void OutputData::set_scheme(int Scheme) {
	scheme = Scheme;
}
void OutputData::set_Filestage(int filestage) {
	Filestage = filestage;
}
int OutputData::get_scheme(void) {
	return scheme;
}
int OutputData::get_Filestage(void) {
	return Filestage;
}
string OutputData::directory_setup(void) {
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
	if (Filestage == 0) {//計算開始後初めて保存場所を作成
		for (int i = 0; check == 0; i++) {
			str1 = str + "/" + "data_" + to_string(i);//C:/../data_i
			//cout << str1 << endl;
			if (stat(str1.c_str(), &statBuf) != 0) {
				//data_iがそんざいしないとき
				str1 = "data_" + to_string(i);
				str = make_directories(str, str1);
				//cout << str << "を作成" <<  endl;
				check = 1;
				dir = str;
				Filestage = 1;
				return str;
			}
			else {
				//data_iがそんざいするときiをインクリメント
			}
		}
	}
	else if (Filestage == 1) {//保存場所が作成済み

		return dir;
	}
	else {
		exit(-1);
	}

}
void OutputData::output_result_csv(int N) {

	string str;
	string str1;
	string str2;
	string str3;

	//str1 = directories_setup(n, scheme);//C:///.../data_(i)
	str1 = directory_setup();
	str2 = "result_csv";
	str3 = make_directories(str1, str2);//C:/..../data_(i)/result_csv
	str = str3 + "/" + "t = " + to_string(t.ntime(N)) + "_" + "phi.csv";

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
void OutputData::output_condition() {
	string str;
	string str1;
	string str2;
	string str3;

	//str1 = directories_setup(n, scheme);//C:///.../data_(i)
	str1 = directory_setup();
	str2 = "condition";
	str3 = make_directories(str1, str2);//C:/..../data_(i)/condition
	str = str3 + "/" + "condition.txt";

	ofstream outputfile(str);
	outputfile << "#calculation_condition" << "\n";
	outputfile << "##mesh_parameter" << "\n";
	outputfile << "xb=" << mesh.xb() << " " << "xt=" << mesh.xt() << "\n";
	outputfile << "yb=" << mesh.yb() << " " << "yt=" << mesh.yt() << "\n";
	outputfile << "dx=" << mesh.dx() << " " << "dy=" << mesh.dy() << "\n";
	outputfile << "xelem=" << mesh.xelem() << " " << "yelem=" << mesh.yelem() << "\n";
	outputfile << "nelem=" << mesh.nelem() << " " << "nnode=" << mesh.nnode() << "\n";
	outputfile << "\n";
	outputfile << "##time_parameter" << "\n";
	outputfile << "dt=" << t.dt() << "\n";
	outputfile << "nend=" << t.nend() << "\n";
	outputfile << "nsample=" << t.nsample() << "\n";
	outputfile << "\n";
	outputfile << "##equation_parameter" << "\n";
	outputfile << "x方向定常流速 cx=" << adp.get_cx() << " " << "y方向定常流速 cy=" << adp.get_cy() << "\n";
	outputfile << "拡散係数 alpha=" << adp.get_alpha() << "\n";
	outputfile << "x方向courant数" << adp.get_couranx() << " " << "y方向courant数" << adp.get_courany() << "\n";
	outputfile << "拡散数" << adp.get_diffusion() << " " << "Peclet数" << adp.get_Pe() << "\n";
	outputfile.close();
}
string OutputData::get_dir() {
	return dir;
}
void OutputData::data_update(PHI& Phi) {
	for (int j = 0; j < mesh.ynode(); j++) {
		for (int i = 0; i < mesh.xnode(); i++) {
			int np = i + mesh.xnode() * j;
			copy[i][j] = Phi[np];
		}
	}
}
/*

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