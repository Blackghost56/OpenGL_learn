#include "engine.h"

Engine *engine;

GLvoid display(GLvoid)
{
	engine->Draw();
	glutSwapBuffers();
}

GLvoid reshape(GLsizei width, GLsizei height)
{
	engine->Resize(width, height);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("2.1. Каркас OpenGL приложения c использованием GLUT. (с) compgraphics.info");
	engine = new Engine();
	engine->Init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
