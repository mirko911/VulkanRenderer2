#include "Camera.hpp"

void Camera::updateVectors()
{
	//https://github.com/SonarSystems/Modern-OpenGL-Game-Engine/blob/master/OpenGLGameEngine/OpenGLGameEngine/SonarGameEngine/Core/Camera.h
	// Calculate the new Front vector
	glm::vec3 front;
	front.z = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	front.y = sin(glm::radians(m_pitch));
	front.x = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

	/*front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch)) * cos(glm::radians(m_pitch));*/
	this->m_front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->m_right = glm::normalize(glm::cross(m_front, m_worldUP));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->m_up = glm::normalize(glm::cross(m_right, m_front));

	//y = pitch
	//z = yaw
	//x = roll
	m_view = glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

Camera::Camera()
{
	m_up = glm::vec3(0.0f, -1.0f, 0.0f);
	m_front = glm::vec3(0.0f, 0.0f, 1.0f);
	m_right = glm::vec3(1.0f, 0.0f, 0.0f);
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_worldUP = m_up;
	m_position = glm::vec3(0.0f);
	updateVectors();

	HandlerEvent::instance().registerEvent("acttion", [this](Event& event) {
		this->onActionEvent(reinterpret_cast<EventAction&>(event));
		});

	HandlerEvent::instance().registerEvent("mouseMove", [this](Event& event) {
		this->moveByMouse(reinterpret_cast<EventMouseMove&>(event));
		});
}

void Camera::setDebugName(const std::string& name)
{
	m_debugName = name;
}

std::string Camera::getDebugName() const
{
	return m_debugName;
}

void Camera::setModuleID(const int32_t ID)
{
	m_moduleID = ID;
}

int32_t Camera::getModuleID() const
{
	return m_moduleID;
}

void Camera::setPosition(const float x, const float y, const float z)
{
	m_position = Vec3(x, y, z);
	updateVectors();
}

void Camera::setPosition(const Vec3 position)
{
	m_position = position;
	updateVectors();
}

void Camera::setPosition(const Vec3 position, const float yaw, const float pitch)
{
	m_position = position;
	m_yaw = yaw;
	m_pitch = pitch;
	updateVectors();
}

void Camera::setPerspective(const float fov, const float aspect, const float zNear, const float zFar)
{
	m_FoV = fov;
	m_zNear = zNear;
	m_zFar = zFar;
	m_projection = glm::perspective(glm::radians(fov), aspect, m_zNear, m_zFar);
}

void Camera::setYaw(const float yaw)
{
	m_yaw = yaw;
}

void Camera::setPitch(const float pitch)
{
	m_pitch = pitch;
}

void Camera::setView(const Mat4 view)
{
	m_view = view;
}

void Camera::setProjection(const Mat4 proj)
{
	m_projection = proj;
}

float Camera::getYaw() const
{
	return m_yaw;
}

float Camera::getPitch() const
{
	return m_pitch;
}

Vec3 Camera::getPosition() const
{
	return m_position;
}

Vec3 Camera::getPositionPrev() const
{
	return m_positionPrev;
}

Vec3 Camera::getFront() const
{
	return m_front;
}

float Camera::getZNear() const
{
	return m_zNear;
}

float Camera::getZFar() const
{
	return m_zFar;
}

float Camera::getFOV() const
{
	return m_FoV;
}

Mat4 Camera::getView() const
{
	return m_view;
}

Mat4 Camera::getProjection() const
{
	return m_projection;
}

void Camera::moveByMouse(EventMouseMove& event)
{
	//y = pitch
	//x = yaw
	if (event.speed_x > 0) {
		m_yaw += (float)yawSpeed;
	}
	else if (event.speed_x < 0) {
		m_yaw -= (float)yawSpeed;
	}

	if (event.speed_y > 0) {
		m_pitch -= (float)pitchSpeed;
	}
	else if (event.speed_y < 0) {
		m_pitch += (float)pitchSpeed;
	}

	std::clamp(m_pitch, -89.0f, 89.0f);
	//if (m_pitch > 89.0f) m_pitch = 89.0f;
	//if (m_pitch < -89.0f) m_pitch = -89.0f;
	updateVectors();

}

void Camera::onActionEvent(EventAction& event)
{
	char forward = 0;
	char right = 0;
	char up = 0;

	if (event.action & ActionType::FORWARD) {
		forward += 1;
	}
	if (event.action & ActionType::BACKWARD) {
		forward = -1;
	}
	if (event.action & ActionType::LEFT) {
		right -= 1;
	}
	if (event.action & ActionType::RIGHT) {
		right =+ 1;
	}
	if (event.action & ActionType::UP) {
		up -= 1;
	}
	if (event.action & ActionType::DOWN) {
		up =+ 1;
	}

	m_position += m_front * static_cast<float>(forward * moveVelocity);
	m_position += m_right * static_cast<float>(right * moveVelocity);
	m_position += m_worldUP * static_cast<float>(up * moveVelocity);

	updateVectors();
}
