#pragma once
#include<vector>
#include<unordered_set>
#include<memory>
#include"Maid.h"
class Maid;
class Vertex
{
private:
	int mBlood;
	std::unordered_set<std::shared_ptr<Maid>> mMaid;
public:
	Vertex()
	{
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
	std::vector<std::vector<int>>mEdge;
	std::vector<Vertex>mVertex;
	int mSize;
public:
	Map(int size);
	void addEdge(int from, int to);
	void addUndirectEdge(int u, int v);
	Vertex& getVertex(int id);
	int getSize() { return mSize; }
	void addBlood(int pos,int val);
	std::vector<int>getNearByVertexId(int id);
	std::vector<int>getWayPoints(int startPos,int targetPos);
};