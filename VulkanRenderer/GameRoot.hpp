#pragma once

#include "defintions.hpp"

#include "Handler/HandlerGeometry.hpp"
#include "Handler/HandlerTransformation.hpp"
#include "Handler/HandlerGameobject.hpp"
#include "Handler/HandlerCamera.hpp"
#include "Handler/HandlerScene.hpp"
#include "Handler/HandlerTexture.hpp"
#include "Handler/HandlerInput.hpp"
#include "Handler/HandlerSkybox.hpp"
#include "Handler/HandlerPortal.hpp"
#include "Handler/HandlerMaterial.hpp"
#include "Handler/HandlerSceneNode.hpp"

class GameRoot {
public:
	HandlerGeometry hGeometry;
	HandlerTransformation hTransformation;
	HandlerGameobject hGameObject;
	HandlerCamera hCamera;
	HandlerScene hScene;
	HandlerTexture hTexture;
	HandlerInput hInput;
	HandlerSkybox hSkybox;
	HandlerPortal hPortal;
	HandlerMaterial hMaterial;
	HandlerSceneNode hSceneNode;
	int32_t m_mainScene = ENTITY_NOT_FOUND;

	void Init(VulkanDevice& device);
	void update(const float ftimeDelta);
};