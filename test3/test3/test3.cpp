// test3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Engine.h"

#include <iostream>

Engine *engine;

void reshape(int width, int height)
{
	engine->Reshape(width, height);
}


void render(void)
{
	engine->Draw();
}


int main(int argc, char** argv)
{
	engine = new Engine();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(800, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_3");
	
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}


