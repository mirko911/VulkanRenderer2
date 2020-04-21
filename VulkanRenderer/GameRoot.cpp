#include "GameRoot.hpp"

void GameRoot::Init(VulkanDevice& device)
{
	hGeometry.init(device);
	hTransformation.init(device);
	hGameObject.init(device);
	hCamera.init(device);
	hScene.init(device);
	hTexture.init(device);
	hInput.init(device);
	hSkybox.init(device);
}

void GameRoot::update(const float ftimeDelta)
{
	hGeometry.update(ftimeDelta, *this);
	hTransformation.update(ftimeDelta, *this);
	hGameObject.update(ftimeDelta, *this);
	hCamera.update(ftimeDelta, *this);
	hScene.update(ftimeDelta, *this);
	hTexture.update(ftimeDelta, *this);
	hInput.update(ftimeDelta, *this);
	hSkybox.update(ftimeDelta, *this);
	hPortal.update(ftimeDelta, *this);
}

void GameRoot::clear()
{
	hTransformation.clear();
	hGameObject.clear();
	hCamera.clear();
	hScene.clear();
	hSceneNode.clear();
	hPortal.clear();
}
