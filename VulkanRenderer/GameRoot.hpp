#pragma once

#include "defintions.hpp"

#include "handler/HandlerGeometry.hpp"
#include "handler/HandlerTransformation.hpp"
#include "handler/HandlerGameobject.hpp"
#include "handler/HandlerCamera.hpp"
#include "handler/HandlerScene.hpp"
#include "handler/HandlerTexture.hpp"
#include "handler/HandlerInput.hpp"
#include "handler/HandlerSkybox.hpp"
#include "handler/HandlerPortal.hpp"
#include "handler/HandlerMaterial.hpp"
#include "handler/HandlerSceneNode.hpp"

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
	std::vector<int32_t> m_activeScenes;

	void Init(VulkanDevice& device);
	void update(const float ftimeDelta);
	void clear();
};