#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);
	
	void BindTexture(unsigned int unit);

	~Texture();

private:
	GLuint m_texture;
};

