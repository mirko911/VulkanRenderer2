#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

#include "../defintions.hpp"

#include "ModuleBase.hpp"
#include "../Handler/HandlerEvent.hpp"
class Camera;
class ModuleGeometry;

class ModulePortal : public ModuleBase {
private:
	int32_t m_startGameobjectID = ENTITY_NOT_FOUND;
	int32_t m_destinationGameobjectID = ENTITY_NOT_FOUND;

	//Portal teleports to destination in same scene
	bool m_sameScenePortal = false;
public:
	void update(const float ftimeDelta, GameRoot& gameRoot);
	void init(VulkanDevice& device);
	void setStartGameObject(const int32_t ID);
	void setDestinatioNGameObject(const int32_t ID);
	int32_t getStartGameObject() const;
	int32_t getDestinationGameObject() const;
	Mat4 getObliquePlane(const Vec3& pos, const Vec3& normal, Mat4 proj, Mat4 view);
	bool checkTeleport(Camera* cam, const Mat4& modelMat, ModuleGeometry* geo);
	void setSameScenePortal(const bool sameScenePortal);
};