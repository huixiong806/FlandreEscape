#include"MaidManager.h"
#include<sstream>
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
	this->mAlertTimeLeft = this->mMaxAlertTime;
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
void MaidManager::update(std::shared_ptr<InfoManager>info)
{
	//以下为测试代码
	//保持场上有3个女仆
	if(mMaidSet->size()<3)
		this->addNewMaid(1);
	//对于所有女仆
	for (auto& maid : *mMaidSet)
	{
		//如果哪个闲着
		if (maid->free())
		{
			//派去巡逻
			maid->receiveInstruction(Instruction(InstructionType::MOVETO, { rand() % mMap->getSize() }));
		}
		else maid->receiveInstruction(Instruction(InstructionType::NUL, std::vector<int>()));
	}
	std::vector<std::shared_ptr<Maid>>deadMaid;
	//每个女仆执行回合操作
	for (auto& maid : *mMaidSet)
	{
		//std::cout << maid.use_count() <<std:: endl; 输出3
		MaidInfoType maidInfo=maid->update(info);
		if(maidInfo== MaidInfoType::ALERT)
			
		/**
		std::cout << "nameless maid"<<std::endl;
		std::cout << "Pos:" << maid->getPos() << std::endl;
		std::cout << "Hp:" << maid->getHp() << std::endl;
		std::cout << "State:" << maidStateOutput[(int)maid->getState()] << std::endl;
		std::cout << "WayPoint:";
		auto wayPoint = maid->getWayPoint();
		for (auto i : wayPoint)std::cout <<i.pos << ",";
		std::cout << std::endl;
		std::cout << "Instruction:" << instructionOutput[(int)maid->getInstructionType()] << std::endl;
		std::cout<<std::endl;
		**/
		//update info
		// Test new log class
		/*
		std::shared_ptr<Log> logger= info->getLogger();
		logger->add(maid->getName());
		//char position[100], hp[100], state[100], instruction[100];v
		std::stringstream pos, hp, state, insruction, wayp;
		pos << "Pos:" << maid->getPos();
		hp << "Hp:" << maid->getHp();
		state << "State:" << maidStateOutput[(int)maid->getState()];
		insruction << "Instruction:" << instructionOutput[(int)maid->getInstructionType()];
		wayp << "WayPoint:";
		auto wayPoint = maid->getWayPoint();
		for (auto i : wayPoint)wayp << i.pos << ",";
		logger->add(pos.str());
		logger->add(hp.str());
		logger->add(state.str());
		logger->add(insruction.str());
		logger->add(wayp.str());
		*/
		if (maid->dead())
		{
			deadMaid.push_back(maid);
			mMap->addBlood(maid->getPos(), 1);
		}
	}
	//删除死亡的女仆
	for (auto& maid : deadMaid)
		this->deleteMaid(maid);
	if (mAlertIsOn)
	{
		if (mAlertTimeLeft > 0)
			mAlertTimeLeft--;
		else turnOffAlert(MaidManagerStateType::NORMAL);
	}
}
void MaidManager::bindMap(std::shared_ptr<Map>map)
{
	mMap = map;
}