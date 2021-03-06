#include"GameManager.h"
#include<iostream>
#include<sstream>
#include<SDL2\SDL.h>
GameManager::GameManager()
{

}
void GameManager::loadGame(std::string fileName)
{
	mMap = std::make_shared<Map>(8, 8);
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			mMap->getVertex(mMap->getPos(i, j)).setEnable(testMap[i][j]);
	InfoManager::bind(this->mMap);
	mFlan = std::make_shared<FlandreScarlet>();
	InfoManager::bind(this->mFlan);
	mMaidManager = std::make_shared<MaidManager>();
	InfoManager::bind(mMaidManager->getMaidSet());
	InfoManager::bind(mMaidManager->getAlertPtr());
}
void GameManager::update()
{
	//maid manager执行回合操作
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maidSet = mMaidManager->getMaidSet();
	mFlan->update();
	mMaidManager->update();
	//std::cout << "MaidCount:" << maidSet->size() << std::endl;
}
std::shared_ptr<Map> GameManager::getMap()
{
	return mMap;
}
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> GameManager::getMaidSet()
{
	return mMaidManager->getMaidSet();
}
std::shared_ptr<FlandreScarlet> GameManager::getFlan()
{
	return mFlan;
}
