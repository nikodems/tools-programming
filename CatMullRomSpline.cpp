#include "CatMullRomSpline.h"

CatMullRomSpline::CatMullRomSpline()
{
}

CatMullRomSpline::~CatMullRomSpline()
{
}

std::vector<std::vector<SceneObject>> CatMullRomSpline::FindAIObjects(std::vector<SceneObject> sceneGraph)
{
	std::vector<std::vector<SceneObject>> listOfPaths;

	//Loop through scene graph searching for objects with path_node_start
	for (auto &i : sceneGraph)
	{
		if (i.path_node_start)
		{
			std::vector<SceneObject> path;

			path.push_back(i);

			//Loop again searching for objects with path_node and path_node_end as well as parent ID matching path_node_start
			for (auto &i : sceneGraph)
			{
				if (i.path_node || i.path_node_end)
				{
					if (i.parent_id == path[0].ID)
					{
						path.push_back(i);
					}
				}
			}

			listOfPaths.push_back(path);
		}
	}

	return listOfPaths;
}

std::vector<DirectX::SimpleMath::Vector3> CatMullRomSpline::CalcPoints(std::vector<SceneObject> pathVector)
{
	std::vector<DirectX::SimpleMath::Vector3> splinePointVector;

	if (pathVector.size() > 0)
	{
		//Shape of curve
		float alpha = 0.5f;
		float tension = 0.0f;
		//Amount to add each time a new point is created. Higher = more points = smoother curve
		float tensionAdd = 0.01f;

		DirectX::SimpleMath::Vector3 desiredPoint;

		for (int i = 0; i < pathVector.size() - 1; i++)
		{
			DirectX::SimpleMath::Vector3 p0;
			DirectX::SimpleMath::Vector3 p1;
			DirectX::SimpleMath::Vector3 p2;
			DirectX::SimpleMath::Vector3 p3;
			//Create the points
			//Create imaginary points where necessary as two point are required on each side of the desired point at all times
			if (i == 0)
			{
				p0 = DirectX::SimpleMath::Vector3(pathVector[0].posX, pathVector[0].posY, pathVector[0].posZ) - DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
				p1 = DirectX::SimpleMath::Vector3(pathVector[i].posX, pathVector[i].posY, pathVector[i].posZ);
				p2 = DirectX::SimpleMath::Vector3(pathVector[i + 1].posX, pathVector[i + 1].posY, pathVector[i + 1].posZ);
				p3 = DirectX::SimpleMath::Vector3(pathVector[i + 2].posX, pathVector[i + 2].posY, pathVector[i + 2].posZ);
			}
			else if (i > 0 && i < pathVector.size() - 1 - 1)
			{
				p0 = DirectX::SimpleMath::Vector3(pathVector[i - 1].posX, pathVector[i - 1].posY, pathVector[i - 1].posZ);
				p1 = DirectX::SimpleMath::Vector3(pathVector[i].posX, pathVector[i].posY, pathVector[i].posZ);
				p2 = DirectX::SimpleMath::Vector3(pathVector[i + 1].posX, pathVector[i + 1].posY, pathVector[i + 1].posZ);
				p3 = DirectX::SimpleMath::Vector3(pathVector[i + 2].posX, pathVector[i + 2].posY, pathVector[i + 2].posZ);
			}
			else
			{
				p0 = DirectX::SimpleMath::Vector3(pathVector[i - 1].posX, pathVector[i - 1].posY, pathVector[i - 1].posZ);
				p1 = DirectX::SimpleMath::Vector3(pathVector[i].posX, pathVector[i].posY, pathVector[i].posZ);
				p2 = DirectX::SimpleMath::Vector3(pathVector[i + 1].posX, pathVector[i + 1].posY, pathVector[i + 1].posZ);
				p3 = DirectX::SimpleMath::Vector3(pathVector[i + 1].posX, pathVector[i + 1].posY, pathVector[i + 1].posZ) + DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
			}


			for (float t = tension; t <= 1.0f; t += tensionAdd)
			{
				desiredPoint = alpha * ((2 * p1) +
					(-p0 + p2) * t +
					(2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t +
					(-p0 + 3 * p1 - 3 * p2 + p3) * t * t * t);

				splinePointVector.push_back(desiredPoint);
			}
		}
	}

	return splinePointVector;
}