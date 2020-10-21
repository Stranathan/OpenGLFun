#pragma once

#include <glad\glad.h>

namespace Rendering
{
	struct Shape
	{
		// constructor: zero out member variables
		Shape() : vertices(0), numVertices(0), indices(0), numIndices(0), vertexColor(0), numVertexColor(0)
		{
		}

		GLfloat* vertices;
		GLuint numVertices;

		GLushort* indices;
		GLuint numIndices;

		GLfloat* vertexColor;
		GLuint numVertexColor;

		// Sizei pointer function for the sizes of the vertex and index buffer arrays
		GLsizeiptr vertexBufferSize() const
		{
			return numVertices * sizeof(GLfloat);
		}

		GLsizeiptr indexBufferSize() const
		{
			return numIndices * sizeof(GLushort);
		}

		GLsizeiptr colorBufferSize() const
		{
			return numVertexColor * sizeof(GLfloat);
		}

		void deleteShape()
		{
			delete[] vertices;
			delete[] indices;
			delete[] vertexColor;
			numVertices = numIndices = numVertexColor = 0;
		}
	};
}