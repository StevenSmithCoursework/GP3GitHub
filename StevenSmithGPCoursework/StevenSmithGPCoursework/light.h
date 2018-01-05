#pragma once

#include "glm\glm.hpp"
#include "GL\glew.h"

struct lightColour4
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha
};

class light
{
public:
	light();
	light(GLenum lightID, lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, glm::vec4 position, glm::vec3 spotDirection
		, GLfloat  spotExponent, GLfloat  spotCutoff, GLfloat  constantAttenuation, GLfloat  linearAttenuation, GLfloat  quadraticAttenuation);
	~light();

	void lightOn();
	void lightOff();

private:

	GLenum m_LightID;
	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;

	glm::vec4 m_Position;
	glm::vec3 m_SpotDirection;

	GLfloat  m_SpotExponent;
	GLfloat  m_SpotCutoff;
	GLfloat  m_ConstantAttenuation;
	GLfloat  m_LinearAttenuation;
	GLfloat  m_QuadraticAttenuation;
};

