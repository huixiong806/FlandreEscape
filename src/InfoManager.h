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
//��Ů�ͣ�ܽ����Ů�͹���������ͼ֮�佻����Ϣ
class InfoManager
{
private:
	static std::shared_ptr<Map> mMap;
	static std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> mMaid;
	static std::shared_ptr<FlandreScarlet> mFlan;
	static std::shared_ptr<bool> mAlertIsOn;
	static std::shared_ptr<Log> mLogger;
public:
	//Game ��ܽ��
	static void bind(std::shared_ptr<FlandreScarlet> flan);
	//Game ��Ů�ͼ���
	static void bind(std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maid);
	//Game �󶨾���
	static void bind(std::shared_ptr<bool> alert);
	//Game �󶨵�ͼ
	static void bind(std::shared_ptr<Map> map);
	//Game ��Logger
	static void bind(std::shared_ptr<Log> logger);
	//Maid �Ƿ��о���
	static bool haveAlert();
	//Maid �Ƿ��ܿ���ܽ��
	static bool CanSeeFlan(std::shared_ptr<Maid> maid);
	//Maid ����ܽ��
	static std::shared_ptr<FlandreScarlet> getFlan();
	//Maid ��ȡѪ��
	static int getBloodStain(std::shared_ptr<Maid> maid);
	//Maid ����Ѫ��(һ������1)
	static void cleanBloodStain(std::shared_ptr<Maid> maid);
	//Maid �ƶ���
	static void moveTo(std::shared_ptr<Maid> maid,int pos);
	//Maid ��ȡ·��(��������㣬�����յ�)
	static std::vector<int> getPath(std::shared_ptr<Maid> maid, int targetPos);
	//ͨ�� ��ȡ·��(��������㣬�����յ�)
	static std::vector<int> getPath(int startPos, int targetPos);
	//ͨ�� ��ȡlogger
	static std::shared_ptr<Log> getLogger();
	//ͨ�� ��Ҫ�ƶ���ĳ�����ӣ�Ӧ�����ĸ������ߣ�����һ����λ����
	static Vec2d getTheDirectionTo(Vec2d startPos, int tarPos);
	//ͨ�� ����ʵ������ȷ��λ��
	static int getPosByCoord(Vec2d coord);
	//ͨ�� ���ظø����м������
	static Vec2d getCoordByPos(int pos);
	//ͨ�� ��λ��ת��ΪVec2i
	static Vec2i getPos(int pos); 
	//ͨ�ã��ж�һ�������Ƿ��ڸ������м�,������eps(epsΪ��Χ���Ը��Ӵ�С)
	static bool inMid(Vec2d coord, int pos, double eps);
	//MaidManager ��ȡָ���ͼ��ָ��
	static std::shared_ptr<Map> getMap();
	//Flan ���������ܿ�����Ů��
	//std::vector<std::shared_ptr<Maid>> maidsInSight();
};