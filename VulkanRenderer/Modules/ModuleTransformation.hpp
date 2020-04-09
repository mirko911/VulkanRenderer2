#pragma once

#include <vector>

#include <vulkan/vulkan.hpp>
#include <loguru.hpp>

#include "../defintions.hpp"

#include "ModuleBase.hpp"

class ModuleTransformation : public ModuleBase {
	std::string m_debugName = "Generic Transformation";
private:
	Transformation m_transformation;
	Mat4 m_localMat = Mat4(1.0f);
	Mat4 m_globalMat = Mat4(1.0f);
	bool m_isDirty = true;
	bool m_recalculateGlobalMat = true;
public:
	void update(const float ftimeDelta);
	void init(VulkanDevice& device);

	Mat4 getGlobalMat() const;
	Mat4 getLocalMat() const;
	Vec3 getTranslation() const;
	Vec3 getRotation() const;
	Vec3 getScale() const;
	Transformation& getTransformation();
	Mat4 updateGlobalMat(const Mat4& mat);
	void updateLocalMat();

	void translate(const float x, const float y, const float z);
	void translate(const Vec3& translation);
	void translateX(const float value);
	void translateY(const float value);
	void translateZ(const float value);
	void translateAbsolute(const float x, const float y, const float z);
	void translateAbsolute(const Vec3& translation);
	void translateAbsoluteX(const float value);
	void translateAbsoluteY(const float value);
	void translateAbsoluteZ(const float value);

	void rotate(const float x, const float y, const float z);
	void rotate(const Vec3& rotation);
	void rotateX(const float value);
	void rotateY(const float value);
	void rotateZ(const float value);
	void rotateAbsolute(const float x, const float y, const float z);
	void rotateAbsolute(const Vec3& rotation);
	void rotateAbsoluteX(const float value);
	void rotateAbsoluteY(const float value);
	void rotateAbsoluteZ(const float value);

	void scale(const float x, const float y, const float z);
	void scale(const Vec3& scale);
	void scaleX(const float value);
	void scaleY(const float value);
	void scaleZ(const float value);
	void scaleAbsolute(const float x, const float y, const float z);
	void scaleAbsolute(const Vec3& scale);
	void scaleAbsoluteX(const float value);
	void scaleAbsoluteY(const float value);
	void scaleAbsoluteZ(const float value);
};