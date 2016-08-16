#include "Display.h"
#include <GL/glew.h>
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	m_iWidth = width;
	m_iHeight = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_iWidth, m_iHeight, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	m_bIsClosed = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_bIsClosed = true;
		}
	}
}

bool Display::IsClosed() {
	return m_bIsClosed;
}

void Display::Clear(float r, float g, float b, float a) 
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}