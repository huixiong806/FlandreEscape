#pragma once
#include<memory>
#include"Maid.h"
#include"Map.h"
#include"FlandreScarlet.h"
class Maid;
class Map;
class FlandreScarlet;
//��Ů�ͣ�ܽ����Ů�͹���������ͼ֮�佻����Ϣ
class InfoManager
{
private:
	std::shared_ptr<Map> mMap;
	std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> mMaid;
	std::shared_ptr<FlandreScarlet> mFlan;
	std::shared_ptr<bool> mAlertIsOn;
public:
	//Game ��ܽ��
	void bind(std::shared_ptr<FlandreScarlet> flan);
	//Game ��Ů�ͼ���
	void bind(std::shared_ptr<std::unordered_set<std::shared_ptr<Maid>>> maid);
	//Game �󶨾���
	void bind(std::shared_ptr<bool> alert);
	//Game �󶨵�ͼ
	void bind(std::shared_ptr<Map> map);
	//Maid �Ƿ��о���
	bool haveAlert();
	//Maid �Ƿ��ܿ���ܽ��
	bool CanSeeFlan(std::shared_ptr<Maid> maid);
	//Maid ����ܽ��
	std::shared_ptr<FlandreScarlet> getFlan();
	//Maid ��ȡѪ��
	int getBloodStain(std::shared_ptr<Maid> maid);
	//Maid ����Ѫ��(һ������1)
	void cleanBloodStain(std::shared_ptr<Maid> maid);
	//Maid �ƶ���
	void moveTo(std::shared_ptr<Maid> maid,int pos);
	//Maid ��ȡ·��(��������㣬�����յ�)
	std::vector<int> getPath(std::shared_ptr<Maid> maid, int targetPos);
	//ͨ�� ��ȡ·��(��������㣬�����յ�)
	std::vector<int> getPath(int startPos, int targetPos);
	//Flan ���������ܿ�����Ů��
	//std::vector<std::shared_ptr<Maid>> maidsInSight();
};