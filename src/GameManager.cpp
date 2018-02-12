#include"GameManager.h"
#include<iostream>
#include<sstream>
GameManager::GameManager()
{

}
void GameManager::loadGame(std::string fileName)
{
	mInfoManager = std::make_shared<InfoManager>();
	mMap = std::make_shared<Map>(5,5);
	mFlan = std::make_shared<FlandreScarlet>();
	mMaidManager = std::make_shared<MaidManager>(this->mMap);
	mInfoManager->bind(mMaidManager->getMaidSetPtr());
	mInfoManager->bind(mMaidManager->getAlertPtr());
	mInfoManager->bind(this->mFlan);
	mInfoManager->bind(this->mMap);
}
void GameManager::update()
{
	//maid manager执行回合操作
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maidSet = mMaidManager->getMaidSetPtr();
	mMaidManager->update();
	std::vector<std::shared_ptr<Maid>>deadMaid;
	std::cout << "MaidCount:" << maidSet->size() << std::endl;
	//每个女仆执行回合操作
	for (auto& maid : *maidSet)
	{
		//std::cout << maid.use_count() <<std:: endl; 输出3
		maid->update(mInfoManager);
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
		/*
		info.clear();
		info.push_back("nameless maid");
		char position[100], hp[100], state[100], instruction[100];
		sprintf_s(position, "Pos:%d", maid->getPos());
		sprintf_s(hp, "Hp:%d", maid->getHp());
		sprintf_s(state, "State:%s", maidStateOutput[(int)maid->getState()].c_str());
		sprintf_s(instruction, "Instruction:%s", instructionOutput[(int)maid->getInstructionType()].c_str());
		info.push_back(position);
		info.push_back(hp);
		info.push_back(state);
		info.push_back(instruction);
		*/
		// Test new log class
		logger.add("nameless maid");
		//char position[100], hp[100], state[100], instruction[100];v
		std::stringstream pos,hp,state,insruction,wayp;
		pos << "Pos:"<< maid->getPos();
		hp << "Hp:" << maid->getHp();
		state << "State:" << maidStateOutput[(int)maid->getState()];
		insruction << "Instruction:" << instructionOutput[(int)maid->getInstructionType()] ;
		wayp << "WayPoint:";
		auto wayPoint = maid->getWayPoint();
		for (auto i : wayPoint)wayp << i.pos << ",";
		logger.add(pos.str());
		logger.add(hp.str());
		logger.add(state.str());
		logger.add(insruction.str());
		logger.add(wayp.str());
		if (maid->dead())
		{
			deadMaid.push_back(maid);
			mMap->addBlood(maid->getPos(),1);
		}
	}
	//删除死亡的女仆
	for (auto& maid : deadMaid)
		mMaidManager->deleteMaid(maid);
}
Log& GameManager::getLog()
{
	return logger;
}

Map & GameManager::getMap()
{
	return * mMap;
}

std::unordered_set<std::shared_ptr<Maid>> GameManager::getMaids()
{
	return mMaidManager->getMaids();
}
