#pragma once

#include <typeindex>


#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_CXX17
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion_simd.inl>
#include <glm/gtx/euler_angles.hpp>



typedef glm::mat4 Mat4;
typedef glm::mat3 Mat3;

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

constexpr int32_t ENTITY_NOT_FOUND = -1;


struct QueueFamilyIndices {
	uint32_t graphicsFamily = VK_QUEUE_FAMILY_IGNORED;
	uint32_t presentFamily = VK_QUEUE_FAMILY_IGNORED;
	uint32_t computeFamily = VK_QUEUE_FAMILY_IGNORED;

	bool isComplete() {
		return (
			graphicsFamily != VK_QUEUE_FAMILY_IGNORED &&
			presentFamily != VK_QUEUE_FAMILY_IGNORED);
	}
};

struct GameState {
public:
	enum class STATE : char { Stopped = 0, Running, Paused, SIZE};
	bool isRunning() const {
		return m_state > STATE::Stopped;
	}
	void setState(const STATE state) {
		m_state = state;
	}
private:
	STATE m_state = STATE::Stopped;
};

struct Vertex {
public:
	Vec3 position;
	Vec3 normal;
	Vec3 tangent;
	Vec3 bitangent;
	Vec2 uv;
	Vec3 color;

	static std::array<VkVertexInputBindingDescription, 1> getBindingDescription() {
		std::array<VkVertexInputBindingDescription, 1> bindingDescriptions = {};
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescriptions;
	};

	static std::array<VkVertexInputAttributeDescription, 6> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 6> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, tangent);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(Vertex, bitangent);

		attributeDescriptions[4].binding = 0;
		attributeDescriptions[4].location = 4;
		attributeDescriptions[4].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[4].offset = offsetof(Vertex, uv);

		attributeDescriptions[5].binding = 0;
		attributeDescriptions[5].location = 5;
		attributeDescriptions[5].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[5].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const {
		return position == other.position && normal == other.normal;
	}
};

struct Ubo {
	Mat4 test;
	Vec4 test2;
};

template <typename T>
struct ModuleInfo {
	const int32_t ID;
	T* instance;
	T* operator-> () {
		return instance;
	}
};

struct Transformation {
	Vec3 translation = Vec4(0.0f);
	Vec3 rotation = Vec4(0.0f);
	Vec3 scale = Vec4(1.0f);
};

template <typename T>
inline std::type_index getType() {
	return std::type_index(typeid(T));
}
