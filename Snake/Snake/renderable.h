#pragma once

#include <iostream>

#include "geometry.h"
#include "Shader.h"
/*
	This classallocates resources through: glGenVertexArrays(1, &this->quadVAO);
	This needs to be cleaned up

	It uses the resource managed by resourceManager (shaders, textures)
	Not responsible for those resources
*/
struct uniforms
{
	glm::vec2 resolution;
	float time;
	glm::vec3 pos;
	int index; // for offsetting sinusoidal coloring
};

enum availableGeometry
{
	unit_quad,
	circle
};

class Renderable
{
private:
public:
	Shader program;
	unsigned int vao;

	// -------------------
	availableGeometry shape;
	glm::vec2 viewPort;
	glm::mat4 model;
	GLenum primitiveType;
	int arrayedVertCount;
	uniforms m_uniforms;

	// -------------------
	void initRenderable();

	// Maybe consider rule of three or five since I am making a constructor
	Renderable(glm::mat4 transform, availableGeometry shape, GLenum drawType, Shader& shaderProgram, glm::vec2 viewPort);

	// deletes assocaited vao
	void unbind();
};

