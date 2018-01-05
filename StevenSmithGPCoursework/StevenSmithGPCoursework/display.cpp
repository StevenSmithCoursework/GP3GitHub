#include "display.h"
#include <GL\glew.h>
#include <iostream>
#include"SDL_ttf.h"

SDL_Renderer *Display::renderer = nullptr;


Display::Display(int windowWidth, int windowHeight, const std::string& windowName)
{
	//Initialises everything for SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Sets attributes to help with displaying colours etc
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Creates the window and context and binds the information to the relevant variable
	m_Window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_Window);

	//Initialises glew and an error check is performed
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialise" << std::endl;
	}

	renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	
	if (renderer == nullptr)
	{
		std::cerr << "Failed to create renderer" << std::endl;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "SDL_TTF failed to initialise" << std::endl;
	}

	//Sets closed to false
	m_isClosed = false;

	//Enables a depth test and face culling to help with drawing objects within the window
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearStencil(0);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
}

Display::~Display()
{
	//Clears any information that was created within the constructor
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_Window);
	TTF_Quit();
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	//Clears the display screen
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool Display::IsClosed()
{
	//Used to check the status of m_isClosed
	return m_isClosed;
}

void Display::SwapBuffers()
{
	//Swaps the buffers and checks if the window has been closed
	SDL_GL_SwapWindow(m_Window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}

void Display::onResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void Display::setOrtho2D(int windowWidth, int windowHeight)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, windowWidth, windowHeight, 0.0, 0.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display::setProjection3D(int windowWidth, int windowHeight)
{
	onResize(windowWidth, windowHeight);
}