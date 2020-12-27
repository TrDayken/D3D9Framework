#pragma once

#include "GameObject.h"
#include "Node.h"



class NodeMap :public GameObject
{
private:
	std::unordered_map<int, Node*> nodes;
public:
	NodeMap();
	~NodeMap();

	void InsertNode(Node* node);

	Node* getNode(int id); 

};

