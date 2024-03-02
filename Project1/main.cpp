#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;
using namespace std;

void backup(void); // 备份功能函数
string Time(void); // 获取当前时间并转为string类型

const string path_state = "Date/State.txt";
const string path_mainlog = "Date/log.txt";
const string path_main = "Date/Main/";
const string path_backuplog = "Backup/log.txt";

int main() {
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
		fout.open(path_mainlog, ios::app);
		fout << Time() << "  The file was initialized.\n";
		fout.close();
		fout.open(path_state, ios::out);
		fout << "Active";
		fout.close();
	}
	else {
		// 未完成
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
	vector<string> allbackuplog;
	string line;
	string note;
	string time = Time();
	cout << "Please enter a note:";
	cin.get();
	getline(cin, note);
	string str_backuplog;
	ifstream fin;
	ofstream fout;
	fin.open(path_backuplog, ios::in);
	getline(fin, str_backuplog);
	cout << str_backuplog;
	fs::path folderPath = "Backup/backup" + str_backuplog;
	fin.close();
	cout << folderPath;
	if (!fs::exists(folderPath)) {
		bool success = fs::create_directory(folderPath);
	}
	try {
		fs::copy("Date/Main/", "Backup/backup" + str_backuplog + "/", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
		std::cout << "Folder copied successfully." << std::endl;
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Folder copy failed: " << e.what() << std::endl;
	}
	fout.open(path_backuplog, ios::app);
	fout << "\n" << time << "  " << note;
	fout.close();
	fin.open(path_backuplog);
	while (getline(fin, line)) {
		allbackuplog.push_back(line);
	}
	fin.close();
	allbackuplog[0] = to_string(stoi(str_backuplog) + 1);
	fout.open(path_backuplog, ios::out);
	for (const auto& content : allbackuplog) {
		fout << content << "\n";
	}
	fout.close();
}

