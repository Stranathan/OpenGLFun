#pragma once
#include <math.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define PI (3.14159265)

static float unitQuadVertices[] =
{
	// 0, 1, 2,
	// 0, 2, 3,
	-1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	+1.0f, -1.0f, 0.0f,

	-1.0f,  1.0f, 0.0f,
	+1.0f, -1.0f, 0.0f,
	+1.0f,  1.0f, 0.0f,
};

void makeACircle(float radius, int numSides, float(&vertArr)[720], glm::vec2 viewPort);
