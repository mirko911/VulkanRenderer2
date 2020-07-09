#pragma once

#include <loguru.hpp>
#include <vulkan/vulkan.hpp>

class RenderPass
{
private:
	VkDevice m_device;
	VkRenderPass m_renderpass;

	std::vector<VkAttachmentReference> m_inputattachments;
	std::vector<VkAttachmentDescription> m_attachments;
	std::vector<VkAttachmentReference> m_colorReferences;
	std::vector<VkAttachmentReference> m_depthReferences;
	std::vector<VkSubpassDescription> m_subpasses;
	std::vector<VkSubpassDependency> m_dependencys; 
	std::vector<VkClearValue> m_clearValues;
	std::vector<VkFramebuffer> m_frameBuffers;


	uint32_t m_imageWidth;
	uint32_t m_imageHeight;
public:
	void Init(const VkDevice& device);
	void Destroy();

	void addAttachment(const VkFormat& format, const VkImageLayout imageLayout, bool clearAttachment = true);
	void addSubpass(const VkAttachmentReference& colorRef, const VkAttachmentReference& depthRef);
	void addSubpassDepth(const VkAttachmentReference& depthRef);
	void addSubPassDependency(uint32_t src_subpass, uint32_t dstSubpass);
	void createRenderpass();
	void createFrameBuffer(const std::vector<VkImageView>& imageViews, uint32_t width, uint32_t height, uint32_t layerCount);
	//void setClearColor(VkClearColorValue& backgroundColor);


	void addAttachmentCustom(const VkAttachmentDescription& attachment);
	void addSubpassCustom(const VkSubpassDescription& subpass);
	void addSubpassDependencyCustom(const VkSubpassDependency& subpassDependency);

	VkRenderPass& get();
	VkExtent2D getExtend();
	uint32_t getWidth();
	uint32_t getHeight();
	std::vector<VkFramebuffer>& getFramebuffers();
	
	void setDimensions(const uint32_t width, const uint32_t height);
	void setFrameBuffers(std::vector<VkFramebuffer>& framebuffers);

	VkRenderPassBeginInfo getBeginInfo(const VkClearColorValue& backgroundColor, const uint32_t index);
};

