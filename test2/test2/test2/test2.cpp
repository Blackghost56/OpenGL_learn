// test2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "include/glut.h"
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>


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
GLdouble wx_1, wy_1, wz_1;

GLfloat zval;
int flag_2 = 0;
int g_x, g_y;

GLfloat zv = 0;

std::string s_1, s_2, s_3, s_4;
//std::vector<std::string> str;


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
	gluPerspective(45, ratio, 1, 10);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);

	/*glLoadIdentity();
	// установка камеры
	gluLookAt(	0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);*/

}


void setOrthographicProjection3D(int left, int right, int bottom, int top, int o_near, int o_far) {
	//переключения режима проецирования
	glMatrixMode(GL_PROJECTION);
	//Сохраняем предыдущую матрицу, которая содержит
	//параметры перспективной проекции
	glPushMatrix();
	//обнуляем матрицу
	glLoadIdentity();
	//устанавливаем 2D ортогональную проекцию
	glOrtho(left, right, bottom, top, o_near, o_far);
	// возврата в режим обзора модели
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection2D(int w_down, int w_up, int h_down, int h_up) {
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

GLfloat cord_q[] = {
	0.0, 0.0, 
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0
};


void renderScene(void) {

	

	static float angle;

	glLoadIdentity();
	

	// установка камеры
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glPushMatrix();
	//glLoadIdentity();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(1.0, 0.0, 0.0);
	glVertexPointer(2, GL_FLOAT, 0, cord_q);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POLYGON, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	/*glBegin(GL_QUADS);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0);
	glVertex3f(2.0, 1.0, 0);
	glVertex3f(1.0, 1.0, 0);
	glEnd();*/
	glPopMatrix();


	//glRotatef(angle, 0.0f, 1.0f, 0.0f);
	/*
	glBegin(GL_TRIANGLES);
	glColor3fv(array_color[flag]);
	glVertex3f(-0.5, -0.5, 0);
	glColor3fv(array_color[(flag + 1) % 3]);
	glVertex3f(0.0, 0.5, 0);
	glColor3fv(array_color[(flag + 2) % 3]);
	glVertex3f(0.5, -0.5, 0);
	glEnd();
	*/

	
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.5, 0.7, 0.5);
	glTranslated(0.0, -0.5, 0.0);
	//glutWireCone(1, 1, 20, 1);
	glutSolidCone(0.5, 1.5, 40, 1);
	
	
	//glFlush();

	// Cord 
	//setOrthographicProjection2D(-1, 1, -1, 1); 
	setOrthographicProjection3D(-1, 1, -1, 1, 0, -1);
	glPushMatrix();
	glLoadIdentity();
	//glScalef(1, -1, 1);

	glReadPixels(g_x, h - g_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zv);
	
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	gluUnProject(g_x, g_y, zv, modelview, projection, viewport, &wx, &wy, &wz);
	gluProject(wx, wy, wz, modelview, projection, viewport, &wx_1, &wy_1, &wz_1);
	glPopMatrix();
	restorePerspectiveProjection();

	s_1 = "x= " + std::to_string(g_x) + "   y= " + std::to_string(g_y) + "   z= " + std::to_string(zv) + "\t\t\t window\n";
	s_2 = "x= " + std::to_string(wx) + "   y= " + std::to_string(wy) + "   z= " + std::to_string(wz) + "\t windows to global\n";
	s_3 = "x= " + std::to_string(wx_1) + "   y= " + std::to_string(wy_1) + "   z= " + std::to_string(wz_1) + "\t global to windows\n";
	s_4 = std::to_string(zv);
	// --------------


	
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
	// --------------

	// Text out
	setOrthographicProjection2D(0, w, 0, h);
	glPushMatrix();
	glLoadIdentity();
	
	renderBitmapString(10.0, 10.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, count_frame_str);		//FPS
	renderBitmapString(10.0, 25.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, s_3);
	renderBitmapString(10.0, 40.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, s_2);
	renderBitmapString(10.0, 55.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, s_1);
	renderBitmapString(10.0, 70.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, s_4);

	glPopMatrix();
	restorePerspectiveProjection();
	// --------------

	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) 
{
	if (key == 27)
		exit(0);
}


void processSpecialKeys(int key, int x, int y) 
{
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


void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {

		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {

		}
	}
}

void mouse(int x, int y)
{
	g_x = x;
	g_y = y;
}


void Timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(40, Timer, 0);
}

float ambient[] = { 0.3, 0.3, 0.3, 1.0 };
float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
float black[] = { 0.0, 0.0, 0.0, 1.0 };
float lpos[] = { 0.0, 0.0 , 1.0, 0.0 };

int main(int argc, char **argv) {

	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(800, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_2");

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);

	// Новая функция изменения размеров окна
	glutReshapeFunc(changeSize);

	// новая функция для регистрации
	glutIdleFunc(renderScene);

	//glutTimerFunc(40, Timer, 0);//анимация таймер ф-я нужна в милисек.

	//фон
	glClearColor(1, 1, 1, 1);

	// Освещение
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//один источник света
	/*glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);//убираем рассеянный свет
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);//тусклый рассеянный свет
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);//диффузный белый 
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);//расположен в точке lpos
	glEnable(GL_COLOR_MATERIAL);//освещаем окрашенный предмет без текстур
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);//спереди и сзади, ведь предмет анимированый, потом указываем, что свет и диффузный и рассеянный
	*/
	// Keyboard
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// Mouse
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouse);


	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}