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
std::vector<int> Map::getNearByVertexId(int id)
{
	std::vector<int> res;
	for (int i = 0; i < mEdge[id].size();++i)
		res.push_back(mEdge[id][i]);
	return res;
}
std::vector<int> Map::getWayPoints(int startPos, int targetPos)
{
	std::queue<int>q;
	std::vector<int>dist(mSize, -1);
	std::vector<int>pre(mSize, 0);
	dist[startPos] = 0;
	q.push(startPos);
	//BFSѰ·
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < mEdge[now].size();++i)
		{
			int next = mEdge[now][i];
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
Map::Map(int size)
{
	mVertex.resize(size);
	mEdge.resize(size);
	mSize = size;
}
void Map::addBlood(int pos, int val)
{
	this->mVertex[pos].addBlood(val);
}
void Map::addEdge(int from, int to)
{
	mEdge[from].push_back(to);
}
void Map::addUndirectEdge(int u, int v)
{
	mEdge[u].push_back(v);
	mEdge[v].push_back(u);
}