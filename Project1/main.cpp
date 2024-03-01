#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
void backup(void);
string Time(void); //获取当前时间并转为string类型
int main() {
	
	string path_state = "Date/State.txt";
	string path_log = "Date/log.txt";
	string path_main = "Date/Main/";
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
		for (int i = 1; i <= size; ++i) {
			fs::path folderPath = path_main + to_string(i);
			if (!fs::exists(folderPath)) {
				bool success = fs::create_directory(folderPath);
			}
		}
		fin.close();
		fout.open(path_log, ios::app);
		fout << Time() << "  The file was initialized.\n";
		fout.close();
		backup();
	}
	else {
		//未完成
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

void backup(void) {
	string log;
	ifstream fin;
	ofstream fout;
	fin.open("/Backup/log.txt", ios::in);
	fin >> log;
	fs::path folderPath = "/Backup/backup" + log;
	fin.close();
	if (!fs::exists(folderPath)) {
		bool success = fs::create_directory(folderPath);
	}
	try {
		fs::copy("/Date/Main/", "/Backup/backup" + log + "/", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
		std::cout << "Folder copied successfully." << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Folder copy failed: " << e.what() << std::endl;
	}
	fout.open("/Backup/log.txt", ios::out);
	fout << stoi(log.c_str()) + 1;
	fout.close();
}

