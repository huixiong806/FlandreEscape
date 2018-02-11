#include"Maid.h"
Maid::Maid(int pos)
{
	this->setPos(pos);
	this->setHp(this->getHpLimit());
	this->setName("nameless maid");
	this->mState = MaidState::STOP;
	this->mCurInstruction = Instruction(InstructionType::NUL,std::vector<int>());
}
Maid::Maid()
{
	this->setPos(0);
	this->setHp(this->getHpLimit());
	this->setName("nameless maid");
	this->mState = MaidState::STOP;
	this->mCurInstruction = Instruction(InstructionType::NUL, std::vector<int>());
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
MaidInfoType Maid::update(std::shared_ptr<InfoManager> info)
{
	//�ظ�HP
	if(this->getHp()<this->getHpLimit())
		this->addHp(this->getHpRecoverPerTick());
	if (this->dead())return MaidInfoType::MEET;
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
		std::vector<int> wayPoint = info->getPath(getSelf(), firstPoint);
		//�ӵ�һ��·���㵽�յ�
		for (int i = 0;i < mCurInstruction.parameters.size() - 1; ++i)
		{
			//������������֮���·��
			int curPoint = mCurInstruction.parameters[i];
			int nextPoint = mCurInstruction.parameters[i + 1];
			std::vector<int> newWayPoint = info->getPath(curPoint, nextPoint);
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
		std::vector<int> wayPoint = info->getPath(getSelf(), startPoint);
		mWayPoint.clear();
		for (auto item : wayPoint)
			mWayPoint.push_back(WayPoint(WayPointType::ONETIME, item));
		wayPoint.clear();
		for (int i = 1; i < mCurInstruction.parameters.size()-1; ++i)
		{
			//������������֮���·��
			int curPoint = mCurInstruction.parameters[i];
			int nextPoint = mCurInstruction.parameters[i+1];
			std::vector<int> newWayPoint= info->getPath(curPoint, nextPoint);
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
		}
		if (loop)
		{
			//�������һ���㵽����·��
			int curPoint = *(mCurInstruction.parameters.end()-1);
			int nextPoint = mCurInstruction.parameters[1];
			std::vector<int> newWayPoint = info->getPath(curPoint, nextPoint);
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
		//����Ѫ�������쾯��
		if (info->getBloodStain(getSelf()))
			return MaidInfoType::ALERT;
		//����ܽ���������о����Ļ���״̬ת��Ϊ����
		if (info->CanSeeFlan(getSelf()) && info->haveAlert())
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
				WayPoint target = mWayPoint.front();
				mWayPoint.pop_front();
				if (target.type == WayPointType::LOOP)
					mWayPoint.push_back(target);
				info->moveTo(getSelf(), target.pos);
				return MaidInfoType::NUL;
			}
		}
		break;
	case MaidState::FIGHT:
		//����ܽ�����򹥻�������ָ�ԭ��״̬
		if (info->CanSeeFlan(getSelf()))
		{
			this->attack(info->getFlan().get());
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
