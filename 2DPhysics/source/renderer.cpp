#include "renderer.hpp"

renderer::renderer()
{
	init();
	pos = glm::vec3(0.0f, 0.0f, -1.0f);
}

renderer::renderer(glm::vec3 renderPos)
{
	init();
	pos = renderPos;
}

renderer::~renderer()
{
	shaderManager::clear();
	vaoManager::clearAllVAOs();
}

void renderer::init()
{
	// set GL state
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_MULTISAMPLE);

	// correct AR & set scale
	// set VP matrix
	view = glm::mat4(1.0f);
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::mat4(1.0f);
	projection = glm::ortho(-orthoWidth / 2.0f, orthoWidth / 2.0f,
		-orthoHeight / 2.0f, orthoHeight / 2.0f, 1.0f, 100.0f);

	// load all geometry
	// initialize vao manager
	vaoManager::loadVAO(rendering::shapes::TRIANGLE);
	vaoManager::loadVAO(rendering::shapes::RECTANGLE);
	vaoManager::loadVAO(rendering::shapes::CIRCLE);

	// load all shader programs
	// initialize shader manager
	shaderManager::loadShader("shaders/baseVert.glsl", "shaders/baseFrag.glsl", "base").use();
}

void renderer::makeATriangle()
{
	renderable aTriangle = renderable(rendering::shapes::TRIANGLE);
	renderables.push_back(aTriangle); // copies a GLuint vao, GLenum primitve type & an int vertCount, no big deal
}

void renderer::makeARectangle()
{
	renderable aRect = renderable(rendering::shapes::RECTANGLE);
	renderables.push_back(aRect); // copies a GLuint vao, GLenum primitve type & an int vertCount, no big deal
}
void renderer::makeARectangle(glm::vec2 pos)
{
	renderable aRect = renderable(rendering::shapes::RECTANGLE, pos);
	renderables.push_back(aRect); // copies a GLuint vao, GLenum primitve type & an int vertCount, no big deal
}

void renderer::makeACircle()
{
	renderable aCircle = renderable(rendering::shapes::CIRCLE);
	renderables.push_back(aCircle); // copies a GLuint vao, GLenum primitve type & an int vertCount, no big deal
}

void renderer::render(float time)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// render each vao
	for(auto& r : renderables)
	{
		shaderManager::getShader(r.programName).use();

		// go through each uniform in the renderable and set it
		for(auto& u : r.uniforms)
		{
			switch (u)
			{
			case rendering::uniforms::MODEL:
				glm::mat4 aMat4 = glm::mat4(1.0f);
				r.modelTransform = glm::translate(aMat4, glm::vec3(float(cos(time)) * orthoWidth / 2.0f, float(sin(time)) * orthoHeight / 2.0f, 0.0f));
				shaderManager::getShader(r.programName).setMatrix4("model", r.modelTransform);
				break;
			case rendering::uniforms::VIEW:
				shaderManager::getShader(r.programName).setMatrix4("view", view);
				break;
			case rendering::uniforms::PROJECTION:
				shaderManager::getShader(r.programName).setMatrix4("projection", projection);
				break;
			case rendering::uniforms::TIME:
				shaderManager::getShader(r.programName).setFloat("time", time);
				break;
			}
		}
		glBindVertexArray(r.vao);
		glDrawArrays(r.primitiveType, 0, r.vertCount);
	}
	
}