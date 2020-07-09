#pragma once

#include "Pipeline.hpp"
class PipelineFont : public Pipeline
{
private:
	std::array<VkVertexInputBindingDescription, 2> vertexInputBindings = {};
	std::array<VkVertexInputAttributeDescription, 2> vertexInputAttributes = {};

protected:
	void fillPipelineStructs() override;
public:
	void createPipeline(const uint32_t subpass) override;
};

