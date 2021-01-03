#pragma once
#include "GameObject.h"

enum class NextNode
{
	none,
	left,
	right,
	up,
	down
};

struct Edge
{
	int nodeID;
	NextNode direction;
};

class Node :
	public GameObject
{

	int nodeID;

	Vector2 position;

	std::vector<Edge>* adjacentNodes;

	std::string containedScence;

public:

	Node();
	~Node();

	int getNodeID();
	void setNodeID(int id);

	void setPosition(Vector2 pos);
	Vector2 getPosition();

	void setScence(std::string id);
	std::string getScence(); 

	std::vector<Edge>* getAdjacentList();
};

