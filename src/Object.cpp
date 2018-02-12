#include "Object.h"
void Object::setPos(int pos)
{
	mPos = pos;
}
int Object::getPos()
{
	return mPos;
}
void Object::addHp(int hp)
{
	mHp += hp;
}
void Object::attack(Object& opponent)
{
	opponent.addHp(-this->getDamage());
}
void Object::attack(Object* opponent)
{
	opponent->addHp(-this->getDamage());
}
void Object::setHp(int hp)
{
	mHp = hp;
}
bool Object::dead()
{
	return mHp <= 0;
}
int Object::getHp()
{
	return mHp;
}
void Object::setName(const std::string& str)
{
	mName = str;
}
std::string Object::getName()
{
	return mName;
}
void Object::setCoord(Vec2d coord)
{
	mCoord = coord;
}
Vec2d Object::getCoord()
{
	return mCoord;
}
void Object::move(Vec2d delta)
{
	mCoord += delta;
}