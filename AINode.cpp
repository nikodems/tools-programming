#include "AINode.h"



AINode::AINode()
{

}


AINode::~AINode()
{
}

void AINode::SetGameClass(Game * gC)
{
	m_gameClass = gC;
}

void AINode::SetToolMainClass(ToolMain * toolMainClass)
{
	m_toolMainClass = toolMainClass;
}

void AINode::CreateNode(std::vector<SceneObject> &sceneGraph)
{
	SceneObject newSceneObject;
	int tempID = 99;

	newSceneObject.model_path = "database/data/placeholder.cmo";
	newSceneObject.tex_diffuse_path = "database/data/placeholder.dds";

	DirectX::SimpleMath::Vector3 tempPos = DirectX::SimpleMath::Vector3(14.0f, 3.0f, 8.0f);
	DirectX::SimpleMath::Vector3 tempScale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	std::vector<SceneObject> aiNodeVector;

	newSceneObject.ID = FindNewID(sceneGraph);

	int parentID = newSceneObject.ID;

	newSceneObject.posX = 18.0f;
	newSceneObject.posY = 3.0f;
	newSceneObject.posZ = 8.0f;

	newSceneObject.scaX = 1.0f;
	newSceneObject.scaY = 1.0f;
	newSceneObject.scaZ = 1.0f;


	newSceneObject.path_node_start = true;

	aiNodeVector.push_back(newSceneObject);

	m_gameClass->UpdateDisplayList(newSceneObject);

	m_toolMainClass->UpdateSceneGraph(newSceneObject);

	newSceneObject.ID = FindNewID(sceneGraph);

	newSceneObject.parent_id = parentID;

	newSceneObject.posX = 12.0f;
	newSceneObject.posY = 3.0f;
	newSceneObject.posZ = 0.0f;

	newSceneObject.path_node_start = false;
	newSceneObject.path_node = true;

	aiNodeVector.push_back(newSceneObject);

	m_gameClass->UpdateDisplayList(newSceneObject);

	m_toolMainClass->UpdateSceneGraph(newSceneObject);

	newSceneObject.ID = FindNewID(sceneGraph);
	newSceneObject.parent_id = parentID;

	newSceneObject.posX = 28.0f;
	newSceneObject.posY = 7.0f;
	newSceneObject.posZ = 0.0f;

	newSceneObject.path_node = false;
	newSceneObject.path_node_end = true;

	aiNodeVector.push_back(newSceneObject);

	m_gameClass->UpdateDisplayList(newSceneObject);

	m_toolMainClass->UpdateSceneGraph(newSceneObject);
}

int AINode::FindNewID(std::vector<SceneObject> sceneGraph)
{
	int tempID = 0;
	//Loop through scene graph looking for the highest ID value
	for (auto &i : sceneGraph)
	{
		if (i.ID > tempID)
		{
			tempID = i.ID;
		}
	}

	return (tempID + 1);
}


