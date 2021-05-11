#include "shaderManager.hpp"

std::map<std::string, shader> shaderManager::theShaders;


shader shaderManager::loadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
	theShaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return theShaders[name];
}

shader shaderManager::getShader(std::string name)
{
	return theShaders[name];
}

void shaderManager::clear()
{
	for (auto iter : theShaders)
		glDeleteProgram(iter.second.ID);	
}

shader shaderManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();	
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	// turn them into a char*
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	// create shader object from source code
	shader shader;
	shader.compile(vShaderCode, fShaderCode);

	return shader;
}
