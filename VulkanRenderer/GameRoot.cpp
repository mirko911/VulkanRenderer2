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
	hGeometry.update(ftimeDelta);
	hTransformation.update(ftimeDelta);
	hGameObject.update(ftimeDelta);
	hCamera.update(ftimeDelta);
	hScene.update(ftimeDelta);
	hTexture.update(ftimeDelta);
	hInput.update(ftimeDelta);
	hSkybox.update(ftimeDelta);
}
