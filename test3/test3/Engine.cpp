#include "pch.h"
#include "Engine.h"

CButton *button_1 = new CButton(0, 0, 200, 100, "Text 1\n");


Engine::Engine()
{
	this->window_width = 0;
	this->window_height = 0;
}


Engine::~Engine()
{
}

int Engine::getWindow_width(void)
{
	return window_width;
}

int Engine::getWindow_height(void)
{
	return window_height;
}

void Engine::Draw(void)
{
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.5, -1.5, -5.0);
	glVertex3f(0.0, 1.5, -5.0);
	glVertex3f(1.5, -1.5, -5.0);
	glEnd();

	button_1->Draw();

	glutSwapBuffers();
}

void Engine::Reshape(int width, int height)
{
	this->window_width = width;
	this->window_height = height;

	if (height == 0)
		height = 1;
	float ratio = (float)width / (float)height;

	glViewport(0, 0, width, height);

	// ----------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 10);
	glMatrixMode(GL_MODELVIEW);
}

void Engine::Init(void)
{
	glClearColor(0.2f, 0.5f, 0.75f, 1.0f);				// Фон

	glClearDepth(1.0f);									// Значение для заполнения буфера глубины по умолчанию
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								// Режим работы буфера глубины

	glShadeModel(GL_SMOOTH);							// Плавное затенение
	glEnable(GL_LINE_SMOOTH);							// Сглаживание линий
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);				// Режим сглаживания для линий, GL_NICEST - макс. качество
	glEnable(GL_BLEND);									// Смешение цветов, необходимое для работы сглаживания
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Способ смешения

	
	//button_1->setColor(1.0, 1.0, 1.0);
}

void Engine::Light(void)
{
	float ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float black[] = { 0.0, 0.0, 0.0, 1.0 };
	float lpos[] = { 0.0, 0.0 , 1.0, 0.0 };
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
}

void Engine::setOrthographicProjection3D(int left, int right, int bottom, int top, int o_near, int o_far) 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left, right, bottom, top, o_near, o_far);
	glMatrixMode(GL_MODELVIEW);
}

void Engine::setOrthographicProjection3D_Mi(int left, int right, int bottom, int top, int o_near, int o_far)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left, right, bottom, top, o_near, o_far);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Engine::setOrthographicProjection2D(int w_down, int w_up, int h_down, int h_up) 
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(w_down, w_up, h_down, h_up);
	glMatrixMode(GL_MODELVIEW);
}

void Engine::setOrthographicProjection2D_Mi(int w_down, int w_up, int h_down, int h_up)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(w_down, w_up, h_down, h_up);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Engine::restorePerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Engine::restorePerspectiveProjection_Mi()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Engine::renderBitmapString_3f(const float &x, const float &y, const float &z, void *font, const std::string &string)
{
	glRasterPos3f(x, y, z);

	for (auto i : string)
	{
		glutBitmapCharacter(font, i);
	}
}

void Engine::renderBitmapString_3i(const int & x, const int & y, const int & z, void *font, const std::string &string)
{
	glRasterPos3i(x, y, z);

	for (auto i : string)
	{
		glutBitmapCharacter(font, i);
	}
}

void Engine::renderStrokeString_3i(const int & x, const int & y, const int & z, void *font, const std::string &string)
{
	//glPushMatrix();
	//glTranslatef(x, y, z);

	//for (auto i : string)
	//{
	//	glutStrokeCharacter(font, 47);
	//}

	//glPopMatrix();
}


