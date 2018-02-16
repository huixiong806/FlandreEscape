#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
class Log
{
private:
	std::vector<std::string> history;
	std::fstream logOutput;
	bool update;
	int progress;
public:
	Log();
	void add(std::string info);
	std::string query(int i);
	size_t getSize();
	std::vector<std::string> getNew();
	std::vector<std::string> getLast(int size);
};