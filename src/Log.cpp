#include "Log.h"
Log::Log()
{
	std::stringstream fileName;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t tt;
	tt = std::chrono::system_clock::to_time_t(now);
	fileName << tt << ".log";

	logOutput.open(fileName.str());
	update = false;
	progress = 0;
}
void Log::add(std::string info)
{
	logOutput << info << std::endl;
	history.push_back(info);
	update = true;
}
std::string Log::query(int i)
{
	if (i < history.size())
		return history[i];
	return "";
}
size_t Log::getSize()
{
	return history.size();
}
std::vector<std::string> Log::getNew()
{
	std::vector<std::string> ret;
	for (; progress < history.size(); progress++)
		ret.push_back(history[progress]);
	return ret;
}
std::vector<std::string> Log::getLast(int size = 10)
{
	if (history.size() < size)
	{
		std::vector<std::string> r = history;
		return r;
	}
	else
	{
		std::vector<std::string> r;
		for (int i = size; i > 0; i--)
			r.push_back(history[history.size() - i]);
		return r;
	}
}