#pragma once
#include<vector>
#include<unordered_set>
#include<memory>
#include"Vec2.hpp"
#include"Maid.h"
class Maid;
class Vertex
{
private:
	bool enabled;
	int mBlood;
	std::unordered_set<std::shared_ptr<Maid>> mMaid;
public:
	Vertex()
	{
		enabled = true;
		mBlood = 0;
	}
	int getBlood();
	void addBlood(int val);
	void deleteMaid(std::shared_ptr<Maid> maid);
	void addMaid(std::shared_ptr<Maid> maid);
};
class Map
{
private:
	//std::vector<std::vector<int>>mEdge;
	std::vector<Vertex>mVertex;
	int mSizeR,mSizeC;
public:
	Map(int sizeR,int sizeC);
	//void addEdge(int from, int to);
	//void addUndirectEdge(int u, int v);
	Vertex& getVertex(int id);
	int getSizeR() { return mSizeR; }
	int getSizeC() { return mSizeC; }
	int getSize() { return mSizeR * mSizeC; }
	void addBlood(int pos,int val);
	Vec2i getPos(int pos) { return Vec2i(pos / mSizeC, pos%mSizeC); }
	int getPos(int r,int c) { return r*mSizeC+c; }
	std::vector<int>getNearByVertexId(int id);
	std::vector<int>getWayPoints(int startPos,int targetPos);
};