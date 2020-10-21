#pragma once
#include <glad/glad.h>

class Texture
{
public:
	GLuint objectID;
	unsigned char* data;
	GLint width, height; // Loaded image in pixels
	GLuint Internal_Format; // Format of texture object
	GLuint Image_Format; // Format of loaded image

	// Texture settings
	GLuint Wrap_u; // Wrapping mode on u axis
	GLuint Wrap_v; // Wrapping mode on v axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

	// Constructor
	Texture();
	
	inline GLint getObjectID() const
	{
		return objectID;
	}

	// Generates texture & dimensions from image data
	void generate(char const* filename);

	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void bind() const;
};

