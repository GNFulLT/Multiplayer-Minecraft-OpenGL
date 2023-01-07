#pragma once

#include "Mesh.h"
#include "Direction.h"
namespace GNF::Primitive
{
	class Chunk : public Mesh
	{
		public:
			Chunk() = default;
			Chunk(Chunk&) = default;
			Chunk(const glm::vec3& worldPos);
			void GenerateVAOVBO();
			void GenerateChunk();
			const glm::vec3& GetChunkSize()
			{
				return chunkSize;
			}
			static const glm::vec3& GetDefaultChunkSize()
			{
				return defaultChunkSize;
			}
		private:
			bool IsDirectionTransparent(Direction dir, int x, int y, int z);
			void GenerateVAOForFace(Direction dir, glm::vec3& blockCenterPos);			
			void GenerateVAOXYZ(int x, int y, int z);
		private:
			int m_chunkId;
			glm::vec3 m_worldPos;
			uint8_t blocks[16][16][16];
			static inline float g_size = 0.5f;
			static inline int g_createdChunks = 0;
			glm::vec3 chunkSize;
			static inline glm::vec3 defaultChunkSize = { 8.f,8.f,8.f };

	};
}