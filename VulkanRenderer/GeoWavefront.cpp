#include "GeoWavefront.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

GeoWavefront::GeoWavefront(const std::string& fileName) : m_fileName(fileName)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, m_fileName.c_str())) {
		throw std::runtime_error(warn + err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			if (!attrib.normals.empty() && attrib.normals.size() % 3 == 0) {
				vertex.normal = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}

			if (!attrib.texcoords.empty()) {
				vertex.uv = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(m_vertex .size());
				m_vertex.push_back(vertex);
			}

			m_index.push_back(uniqueVertices[vertex]);
		}
	}

	for (auto& vertex : m_vertex) {
		vertex.color.x = (vertex.position.x / 255) + 0.2f;
		vertex.color.y = (vertex.position.y / 255) + 0.2f;
		vertex.color.z = (vertex.position.z / 255) + 0.2f;
	}
}
