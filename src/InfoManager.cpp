#include"InfoManager.h"
void InfoManager::bind(std::shared_ptr<FlandreScarlet> flan)
{
	mFlan = flan;
}
void InfoManager::bind(std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maid)
{
	mMaid=maid;
}
void InfoManager::bind(std::shared_ptr<bool> alert)
{
	mAlertIsOn = alert;
}
void InfoManager::bind(std::shared_ptr<Map> map)
{
	mMap= map;
}
bool InfoManager::haveAlert()
{
	return *mAlertIsOn;
}
bool InfoManager::CanSeeFlan(std::shared_ptr<Maid> maid)
{
	return mFlan->getPos() == maid->getPos();
}
std::shared_ptr<FlandreScarlet> InfoManager::getFlan()
{
	return mFlan;
}
int InfoManager::getBloodStain(std::shared_ptr<Maid> maid)
{
	return mMap->getVertex(maid->getPos()).getBlood();
}
//Maid 清理血迹(一次清理1)
void InfoManager::cleanBloodStain(std::shared_ptr<Maid> maid)
{
	if (mMap->getVertex(maid->getPos()).getBlood() > 0)
		mMap->getVertex(maid->getPos()).addBlood(-1);
}
void InfoManager::moveTo(std::shared_ptr<Maid> maid,int pos)
{
	mMap->getVertex(maid->getPos()).deleteMaid(maid);
	maid->setPos(pos);
	mMap->getVertex(maid->getPos()).addMaid(maid);
}
//Maid 获取路径
std::vector<int> InfoManager::getPath(std::shared_ptr<Maid> maid, int targetPos)
{
	return mMap->getWayPoints(maid->getPos(),targetPos);
}
//通用 获取路径
std::vector<int> InfoManager::getPath(int startPos, int targetPos)
{
	return mMap->getWayPoints(startPos, targetPos);
}
/*
std::vector<std::shared_ptr<Maid>> InfoManager::maidsInSight()
{
	//TODO:
}*/
