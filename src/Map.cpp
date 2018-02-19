#include"Map.h"
#include<queue>
#include<stack>
int Vertex::getBlood()
{
	return mBlood;
}
Vertex& Map::getVertex(int id)
{
	return mVertex[id];
}
void Vertex::deleteMaid(std::shared_ptr<Maid> maid)
{
	mMaid.erase(maid);
}
void Vertex::addMaid(std::shared_ptr<Maid> maid)
{
	mMaid.insert(maid);
}
void Vertex::addBlood(int val)
{
	mBlood += val;
}
std::vector<std::shared_ptr<Maid>> Vertex::getMaidPool()
{
	std::vector<std::shared_ptr<Maid>> res;
	for (auto i : mMaid)
		res.push_back(i);
	return res;
}
std::vector<int> Map::getNearByVertexId(int id)
{
	std::vector<int> res;
	const int dr[4] = { -1,1, 0,0 };
	const int dc[4] = { 0,0,-1,1 };
	int nowR = id / mSizeC;
	int nowC = id % mSizeC;
	for (int i = 0; i < 4; ++i)
	{
		int nextR = nowR + dr[i];
		int nextC = nowC + dc[i];
		if (nextR < 0 || nextR >= mSizeR)continue;
		if (nextC < 0 || nextC >= mSizeC)continue;
		res.push_back(nextR*mSizeC+nextC);
	}
	return res;
}
std::vector<int> Map::getWayPoints(int startPos, int targetPos)
{
	std::queue<int>q;
	std::vector<int>dist(mSizeR*mSizeC, -1);
	std::vector<int>pre(mSizeR*mSizeC, 0);
	dist[startPos] = 0;
	q.push(startPos);
	//BFS
	while (!q.empty())
	{
		int now = q.front();
		int nowR = now / mSizeC;
		int nowC = now % mSizeC;
		q.pop();
		const int dr[4] = {-1,1, 0,0};
		const int dc[4] = { 0,0,-1,1 };
		for (int i = 0; i<4;++i)
		{
			int nextR = nowR + dr[i];
			int nextC = nowC + dc[i];
			if (nextR < 0 || nextR >= mSizeR)continue;
			if (nextC < 0 || nextC >= mSizeC)continue;
			int next = nextR * mSizeC + nextC;
			if (!mVertex[next].getEnable())continue;
			if (dist[next] == -1)
			{
				dist[next] = dist[now] + 1;
				pre[next] = now;
				q.push(next);
			}
		}
	}
	std::stack<int>storge;
	int v = targetPos;
	while (v != startPos)
	{
		storge.push(v);
		v = pre[v];
	}
	std::vector<int>res;
	while (!storge.empty())
	{
		res.push_back(storge.top());
		storge.pop();
	}
	return res;
}
Map::Map(int sizeR,int sizeC)
{
	mVertex.resize(sizeR*sizeC);
	mSizeR = sizeR;
	mSizeC = sizeC;
	//mEdge.resize(size);
	//mSize = size;
}
void Map::addBlood(int pos, int val)
{
	this->mVertex[pos].addBlood(val);
}
/*
void Map::addEdge(int from, int to)
{
	mEdge[from].push_back(to);
}
void Map::addUndirectEdge(int u, int v)
{
	mEdge[u].push_back(v);
	mEdge[v].push_back(u);
}*/