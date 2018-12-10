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

void renderBitmapString(float x, float y, float z, void *font, std::string &string)
{
	glRasterPos3f(x, y, z);

	for (auto i : string)
	{
		glutBitmapCharacter(font, i);
	}
}


void changeSize(int w, int h) {

	// предупредим деление на ноль
	// если окно сильно перетянуто будет
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, w, h);

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

void renderScene(void) {

	static float angle;

	count_frame++;
	if (((GetTickCount() - time) / 1000.0) >= 1.0)
	{
		count_frame_str = "FPS: " + std::to_string(count_frame);
		time = GetTickCount();
		count_frame = 0;
	}


	glLoadIdentity();
	// установка камеры
	gluLookAt(0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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




int main(int argc, char **argv) {



	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Test_1");

	//glClearColor(1, 1, 1, 1);  //фон

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);

	// Новая функция изменения размеров окна
	glutReshapeFunc(changeSize);

	// новая функция для регистрации
	glutIdleFunc(renderScene);

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);




	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}
