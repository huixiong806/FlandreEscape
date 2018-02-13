#include "FlandreScarlet.h"
FlandreScarlet::FlandreScarlet()
{
	this->setName("Flandre");
	this->setPos(0);
	this->setCoord(InfoManager::getCoordByPos(this->getPos()));
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

}