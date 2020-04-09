#include "GeoCube.hpp"

GeoCube::GeoCube()
{
	m_debugName = "Generic Cube";
	
	m_index.resize(36);
	m_vertex.resize(24);

	float fxSizeHalf = 1 * 0.5f;
	float fySizeHalf = 1 * 0.5f;
	float fzSizeHalf = 1 * 0.5f;

	//Front side

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

	//back side
	m_vertex[4].position.x = -fxSizeHalf;
	m_vertex[4].position.y = fySizeHalf; //4
	m_vertex[4].position.z = -fzSizeHalf;
	m_vertex[4].normal.x = 0.0f;
	m_vertex[4].normal.y = 0.0f;
	m_vertex[4].normal.z = -1.0f;

	m_vertex[5].position.x = fxSizeHalf; //5
	m_vertex[5].position.y = fySizeHalf;
	m_vertex[5].position.z = -fzSizeHalf;
	m_vertex[5].normal.x = 0.0f;
	m_vertex[5].normal.y = 0.0f;
	m_vertex[5].normal.z = -1.0f;

	m_vertex[6].position.x = fxSizeHalf; //6
	m_vertex[6].position.y = -fySizeHalf;
	m_vertex[6].position.z = -fzSizeHalf;
	m_vertex[6].normal.x = 0.0f;
	m_vertex[6].normal.y = 0.0f;
	m_vertex[6].normal.z = -1.0f;

	m_vertex[7].position.x = -fxSizeHalf; //7
	m_vertex[7].position.y = -fySizeHalf;
	m_vertex[7].position.z = -fzSizeHalf;
	m_vertex[7].normal.x = 0.0f;
	m_vertex[7].normal.y = 0.0f;
	m_vertex[7].normal.z = -1.0f;


	//back side
	m_index[6] = 7;
	m_index[7] = 5;
	m_index[8] = 6;

	m_index[9] = 7;
	m_index[10] = 4;
	m_index[11] = 5;


	//right side
	m_vertex[8].position.x = fxSizeHalf; //8
	m_vertex[8].position.y = -fySizeHalf;
	m_vertex[8].position.z = fzSizeHalf;
	m_vertex[8].normal.x = 1.0f;
	m_vertex[8].normal.y = 0.0f;
	m_vertex[8].normal.z = 0.0f;

	m_vertex[9].position.x = fxSizeHalf; //9
	m_vertex[9].position.y = -fySizeHalf;
	m_vertex[9].position.z = -fzSizeHalf;
	m_vertex[9].normal.x = 1.0f;
	m_vertex[9].normal.y = 0.0f;
	m_vertex[9].normal.z = 0.0f;

	m_vertex[10].position.x = fxSizeHalf; //10
	m_vertex[10].position.y = fySizeHalf;
	m_vertex[10].position.z = -fzSizeHalf;
	m_vertex[10].normal.x = 1.0f;
	m_vertex[10].normal.y = 0.0f;
	m_vertex[10].normal.z = 0.0f;

	m_vertex[11].position.x = fxSizeHalf; //11
	m_vertex[11].position.y = fySizeHalf;
	m_vertex[11].position.z = fzSizeHalf;
	m_vertex[11].normal.x = 1.0f;
	m_vertex[11].normal.y = 0.0f;
	m_vertex[11].normal.z = 0.0f;

	m_index[12] = 8;
	m_index[13] = 9;
	m_index[14] = 10;

	m_index[15] = 8;
	m_index[16] = 10;
	m_index[17] = 11;

	//left side
	m_vertex[12].position.x = -fxSizeHalf; //12
	m_vertex[12].position.y = fySizeHalf;
	m_vertex[12].position.z = fzSizeHalf;
	m_vertex[12].normal.x = -1.0f;
	m_vertex[12].normal.y = 0.0f;
	m_vertex[12].normal.z = 0.0f;

	m_vertex[13].position.x = -fxSizeHalf; //13
	m_vertex[13].position.y = fySizeHalf;
	m_vertex[13].position.z = -fzSizeHalf;
	m_vertex[13].normal.x = -1.0f;
	m_vertex[13].normal.y = 0.0f;
	m_vertex[13].normal.z = 0.0f;

	m_vertex[14].position.x = -fxSizeHalf; //14
	m_vertex[14].position.y = -fySizeHalf;
	m_vertex[14].position.z = -fzSizeHalf;
	m_vertex[14].normal.x = -1.0f;
	m_vertex[14].normal.y = 0.0f;
	m_vertex[14].normal.z = 0.0f;

	m_vertex[15].position.x = -fxSizeHalf; //15
	m_vertex[15].position.y = -fySizeHalf;
	m_vertex[15].position.z = fzSizeHalf;
	m_vertex[15].normal.x = -1.0f;
	m_vertex[15].normal.y = 0.0f;
	m_vertex[15].normal.z = 0.0f;

	m_index[18] = 15;
	m_index[19] = 12;
	m_index[20] = 13;

	m_index[21] = 15;
	m_index[22] = 13;
	m_index[23] = 14;

	//top
	m_vertex[16].position.x = -fxSizeHalf; //16
	m_vertex[16].position.y = fySizeHalf;
	m_vertex[16].position.z = fzSizeHalf;
	m_vertex[16].normal.x = 0.0f;
	m_vertex[16].normal.y = 1.0f;
	m_vertex[16].normal.z = 0.0f;

	m_vertex[17].position.x = fxSizeHalf;
	m_vertex[17].position.y = fySizeHalf;
	m_vertex[17].position.z = fzSizeHalf;
	m_vertex[17].normal.x = 0.0f;
	m_vertex[17].normal.y = 1.0f;
	m_vertex[17].normal.z = 0.0f;

	m_vertex[18].position.x = fxSizeHalf;
	m_vertex[18].position.y = fySizeHalf;
	m_vertex[18].position.z = -fzSizeHalf;
	m_vertex[18].normal.x = 0.0f;
	m_vertex[18].normal.y = 1.0f;
	m_vertex[18].normal.z = 0.0f;

	m_vertex[19].position.x = -fxSizeHalf;
	m_vertex[19].position.y = fySizeHalf;
	m_vertex[19].position.z = -fzSizeHalf;
	m_vertex[19].normal.x = 0.0f;
	m_vertex[19].normal.y = 1.0f;
	m_vertex[19].normal.z = 0.0f;

	m_index[24] = 16;
	m_index[25] = 17;
	m_index[26] = 18;

	m_index[27] = 16;
	m_index[28] = 18;
	m_index[29] = 19;

	//bottom
	m_vertex[20].position.x = -fxSizeHalf; //20
	m_vertex[20].position.y = -fySizeHalf;
	m_vertex[20].position.z = -fzSizeHalf;
	m_vertex[20].normal.x = 0.0f;
	m_vertex[20].normal.y = -1.0f;
	m_vertex[20].normal.z = 0.0f;

	m_vertex[21].position.x = fxSizeHalf;
	m_vertex[21].position.y = -fySizeHalf;
	m_vertex[21].position.z = -fzSizeHalf;
	m_vertex[21].normal.x = 0.0f;
	m_vertex[21].normal.y = -1.0f;
	m_vertex[21].normal.z = 0.0f;

	m_vertex[22].position.x = fxSizeHalf;
	m_vertex[22].position.y = -fySizeHalf;
	m_vertex[22].position.z = fzSizeHalf;
	m_vertex[22].normal.x = 0.0f;
	m_vertex[22].normal.y = -1.0f;
	m_vertex[22].normal.z = 0.0f;

	m_vertex[23].position.x = -fxSizeHalf;
	m_vertex[23].position.y = -fySizeHalf;
	m_vertex[23].position.z = fzSizeHalf;
	m_vertex[23].normal.x = 0.0f;
	m_vertex[23].normal.y = -1.0f;
	m_vertex[23].normal.z = 0.0f;

	m_index[30] = 23;
	m_index[31] = 21;
	m_index[32] = 22;

	m_index[33] = 23;
	m_index[34] = 20;
	m_index[35] = 21;

	for (auto& vertex : m_vertex) {
		vertex.color.x = (vertex.position.x + 0.5f);
		vertex.color.y = (vertex.position.y + 0.5f);
		vertex.color.z = (vertex.position.z + 0.5f) * 0;
	}
}
