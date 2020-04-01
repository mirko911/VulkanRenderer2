#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

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