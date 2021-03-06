#include "FlandreScarlet.h"
FlandreScarlet::FlandreScarlet()
{
	this->setName("Flandre");
	this->setPos(0);
	this->setCoord(InfoManager::getCoordByPos(0));
	this->mSpeed = 2.5;
}
const int FlandreScarlet ::getHpLimit()
{
	return mHpLimit;
}
const int FlandreScarlet::getDamage()
{
	return mDamage;
}
const int FlandreScarlet::getHpRecoverPerTick()
{
	return mHpRecoverPerTick;
}
void FlandreScarlet::update()
{
	//����
	if (Console::checkSignal("flanAttack"))
	{
		auto maids=InfoManager::maidsInSight();
		int size = maids.size();
		if (size > 0)
		{
			auto maid = maids[rand() % size];
			this->attack(*maid);
		}
	}
	//�ƶ�
	Vec2d direction=Vec2d(0,0);
	if (Console::checkSignal("flanMoveUp"))
		direction.x -= 1.0;
	if (Console::checkSignal("flanMoveDown"))
		direction.x -= -1.0;
	if (Console::checkSignal("flanMoveLeft"))
		direction.y -= 1.0;
	if (Console::checkSignal("flanMoveRight"))
		direction.y += 1.0;
	if (direction.norm() > 0.0)
	{
		direction = direction.unit();
		Vec2d targetCoord = this->getCoord() + direction *mSpeed;
		if (InfoManager::vertexIsEnable(InfoManager::getPosByCoord(targetCoord)))
		{
			this->walk(direction);
			this->setPos(InfoManager::getPosByCoord(this->getCoord()));
		}	
	}
}