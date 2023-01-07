#include "World.h"

namespace GNF
{
	World::World() : World(16,16,16)
	{
	}

	World::World(int xx, int yy, int zz)
	{
		m_xSize = xx;
		m_ySize = yy;
		m_zSize = zz;
		m_chunks.reset(new std::vector<std::vector<std::vector<std::unique_ptr<Primitive::Chunk>> > >(m_xSize));
		for (auto& chnk : *(m_chunks.get()))
		{
			for (int y = 0; y < yy; y++)
			{
				chnk.push_back(std::vector<std::unique_ptr<Primitive::Chunk>>(m_zSize));
			}
		}
		

		
		for (int x = 0; x < m_xSize; x++)
		{
			for (int y = 0; y < m_ySize; y++)
			{
				for (int z = 0; z < m_zSize; z++)
				{
					auto defaultSize = GNF::Primitive::Chunk::GetDefaultChunkSize();
					glm::vec3 worldPos = { defaultSize.x / 2 + (x*defaultSize.x),defaultSize.y/2 + (y*defaultSize.y),defaultSize.z/2 + (z*defaultSize.z)};
					(*m_chunks.get())[x][y][z].reset(new Primitive::Chunk(worldPos));
					(*m_chunks.get())[x][y][z]->GenerateChunk();
					(*m_chunks.get())[x][y][z]->GenerateVAOVBO();
				}
			}
		}
	}
}