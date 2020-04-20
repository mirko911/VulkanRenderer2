#include "ModulePortal.hpp"
#include "../GameObjekt.hpp"
#include "../GameRoot.hpp"
//void ModulePortal::update(const float ftimeDelta, GameRoot& gameRoot)
//{
//}

void ModulePortal::update(const float ftimeDelta, GameRoot& gameRoot)
{
	if (m_destinationGameobjectID == ENTITY_NOT_FOUND) {
		return;
	}


	GameObjekt* startGO = gameRoot.hGameObject.get(m_startGameobjectID);
	if (startGO->getSceneID() != gameRoot.m_mainScene) {
		//Portal doesn't belong to active scene. Skip it!
		return;
	}
	
	
	GameObjekt* destinationGO = gameRoot.hGameObject.get(m_destinationGameobjectID);


	Scene* startScene = gameRoot.hScene.get(startGO->getSceneID());
	Scene* endScene = gameRoot.hScene.get(destinationGO->getSceneID());

	Camera* startCam = gameRoot.hCamera.get(startScene->m_activeCamera);
	Camera* endCam = gameRoot.hCamera.get(endScene->m_activeCamera);

	ModuleTransformation* startTrans = gameRoot.hTransformation.get(startGO);
	ModuleTransformation* endTrans = gameRoot.hTransformation.get(destinationGO);

	Mat4 startMat = startTrans->getGlobalMat();
	Mat4 endMat = endTrans->getGlobalMat();

	ModuleGeometry* geo = gameRoot.hGeometry.get<ModuleGeometry>(startGO);

	Vec3 normal = geo->getVertexData()[0].normal;

	const bool frontDir = glm::dot(startCam->getPosition() - endTrans->getTranslation(), normal) > 0;
	if (frontDir) {
		normal = -normal;
	}

	glm::mat4 mv = startCam->getView() * startMat;
	glm::mat4 portal_cam =
		mv * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0))
		* glm::inverse(endMat);

	endCam->setView(portal_cam);
	float extra_clip = 0.1f;

	Mat4 proj = getObliquePlane(startTrans->getTranslation() - (normal * extra_clip), -normal, startCam->getProjection(), startCam->getView());
	endCam->setProjection(proj);

	if (checkTeleport(startCam, startTrans->getLocalMat(), geo)) {
		gameRoot.m_mainScene = destinationGO->getSceneID();

		endCam->setStatic(false);
		startCam->setStatic(true);

		const Mat4 inverted = glm::inverse(portal_cam);
		Vec3 position = inverted[3];
		position += startCam->getFront() * Vec3(-3, -3, -3);
		const Vec3 direction = -inverted[2];
		const float yaw = glm::degrees(glm::atan(direction.z, direction.x)) - 90;
		const float pitch = glm::degrees(glm::asin(direction.y));
		endCam->setPosition(position, yaw, pitch);

		endCam->setProjection(startCam->getProjection());

		LOG_F(WARNING, "Touched portal %i", startGO->getModuleID());

		EventDrawCall drawCallEvent = EventDrawCall(gameRoot);
		HandlerEvent::instance().notify("redraw", drawCallEvent);
	}

	//const Mat4 inverted = glm::inverse(portal_cam);
	//const Vec3 position = inverted[3];
	//const Vec3 direction = -inverted[2];
	//const float yaw = glm::degrees(glm::atan(direction.z, direction.x)) - 90;
	//const float pitch = glm::degrees(glm::asin(direction.y));
	//endCam->setPosition(position, yaw, pitch);

}

void ModulePortal::init(VulkanDevice& device)
{
}

void ModulePortal::setStartGameObject(const int32_t ID)
{
	m_startGameobjectID = ID;
}

void ModulePortal::setDestinatioNGameObject(const int32_t ID)
{
	m_destinationGameobjectID = ID;
}

int32_t ModulePortal::getStartGameObject() const
{
	return m_startGameobjectID;
}

int32_t ModulePortal::getDestinationGameObject() const
{
	return m_destinationGameobjectID;
}

Mat4 ModulePortal::getObliquePlane(const Vec3& pos, const Vec3& normal, Mat4 proj, Mat4 view)
{
	const Vec3 cpos = (view * Vec4(pos, 1.0f));
	const Vec3 cnormal = (view * Vec4(normal, 0));
	const Vec4 clipPlane2(cnormal.x, cnormal.y, cnormal.z, -glm::dot(cpos, cnormal));

	glm::vec4 q1;
	q1.x = (glm::sign(clipPlane2.x) - proj[0][2]) / proj[0][0];
	q1.y = (glm::sign(clipPlane2.y) - proj[1][2]) / proj[1][1];
	q1.z = 1.0f;
	q1.w = (1.0f - proj[2][2]) / proj[2][3];


	glm::vec4 c2 = clipPlane2 * (1.0f / glm::dot(clipPlane2, q1));
	glm::mat4 newProj2 = proj;
	newProj2[0][2] = c2.x;
	newProj2[1][2] = c2.y;
	newProj2[2][2] = c2.z;
	newProj2[3][2] = c2.w;

	return newProj2;
}

bool ModulePortal::checkTeleport(Camera* cam, const Mat4& modelMat, ModuleGeometry* geo)
{
	if (cam->getPositionPrev() == cam->getPosition()) {
		return false;
	}

	for (int i = 0; i < 2; i++) {
		uint32_t index0 = geo->getIndexData()[i * 3 + 0];
		uint32_t index1 = geo->getIndexData()[i * 3 + 1];
		uint32_t index2 = geo->getIndexData()[i * 3 + 2];
		Vec3 point0 = modelMat * Vec4(geo->getVertexData()[index0].position, 1);
		Vec3 point1 = modelMat * Vec4(geo->getVertexData()[index1].position, 1);
		Vec3 point2 = modelMat * Vec4(geo->getVertexData()[index2].position, 1);

		float dist = glm::distance(cam->getPosition(), point0);
		if (dist < 3) {
			return true;
		}

		glm::vec3 tuv =
			glm::inverse(
				glm::mat3(
					Vec3(cam->getPositionPrev() - cam->getPosition()),
					Vec3(point1 - point0),
					Vec3(point2 - point0)))
			* Vec3(cam->getPositionPrev() - point0);

		float t = tuv.x; float u = tuv.y; float v = tuv.z;

		float eps = 1e-7;
		if (t >= 0 - eps && t <= 1 + eps) {
			if (u >= 0 - eps && u <= 1 + eps && v >= 0 - eps && v <= 1 + eps && (u + v) <= 1 + eps) {
				return true;
			}
		};
	}
	return false;
}
