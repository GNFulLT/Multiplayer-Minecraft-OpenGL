#pragma once

#include <stdint.h>
#include "Common/glad_wrapper.h"

#include <cstring>
#include <iostream>
#include "Primitive/Mesh.h"
#include <glm/glm.hpp>



class Chunk : public GNF::Primitive::Mesh
{
    public:
        Chunk(int width,int height,int depth,const glm::vec3& pos);
        ~Chunk();
        float GetActualWidth()
        {
            return m_width * cubeWidth;
        }
        float GetActualHeight()
        {
            return m_height * cubeHeight;
        }

        float GetActualDepth()
        {
            return m_depth * cubeWidth;
        }

    private:

       

        void CreateBuffers();
        void UpdateBuffers();

        void GenerateChunk();

        int m_width;
        int m_height;
        int m_depth;

        int cubeWidth = 1;
        int cubeHeight = 1;

        uint8_t*** m_chunk;

        glm::vec3 worldPosition;
};

