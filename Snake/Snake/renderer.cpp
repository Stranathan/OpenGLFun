#include "renderer.h"

/*
	Renderer: This is just something that will run through a a dynamic list of renderables
*/
/*
*/
Renderer::Renderer(glm::vec2 screenDimensions)
	: viewPort(screenDimensions),
	  projectionMat4(glm::ortho(-screenDimensions.x / 2.0f, screenDimensions.x / 2.0f, -screenDimensions.y / 2.0f, screenDimensions.y / 2.0f, -1.0f, 1.0f))
{
	this->initRenderer();
}

Renderer::~Renderer()
{
	// for each renderable, delete its assocaited vao
	for (auto renderable : renderables)
		renderable.unbind();
}

void Renderer::render(float globalTime)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); // not using DEPTH_BUFFER_BIT

	if (renderables.size() != 0)
	{
		for (int i = 0; i < renderables.size(); i++)
		{
			glBindVertexArray(renderables[i].vao);
			renderables[i].program.Use();

			renderables[i].program.setMatrix4("model", renderables[i].model);
			renderables[i].program.setMatrix4("projection", projectionMat4);
			renderables[i].program.setFloat("time", globalTime);
			renderables[i].program.setInteger("linkIndex", renderables[i].m_uniforms.index);
			renderables[i].program.setVector2f("resolution", renderables[i].viewPort);
			renderables[i].program.setVector3f("pos", renderables[i].m_uniforms.pos);

			
			glDrawArrays(renderables[i].primitiveType, 0, renderables[i].arrayedVertCount);
		}
	}
}
void Renderer::initRenderer()
{
	// ----------- Init OpenGL State -----------
	glViewport(0, 0, viewPort.x, viewPort.y);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ----------- Make all the Shaders -----------
	ResourceManager::loadShader("shaders/foodVert.glsl", "shaders/foodFrag.glsl", "food");
	ResourceManager::loadShader("shaders/snakeBodyVert.glsl", "shaders/snakeBodyFrag.glsl", "snakeBody");
	ResourceManager::loadShader("shaders/snakeHeadVert.glsl", "shaders/snakeHeadFrag.glsl", "snakeHead");
	ResourceManager::loadShader("shaders/helloVert.glsl", "shaders/helloFrag.glsl", "background");

	// ----------- Get Shaders for Renderable -----------
	Shader backgroundShader = ResourceManager::getShader("background");
	// ----------- Background doesn't transform -----------
	glm::mat4 unitQuadModel = glm::mat4(1.0f);
	// ----------- Make the background renderable and add to draw queue -----------
	Renderable background(unitQuadModel, unit_quad, GL_TRIANGLES, backgroundShader, viewPort);
	{
		// ----------- Put it onto draw queue -----------
		// 1) std::vector.push_back(object) -- by value, copy

		// 2) std::vector.emplace_back((object)); emplace back is equivalent to push_back(Type&& _value)
		//    renderables.emplace_back(model, unit_quad, GL_TRIANGLES, aShader, viewPort);

		// 3) std::vector.push_back(std::move(object));
	}
	renderables.push_back(std::move(background));
}

