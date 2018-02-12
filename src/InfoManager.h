#pragma once
#include<memory>
#include"Maid.h"
#include"Map.h"
#include"FlandreScarlet.h"
class Maid;
class Map;
class FlandreScarlet;
//在女仆，芙兰，女仆管理器，地图之间交换信息
class InfoManager
{
private:
	std::shared_ptr<Map> mMap;
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> mMaid;
	std::shared_ptr<FlandreScarlet> mFlan;
	std::shared_ptr<bool> mAlertIsOn;
public:
	//Game 绑定芙兰
	void bind(std::shared_ptr<FlandreScarlet> flan);
	//Game 绑定女仆集合
	void bind(std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maid);
	//Game 绑定警报
	void bind(std::shared_ptr<bool> alert);
	//Game 绑定地图
	void bind(std::shared_ptr<Map> map);
	//Maid 是否有警报
	bool haveAlert();
	//Maid 是否能看到芙兰
	bool CanSeeFlan(std::shared_ptr<Maid> maid);
	//Maid 返回芙兰
	std::shared_ptr<FlandreScarlet> getFlan();
	//Maid 获取血迹
	int getBloodStain(std::shared_ptr<Maid> maid);
	//Maid 清理血迹(一次清理1)
	void cleanBloodStain(std::shared_ptr<Maid> maid);
	//Maid 移动到
	void moveTo(std::shared_ptr<Maid> maid,int pos);
	//Maid 获取路径(不包括起点，包括终点)
	std::vector<int> getPath(std::shared_ptr<Maid> maid, int targetPos);
	//通用 获取路径(不包括起点，包括终点)
	std::vector<int> getPath(int startPos, int targetPos);
	//Flan 返回所有能看到的女仆
	//std::vector<std::shared_ptr<Maid>> maidsInSight();
};