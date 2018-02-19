#include"InfoManager.h"
std::shared_ptr<Map> InfoManager::mMap;
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> InfoManager::mMaid;
std::shared_ptr<FlandreScarlet> InfoManager::mFlan;
std::shared_ptr<bool> InfoManager::mAlertIsOn;
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
//Maid ����Ѫ��(һ������1)
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
//Maid ��ȡ·��
std::vector<int> InfoManager::getPath(std::shared_ptr<Maid> maid, int targetPos)
{
	return mMap->getWayPoints(maid->getPos(),targetPos);
}
//ͨ�� ��ȡ·��
std::vector<int> InfoManager::getPath(int startPos, int targetPos)
{
	return mMap->getWayPoints(startPos, targetPos);
}
//ͨ�� ��Ҫ�ƶ���ĳ�����ӣ�Ӧ�����ĸ������ߣ�����һ����λ����
Vec2d InfoManager::getTheDirectionTo(Vec2d startPos, int tarPos)
{
	Vec2i tarPairPos = mMap->getPos(tarPos);
	return (Vec2d(tarPairPos.x, tarPairPos.y) * girdSize+Vec2d(girdSize, girdSize)*0.5 - startPos).unit();
}
//ͨ�� ����ʵ������ȷ��λ��
int InfoManager::getPosByCoord(Vec2d coord)
{
	coord/= girdSize;
	if (coord.x < 0 || coord.y < 0||coord.x>=mMap->getSizeR()|| coord.y >= mMap->getSizeC())return -1;
	return mMap->getPos(coord.x, coord.y);
}
Vec2i InfoManager::getPos(int pos)
{
	return mMap->getPos(pos);
}
//ͨ�� ���ظø����м������
Vec2d InfoManager::getCoordByPos(int pos)
{
	Vec2i coord = getPos(pos);
	return Vec2d(coord.x, coord.y)*girdSize + Vec2d(girdSize, girdSize)*0.5;
}
//ͨ�ã��ж�һ�������Ƿ��ڸ������м�,������eps(epsΪ��Χ�ȸ��Ӵ�С)
bool InfoManager::inMid(Vec2d coord, int pos,double eps)
{
	eps *= 0.5;
	Vec2d mid = getCoordByPos(pos);
	bool xok = mid.x - eps *girdSize <= coord.x&&coord.x <= mid.x + eps *girdSize ;
	bool yok= mid.y - eps *girdSize <= coord.y&&coord.y <= mid.y + eps *girdSize;
	return xok&&yok;
}
//MaidManager ��ȡָ���ͼ��ָ��
std::shared_ptr<Map> InfoManager::getMap()
{
	return mMap;
}
//ͨ�� ���ص��Ƿ����ϰ�
bool InfoManager::vertexIsEnable(int pos)
{
	if (pos < 0||pos>=mMap->getSize())return false;
	return mMap->getVertex(pos).getEnable();
}
std::vector<std::shared_ptr<Maid>> InfoManager::maidsInSight()
{
	return mMap->getVertex(mFlan->getPos()).getMaidPool();
}
