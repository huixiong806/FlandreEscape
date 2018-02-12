#include"MaidManager.h"
MaidManager::MaidManager()
{ 
	mAlertIsOn = std::make_shared<bool>(false); 
	mMaidSet = std::make_shared<std::unordered_set<std::shared_ptr<Maid>>>();
	
}
MaidManager::MaidManager(std::shared_ptr<Map> map)
{
	mAlertIsOn = std::make_shared<bool>(false);
	mMaidSet = std::make_shared<std::unordered_set<std::shared_ptr<Maid>>>();
	this->bindMap(map);
	//以下为测试代码
	//我们先在位置0创造一个女仆来测试一下w
	this->addNewMaid(0);
}
void MaidManager::addNewMaid(int pos)
{
	std::shared_ptr<Maid> maid = std::make_shared<Maid>(pos);
	mMaidSet->insert(maid);
	mMap->getVertex(pos).addMaid(maid);
}
void MaidManager::deleteMaid(std::shared_ptr<Maid> maid)
{
	mMap->getVertex(maid->getPos()).deleteMaid(maid);
	mMaidSet->erase(maid);
}
void MaidManager::turnOnAlert()
{
	*mAlertIsOn = true;
	this->mState = MaidManagerStateType::ALERT;
}
void MaidManager::turnOffAlert(MaidManagerStateType newState)
{
	*mAlertIsOn = false;
	this->mState = newState;
}
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> MaidManager::getMaidSetPtr()
{
	return mMaidSet;
}
std::shared_ptr<bool> MaidManager::getAlertPtr()
{
	return mAlertIsOn;
}
void MaidManager::update()
{
	//以下为测试代码
	//对于所有女仆
	if (mMaidSet->empty())
		this->addNewMaid(1);
	for (auto& maid : *mMaidSet)
	{
		//如果哪个闲着
		if (maid->free())
		{
			//派去巡逻
			maid->receiveInstruction(Instruction(InstructionType::PATROL, { 0,0,24 }));
		}
		else
		{
			maid->receiveInstruction(Instruction(InstructionType::NUL, std::vector<int>()));
		}
	}
}
std::unordered_set<std::shared_ptr<Maid>> MaidManager::getMaids()
{
	return *mMaidSet;
}
void MaidManager::bindMap(std::shared_ptr<Map>map)
{
	mMap = map;
}