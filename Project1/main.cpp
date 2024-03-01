#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
string Time(void);
int main() {
	string path_state = "Date/State.txt";
	string path_log = "Date/log.txt";
	ifstream fin;
	ofstream fout;
	fin.open(path_state, ios::in);
	char state[10];
	fin.getline(state, 10);
	string str_state = state;
	if (str_state == "Inactive") {
		int size;
		cout << "For the first time,initialization is required.\n";
		cout << "Please enter the class size:";
		cin >> size;
		time_t timep;
		time(&timep);

	}
	else {

	}
	return 0;
}

string Time(void) {
	time_t timep;
	time(&timep);
	char tmp[32];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	string strtime = tmp;
	return strtime;
}