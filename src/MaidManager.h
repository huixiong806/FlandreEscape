#pragma once
#include"Maid.h"
#include <unordered_set>
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
	std::shared_ptr<Map>mMap;
public:
	MaidManager();
	MaidManager(std::shared_ptr<Map> map);
	void bindMap(std::shared_ptr<Map>map);
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> getMaidSetPtr();
	std::shared_ptr<bool> getAlertPtr();
	void addNewMaid(int pos);
	void deleteMaid(std::shared_ptr<Maid> maid);
	void turnOnAlert();
	void turnOffAlert(MaidManagerStateType newState);
	void update();
};
