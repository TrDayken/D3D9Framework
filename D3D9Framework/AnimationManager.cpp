#include "AnimationManager.h"

AnimationManager * AnimationManager::_instance = NULL;

void AnimationManager::AddAnimation(std::string id, LPANIMATION animation)
{
	animationDatabase[id] = animation;
}

LPANIMATION AnimationManager::Get(std::string id)
{
	LPANIMATION ani = animationDatabase[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d \n", id);
	return ani;
}

void AnimationManager::Clear()
{
	for (auto x : animationDatabase)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animationDatabase.clear();
}

void AnimationManager::AddAnimationUsingXML(const char* FilePath)
{
	TiXmlDocument XMLdoc(FilePath);

	if (XMLdoc.LoadFile())
	{
		TiXmlElement* root = XMLdoc.RootElement()->FirstChildElement();
		TiXmlElement* XMLanimation = NULL;
		TiXmlElement* XMLanimationsprites = NULL;

		LPANIMATION ani;

		for (XMLanimation = root->FirstChildElement(); XMLanimation != NULL; XMLanimation = XMLanimation->NextSiblingElement())
		{
			int aniframetime;
			
			std::string aniID = XMLanimation->Attribute("aniId");
			XMLanimation->QueryIntAttribute("frameTime", &aniframetime);
			ani = new Animation(aniframetime);

			for (XMLanimationsprites = XMLanimation->FirstChildElement(); XMLanimationsprites != NULL; XMLanimationsprites = XMLanimationsprites->NextSiblingElement())
			{
				int frametime;
				std::string spriteId = XMLanimationsprites->Attribute("id");
				XMLanimationsprites->QueryIntAttribute("frameTime", &frametime);

				ani->AddFrame(spriteId, frametime);
			}
			
			AddAnimation(aniID, ani);

			DebugOut(L"[INFO] loaded ok %d \n", aniID);
		}
	}
	else
	{
		DebugOut(L"[] could not load file %d \n", FilePath);
	}
}

AnimationManager* AnimationManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new AnimationManager();
	return _instance;
}
