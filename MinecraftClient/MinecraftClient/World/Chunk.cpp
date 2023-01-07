#include "Chunk.h"



Chunk::Chunk(int width,int height,int depth,const glm::vec3& pos) : worldPosition(pos),m_width(width),m_height(height),m_depth(depth)
{
	GenerateChunk();

	CreateBuffer();

}

Chunk::~Chunk()
{
	for (int i = 0; i < m_width; ++i) {
		for (int j = 0; j < m_height; ++j) {
			delete[] m_chunk[i][j];
		}
		delete[] m_chunk[i];
	}
	delete[] m_chunk;

}

void Chunk::CreateBuffers()
{
	
}

void Chunk::UpdateBuffers()
{

	int localX = worldPosition.x;
	int localY = worldPosition.y;
	int localZ = worldPosition.z;



	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			for (int z = 0; z < m_depth; z++)
			{
							
			}
		}
	}
}

void Chunk::GenerateChunk()
{

	int localX0 = worldPosition.x - (m_width * cubeWidth) / 2;
	int localY0 = worldPosition.y - (m_height * cubeHeight) / 2;
	int localZ0 = worldPosition.z + (m_depth * cubeWidth) / 2;

	m_chunk = new uint8_t * *[m_width];
	for (int i = 0; i < m_width; i++) {
		m_chunk[i] = new uint8_t * [m_height];

		int xLocLeft = localX0 + i * cubeWidth;
		int xLocRight = xLocLeft + cubeWidth;

		for (int j = 0; j < m_height; j++) {
			m_chunk[i][j] = new uint8_t[m_depth];

			int yLocUp = localY0 + j*cubeHeight;
			int yLocDown = yLocUp + cubeHeight;


			for (int z = 0; z < m_depth; z++)
			{
				m_chunk[i][j][z] = 0;
				int zLocBack = localZ0 - z*cubeWidth;
				int zLocForward = zLocBack - cubeWidth;
				
				int a0 = AddVertex({ xLocLeft,yLocUp,zLocForward }, { 0,1.0f });    // Front Top Left          0  + (z*16) + (j*16*m_depth) + (i*16*m_height*m_depth)
				int a1 = AddVertex({ xLocRight,yLocUp,zLocForward }, { 1.f,1.f }); // Front Top Right          1
				int a2 = AddVertex({ xLocRight,yLocDown,zLocForward }, { 1.f,0 }); // Front Bottom Right       2 
				int a3 = AddVertex({ xLocLeft,yLocDown,zLocForward }, { 0.f,0.f }); // Front Bottom Left       3
			
				int a4 = AddVertex({ xLocLeft,yLocUp,zLocBack }, { 0,1.0f });    // Back Top Left             4
				int a5 = AddVertex({ xLocRight,yLocUp,zLocBack }, { 1.f,1.f }); // Back Top Right             5
				int a6 = AddVertex({ xLocRight,yLocDown,zLocBack }, { 1.f,0 }); // Back Bottom Right           6
				int a7 = AddVertex({ xLocLeft,yLocDown,zLocBack }, { 0.f,0.f }); // Back Bottom Left            7
			


				//For Up
				int a8 = AddVertex({ xLocLeft,yLocUp,zLocForward }, { 0,0.0f });    // Bottom Left            8
				int a9 = AddVertex({ xLocLeft,yLocUp,zLocBack }, { 0,1.0f });    // Top Left                  9
				int a10 = AddVertex({ xLocRight,yLocUp,zLocBack }, { 1.f,1.f }); // Top Right                  10
				int a11 = AddVertex({ xLocRight,yLocDown,zLocForward }, { 1.f,0 }); // Bottom Right           11
				 
				//For Down
				int a12 = AddVertex({ xLocRight,yLocDown,zLocForward }, { 0.f,0 }); //  Bottom Left          12
				int a13 = AddVertex({ xLocRight,yLocDown,zLocForward }, { 0.f,1.0f }); //  Top Left           13
				int a14 = AddVertex({ xLocLeft,yLocDown,zLocForward }, { 1.f,1.f }); // Top Right            14
				int a15 = AddVertex({ xLocLeft,yLocDown,zLocBack }, { 1.f,0.f }); // Bottom Right           15

				
				//Front
				AddTriangle({a0,a1,a2});
				AddTriangle({ a2,a3,a0 });

				//Back
				AddTriangle({ a4,a5,a6 });
				AddTriangle({ a6,a7,a4 });

				//Left
				AddTriangle({ a7,a4,a0 });
				AddTriangle({ a7,a0,a3 });

				//Right
				AddTriangle({ a5,a1,a2 });
				AddTriangle({ a5,a2,a6 });

				// Up
				AddTriangle({a8,a9,a10});
				AddTriangle({ a8,a10,a11 });

				// Down
				AddTriangle({ a12,a13,a14 });
				AddTriangle({ a12,a14,a15 });

			}
		}
	}
}
