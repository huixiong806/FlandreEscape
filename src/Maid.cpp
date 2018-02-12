#include"Maid.h"
#include<sstream>
const std::string maidName[12] = { "Sakuya","Daiyousei","Lily","Marisa","Reimu","Sanae","Satori","Koishi","Remilia","Patchouli","Koakuma","Cirno"};
Maid::Maid(int pos)
{
	this->setPos(pos);
	this->setCoord(InfoManager::getCoordByPos(pos));
	this->setHp(this->getHpLimit());
	std::stringstream ss;
	this->setName(maidName[rand()%12]);
	this->mState = MaidState::STOP;
	this->mCurInstruction = Instruction(InstructionType::NUL,std::vector<int>());
	mSpeed = 2.0;
}
Maid::Maid()
{
	this->setPos(0);
	this->setCoord(InfoManager::getCoordByPos(0));
	this->setHp(this->getHpLimit());
	std::stringstream ss;
	this->setName(maidName[rand() % 12]);
	this->mState = MaidState::STOP;
	this->mCurInstruction = Instruction(InstructionType::NUL, std::vector<int>());
	mSpeed = 2.0;
}
Maid::~Maid()
{

}
void Maid::receiveInstruction(const Instruction& instruction)
{
	mCurInstruction = instruction;
}
const int Maid::getHpLimit()
{
	return mHpLimit;
}
const int Maid::getDamage()
{
	return mDamage;
}
const int Maid::getHpRecoverPerTick()
{
	return mHpRecoverPerTick;
}
std::shared_ptr<Maid> Maid::getSelf()
{
	return shared_from_this();
}
//ÿtick�Ĳ���
MaidInfoType Maid::update()
{
	//�ظ�HP
	if(this->getHp()+this->getHpRecoverPerTick ()<=this->getHpLimit())
		this->addHp(this->getHpRecoverPerTick());
	if (this->dead())return MaidInfoType::NUL;
	//����maid manager������ָ��
	switch (mCurInstruction.type)
	{
	case InstructionType::NUL:
		break;
	//�ƶ�
	case InstructionType::MOVETO:
	{
		mState = MaidState::MOVE;
		int firstPoint = mCurInstruction.parameters[0];
		//���Լ�����λ�õ���һ��·����
		std::vector<int> wayPoint = InfoManager::getPath(getSelf(), firstPoint);
		//�ӵ�һ��·���㵽�յ�
		for (int i = 0;i < mCurInstruction.parameters.size() - 1; ++i)
		{
			//������������֮���·��
			int curPoint = mCurInstruction.parameters[i];
			int nextPoint = mCurInstruction.parameters[i + 1];
			std::vector<int> newWayPoint = InfoManager::getPath(curPoint, nextPoint);
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
		}
		mWayPoint.clear();
		for (auto item : wayPoint)
			mWayPoint.push_back(WayPoint(WayPointType::ONETIME,item));
	}
		break;
	//Ѳ��
	case InstructionType::PATROL:
	{
		mState = MaidState::PATROL;
		bool loop = mCurInstruction.parameters[0];
		int startPoint = mCurInstruction.parameters[1];
		std::vector<int> wayPoint = InfoManager::getPath(getSelf(), startPoint);
		mWayPoint.clear();
		for (auto item : wayPoint)
			mWayPoint.push_back(WayPoint(WayPointType::ONETIME, item));
		wayPoint.clear();
		for (int i = 1; i < mCurInstruction.parameters.size()-1; ++i)
		{
			//������������֮���·��
			int curPoint = mCurInstruction.parameters[i];
			int nextPoint = mCurInstruction.parameters[i+1];
			std::vector<int> newWayPoint= InfoManager::getPath(curPoint, nextPoint);
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
		}
		if (loop)
		{
			//�������һ���㵽����·��
			int curPoint = *(mCurInstruction.parameters.end()-1);
			int nextPoint = mCurInstruction.parameters[1];
			std::vector<int> newWayPoint = InfoManager::getPath(curPoint, nextPoint);
			//���һ���㲻���ظ��ӽ�ȥ����Ϊ֮ǰ�ӽ�ȥ��������ONETIME,����ʹ�ü���������
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
			for (auto item : wayPoint)
				mWayPoint.push_back(WayPoint(WayPointType::LOOP, item));
		}
		else
		{
			//��·���������һ�飬����ѭ��
			if (wayPoint.size() > 1)
			{
				int i = wayPoint.size() - 2;
				for (i; i >= 0; --i)
					wayPoint.push_back(wayPoint[i]);
			}
			//�������
			wayPoint.push_back(startPoint);
			for (auto item : wayPoint)
				mWayPoint.push_back(WayPoint(WayPointType::LOOP, item));
		}
	}
		break;
	default:
		break;
	}
	//tick����
	switch (mState)
	{
	case MaidState::STOP:
		return MaidInfoType::FREE;
		break;
	case MaidState::MOVE:
	case MaidState::PATROL:
	{
		//����Ѫ�������쾯��
		if (InfoManager::getBloodStain(getSelf()))
		{
			InfoManager::cleanBloodStain(getSelf());
			return MaidInfoType::ALERT;
		}
		//����ܽ���������о����Ļ���״̬ת��Ϊ����
		if (InfoManager::CanSeeFlan(getSelf()) && InfoManager::haveAlert())
		{
			mPreState = mState;
			mState = MaidState::FIGHT;
			return MaidInfoType::MEET;
		}
		else//���������ƶ�
		{
			if (mWayPoint.empty())
			{
				mState = MaidState::STOP;
				return MaidInfoType::FREE;
			}
			else
			{
				//�ƶ�
				WayPoint target = mWayPoint.front();
				this->walk(InfoManager::getTheDirectionTo(mCoord, target.pos));
				//����Ŀ��·����
				if (InfoManager::getPosByCoord(mCoord) == target.pos&&InfoManager::inMid(mCoord, target.pos,0.3))
				{
					mWayPoint.pop_front();
					//ѭ��·�������¼����β
					if (target.type == WayPointType::LOOP)
						mWayPoint.push_back(target);
					InfoManager::moveTo(getSelf(), target.pos);
				}
				return MaidInfoType::NUL;
			}
		}
	}
		break;
	case MaidState::FIGHT:
		//����ܽ�����򹥻�������ָ�ԭ��״̬
		if (InfoManager::CanSeeFlan(getSelf()))
		{
			this->attack(InfoManager::getFlan().get());
			return MaidInfoType::MEET;
		}
		else
		{
			mState = mPreState;
			return MaidInfoType::NUL;
		}
		break;
	default:
		break;
	}
	return MaidInfoType::NUL;
}