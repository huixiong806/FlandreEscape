#pragma once
#include<memory>
#include"Constants.h"
#include"Log.hpp"
#include"Maid.h"
#include"Map.h"
#include"FlandreScarlet.h"
class Log;
class Maid;
class Map;
class FlandreScarlet;
//在女仆，芙兰，女仆管理器，地图之间交换信息
class InfoManager
{
private:
	static std::shared_ptr<Map> mMap;
	static std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> mMaid;
	static std::shared_ptr<FlandreScarlet> mFlan;
	static std::shared_ptr<bool> mAlertIsOn;
	static std::shared_ptr<Log> mLogger;
public:
	//Game 绑定芙兰
	static void bind(std::shared_ptr<FlandreScarlet> flan);
	//Game 绑定女仆集合
	static void bind(std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maid);
	//Game 绑定警报
	static void bind(std::shared_ptr<bool> alert);
	//Game 绑定地图
	static void bind(std::shared_ptr<Map> map);
	//Game 绑定Logger
	static void bind(std::shared_ptr<Log> logger);
	//Maid 是否有警报
	static bool haveAlert();
	//Maid 是否能看到芙兰
	static bool CanSeeFlan(std::shared_ptr<Maid> maid);
	//Maid 返回芙兰
	static std::shared_ptr<FlandreScarlet> getFlan();
	//Maid 获取血迹
	static int getBloodStain(std::shared_ptr<Maid> maid);
	//Maid 清理血迹(一次清理1)
	static void cleanBloodStain(std::shared_ptr<Maid> maid);
	//Maid 移动到
	static void moveTo(std::shared_ptr<Maid> maid,int pos);
	//Maid 获取路径(不包括起点，包括终点)
	static std::vector<int> getPath(std::shared_ptr<Maid> maid, int targetPos);
	//通用 获取路径(不包括起点，包括终点)
	static std::vector<int> getPath(int startPos, int targetPos);
	//通用 获取logger
	static std::shared_ptr<Log> getLogger();
	//通用 想要移动到某个格子，应该往哪个方向走？返回一个单位向量
	static Vec2d getTheDirectionTo(Vec2d startPos, int tarPos);
	//通用 根据实数坐标确定位置
	static int getPosByCoord(Vec2d coord);
	//通用 返回该格子中间的坐标
	static Vec2d getCoordByPos(int pos);
	//通用 将位置转换为Vec2i
	static Vec2i getPos(int pos); 
	//通用，判断一个坐标是否在格子正中间,误差不超过eps(eps为误差范围除以格子大小)
	static bool inMid(Vec2d coord, int pos, double eps);
	//MaidManager 获取指向地图的指针
	static std::shared_ptr<Map> getMap();
	//Flan 返回所有能看到的女仆
	//std::vector<std::shared_ptr<Maid>> maidsInSight();
};