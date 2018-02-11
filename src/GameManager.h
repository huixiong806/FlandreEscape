#pragma once
#include<fstream>
#include<string>
#include<vector>
#include<cstdio>
#include"InfoManager.h"
#include"MaidManager.h"
#include"Map"
//class InfoManager;
//class MaidManager;
class GameManager
{
private:
	std::shared_ptr<InfoManager> mInfoManager;
	std::shared_ptr<MaidManager> mMaidManager;
	std::shared_ptr<FlandreScarlet> mFlan;
	std::shared_ptr<Map> mMap;
	std::vector<std::string> info;
public:
	GameManager();
	void loadGame(std::string fileName);
	void update();
	std::vector<std::string> getInfo();
};