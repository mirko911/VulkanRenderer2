#pragma once
#include "Renderer.hpp"
#include <vector>

#include <loguru.hpp>

#include <stb_truetype.h>


#include "TextureFont.hpp"
#include "PipelineFont.hpp"

constexpr int FONT_MAX_CHAR_COUNT = 2048;
enum TextAlign { alignLeft, alignCenter, alignRight };


class RendererFont : public Renderer
{
private:
	VulkanDevice m_device;
	TextureFont m_fontTexture;
	PipelineFont m_pipeline;
	RenderPass m_renderpass;
	Shader m_shader;
	Buffer m_vertexBuffer;
	std::vector<CommandBuffer> m_commandBuffers;

	std::vector<Descriptor> m_fontDescriptors;
	std::vector<unsigned char> ttf_buffer;
	std::vector<stbtt_bakedchar> cdata;
	std::vector<unsigned char> temp_bitmap;

	std::vector<VkFramebuffer> m_frameBuffers;

	Vec4* mapped;
	uint32_t numLetters = 0;
	void loadFont();
public:
	virtual void Init(VulkanDevice& device, GameRoot& gameRoot);
	virtual void Draw(GameRoot& gameRoot);
	virtual void Render(GameRoot& gameRoot);
	virtual void updateUniformBuffer(GameRoot& gameRoot, const bool initial = false);
	virtual void Destroy();

	CommandBuffer& getCommandBuffer();
	void linkFrameBuffers(std::vector<VkFramebuffer>& frameBuffers);
	void updateCommandBuffer();
	void mapVertexBuffer();
	void unmapVertexBuffer();
	void addText(const std::string& text, const float x, const float y, const TextAlign align = TextAlign::alignLeft);
};

