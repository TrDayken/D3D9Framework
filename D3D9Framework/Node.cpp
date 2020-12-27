#include "Node.h"

Node::Node(int id)
{
	this->nodeID = id;

	adjacentNodes = new std::vector<Edge>();
}

Node::~Node()
{
	adjacentNodes->clear();

	delete adjacentNodes;
}

int Node::getNodeID()
{
	return this->nodeID;
}

void Node::setPosition(Vector2 pos)
{
	this->position = pos;
}

Vector2 Node::getPosition()
{
	return this->position;
}

void Node::setScence(std::string id)
{
	this->containedScence = id; 
}

std::string Node::getScence()
{
	return this->containedScence;
}

std::vector<Edge>* Node::getAdjacentList()
{
	return this->adjacentNodes;
}
