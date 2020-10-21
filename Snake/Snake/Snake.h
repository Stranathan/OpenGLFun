#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "renderable.h"
#include "Shader.h"
#include "resourceManager.h"
#include <ctime>
#include <stdlib.h>

/*
	I'm sure it's not the greatest design choice, but the snakes positions correspond to the renderables 1:1 with an offset of one.
	so renderables[1, 2... ] == positions[0, 1, 2..]
	positions will multiply a translation matrix into the model of each renderable
*/
/*
	Just rolling with the scaling: x live in [-25.0f, 25.0f] & y live in [-20.0f, 20.0f]
*/
class Snake
{
private:
	float radius = 1.0f;
	float speed = 10.0f;
	int baseLength = 5; 
public:

	int lastRenderableIndex = 0; // 
	std::vector<glm::vec4> positions; // positions of the circles
	glm::vec3 velocity;
	//
	Snake(std::vector<Renderable>& renderersRenderables, glm::vec2 viewPort);
	glm::vec2 screenDimensions; // viewport for correcting AR
	//
	void init(std::vector<Renderable>& renderersRenderables);
	void update(float deltaTime, std::vector<Renderable>& renderersRenderables);
	void reset();
	void makeNewBodyLink(std::vector<Renderable>& renderersRenderables);
	//
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	//
	void eat();
};

