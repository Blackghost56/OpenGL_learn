// test2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "include/glut.h"
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <iostream>


float array_color[3][3] = { { 1.0, 0.0, 0.0 }, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
int	flag = 0;

DWORD time = 0;
int count_frame = 0;
std::string count_frame_str = "";
int h, w;


GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];

GLdouble wx, wy, wz;

GLfloat zval;
int flag_2 = 0;
int g_x, g_y;


void renderBitmapString(float x, float y, float z, void *font, std::string &string)
{
	glRasterPos3f(x, y, z);

	for (auto i : string)
	{
		glutBitmapCharacter(font, i);
	}
}


void changeSize(int ww, int hh) {
	
	h = hh;
	w = ww;
	// предупредим деление на ноль
	// если окно сильно перетянуто будет
	if (hh == 0)
		hh = 1;
	float ratio = 1.0* ww / hh;

	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, ww, hh);

	// установить корректную перспективу.
	gluPerspective(45, ratio, 1, 100);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);

	/*glLoadIdentity();
	// установка камеры
	gluLookAt(	0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);*/

}


void setOrthographicProjection(int w_down, int w_up, int h_down, int h_up) {
	//переключения режима проецирования
	glMatrixMode(GL_PROJECTION);
	//Сохраняем предыдущую матрицу, которая содержит
		//параметры перспективной проекции
	glPushMatrix();
	//обнуляем матрицу
	glLoadIdentity();
	//устанавливаем 2D ортогональную проекцию
	gluOrtho2D(w_down, w_up, h_down, h_up);
	// возврата в режим обзора модели
	glMatrixMode(GL_MODELVIEW);
}


void restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	//восстановить предыдущую матрицу проекции
	glPopMatrix();
	//вернуться в режим модели
	glMatrixMode(GL_MODELVIEW);
}

GLfloat Quad_Coords[] = {
	1.0f, 0.0f,		// Нижний левый угол 
	2.0f, 0.0f,		// Нижний правый угол
	2.0f, 1.0f,		// Верхний правый угол 
	1.0f, 1.0f		// Верхний левый угол
};

void renderScene(void) {

	static float angle;

	glLoadIdentity();

	// установка камеры
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);	
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0);
	glVertex3f(2.0, 1.0, 0);
	glVertex3f(1.0, 1.0, 0);
	glEnd();

	/*
	std::string start_str = "Start";

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(1.5, 0.5, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, start_str);		//Start
	*/
	
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3fv(array_color[flag]);
	glVertex3f(-0.5, -0.5, 0);
	glColor3fv(array_color[(flag + 1) % 3]);
	glVertex3f(0.0, 0.5, 0);
	glColor3fv(array_color[(flag + 2) % 3]);
	glVertex3f(0.5, -0.5, 0);
	glEnd();
	

	// ------------------------------------
	setOrthographicProjection(-1, 1, -1, 1); 
	glPushMatrix();
	glLoadIdentity();

	if (flag_2 == 1)
	{	
		flag_2 = 0;
		GLfloat zv = 0;

		glReadPixels(g_x, g_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zv);

		std::cout << "x= " + std::to_string(g_x) + "   y= " + std::to_string(g_y) + "   z= " + std::to_string(zv) + "\t\t\t window" << std::endl;

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		gluUnProject(g_x, g_y, zv, modelview, projection, viewport, &wx, &wy, &wz);
		std::cout << "x= " + std::to_string(wx) + "   y= " + std::to_string(wy) + "   z= " + std::to_string(wz) + "\t windows to global" << std::endl;

		gluProject(wx, wy, wz, modelview, projection, viewport, &wx, &wy, &wz);
		std::cout << "x= " + std::to_string(wx) + "   y= " + std::to_string(wy) + "   z= " + std::to_string(wz) + "\t global to windows" << std::endl;	
		std::cout << "___________________________________________________________" << std::endl;
	}

	glPopMatrix();
	restorePerspectiveProjection(); 
	//-----------------------------------

	angle += 0.1f;

	if (angle >= 360.0)
	{
		angle = 0.0;
	}

		
	// FPS --------------
	DWORD delta_t_s = (GetTickCount() - time) / 1000.0;

	count_frame++;
	if (delta_t_s >= 1.0)
	{
		count_frame_str = "FPS: " + std::to_string((double)count_frame / delta_t_s);
		time = GetTickCount();
		count_frame = 0;
	}
	setOrthographicProjection(0, w, 0, h); 
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(10.0, 10.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, count_frame_str);		//FPS
	glPopMatrix();
	restorePerspectiveProjection();
	// --------------

	

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}


void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		flag = 0;
		break;
	case GLUT_KEY_F2:
		flag = 1;
		break;
	case GLUT_KEY_F3:
		flag = 2;
		break;
	}
}


void mouseButton(int button, int state, int x, int y) {
 
	// только при начале движения, если нажата левая кнопка
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			//count_frame_str = "x= " + std::to_string(x) + "   y= " + std::to_string(y);
			
			flag_2 = 1;
			g_x = x;
			g_y = y;
			
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {

			
		}
	}
}


void Timer(int)
{

	glutPostRedisplay();
	glutTimerFunc(40, Timer, 0);
}


int main(int argc, char **argv) {

	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(800, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_2");

	//glClearColor(1, 1, 1, 1);  //фон

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);

	// Новая функция изменения размеров окна
	glutReshapeFunc(changeSize);

	// новая функция для регистрации
	glutIdleFunc(renderScene);

	//glutTimerFunc(40, Timer, 0);//анимация таймер ф-я нужна в милисек.

	// Keyboard
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// Mouse
	glutMouseFunc(mouseButton);


	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}
