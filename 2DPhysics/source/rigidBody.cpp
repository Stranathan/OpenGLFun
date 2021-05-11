#include "rigidBody.hpp"

rigidBody::rigidBody()
{
	pos = glm::vec2(0.0f, 0.0f);
	vel = glm::vec2(0.0f, 0.0f);
	accl = glm::vec2(0.0f, 0.0f);
	mass = 1.0f;

	// copy the vertices from the geometry
	unsigned int vertsArraySize = sizeof(unitTriangle) / sizeof(float);
	vertices.insert(vertices.begin(), &unitTriangle[0], &unitTriangle[vertsArraySize]);

	m_renderable = renderable(rendering::shapes::TRIANGLE, pos);
}

rigidBody::rigidBody(std::string shape, glm::vec2 position)
{
	pos = position;
	vel = glm::vec2(0.0f, 0.0f);
	accl = glm::vec2(0.0f, 0.0f);
	mass = 1.0f;

	if(shape == "triangle")
	{
		// copy the vertices from the geometry
		unsigned int vertsArraySize = sizeof(unitTriangle) / sizeof(float);
		vertices.insert(vertices.begin(), &unitTriangle[0], &unitTriangle[vertsArraySize]);

		m_renderable = renderable(rendering::shapes::TRIANGLE, pos);
	}
	else if(shape == "rectangle")
	{
		// copy the vertices from the geometry
		unsigned int vertsArraySize = sizeof(unitQuad) / sizeof(float);
		vertices.insert(vertices.begin(), &unitQuad[0], &unitQuad[vertsArraySize]);

		m_renderable = renderable(rendering::shapes::RECTANGLE, pos);
	}
	else if(shape == "circle")
	{
		// copy the vertices from the geometry
		unsigned int vertsArraySize = sizeof(unitCircle) / sizeof(float);
		vertices.insert(vertices.begin(), &unitCircle[0], &unitCircle[vertsArraySize]);

		m_renderable = renderable(rendering::shapes::CIRCLE, pos);
	}
	else
	{
		// copy the vertices from the geometry
		unsigned int vertsArraySize = sizeof(unitTriangle) / sizeof(float);
		vertices.insert(vertices.begin(), &unitTriangle[0], &unitTriangle[vertsArraySize]);

		m_renderable = renderable(rendering::shapes::TRIANGLE, pos);
	}
}
