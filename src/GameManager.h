#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include"InfoManager.h"
#include"MaidManager.h"
#include"Map"
#include"Log.hpp"
//class InfoManager;
//class MaidManager;
class Log;
class GameManager
{
private:
	std::shared_ptr<InfoManager> mInfoManager;
	std::shared_ptr<MaidManager> mMaidManager;
	std::shared_ptr<FlandreScarlet> mFlan;
	std::shared_ptr<Map> mMap;
	std::vector<std::string> info;
	std::shared_ptr<Log> mLogger;
public:
	GameManager();
	void loadGame(std::string fileName);
	void update();
	std::shared_ptr<Log> getLog();
	std::shared_ptr<Map> getMapPtr();
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> getMaidSetPtr();
};