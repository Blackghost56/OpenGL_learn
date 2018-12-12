// test2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "include/glut.h"
#include <stdlib.h>
#include <Windows.h>
#include <string>


float array_color[3][3] = { { 1.0, 0.0, 0.0 }, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
int	flag = 0;

DWORD time = 0;
int count_frame = 0;
std::string count_frame_str = "";
int h, w;


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
	gluPerspective(45, ratio, 1, 1000);

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);

	/*glLoadIdentity();
	// установка камеры
	gluLookAt(	0.0f, 0.0f, 5.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);*/

}


void setOrthographicProjection() {
	//переключения режима проецирования
	glMatrixMode(GL_PROJECTION);
	//Сохраняем предыдущую матрицу, которая содержит
		//параметры перспективной проекции
	glPushMatrix();
	//обнуляем матрицу
	glLoadIdentity();
	//устанавливаем 2D ортографическую проекцию
	gluOrtho2D(0, w, 0, h);
	//перевернём ось y, положительное направление вниз
	glScalef(1, -1, 1);
	// Движение происходит из левого нижнего угла
	// В верхний левый угол
	glTranslatef(0, -h, 0);
	// возврата в режим обзора модели
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	static float angle;

	// FPS
	count_frame++;
	if (((GetTickCount() - time) / 1000.0) >= 1.0)
	{
		count_frame_str = "FPS: " + std::to_string(count_frame);
		time = GetTickCount();
		count_frame = 0;
	}
	// --------------


	glLoadIdentity();
	// установка камеры
	gluLookAt(0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);


	glRotatef(0.0, 0.0f, 1.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.0, 0.0, 0.0);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(2.0, 0.0, 0);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(2.0, 1.0, 0);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.0, 1.0, 0);

	glEnd();

	std::string start_str = "Start";

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(1.5, 0.5, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, start_str);		//Start


	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

	//glColor3f(1.0, 0.0, 0.0);		// red
	glColor3fv(array_color[flag]);
	glVertex3f(-0.5, -0.5, 0);

	//glColor3f(0.0, 1.0, 0.0);		// green
	glColor3fv(array_color[(flag + 1) % 3]);
	glVertex3f(0.0, 0.5, 0);

	//glColor3f(0.0, 0.0, 1.0);		// blue
	glColor3fv(array_color[(flag + 2) % 3]);
	glVertex3f(0.5, -0.5, 0);

	glEnd();


	angle += 0.1f;

	if (angle >= 360.0)
	{
		angle = 0.0;
	}


	renderBitmapString(0.0, -1.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_10, count_frame_str);		//FPS

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
 
		// когда кнопка отпущена
		if (state == GLUT_DOWN) {
			count_frame_str = "x= " + std::to_string(x) + "   y= " + std::to_string(y);
		}
	}
}


int main(int argc, char **argv) {



	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_2");

	//glClearColor(1, 1, 1, 1);  //фон

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);

	// Новая функция изменения размеров окна
	glutReshapeFunc(changeSize);

	// новая функция для регистрации
	glutIdleFunc(renderScene);

	// Keyboard
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// Mouse
	glutMouseFunc(mouseButton);


	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}
