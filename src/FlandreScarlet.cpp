#include "FlandreScarlet.h"
FlandreScarlet::FlandreScarlet()
{
	this->setName("Flandre");
	this->setPos(0);
	this->setCoord(InfoManager::getCoordByPos(0));
	this->mSpeed = 2.0;
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
	//ÒÆ¶¯·½Ïò
	Vec2d direction=Vec2d(0,0);
	if (Console::checkSignal("flanMoveUp"))
		direction.x -= 1.0;
	if (Console::checkSignal("flanMoveDown"))
		direction.x += 1.0;
	if (Console::checkSignal("flanMoveLeft"))
		direction.y -= 1.0;
	if (Console::checkSignal("flanMoveRight"))
		direction.y += 1.0;
	if (direction.norm() > 0.0)
	{
		direction = direction.unit();
		this->walk(direction);
		this->setPos(InfoManager::getPosByCoord(this->getCoord()));
	}
}