#include "geometry.h"

/*
	Notes:
		Unless you have a transform that maps screen dimensions to cannonical view volume, you need to account for the aspect ratio
*/

// length of array = numSides * 3 verts per tri * 3 floats per tri
void makeACircle(float radius, int numSides, float(&vertArr)[720], glm::vec2 viewPort)
{
	/*std::cout << "this is the address of beginning of array being modifed in makeACircle" << std::endl;
	std::cout << &vertArr << std::endl;*/

	float ar = viewPort.x / viewPort.y;
	float theta = 0.0f;
	float deltaTheta = 2.0f * PI / numSides;

	int j = 0;
	for (int i = 0; i < numSides; i++)
	{
		float x1 = 0.0f;
		float y1 = 0.0f;
		float z1 = 0.0f;

		float x2 = radius * cosf(theta);
		//float y2 = radius * sinf(theta) * ar;
		float y2 = radius * sinf(theta);
		float z2 = 0.0f;

		float x3 = radius * cosf(theta + deltaTheta) ;
		//float y3 = radius * sinf(theta + deltaTheta) * ar;
		float y3 = radius * sinf(theta + deltaTheta);
		float z3 = 0.0f;

		vertArr[j + 0] = x1;
		vertArr[j + 1] = y1;
		vertArr[j + 2] = z1;

		vertArr[j + 3] = x2;
		vertArr[j + 4] = y2;
		vertArr[j + 5] = z2;

		vertArr[j + 6] = x3;
		vertArr[j + 7] = y3;
		vertArr[j + 8] = z3;

		j += 9;
		theta += deltaTheta;
	}
}
