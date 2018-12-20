#include "pch.h"
#include "Engine.h"


Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Draw(void)
{
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.5, -1.5, -5.0);
	glVertex3f(0.0, 1.5, -5.0);
	glVertex3f(1.5, -1.5, -5.0);
	glEnd();

	glutSwapBuffers();
}

void Engine::Reshape(int width, int height)
{
	this->window_width = width;
	this->window_height = height;

	if (height == 0)
		height = 1;
	float ratio = (float)width / (float)height;

	// --------------------------------------------- Need edit 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, ratio, 1, 10);
	glMatrixMode(GL_MODELVIEW);
}
