#include "renderable.h"

Renderable::Renderable(glm::mat4 transform, availableGeometry shape, GLenum drawType, Shader& shaderProgram, glm::vec2 viewPort)
	: primitiveType(drawType)
{
	this->model = transform;
	this->program = shaderProgram; // this is sharing a resource with the resource manager, manager is responsible for deleting it
	this->shape = shape;
	this->viewPort = viewPort;
	m_uniforms.pos = glm::vec3(0.0f); // this is probably not necessary, but I'm feeding this to every shader program and wanna be safe
	m_uniforms.index = 0;
	//
	this->initRenderable();
}
void Renderable::initRenderable()
{
	if (shape == unit_quad)
	{
		unsigned int VBO;
		glGenVertexArrays(1, &this->vao);

		glGenBuffers(1, &VBO);
		glBindVertexArray(this->vao);
		/*std::cout << "This is the address of the int that is the binding point for its VAO when it was made" << std::endl;
		std::cout << &this->vao << std::endl;*/
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(unitQuadVertices), unitQuadVertices, GL_STATIC_DRAW); // feeding it an array is just a pointer to its starting address
		// configire attrib
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		this->arrayedVertCount = 6;
	}
	else if (shape == circle)
	{
		unsigned int VBO;
		float vertArray[720];
		/*std::cout << "this is the address of beginning of array originally declared" << std::endl;
		std::cout << &vertArray << std::endl;*/

		makeACircle(1.0, 80, vertArray, viewPort); 

		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &VBO);
		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertArray), vertArray, GL_STATIC_DRAW); // feeding it an array is just a pointer to its starting address
		// configire attrib
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		this->arrayedVertCount = 240;
	}
}
void Renderable::unbind()
{
	glDeleteVertexArrays(1, &vao);
}

