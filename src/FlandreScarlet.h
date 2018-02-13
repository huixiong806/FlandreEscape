#pragma once
#include<vector>
#include<deque>
#include"InfoManager.h"
#include"Object.h"
#include"Instruction.h"
//ܽ����¶
class InfoManager;
class FlandreScarlet :public Object,public std::enable_shared_from_this<FlandreScarlet>
{
private:
	static const int mHpLimit = 10;         //Ѫ������
	static const int mDamage = 3;           //ÿ�ι�����ɵ��˺�
	static const int mHpRecoverPerTick = 1; //ÿtickѪ���ظ�
	const int getHpLimit();
	const int getDamage();
	const int getHpRecoverPerTick();
public:
	FlandreScarlet();
	void update();
};
