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
	InfoManager::bind(this->mMap);
	mFlan = std::make_shared<FlandreScarlet>();
	InfoManager::bind(this->mFlan);
	mMaidManager = std::make_shared<MaidManager>();
	InfoManager::bind(mMaidManager->getMaidSetPtr());
	InfoManager::bind(mMaidManager->getAlertPtr());
}
void GameManager::update()
{
	//maid manager执行回合操作
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maidSet = mMaidManager->getMaidSetPtr();
	mFlan->update();
	mMaidManager->update();
	//std::cout << "MaidCount:" << maidSet->size() << std::endl;
}
std::shared_ptr<Map> GameManager::getMapPtr()
{
	return mMap;
}
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> GameManager::getMaidSetPtr()
{
	return mMaidManager->getMaidSetPtr();
}
