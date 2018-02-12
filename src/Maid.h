#pragma once
#include<vector>
#include<deque>
#include<memory>
#include"InfoManager.h"
#include"Object.h"
#include"Instruction.h"
const std::string maidStateOutput[4] = { "Stop", "Partrol", "Move", "Fight" };
//路径点标记
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
//女仆的状态
enum class MaidState:int
{
	STOP, 
	PATROL,
	MOVE,
	FIGHT
};
class InfoManager;
//女仆
class Maid :public std::enable_shared_from_this<Maid>,public Object
{
private:
	static const int mHpLimit = 10;         //血量上限
	static const int mDamage = 5;           //每次攻击造成的伤害
	static const int mHpRecoverPerTick = 0; //每tick血量回复
	Instruction mCurInstruction;  //当前指令
	MaidState mState,mPreState;   //当前状态,先前状态(战斗时临时纪录)
	std::deque<WayPoint> mWayPoint;    //路径点
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
	MaidInfoType update(std::shared_ptr<InfoManager> info);  //每tick的操作
	InstructionType getInstructionType() { return this->mCurInstruction.type; }
	std::deque<WayPoint>& getWayPoint() { return mWayPoint; }
};