#ifndef _CAT_MULL_ROM_SPLINE_H
#define _CAT_MULL_ROM_SPLINE_H

#include <d3d11.h>
#include <SimpleMath.h>
#include "SceneObject.h"
#include <vector>
#include <algorithm>

class CatMullRomSpline
{
public:
	CatMullRomSpline();
	~CatMullRomSpline();

	std::vector<std::vector<SceneObject>> FindAIObjects(std::vector<SceneObject> sceneGraph);

	std::vector<DirectX::SimpleMath::Vector3> CalcPoints(std::vector<SceneObject> pathVector);

};
#endif _CAT_MULL_ROM_SPLINE_H
