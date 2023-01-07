#pragma once

#include <memory>
#include <vector>

#include "Primitive/Chunk.h"


namespace GNF{
class World
{
	public:
		static World* GetInstance()
		{
			return g_world.get();
		}
		static World* Build()
		{
			g_world.reset(new World(5,5,5));

			return GetInstance();
		}
	public:
		
		std::vector<std::vector<std::vector<std::unique_ptr<Primitive::Chunk>>>>* GetChunks()
		{
			return m_chunks.get();
		}
		int GetChunkSize()
		{
			return m_chunks->size();
		}
		
	private:
		World();
		World(int x, int y, int z);
	private:
		static inline std::unique_ptr<World> g_world;
	private:
		std::unique_ptr<std::vector<std::vector<std::vector<std::unique_ptr<Primitive::Chunk>>>>> m_chunks;
		int m_xSize;
		int m_ySize;
		int m_zSize;
		
};
}