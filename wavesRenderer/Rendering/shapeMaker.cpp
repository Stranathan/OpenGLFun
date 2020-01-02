#include "shapeMaker.hpp"

Rendering::Shape Rendering::ShapeMaker::makeRectangle(glm::vec2 size, glm::vec4 color)
{
	Shape tempShape;

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat vertices[] =
	{
		0, 0, 0,			// 0
		0, size.y, 0,		// 1
		size.x, size.y, 0,	// 2
		size.x, 0, 0		// 3
	};

	GLfloat vertexColors[] =
	{
		color.x, color.y, color.z, color.w, // 0
		color.x, color.y, color.z, color.w, // 1
		color.x, color.y, color.z, color.w, // 2
		color.x, color.y, color.z, color.w  // 3
	};

	// VERTICES
	tempShape.numVertices = sizeof(vertices) / sizeof(*vertices); // total memory/ first element of array -- nice trick
	tempShape.vertices = new GLfloat[tempShape.numVertices];
	memcpy(tempShape.vertices, vertices, sizeof(GLfloat)); // destination, source, size

	// INDICES
	tempShape.numIndices = sizeof(indices) / sizeof(*indices); // total memory/ first element of array -- nice trick
	tempShape.indices = new GLushort[tempShape.numIndices];
	memcpy(tempShape.indices, indices, sizeof(indices)); // destination, source, size

	// COLOR
	tempShape.numVertexColor = sizeof(vertexColors) / sizeof(*vertexColors); // total memory/ first element of array -- nice trick
	tempShape.vertexColor = new GLfloat[tempShape.numVertexColor];
	memcpy(tempShape.vertexColor, vertexColors, sizeof(vertexColors)); // destination, source, size

	return tempShape;
}

Rendering::Shape Rendering::ShapeMaker::makeSolidCircle(glm::vec4 color)
{
	Shape tempShape;

	// literally implemented triangle fan hand by hand... fuaock me
	GLushort indices[] =
	{
		1,   0,  2,
		2,   0,  3,
		3,	 0,  4,
		4,	 0,  5,
		5,	 0,  6,
		6,	 0,  7,
		7,	 0,  8,
		8,	 0,  9,
		9,   0,  10,
	   10,   0,  11,
	   11,	 0,  12,
	   12,	 0,  13,
	   13,   0,  14,
	   14,	 0,  15,
	   15,	 0,  16,
	   16,   0,  17,
	   17,	 0,  18,
	   18,	 0,  19,
	   19,   0,  20,
	   20,	 0,  21,
	   21,	 0,  22,
	   22,   0,  23,
	   23,	 0,  24,
	   24,	 0,  1
	};

	GLfloat vertices[] =
	{
		0,		0,		0,
		0.5,	0.0,	0,
		0.485,	0.121,	0,
		0.438,	0.241,	0,
		0.354,	0.354,	0,
		0.248,	0.434,	0,
		0.121,	0.4851,	0,
		0.0,	0.5,	0, // QUADRANT 1
	   -0.121,	0.4851, 0,
	   -0.248,	0.434,  0,
	   -0.354,	0.354,  0,
	   -0.438,	0.241,  0,
	   -0.485,	0.121,  0,
	   -0.5,	0.0,	0, // QUADRANT 1
	   -0.485, -0.121,	0,
	   -0.438, -0.241,	0,
	   -0.354, -0.354,	0,
	   -0.248, -0.434,	0,
	   -0.121, -0.4851,	0,
		0.0,   -0.5,	0, // QUADRANT 3
		0.121, -0.4851, 0,
		0.248, -0.434,  0,
		0.354, -0.354,  0,
		0.438, -0.241,  0,
		0.485, -0.121,  0,
		//0.5,    0,		0
	};

	GLfloat vertexColors[] =
	{
		color.x, color.y, color.z, color.w, // 0
		color.x, color.y, color.z, color.w, // 1
		color.x, color.y, color.z, color.w, // 2
		color.x, color.y, color.z, color.w, // 3
		color.x, color.y, color.z, color.w, // 4
		color.x, color.y, color.z, color.w, // 5
		color.x, color.y, color.z, color.w, // 6
		color.x, color.y, color.z, color.w, // 7
		color.x, color.y, color.z, color.w, // 8
		color.x, color.y, color.z, color.w, // 9
		color.x, color.y, color.z, color.w, // 10
		color.x, color.y, color.z, color.w, // 11
		color.x, color.y, color.z, color.w, // 12
		color.x, color.y, color.z, color.w, // 13
		color.x, color.y, color.z, color.w, // 14
		color.x, color.y, color.z, color.w, // 15
		color.x, color.y, color.z, color.w, // 16
		color.x, color.y, color.z, color.w, // 17
		color.x, color.y, color.z, color.w, // 18
		color.x, color.y, color.z, color.w, // 19
		color.x, color.y, color.z, color.w, // 20
		color.x, color.y, color.z, color.w, // 21
		color.x, color.y, color.z, color.w, // 22
		color.x, color.y, color.z, color.w, // 23
		color.x, color.y, color.z, color.w, // 24
		color.x, color.y, color.z, color.w, // 25
	};

	// VERTICES
	tempShape.numVertices = sizeof(vertices) / sizeof(*vertices); // total memory/ first element of array -- nice trick
	tempShape.vertices = new GLfloat[tempShape.numVertices];
	memcpy(tempShape.vertices, vertices, sizeof(vertices)); // destination, source, size

	// INDICES
	tempShape.numIndices = sizeof(indices) / sizeof(*indices); // total memory/ first element of array -- nice trick
	tempShape.indices = new GLushort[tempShape.numIndices];
	memcpy(tempShape.indices, indices, sizeof(indices)); // destination, source, size

	// COLOR
	tempShape.numVertexColor = sizeof(vertexColors) / sizeof(*vertexColors); // total memory/ first element of array -- nice trick
	tempShape.vertexColor = new GLfloat[tempShape.numVertexColor];
	memcpy(tempShape.vertexColor, vertexColors, sizeof(vertexColors)); // destination, source, size

	return tempShape;
}

Rendering::Shape Rendering::ShapeMaker::makeVerticalLine(glm::vec4 color)
{
	Shape tempShape;

	GLushort indices[] =
	{
		0, 1
	};

	GLfloat verticalLineVertices[] =
	{
		// positions     // colors
		-1.05f, +1.05f,  0.65f, 1.0f, 1.0f,
		-1.05f, -1.05f,  0.05f, 0.1f, 1.0f,
	};

	GLfloat vertexColors[] =
	{
		color.x, color.y, color.z, color.w, // 0
		color.x, color.y, color.z, color.w, // 1
	};

	// VERTICES
	tempShape.numVertices = sizeof(verticalLineVertices) / sizeof(*verticalLineVertices); // total memory/ first element of array -- nice trick
	tempShape.vertices = new GLfloat[tempShape.numVertices];
	memcpy(tempShape.vertices, verticalLineVertices, sizeof(verticalLineVertices)); // destination, source, size

	// INDICES
	tempShape.numIndices = sizeof(indices) / sizeof(*indices); // total memory/ first element of array -- nice trick
	tempShape.indices = new GLushort[tempShape.numIndices];
	memcpy(tempShape.indices, indices, sizeof(indices)); // destination, source, size

	// COLOR
	tempShape.numVertexColor = sizeof(vertexColors) / sizeof(*vertexColors); // total memory/ first element of array -- nice trick
	tempShape.vertexColor = new GLfloat[tempShape.numVertexColor];
	memcpy(tempShape.vertexColor, vertexColors, sizeof(vertexColors)); // destination, source, size

	return tempShape;
}
