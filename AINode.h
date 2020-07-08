#pragma once

#include <afxwin.h>
#include "DisplayObject.h"
#include "SceneObject.h"
#include "Game.h"
#include <vector>
#include "ToolMain.h"

class AINode
{
public:
	AINode();
	~AINode();

	void CreateNode(std::vector<SceneObject> &sceneGraph);

	void SetGameClass(Game* gameClass);
	void SetToolMainClass(ToolMain* toolMainClass);

	int FindNewID(std::vector<SceneObject> sceneGraph);
private:
	Game* m_gameClass;
	ToolMain * m_toolMainClass;
};

