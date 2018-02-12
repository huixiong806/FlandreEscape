#pragma once
#include<vector>
#include<deque>
#include<memory>
#include"InfoManager.h"
#include"Object.h"
#include"Instruction.h"
const std::string maidStateOutput[4] = { "Stop", "Partrol", "Move", "Fight" };
//·������
enum class WayPointType:bool
{
	ONETIME,
	LOOP
};
struct WayPoint
{
	WayPointType type;
	int pos;
	WayPoint(WayPointType type_, int pos_) :pos(pos_), type(type_) {};
};
//Ů�͵�״̬
enum class MaidState:int
{
	STOP, 
	PATROL,
	MOVE,
	FIGHT
};
class InfoManager;
//Ů��
class Maid :public std::enable_shared_from_this<Maid>,public Object
{
private:
	static const int mHpLimit = 10;         //Ѫ������
	static const int mDamage = 5;           //ÿ�ι�����ɵ��˺�
	static const int mHpRecoverPerTick = 0; //ÿtickѪ���ظ�
	Instruction mCurInstruction;  //��ǰָ��
	MaidState mState,mPreState;   //��ǰ״̬,��ǰ״̬(ս��ʱ��ʱ��¼)
	std::deque<WayPoint> mWayPoint;    //·����
	const int getHpLimit();
	const int getDamage();
	const int getHpRecoverPerTick();
public:
	Maid(int pos);
	Maid();
	~Maid();
	bool free() { return mState == MaidState::STOP; }
	MaidState getState() { return mState; }
	std::shared_ptr<Maid> getSelf();
	void receiveInstruction(const Instruction& instruction);
	MaidInfoType update(std::shared_ptr<InfoManager> info);  //ÿtick�Ĳ���
	InstructionType getInstructionType() { return this->mCurInstruction.type; }
	std::deque<WayPoint>& getWayPoint() { return mWayPoint; }
};