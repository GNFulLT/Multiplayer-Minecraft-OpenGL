#include "Cube.h"


namespace GNF::Primitive
{
	Cube::Cube(float width, float height, const glm::vec3& worldPos)
	{
		



		AddVertex({ (worldPos.x - width / 2),(worldPos.y + width / 2),(worldPos.z + width / 2)},{0.f,1.f}); // Back Top Left                  0
		AddVertex({ (worldPos.x + width / 2),(worldPos.y + width / 2),(worldPos.z + width / 2)}, { 1.f,1.f }); // Back Top Right             1
		AddVertex({ (worldPos.x + width / 2),(worldPos.y - width / 2),(worldPos.z + width / 2)}, { 1.f,0.f }); // Back Bottom Right         2
		AddVertex({ (worldPos.x - width / 2),(worldPos.y - width / 2),(worldPos.z + width / 2)}, { 0.f,0.f }); // Back Bottom Left         3

		AddVertex({ (worldPos.x - width / 2),(worldPos.y + width / 2),(worldPos.z - width / 2)}, { 1.f,1.f }); // Front Top Left           4 
		AddVertex({ (worldPos.x + width / 2),(worldPos.y + width / 2),(worldPos.z - width / 2) }, { 0.f,1.f }); // Front Top Right           5
		AddVertex({ (worldPos.x + width / 2),(worldPos.y - width / 2),(worldPos.z - width / 2) }, { 0.f,0.f }); // Front Bottom Right       6
 		AddVertex({ (worldPos.x - width / 2),(worldPos.y - width / 2),(worldPos.z - width / 2) }, { 1.f,0.f }); // Front Bottom Left       7


		//For Up
		AddVertex({ (worldPos.x - width / 2),(worldPos.y + width / 2),(worldPos.z - width / 2) }, { 0.f,0.f }); // Bottom Left 8
		AddVertex({ (worldPos.x - width / 2),(worldPos.y + width / 2),(worldPos.z + width / 2) }, { 0.f,1.f }); //  Top Left  9
		AddVertex({ (worldPos.x + width / 2),(worldPos.y + width / 2),(worldPos.z + width / 2) }, { 1.f,1.f }); // Top Right 10
		AddVertex({ (worldPos.x + width / 2),(worldPos.y + width / 2),(worldPos.z - width / 2) }, { 1.f,0.f }); // Bottom Right 11
		//Fot Bottom
		AddVertex({ (worldPos.x - width / 2),(worldPos.y - width / 2),(worldPos.z + width / 2) }, { 0.f,0.f }); // Bottom Left  12
		AddVertex({ (worldPos.x - width / 2),(worldPos.y - width / 2),(worldPos.z - width / 2) }, { 0.f,1.f }); // Top Left 13
		AddVertex({ (worldPos.x + width / 2),(worldPos.y - width / 2),(worldPos.z - width / 2) }, { 1.f,1.f }); // Top Right 14
		AddVertex({ (worldPos.x + width / 2),(worldPos.y - width / 2),(worldPos.z + width / 2) }, { 1.f,0.f }); // Bottom Right 15



		//Front Face
		AddTriangle({ 0,1,3 });          
		AddTriangle({ 3,1,2 });

		//Back Face
		AddTriangle({ 7,6,5 });
		AddTriangle({ 7,5,4 });

		//Left Face
		AddTriangle({ 4,0,7 });
		AddTriangle({ 0,7,3 });

		//Right Face
		AddTriangle({ 1,5,2 });
		AddTriangle({ 2,5,6 });
		//Up Face
		AddTriangle({ 8,9,10 });
		AddTriangle({ 8,10,11 });
		//Down Face
		AddTriangle({ 12,13,14 });
		AddTriangle({ 12,14,15 });


		CreateBuffer();
	}

}