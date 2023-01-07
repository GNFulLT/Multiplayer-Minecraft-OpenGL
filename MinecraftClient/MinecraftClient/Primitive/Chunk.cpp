#include "Chunk.h"
#include "Utils/Utils.h"
namespace GNF::Primitive
{
	Chunk::Chunk(const glm::vec3& worldPos)
	{
		m_worldPos = worldPos;
		m_chunkId = g_createdChunks;
		g_createdChunks++;
		chunkSize = { g_size * 16,g_size * 16,g_size * 16 };
	}
	
	void Chunk::GenerateVAOXYZ(int x, int y, int z)
	{
		glm::vec3 center = { ((g_size / 2 + (g_size * x)) - (chunkSize.x/2))+m_worldPos.x,((g_size / 2 + (g_size*y))+(chunkSize.y/2))+m_worldPos.y,((g_size / 2 + (g_size * z)) - (chunkSize.z/2))+m_worldPos.z};
		if (IsDirectionTransparent(Left, x, y, z))
		{
			GenerateVAOForFace(Left, center);
		}
		if (IsDirectionTransparent(Right, x, y, z))
		{
			GenerateVAOForFace(Right, center);

		}
		if (IsDirectionTransparent(Up, x, y, z))
		{
			GenerateVAOForFace(Up, center);

		}
		if (IsDirectionTransparent(Down, x, y, z))
		{
			GenerateVAOForFace(Down, center);

		}
		if (IsDirectionTransparent(Front, x, y, z))
		{
			GenerateVAOForFace(Front, center);

		}
		if (IsDirectionTransparent(Back, x, y, z))
		{
			GenerateVAOForFace(Back, center);
		}
	}

	void Chunk::GenerateVAOVBO()
	{
		
		for (int x = 0; x < 16; x++)
		{
			int a = 5;
			for (int y = 0; y < 16; y++)
			{
				for (int z = 0; z < 16; z++)
				{
					glm::vec3 center = { ((g_size / 2 + (g_size * x)) - (chunkSize.x / 2)) + m_worldPos.x,((g_size / 2 + (g_size * y)) + (chunkSize.y / 2)) + m_worldPos.y,((g_size / 2 + (g_size * z)) - (chunkSize.z / 2)) + m_worldPos.z };
					if (IsTransparent(blocks[x][y][z]))
						continue;
					if (IsDirectionTransparent(Left, x, y, z))
					{
						GenerateVAOForFace(Left, center);
					}
					if (IsDirectionTransparent(Right, x, y, z))
					{
						GenerateVAOForFace(Right, center);

					}
					if (IsDirectionTransparent(Up, x, y, z))
					{
						GenerateVAOForFace(Up, center);

					}
					if (IsDirectionTransparent(Down, x, y, z))
					{
						GenerateVAOForFace(Down, center);

					}
					if (IsDirectionTransparent(Front, x, y, z))
					{
						GenerateVAOForFace(Front, center);

					}
					if (IsDirectionTransparent(Back, x, y, z))
					{
						GenerateVAOForFace(Back, center);
					}

				}
			}
		}
		
		CreateBuffer();
	}
	
	void Chunk::GenerateChunk()
	{
		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				for (int z = 0; z < 16; z++)
				{
					if(x == 0 && ((y > 3) && y < 12) && (z>3 && z<12))
						blocks[x][y][z] = 1;
					else
						blocks[x][y][z] = 0;
				}
			}
		}
	}

	void Chunk::GenerateVAOForFace(Direction dir, glm::vec3& blockCenterPos)
	{
		switch (dir)
		{
			case Up:
			{
				int t1 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
			case Down:
			{
				int t1 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
			case Left:
			{
				int t1 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
			case Right:
			{
				int t1 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
			case Front:
			{
				int t1 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z - g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z - g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
			case Back:
			{
				int t1 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 0.0f,1.0f }); // Top Left
				int t2 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y + g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,1.0f }); // Top Right
				int t3 = AddVertex({ blockCenterPos.x + g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 1.0f,0.0f }); // Bottom Right
				int t4 = AddVertex({ blockCenterPos.x - g_size / 2,blockCenterPos.y - g_size / 2,blockCenterPos.z + g_size / 2 }, { 0.0f,0.0f }); // Bottom Left
				AddTriangle({ t1, t2, t3 });
				AddTriangle({ t1,t4,t3 });
			}
				break;
		}
	}
	bool Chunk::IsDirectionTransparent(Direction dir, int x, int y, int z)
	{
		switch (dir)
		{
			case Up:
				if (y == 15)
					return true;
				return IsTransparent(blocks[x][y + 1][z]);
				break;
			case Right:
				if (x == 15)
					return true;
				return IsTransparent(blocks[x+1][y][z]);
				break;
			case Down:
				if (y == 0)
					return true;
				return IsTransparent(blocks[x][y - 1][z]);
				break;
			case Left:
				if (x == 0)
					return true;
				return IsTransparent(blocks[x-1][y][z]);
				break;
			case Front:
				if (z == 0)
					return true;
				return IsTransparent(blocks[x][y][z-1]);
				break;
			case Back:
				if (z == 15)
					return true;
				return IsTransparent(blocks[x][y][z+1]);
				break;
			default:
				return false;
		}
	
	}
}
