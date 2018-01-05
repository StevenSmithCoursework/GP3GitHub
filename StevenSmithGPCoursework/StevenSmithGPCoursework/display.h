#pragma once

#include <string>
#include <SDL2\SDL.h>

class Display
{
public:
	Display(int windowWidth, int windowHeight, const std::string& windowName);
	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	bool IsClosed();
	void onResize(int windowWidth, int windowHeight);
	void setOrtho2D(int windowWidth, int windowHeight);
	void setProjection3D(int windowWidth, int windowHeight);
	static SDL_Renderer *renderer;
	~Display();

private:
	SDL_Window* m_Window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

