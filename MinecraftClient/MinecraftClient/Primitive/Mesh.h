#pragma once


#include <iostream>
#include <vector>
#include "VertexType.h"

#include "Rendering/IRenderable.h"


namespace GNF::Primitive
{ 
	class Mesh : public Rendering::IRenderable
	{
		public:
			virtual ~Mesh() = default;
			int SizeOfIndices()
			{
				return m_indices.size();
			}
		protected:
			std::vector<VertexType> m_meshVertices;
			std::vector<unsigned int> m_indices;

			virtual int AddVertex(const glm::vec3& pos, const glm::vec2& texPos)
			{
				m_meshVertices.push_back({ pos,texPos });
				return m_meshVertices.size() - 1;
			}

			virtual void AddTriangle(const glm::ivec3& triangle)
			{
				m_indices.push_back(triangle[0]);
				m_indices.push_back(triangle[1]);
				m_indices.push_back(triangle[2]);

			}

			virtual void CreateBuffer()
			{

				glCreateVertexArrays(1, &VAO);


				glCreateBuffers(1, &EBO);
				glNamedBufferStorage(EBO, sizeof(int) * m_indices.size(), m_indices.data(), 0);

				glVertexArrayElementBuffer(VAO, EBO);

				glCreateBuffers(1, &VBO);
				glNamedBufferStorage(VBO, sizeof(VertexType) * m_meshVertices.size(), m_meshVertices.data(), 0);
				//glNamedBufferData(VBO, sizeof(verticesV), verticesV, GL_STATIC_DRAW);
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, VBO);
				
				/*
				BindVAO();
				

				glCreateBuffers(1, &VBO);
				glCreateBuffers(1, &EBO);

				glNamedBufferStorage(EBO, m_indices.size(), m_indices.data(), 0);

				glVertexArrayElementBuffer(VAO,EBO);

				//! Creating VBO
				glNamedBufferStorage(VBO, m_meshVertices.size(), m_meshVertices.data(), 0);

				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, VBO);

				*/
				/*
* 
				glNamedBufferStorage(VBO, m_meshVertices.size() + m_indices.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
				glNamedBufferSubData(VBO, 0, m_meshVertices.size(), m_meshVertices.data());
				glNamedBufferSubData(VBO, m_meshVertices.size(), m_indices.size(), m_indices.data());

				glVertexArrayElementBuffer(VAO, VBO);
				
				glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(m_meshVertices[0]));
				
				glEnableVertexArrayAttrib(VAO, 0);

				glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

				glEnableVertexArrayAttrib(VAO, 1);

				glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
				
				//Make all attributes read from the same buffer.
				glVertexArrayAttribBinding(VAO, 0, 0);
				glVertexArrayAttribBinding(VAO, 1, 0);

				*/
			}

			void PushToBufferVerticesIndices()
			{

			}
	};
}