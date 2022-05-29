#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>
#define DATA_PATH ".\\resources\\dashBoardData.csv"
constexpr const char* dp = DATA_PATH;

namespace {
	struct status {
		int pulsometer;
		double engine;
		int red;
		int blue;
		int green;
	};
}

class DashboardData {
public:
	void loadData() {
		using namespace std;
		_dbData.clear();
		fstream dataFile;
		dataFile.open(dp);
		cout << dp << endl;

		status lineData;
		string line, strElement, timestamp, lineTime;
		getline(dataFile, line); // skip header row

		while (dataFile.good())
		{
			getline(dataFile, line);
			stringstream ssElement(line);

			getline(ssElement, timestamp, ',');
			lineTime = timestamp.substr(timestamp.find("T") + 1, 8);

			getline(ssElement, strElement, ',');
			lineData.pulsometer = stoi(strElement);

			getline(ssElement, strElement, ',');
			lineData.engine = stod(strElement);

			getline(ssElement, strElement, ',');
			lineData.red = stoi(strElement);

			getline(ssElement, strElement, ',');
			lineData.blue = stoi(strElement);

			getline(ssElement, strElement, '\r');
			lineData.green = stoi(strElement);

			_dbData[lineTime] = lineData;
		}

		dataFile.close();
	}
	void getData() {
		using namespace std;
		time_t rawTime;
		time(&rawTime);
		struct tm* sysTime = new tm();
		localtime_s(sysTime, &rawTime);
		strftime((char*)_dataTime.c_str(), 80, "%T", sysTime);
		_currentStatus = _dbData[_dataTime];

	}
	std::string getTime() {
		return _dataTime;
	}
	int getPulsometer() {
		return _currentStatus.pulsometer;
	}
	double getEngine() {
		return _currentStatus.engine;
	}
	int getRed() {
		return _currentStatus.red;
	}
	int getBlue() {
		return _currentStatus.blue;
	}
	int getGreen() {
		return _currentStatus.green;
	}
private:
	status _currentStatus;
	std::string _dataTime = "hh:mm:ss";
	std::map<std::string, status> _dbData;
};
