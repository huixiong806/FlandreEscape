#include"GameManager.h"
#include<iostream>
#include<sstream>
#include<SDL2\SDL.h>
GameManager::GameManager()
{

}
void GameManager::loadGame(std::string fileName)
{
	mInfoManager = std::make_shared<InfoManager>();
	mMap = std::make_shared<Map>(8,8);
	mFlan = std::make_shared<FlandreScarlet>();
	mLogger = std::make_shared<Log>();
	mMaidManager = std::make_shared<MaidManager>(this->mMap);
	mInfoManager->bind(mMaidManager->getMaidSetPtr());
	mInfoManager->bind(mMaidManager->getAlertPtr());
	mInfoManager->bind(this->mFlan);
	mInfoManager->bind(this->mMap);
	mInfoManager->bind(this->mLogger);
}
void GameManager::update()
{
	//maid manager执行回合操作
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maidSet = mMaidManager->getMaidSetPtr();
	mFlan->update(mInfoManager);
	mMaidManager->update(mInfoManager);
	std::cout << "MaidCount:" << maidSet->size() << std::endl;
}
std::shared_ptr<Log> GameManager::getLog()
{
	return mLogger;
}
std::shared_ptr<Map> GameManager::getMapPtr()
{
	return mMap;
}
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> GameManager::getMaidSetPtr()
{
	return mMaidManager->getMaidSetPtr();
}
