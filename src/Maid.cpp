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
//每tick的操作
MaidInfoType Maid::update(std::shared_ptr<InfoManager> info)
{
	//回复HP
	if(this->getHp()<this->getHpLimit())
		this->addHp(this->getHpRecoverPerTick());
	if (this->dead())return MaidInfoType::MEET;
	//处理maid manager发来的指令
	switch (mCurInstruction.type)
	{
	case InstructionType::NUL:
		break;
	//移动
	case InstructionType::MOVETO:
	{
		mState = MaidState::MOVE;
		int firstPoint = mCurInstruction.parameters[0];
		//从自己所在位置到第一个路径点
		std::vector<int> wayPoint = info->getPath(getSelf(), firstPoint);
		//从第一个路径点到终点
		for (int i = 0;i < mCurInstruction.parameters.size() - 1; ++i)
		{
			//加入连续两点之间的路径
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
	//巡逻
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
			//加入连续两点之间的路径
			int curPoint = mCurInstruction.parameters[i];
			int nextPoint = mCurInstruction.parameters[i+1];
			std::vector<int> newWayPoint= info->getPath(curPoint, nextPoint);
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
		}
		if (loop)
		{
			//加入最后一个点到起点的路径
			int curPoint = *(mCurInstruction.parameters.end()-1);
			int nextPoint = mCurInstruction.parameters[1];
			std::vector<int> newWayPoint = info->getPath(curPoint, nextPoint);
			//最后一个点不会重复加进去，因为之前加进去的类型是ONETIME,单次使用即被抛弃。
			wayPoint.insert(wayPoint.end(), newWayPoint.begin(), newWayPoint.end());
			for (auto item : wayPoint)
				mWayPoint.push_back(WayPoint(WayPointType::LOOP, item));
		}
		else
		{
			//将路径倒着添加一遍，构成循环
			if (wayPoint.size() > 1)
			{
				int i = wayPoint.size() - 2;
				for (i; i >= 0; --i)
					wayPoint.push_back(wayPoint[i]);
			}
			//加入起点
			wayPoint.push_back(startPoint);
			for (auto item : wayPoint)
				mWayPoint.push_back(WayPoint(WayPointType::LOOP, item));
		}
	}
		break;
	default:
		break;
	}
	//tick更新
	switch (mState)
	{
	case MaidState::STOP:
		return MaidInfoType::FREE;
		break;
	case MaidState::MOVE:
	case MaidState::PATROL:
		//看到血迹，拉响警报
		if (info->getBloodStain(getSelf()))
			return MaidInfoType::ALERT;
		//看到芙兰，并且有警报的话，状态转换为攻击
		if (info->CanSeeFlan(getSelf()) && info->haveAlert())
		{
			mPreState = mState;
			mState = MaidState::FIGHT;
			return MaidInfoType::MEET;
		}
		else//否则正常移动
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
		//看到芙兰，则攻击，否则恢复原先状态
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
