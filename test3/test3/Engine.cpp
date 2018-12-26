#include "pch.h"
#include "Engine.h"

CButton *button_1 = new CButton(0, 100, 100, 200, 100, "Button 1", 20);
CButton *button_2 = new CButton(1, 100, 300, 200, 100, "Button 2", 20);

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
	button_2->Draw();

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



void Engine::MouseFunc(int button, int state, int x, int y, void(*f)(int button_id))
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			button_1->Click_Handle(state, x, window_height - y, f);
			button_2->Click_Handle(state, x, window_height - y, f);
	
		}
		if (state == GLUT_UP) {
			button_1->Click_Handle(state, x, window_height - y, f);
			button_2->Click_Handle(state, x, window_height - y, f);

		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {

		}
	}
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

void Engine::renderStrokeString_3D(const Engine::TTransformf &transform, void * font, const std::string & string)
{
	glPushMatrix();
	glTranslatef(transform.Translate.x, transform.Translate.y, transform.Translate.z);
	glRotatef(transform.Rotate.angle, transform.Rotate.x, transform.Rotate.y, transform.Rotate.z);
	glScalef(transform.Scale.x, transform.Scale.y, transform.Scale.z);

	for (auto i : string)
	{
		glutStrokeCharacter(font, i);
	}

	glPopMatrix();
}

void Engine::renderStrokeString_2D(const float &x, const float &y, const float &scale_x, const float &scale_y, const float &angle, void *font, const std::string &string)
{
	TTransformf transform;

	transform.Translate.x = x;
	transform.Translate.y = y;
	transform.Translate.z = 0.0;
	transform.Rotate.angle = angle;
	transform.Rotate.x = 0.0;
	transform.Rotate.y = 0.0;
	transform.Rotate.z = 1.0;
	transform.Scale.x = scale_x;
	transform.Scale.y = scale_y;
	transform.Scale.z = 1.0;

	renderStrokeString_3D(transform, font, string);
}

void Engine::renderStrokeString_2D_smart(const float & x, const float & y, const float & width, const float & height, const float & angle, void * font, const std::string & string)
{
	float scale_width = 1.0;
	float scale_height = 1.0;
	int string_width = 0;
	float string_height = (float)Stroke_text_height;

	string_width = StrokeStringWidth(font, string);
	if (width != 0)
	{
		scale_width = width / (float)string_width;
	}
	if (height != 0)
	{
		scale_height = height / string_height;
	}

	renderStrokeString_2D(x, y, scale_width, scale_height, angle, font, string);
}

void Engine::renderStrokeString_2D_font(const float & x, const float & y, const float & angle, void * font, const float & font_size, const std::string & string)
{
	float scale = 1.0;

	if (font_size != 0)
	{
		scale = (float)font_size / (float)Stroke_text_height;
	}

	renderStrokeString_2D(x, y, scale, scale, angle, font, string);
}

int Engine::StrokeStringWidth(void * font, const std::string & string)
{
	int count = 0;

	for (auto i : string)
	{
		count += glutStrokeWidth(font, i);
	}

	return count;
}




