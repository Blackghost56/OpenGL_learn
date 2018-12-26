// test3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Engine.h"

#include <iostream>

#define	FRAME_TIME_MS 40

//Engine engi;
//Engine *engine = &engi;
//Engine *engine;
Engine *engine = new Engine();


void reshape(int width, int height)
{
	engine->Reshape(width, height);
}


void render(void)
{
	engine->Draw();
}

void timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME_MS, timer, val);
}

void foo(void)
{
	static int count = 0;
	count++;
	std::cout << "Click foo main#" << count << std::endl;
}

void mouseButton(int button, int state, int x, int y)
{
	engine->MouseFunc(button, state, x, y, &foo);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(800, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_3");
	//engine = new Engine();
	engine->Init();
	//engine->Light();

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	//glutIdleFunc(render);
	glutTimerFunc(FRAME_TIME_MS, timer, 0);

	glutMouseFunc(mouseButton);

	glutMainLoop();

	return 0;
}


