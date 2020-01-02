#include "textureAtlas.h"
#include <iostream>
#include "..\Vendor\stb_image.h"

TextureAtlas::TextureAtlas()
	: width(0), height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_u(GL_REPEAT), Wrap_v(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->objectID);
}

void TextureAtlas::generate(char const* filename)
{
	int nrChannels;

	glBindTexture(GL_TEXTURE_2D, this->objectID);

	stbi_set_flip_vertically_on_load(true);
	this->data = stbi_load(filename, &width, &height, &nrChannels, 0);

	if (data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_u);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_v);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	
	// free up stb
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureAtlas::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->objectID);
}
