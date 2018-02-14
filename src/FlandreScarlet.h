#pragma once
#include<vector>
#include<deque>
#include"InfoManager.h"
#include"Object.h"
#include"Instruction.h"
//芙兰朵露
class InfoManager;
class FlandreScarlet :public Object,public std::enable_shared_from_this<FlandreScarlet>
{
private:
	static const int mHpLimit = 10;         //血量上限
	static const int mDamage = 3;           //每次攻击造成的伤害
	static const int mHpRecoverPerTick = 1; //每tick血量回复
	const int getHpLimit();
	const int getDamage();
	const int getHpRecoverPerTick();
public:
	FlandreScarlet();
	void update();
};
