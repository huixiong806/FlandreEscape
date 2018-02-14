#pragma once
#include"Maid.h"
#include<sstream>
#include <unordered_set>
#include"Console.h"
enum class MaidManagerStateType
{
	NORMAL,
	ALERT,
	CATCH
};
class MaidManager
{
private:
	static const int mMaxAlertTime=100;
	int mAlertTimeLeft;
	MaidManagerStateType mState;
	std::shared_ptr<bool> mAlertIsOn;
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>>mMaidSet;
public:
	MaidManager();
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> getMaidSetPtr();
	std::shared_ptr<bool> getAlertPtr();
	void addNewMaid(int pos);
	void deleteMaid(std::shared_ptr<Maid> maid);
	void turnOnAlert();
	void turnOffAlert(MaidManagerStateType newState);
	void update();
};
