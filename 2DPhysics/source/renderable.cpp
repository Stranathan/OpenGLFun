#include "renderable.hpp"

renderable::renderable()
{
	primitiveType = GL_TRIANGLES;
	programName = "base";
	modelTransform = glm::mat4(1.0f);
	//modelTransform = glm::scale(modelTransform, glm::vec3(0.5f, 0.5f, 0.5f));
	uniforms.push_back(rendering::uniforms::MODEL);
	uniforms.push_back(rendering::uniforms::VIEW);
	uniforms.push_back(rendering::uniforms::PROJECTION);

	vertCount = 3;
	vao = vaoManager::getVAO("triangle");
}

renderable::renderable(rendering::shapes shape)
{
	primitiveType = GL_TRIANGLES;
	programName = "base";
	modelTransform = glm::mat4(1.0f);
	//modelTransform = glm::scale(modelTransform, glm::vec3(0.5f, 0.5f, 0.5f));
	uniforms.push_back(rendering::uniforms::MODEL);
	uniforms.push_back(rendering::uniforms::VIEW);
	uniforms.push_back(rendering::uniforms::PROJECTION);

	switch (shape)
	{
	case rendering::shapes::CIRCLE:
		vertCount = 16 * 3;
		vao = vaoManager::getVAO("circle");
		break;
	case rendering::shapes::RECTANGLE:
		vertCount = 6;
		vao = vaoManager::getVAO("rectangle");
		break;
	case rendering::shapes::TRIANGLE:
		vertCount = 3;
		vao = vaoManager::getVAO("triangle");
		break;
	default:
		vertCount = 3;
		vao = vaoManager::getVAO("triangle");
		break;
	}
}

renderable::renderable(rendering::shapes shape, glm::vec2 aPos)
{
	primitiveType = GL_TRIANGLES;
	programName = "base";
	modelTransform = glm::mat4(1.0f);
	modelTransform = glm::translate(modelTransform, glm::vec3(aPos, 0.0f));
	uniforms.push_back(rendering::uniforms::MODEL);
	uniforms.push_back(rendering::uniforms::VIEW);
	uniforms.push_back(rendering::uniforms::PROJECTION);
	uniforms.push_back(rendering::uniforms::TIME);

	switch (shape)
	{
	case rendering::shapes::CIRCLE:
		vertCount = 16 * 3;
		vao = vaoManager::getVAO("circle");
		break;
	case rendering::shapes::RECTANGLE:
		vertCount = 6;
		vao = vaoManager::getVAO("rectangle");
		break;
	case rendering::shapes::TRIANGLE:
		vertCount = 3;
		vao = vaoManager::getVAO("triangle");
		break;
	default:
		vertCount = 3;
		vao = vaoManager::getVAO("triangle");
		break;
	}
}


