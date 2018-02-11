#pragma once
#include<vector>
#include<string>
enum class InstructionType :int
{
	NUL,
	MOVETO,
	PATROL,
};
const std::string instructionOutput[3] = {"Null","MoveTo","Partrol"};
/*
指令名       作用       参数
NUL          无         无
MOVETO   按路径点移动  [0,1,2...]路径点
PATROL   在多点间巡逻  [0]是否为圈巡逻，[1,2,3...]路径点
*/
struct Instruction
{
	InstructionType type;
	std::vector<int>parameters;
	Instruction() {}
	Instruction(InstructionType type_, std::vector<int>parameters_):
		type(type_),
		parameters(parameters_)
	{}
};
enum class MaidInfoType :int
{
	NUL,  //正常执行
	FREE, //空闲
	ALERT,//警报
	MEET  //遭遇
};
