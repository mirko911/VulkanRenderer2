#include "ModuleTransformation.hpp"

void ModuleTransformation::update(const float ftimeDelta, GameRoot& gameRoot)
{
	updateLocalMat();
}

void ModuleTransformation::init(VulkanDevice& device)
{
	updateLocalMat();
}

Mat4 ModuleTransformation::getGlobalMat() const
{
	return m_globalMat;
}

Mat4 ModuleTransformation::getLocalMat() const
{
	return m_localMat;
}

Vec3 ModuleTransformation::getTranslation() const
{
	return m_transformation.translation;
}

Vec3 ModuleTransformation::getRotation() const
{
	return m_transformation.rotation;
}

Vec3 ModuleTransformation::getScale() const
{
	return m_transformation.scale;
}

Transformation& ModuleTransformation::getTransformation()
{
	return m_transformation;
}

Mat4 ModuleTransformation::updateGlobalMat(const Mat4& mat)
{
	if (!m_recalculateGlobalMat && mat == m_parentMat) {
		return m_globalMat;
	}

	m_recalculateGlobalMat = false;
	m_globalMat = mat * m_localMat;
	m_parentMat = mat;
	return m_globalMat;
}

void ModuleTransformation::updateLocalMat()
{
	if (!m_isDirty) {
		return;
	}

	Mat4 mat = Mat4(1.0f);

	Mat4 matScale = glm::scale(mat, m_transformation.scale);

	Mat4 matRotation = glm::eulerAngleYXZ(m_transformation.rotation.y, m_transformation.rotation.x, m_transformation.rotation.z);

	Mat4 matTranslation = glm::translate(mat, m_transformation.translation);

	mat = matTranslation * matRotation * matScale;

	m_localMat = mat;

	m_isDirty = false;
	m_recalculateGlobalMat = true;
}

void ModuleTransformation::translate(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.translation += Vec3(x, y, z);
}

void ModuleTransformation::translate(const Vec3& translation)
{
	m_isDirty = true;
	m_transformation.translation += translation;
}

void ModuleTransformation::translateX(const float value)
{
	m_isDirty = true;
	m_transformation.translation.x += value;
}

void ModuleTransformation::translateY(const float value)
{
	m_isDirty = true;
	m_transformation.translation.y += value;
}

void ModuleTransformation::translateZ(const float value)
{
	m_isDirty = true;
	m_transformation.translation.z += value;
}

void ModuleTransformation::translateAbsolute(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.translation = Vec3(x,y,z);
}

void ModuleTransformation::translateAbsolute(const Vec3& translation)
{
	m_isDirty = true;
	m_transformation.translation = translation;
}

void ModuleTransformation::translateAbsoluteX(const float value)
{
	m_isDirty = true;
	m_transformation.translation.x = value;
}

void ModuleTransformation::translateAbsoluteY(const float value)
{
	m_isDirty = true;
	m_transformation.translation.y = value;
}

void ModuleTransformation::translateAbsoluteZ(const float value)
{
	m_isDirty = true;
	m_transformation.translation.z = value;
}

void ModuleTransformation::rotate(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.rotation += Vec3(x,y,z);
}

void ModuleTransformation::rotate(const Vec3& rotation)
{
	m_isDirty = true;
	m_transformation.rotation += rotation;
}

void ModuleTransformation::rotateX(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.x += value;
}

void ModuleTransformation::rotateY(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.y += value;
}

void ModuleTransformation::rotateZ(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.z += value;
}

void ModuleTransformation::rotateAbsolute(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.rotation = Vec3(x, y, z);
}

void ModuleTransformation::rotateAbsolute(const Vec3& rotation)
{
	m_isDirty = true;
	m_transformation.rotation = rotation;
}

void ModuleTransformation::rotateAbsoluteX(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.x = value;
}

void ModuleTransformation::rotateAbsoluteY(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.y = value;
}

void ModuleTransformation::rotateAbsoluteZ(const float value)
{
	m_isDirty = true;
	m_transformation.rotation.z = value;
}

void ModuleTransformation::scale(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.scale += Vec3(x, y, z);
}

void ModuleTransformation::scale(const Vec3& scale)
{
	m_isDirty = true;
	m_transformation.scale += scale;
}

void ModuleTransformation::scaleX(const float value)
{
	m_isDirty = true;
	m_transformation.scale.x += value;
}

void ModuleTransformation::scaleY(const float value)
{
	m_isDirty = true;
	m_transformation.scale.y += value;
}

void ModuleTransformation::scaleZ(const float value)
{
	m_isDirty = true;
	m_transformation.scale.z += value;
}

void ModuleTransformation::scaleAbsolute(const float x, const float y, const float z)
{
	m_isDirty = true;
	m_transformation.scale = Vec3(x, y, z);
}

void ModuleTransformation::scaleAbsolute(const Vec3& scale)
{
	m_isDirty = true;
	m_transformation.scale = scale;
}

void ModuleTransformation::scaleAbsoluteX(const float value)
{
	m_isDirty = true;
	m_transformation.scale.x = value;
}

void ModuleTransformation::scaleAbsoluteY(const float value)
{
	m_isDirty = true;
	m_transformation.scale.y = value;
}

void ModuleTransformation::scaleAbsoluteZ(const float value)
{
	m_isDirty = true;
	m_transformation.scale.z = value;
}

