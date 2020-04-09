#pragma once

#include "defintions.hpp"

#include "Handler/HandlerGeometry.hpp"
#include "Handler/HandlerTransformation.hpp"
#include "Handler/HandlerGameobject.hpp"
#include "Handler/HandlerCamera.hpp"
#include "Handler/HandlerScene.hpp"
#include "Handler/HandlerTexture.hpp"

class GameRoot {
public:
	HandlerGeometry hGeometry;
	HandlerTransformation hTransformation;
	HandlerGameobject hGameObject;
	HandlerCamera hCamera;
	HandlerScene hScene;
	HandlerTexture hTexture;

	int32_t m_mainScene = ENTITY_NOT_FOUND;
};