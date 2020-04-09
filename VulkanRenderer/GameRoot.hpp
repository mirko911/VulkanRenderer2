#pragma once
#include "Handler/HandlerGeometry.hpp"
#include "Handler/HandlerTransformation.hpp"
#include "Handler/HandlerGameobject.hpp"
#include "Handler/HandlerCamera.hpp"

class GameRoot {
public:
	HandlerGeometry hGeometry;
	HandlerTransformation hTransformation;
	HandlerGameobject hGameObject;
	HandlerCamera hCamera;
};