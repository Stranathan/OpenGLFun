#include "vaoManager.hpp"

std::map<std::string, GLuint> vaoManager::vaos;

void vaoManager::loadVAO(rendering::shapes shape)
{
	switch (shape)
	{
		case rendering::shapes::CIRCLE:
			makeACircle();
			break;
		case rendering::shapes::RECTANGLE:
			makeARectangle();
			break; 
		case rendering::shapes::TRIANGLE:
			makeATriangle();
			break;
	}
}

GLuint vaoManager::getVAO(std::string name)
{
	return vaos[name];
}

void vaoManager::makeACircle()
{
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unitCircle), unitCircle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// add vao to vao name: int map
	vaos["circle"] = VAO;

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// delete tmp gpu buffer
	glDeleteBuffers(1, &VBO);
}

void vaoManager::makeARectangle()
{
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unitQuad), unitQuad, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// add vao to vao name: int map
	vaos["rectangle"] = VAO;

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// delete tmp gpu buffer
	glDeleteBuffers(1, &VBO);
}

void vaoManager::makeATriangle()
{
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unitTriangle), unitTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// add vao to vao name: int map
	vaos["triangle"] = VAO;

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// delete tmp gpu buffer
	glDeleteBuffers(1, &VBO);
}

void vaoManager::clearAVAO(std::string name)
{
	glDeleteVertexArrays(1, &vaos[name]);
}

void vaoManager::clearAllVAOs()
{
	for (auto i : vaos)
		glDeleteVertexArrays(1, &(i.second)); // second value in key:value data
}
