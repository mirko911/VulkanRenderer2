#pragma once

#include <vector>

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

#include "defintions.hpp"
#include "Pipeline.hpp"

class PipelineDepth : public Pipeline
{
public:
	void createPipeline(const uint32_t subpass) override;
};

