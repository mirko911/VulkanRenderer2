#include "GeoPlane.hpp"

GeoPlane::GeoPlane()
{
	m_debugName = "Generic Plane";
	
	m_index.resize(6);
	m_vertex.resize(4);

	float fxSizeHalf = 1 * 0.5f;
	float fySizeHalf = 1 * 0.5f;
	float fzSizeHalf = 1 * 0.5f;

	m_vertex[0].position.x = -fxSizeHalf;
	m_vertex[0].position.y = -fySizeHalf;
	m_vertex[0].position.z = fzSizeHalf;
	m_vertex[0].normal.x = 0.0f;
	m_vertex[0].normal.y = 0.0f;
	m_vertex[0].normal.z = 1.0f;

	m_vertex[1].position.x = fxSizeHalf;
	m_vertex[1].position.y = -fySizeHalf; //1
	m_vertex[1].position.z = fzSizeHalf;
	m_vertex[1].normal.x = 0.0f;
	m_vertex[1].normal.y = 0.0f;
	m_vertex[1].normal.z = 1.0f;

	m_vertex[2].position.x = fxSizeHalf; //2
	m_vertex[2].position.y = fySizeHalf;
	m_vertex[2].position.z = fzSizeHalf;
	m_vertex[2].normal.x = 0.0f;
	m_vertex[2].normal.y = 0.0f;
	m_vertex[2].normal.z = 1.0f;

	m_vertex[3].position.x = -fxSizeHalf; //3
	m_vertex[3].position.y = fySizeHalf;
	m_vertex[3].position.z = fzSizeHalf;
	m_vertex[3].normal.x = 0.0f;
	m_vertex[3].normal.y = 0.0f;
	m_vertex[3].normal.z = 1.0f;


	//front side
	m_index[0] = 0;
	m_index[1] = 1;
	m_index[2] = 2;
		 
	m_index[3] = 0;
	m_index[4] = 2;
	m_index[5] = 3;
}
