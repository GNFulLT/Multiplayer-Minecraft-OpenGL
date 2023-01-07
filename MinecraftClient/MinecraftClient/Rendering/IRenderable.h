#pragma once


#include "glad/glad.h"


namespace GNF::Rendering
{
	class IRenderable
	{
		public:
			virtual ~IRenderable() = default;
			virtual void BindVAO()
			{
				glBindVertexArray(VAO);
				
				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, VBO);
			}
	
		protected:
			GLuint VBO;
			GLuint VAO;
			GLuint EBO;
	};
}