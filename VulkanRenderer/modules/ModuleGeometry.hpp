#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>
#include "ModuleBase.hpp"
#include "../Buffer.hpp"
#include "../CommandBuffer.hpp"
class ModuleGeometry : public ModuleBase {
protected:
	std::vector<Vertex> m_vertex;
	std::vector<uint32_t> m_index;
	Buffer m_bufferVertex;
	Buffer m_bufferIndex;
	std::string m_debugName = "Generic Geometry";
public:
	//void update(const float ftimeDelta, GameRoot& gameRoot);
	void init(VulkanDevice& device);
	Buffer& getVertexBuffer();
	Buffer & getIndexBuffer();
	std::vector<Vertex>& getVertexData();
	std::vector<uint32_t>& getIndexData();
};