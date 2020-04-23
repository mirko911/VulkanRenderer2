#pragma once

#include <algorithm>
#include <string>
#include "defintions.hpp"

#include "Handler/HandlerEvent.hpp"

constexpr double moveVelocity = .008f;
constexpr double yawSpeed = 0.3;
constexpr double pitchSpeed = 0.4;

class Camera
{
private:
	int32_t m_moduleID = ENTITY_NOT_FOUND;
	std::string m_debugName = "Generic Camera";

	Mat4 m_view;
	Mat4 m_projection;
	Vec3 m_worldUP;
	Vec3 m_up;
	Vec3 m_front;
	Vec3 m_right;
	Vec3 m_position;
	Vec3 m_positionPrev;
	float m_yaw = 0;
	float m_pitch;
	float m_FoV;
	float m_zNear;
	float m_zFar;
	bool m_static = true;
	int32_t m_actionEventID = ENTITY_NOT_FOUND;
	int32_t m_mouseMoveEventID = ENTITY_NOT_FOUND;
	int32_t m_keyPressEventID = ENTITY_NOT_FOUND;
	void updateVectors();
public:
	Camera();
	~Camera();
	void setDebugName(const std::string& name);
	std::string getDebugName() const;

	void setModuleID(const int32_t ID);
	int32_t getModuleID() const;

	void setPosition(const float x, const float y, const float z);
	void setPosition(const Vec3 position);
	void setPosition(const Vec3 position, const float yaw, const float pitch);
	void setPerspective(const float fov, const float aspect, const float zNear, const float zFar);
	void setYaw(const float yaw);
	void setPitch(const float pitch);
	void setView(const Mat4 view);
	void setProjection(const Mat4 proj);

	float getYaw() const;
	float getPitch() const;
	Vec3 getPosition() const;
	Vec3 getPositionPrev() const;
	Vec3 getFront() const;
	float getZNear() const;
	float getZFar() const;
	float getFOV() const;
	Mat4 getView() const;
	Mat4 getProjection() const;

	void moveByMouse(EventMouseMove& event);
	void onActionEvent(EventAction& event);
	void onKeyPressed(EventKeyPress& event);
	void setStatic(const bool staticVal);
};

