#pragma once
#include<memory>
#include<string>
class Object//:public std::enable_shared_from_this<Object>
{
protected:
	std::string mName;
	int mPos;
	int mHp;
	virtual const int getHpLimit() = 0;
	virtual const int getDamage() = 0;
	virtual const int getHpRecoverPerTick() = 0;
public:
	virtual void setPos(int pos);
	virtual int getPos();
	virtual void attack(Object& opponent);
	virtual void attack(Object* opponent);
	virtual void addHp(int hp);
	virtual void setHp(int hp);
	virtual bool dead();
	virtual int getHp();
	virtual void setName(const std::string& str);
};