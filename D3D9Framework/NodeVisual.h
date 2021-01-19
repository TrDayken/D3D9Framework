#pragma once
#include "GameObject.h"
class NodeVisual :
	public GameObject
{
	int number;

	Sprite* visual[7];

	std::string sceneID;

public:

	NodeVisual();


	void LoadAnimation();

	void Render(Camera* camera);

	void SetNumber(int value);

	void setScenceID(std::string id);
};

