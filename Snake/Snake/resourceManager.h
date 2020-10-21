#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
//#include "texture.h"
#include "shader.h"

/*
	Static singleton resourceManager
	Each loaded texture and /or shader is also stored for future reference by string handles.
	All functions and resources are static and there is no public constructor
*/

class ResourceManager
{
private:
	// private constructor, cannot be instantiated
	ResourceManager() { }
	// loads and generates a shader from file
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
	
	// loads a single texture from file
	//static Texture2D loadTextureFromFile(const char* file, bool alpha);
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	//static std::map<std::string, Texture2D> Textures;

	// loads and creates a shader program from file
	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
	
	// retrieves a stored shader
	static Shader getShader(std::string name);

	// loads (and generates) a texture from file
	//static Texture2D LoadTexture(const char* file, bool alpha, std::string name);

	// retrieves a stored texture
	//static Texture2D GetTexture(std::string name);

	// de-allocates all loaded resources
	static void clear();
};



