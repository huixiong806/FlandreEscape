#pragma once
#include<memory>
#include<string>
#include"Vec2.hpp"
class Object//:public std::enable_shared_from_this<Object>
{
protected:
	std::string mName;
	int mPos;
	//สตสýื๘ฑ๊
	Vec2d mCoord;
	int mHp;
	double mSpeed;
	virtual const int getHpLimit() = 0;
	virtual const int getDamage() = 0;
	virtual const int getHpRecoverPerTick() = 0;
public:
	virtual void setPos(int pos);
	virtual int getPos();
	virtual void setCoord(Vec2d coord);
	virtual Vec2d getCoord();
	virtual void walk(Vec2d direction);
	virtual void attack(Object& opponent);
	virtual void attack(Object* opponent);
	virtual void addHp(int hp);
	virtual void setHp(int hp);
	virtual bool dead();
	virtual int getHp();
	virtual void setName(const std::string& str);
	virtual std::string getName();
};