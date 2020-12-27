#include "NodeMap.h"

NodeMap::NodeMap()
{
}

NodeMap::~NodeMap()
{

}

void NodeMap::InsertNode(Node* node)
{
	this->nodes[node->getNodeID()] = node; 
}

Node* NodeMap::getNode(int id)
{
	return nodes[id];
}
