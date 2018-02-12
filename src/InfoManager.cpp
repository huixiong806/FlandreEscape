#include"InfoManager.h"
std::shared_ptr<Map> InfoManager::mMap;
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> InfoManager::mMaid;
std::shared_ptr<FlandreScarlet> InfoManager::mFlan;
std::shared_ptr<bool> InfoManager::mAlertIsOn;
std::shared_ptr<Log> InfoManager::mLogger;
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
void InfoManager::bind(std::shared_ptr<Log> logger)
{
	mLogger = logger;
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
//通用 获取logger
std::shared_ptr<Log> InfoManager::getLogger()
{
	return mLogger;
}
//通用 想要移动到某个格子，应该往哪个方向走？返回一个单位向量
Vec2d InfoManager::getTheDirectionTo(Vec2d startPos, int tarPos)
{
	Vec2i tarPairPos = mMap->getPos(tarPos);
	return (Vec2d(tarPairPos.x, tarPairPos.y) * girdSize+Vec2d(girdSize, girdSize)*0.5 - startPos).unit();
}
//通用 根据实数坐标确定位置
int InfoManager::getPosByCoord(Vec2d coord)
{
	coord/= girdSize;
	return mMap->getPos(coord.x, coord.y);
}
Vec2i InfoManager::getPos(int pos)
{
	return mMap->getPos(pos);
}
//通用 返回该格子中间的坐标
Vec2d InfoManager::getCoordByPos(int pos)
{
	Vec2i coord = getPos(pos);
	return Vec2d(coord.x, coord.y)*girdSize + Vec2d(girdSize, girdSize)*0.5;
}
//通用，判断一个坐标是否在格子正中间,误差不超过eps(eps为误差范围比格子大小)
bool InfoManager::inMid(Vec2d coord, int pos,double eps)
{
	eps *= 0.5;
	Vec2d mid = getCoordByPos(pos);
	bool xok = mid.x - eps *girdSize <= coord.x&&coord.x <= mid.x + eps *girdSize ;
	bool yok= mid.y - eps *girdSize <= coord.y&&coord.y <= mid.y + eps *girdSize;
	return xok&&yok;
}
/*
std::vector<std::shared_ptr<Maid>> InfoManager::maidsInSight()
{
	//TODO:
}*/
