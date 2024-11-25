#pragma once
#include "Triangulation.h"
#include "Transformation.h"
using namespace Geometry;


class MeshJoiner
{
public:
	MeshJoiner();
	~MeshJoiner();

	Transformations::Transformation transformer;
	std::vector<Triangulation> performTransformations(std::vector<Triangulation>& triangulations);

};
