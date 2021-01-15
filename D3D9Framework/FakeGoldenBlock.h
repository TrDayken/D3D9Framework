#pragma once
#include "QuestionBlock.h"
class FakeGoldenBlock :
	public QuestionBlock
{

public : 
	FakeGoldenBlock();

	void LoadAnimation() override;
};

