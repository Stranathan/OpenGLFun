#pragma once

#include <iostream>
#include <vector>

#include "shader.h"
#include "geometry.h"
#include "renderable.h"
#include "resourceManager.h"

class Renderer
{
private:
	void initRenderer();

public:
	glm::vec2 viewPort;
	glm::mat4 projectionMat4;
	std::vector<Renderable> renderables;

	void render(float globalTime);
	Renderer(glm::vec2 screenDimensions);
	~Renderer();
};

