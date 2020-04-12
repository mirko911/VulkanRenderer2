#pragma once

#include "Modules/ModuleGeometry.hpp"

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.uv) << 1);
		}
	};
}


class GeoWavefront : public ModuleGeometry
{
private:
	std::string m_fileName;
public:
	GeoWavefront(const std::string& fileName);
};

