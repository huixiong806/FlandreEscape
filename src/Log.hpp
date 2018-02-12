#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;
class Log
{
private:
	vector<string> history;
	fstream logOutput;
	bool update;
	int progress;
public:
	Log()
	{
		stringstream fileName;
		chrono::system_clock::time_point now = chrono::system_clock::now();
		time_t tt;
		tt = chrono::system_clock::to_time_t(now);
		fileName << tt << ".log";
		
		logOutput.open(fileName.str());
		update = false;
		progress = 0;
	}
	void add(string info)
	{
		logOutput << info << endl;
		history.push_back(info);
		update = true;
	}
	string query(int i)
	{
		if(i < history.size())
			return history[i];
		return "";
	}
	int getSize()
	{
		return history.size();
	}
	vector<string> getNew()
	{
		vector<string> ret;
		for (; progress < history.size(); progress++)
			ret.push_back(history[progress]);
		return ret;
	}
	vector<string> getLast(int size = 10)
	{
		if (history.size() < size)
		{
			vector<string> r = history;
			return r;
		}
		else
		{
			vector<string> r;
			for (int i = size; i > 0; i--)
				r.push_back(history[history.size() - i]);
			return r;
		}
	}
};