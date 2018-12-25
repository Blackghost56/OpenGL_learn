#include "pch.h"
#include "CButton.h"

extern Engine *engine;

void CButton::coord_calc(const int &x, const int &y, const int &width, const int &height)
{
	coord->Point_1[0] = x;
	coord->Point_1[1] = y;

	coord->Point_2[0] = x + width;
	coord->Point_2[1] = y;

	coord->Point_3[0] = x + width;
	coord->Point_3[1] = y + height;

	coord->Point_4[0] = x;
	coord->Point_4[1] = y + height;
}

bool CButton::check_entry(const int &x, const int &y)
{
	if ((x >= coord->Point_1[0]) && (x <= coord->Point_3[0]) && (y >= coord->Point_1[1]) && (y <= coord->Point_3[1]))
	{
		return true;
	}	
	return false;
}

void CButton::render_text(const TPoint_coord *button_cord, const std::string &text, const float *text_color)
{
	glColor3fv(text_color);

	engine->renderStrokeString_2D_smart(0, 0, 100, 50, 0, GLUT_STROKE_ROMAN, text);
}

CButton::CButton()
{
	this->pos_x = 0;
	this->pos_y = 0;
	this->width = 0;
	this->height = 0;
	this->text = "";
	this->state = false;
	this->setButtonColor(0.5, 0.5, 0.5);		// def set gray
	this->setTextColor(0.0, 0.0, 0.0);			// def set black
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

CButton::CButton(const int &x, const int &y, const int &width, const int &height, const std::string &text)
{
	this->pos_x = x;
	this->pos_y = y;
	this->width = width;
	this->height = height;
	this->text = text;
	this->state = false;
	this->setButtonColor(0.5, 0.5, 0.5);		// def set gray
	this->setTextColor(0.0, 0.0, 0.0);			// def set black
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

CButton::~CButton()
{
}

void CButton::setX(const int &x)
{
	this->pos_x = x;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

void CButton::setY(const int &y)
{
	this->pos_y = y;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

void CButton::setWidth(const int &width)
{
	this->width = width;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

void CButton::setHeight(const int &height)
{
	this->height = height;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
}

void CButton::setText(const std::string &text)
{
	this->text = text;
}

void CButton::setState(const bool &state)
{
	this->state = state;
}

void CButton::setButtonColor(const float &r, const float &g, const float &b)
{
	this->button_color[0] = r;
	this->button_color[1] = g;
	this->button_color[2] = b;
}

void CButton::setButtonColor(float * color_3f)
{
	this->button_color[0] = color_3f[0];
	this->button_color[1] = color_3f[1];
	this->button_color[2] = color_3f[2];
}

void CButton::setTextColor(const float & r, const float & g, const float & b)
{
	this->text_color[0] = r;
	this->text_color[1] = g;
	this->text_color[2] = b;
}

void CButton::setTextColor(float * color_3f)
{
	this->text_color[0] = color_3f[0];
	this->text_color[1] = color_3f[1];
	this->text_color[2] = color_3f[2];
}

int CButton::getX(void)
{
	return this->pos_x;
}

int CButton::getY(void)
{
	return this->pos_y;
}

int CButton::getWidth(void)
{
	return this->width;
}

int CButton::getHeight(void)
{
	return this->height;
}

std::string CButton::getText(void)
{
	return this->text;
}

bool CButton::getState(void)
{
	return this->state;
}

float * CButton::getButtonColor(void)
{
	return button_color;
}

float * CButton::getTextColor(void)
{
	return text_color;
}

void CButton::Draw(void)
{
	if (!state)
	{
		engine->setOrthographicProjection2D_Mi(0, engine->getWindow_width(), 0, engine->getWindow_height());
		glColor3fv(button_color);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2iv(coord->Point_1);
		glVertex2iv(coord->Point_2);
		glVertex2iv(coord->Point_3);
		glVertex2iv(coord->Point_4);
		glEnd();

		
		//  Заменить растровый текст на glutStrokeCharacter
		render_text(coord, text, text_color);
		//std::cout << engine->StrokeStringWidth(GLUT_STROKE_MONO_ROMAN, text) << std::endl;
		/*
		Engine::TTransformf trans;
		trans.Scale.x = 0.5;
		trans.Scale.y = 0.5;
		trans.Scale.z = 1.0;
		trans.Translate.x = 100.0;
		trans.Translate.y = 100.0;
		trans.Translate.z = 0.0;
		trans.Rotate.angle = 45.0;
		trans.Rotate.z = 1.0;*/
		//engine->renderStrokeString_3D(trans, GLUT_STROKE_MONO_ROMAN, text);

		//engine->renderStrokeString_2D(100, 100, 0.5, 0.5, 45, GLUT_STROKE_MONO_ROMAN, text);

		//engine->renderStrokeString_2D_smart(0, 0, 200, 200, 0, GLUT_STROKE_MONO_ROMAN, text);
		//engine->renderStrokeString_2D_smart(0, 0, 100, 50, 0, GLUT_STROKE_ROMAN, text);
		
		//engine->renderBitmapString_3i(10, 10, 0, GLUT_BITMAP_TIMES_ROMAN_10, text);
		//engine->renderStrokeString(100.0, 100.0, 0, GLUT_STROKE_MONO_ROMAN, text);

		engine->restorePerspectiveProjection_Mi();

	}
	else
	{

	}
}

bool CButton::Click_Handle(int x, int y)
{
	state = check_entry(x, y);

	return state;
}
