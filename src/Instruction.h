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
ָ����       ����       ����
NUL          ��         ��
MOVETO   ��·�����ƶ�  [0,1,2...]·����
PATROL   �ڶ���Ѳ��  [0]�Ƿ�ΪȦѲ�ߣ�[1,2,3...]·����
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
	NUL,  //����ִ��
	FREE, //����
	ALERT,//����
	MEET  //����
};
