#include"MaidManager.h"
MaidManager::MaidManager()
{ 
	mAlertIsOn = std::make_shared<bool>(false); 
	mMaidSet = std::make_shared<std::unordered_set<std::shared_ptr<Maid>>>();
	
}
void MaidManager::addNewMaid(int pos)
{
	std::shared_ptr<Maid> maid = std::make_shared<Maid>(pos);
	mMaidSet->insert(maid);
	InfoManager::getMap()->getVertex(pos).addMaid(maid);
}
void MaidManager::deleteMaid(std::shared_ptr<Maid> maid)
{
	InfoManager::getMap()->getVertex(maid->getPos()).deleteMaid(maid);
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
std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> MaidManager::getMaidSet()
{
	return mMaidSet;
}
std::shared_ptr<bool> MaidManager::getAlertPtr()
{
	return mAlertIsOn;
}
void MaidManager::update()
{
	//����Ϊ���Դ���
	//���ֳ�����3��Ů��
	if(mMaidSet->size()<3)
		this->addNewMaid(1);
	//��������Ů��
	for (auto& maid : *mMaidSet)
	{
		//����ĸ�����
		if (maid->free())
		{
			//��ȥѲ��
			int pos;
			do
			{
				pos=rand() % InfoManager::getMap()->getSize();
			} while (!InfoManager::vertexIsEnable(pos));
			maid->receiveInstruction(Instruction(InstructionType::MOVETO, { pos }));
		}
		else maid->receiveInstruction(Instruction(InstructionType::NUL, std::vector<int>()));
	}
	std::vector<std::shared_ptr<Maid>>deadMaid;
	//ÿ��Ů��ִ�лغϲ���
	for (auto& maid : *mMaidSet)
	{
		//std::cout << maid.use_count() <<std:: endl; ���3
		MaidInfoType maidInfo=maid->update();
		if (maidInfo == MaidInfoType::ALERT)
			this->turnOnAlert();
		if (Console::getFlag("maidStatus"))
		{
			Console::add(maid->getName());
		
			std::stringstream pos, hp, state, insruction, wayp;
			pos << "Pos:" << maid->getPos();
			hp << "Hp:" << maid->getHp();
			state << "State:" << maidStateOutput[(int)maid->getState()];
			insruction << "Instruction:" << instructionOutput[(int)maid->getInstructionType()];
			wayp << "WayPoint:";
			auto wayPoint = maid->getWayPoint();
			for (auto i : wayPoint)wayp << i.pos << ",";
			Console::add(pos.str());
			Console::add(hp.str());
			Console::add(state.str());
			Console::add(insruction.str());
			Console::add(wayp.str());
		}
		if (maid->dead())
		{
			deadMaid.push_back(maid);
			InfoManager::getMap()->addBlood(maid->getPos(), 100);
		}
	}
	//ɾ�������Ů��
	for (auto& maid : deadMaid)
		this->deleteMaid(maid);
	if (mAlertIsOn)
	{
		if (mAlertTimeLeft > 0)
			mAlertTimeLeft--;
		else turnOffAlert(MaidManagerStateType::NORMAL);
	}
}