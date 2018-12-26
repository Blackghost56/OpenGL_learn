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

void CButton::text_update(const TPoint_coord *button_cord, TText_container *text)
{
	int x = 0;
	int y = 0;
	int centre_x = 0;
	int centre_y = 0;
	float text_length = (float)engine->StrokeStringWidth(text->font, text->text) * ((float)text->font_size / (float)Stroke_text_height);

	centre_x = (button_cord->Point_2[0] - button_cord->Point_1[0]) / 2 + button_cord->Point_1[0];
	centre_y = (button_cord->Point_4[1] - button_cord->Point_1[1]) / 2 + button_cord->Point_1[1];

	x = centre_x - (text_length / 2.0);
	y = centre_y - ((float)text->font_size / 2.0);
	
	if ((x > button_cord->Point_1[0]) && (y > button_cord->Point_1[1]))
	{
		text->x = x;
		text->y = y;
	}
	else
	{
		text->x = button_cord->Point_1[0];
		text->y = button_cord->Point_1[1];
		text->text = "Err. Lenghth";
	}
	
	
	/*std::cout << "text_length    " << text_length << std::endl;
	std::cout << "centre_x    " << centre_x << std::endl;
	std::cout << "centre_y    " << centre_y << std::endl;
	std::cout << "text->x    " << text->x << std::endl;
	std::cout << "text->y    " << text->y << std::endl;*/

}

CButton::CButton()
{
	this->id = 0;
	this->pos_x = 0;
	this->pos_y = 0;
	this->width = 0;
	this->height = 0;
	this->state = false;
	mouse_state = MOUSE_UP;
	this->setButtonColorUp(0.5, 0.5, 0.5);		// def set gray
	this->setButtonColorDown(0.4, 0.4, 0.4);
	//this->setTextColor(0.0, 0.0, 0.0);			// def set black
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, this->text);
}

CButton::CButton(const int &id, const int &x, const int &y, const int &width, const int &height, const std::string &text, const int font_size)
{
	this->id = id;
	this->pos_x = x;
	this->pos_y = y;
	this->width = width;
	this->height = height;
	this->text->text = text;
	this->state = false;
	mouse_state = MOUSE_UP;
	this->setButtonColorUp(0.5, 0.5, 0.5);		// def set gray
	this->setButtonColorDown(0.4, 0.4, 0.4);
	//this->setTextColor(0.0, 0.0, 0.0);			// def set black
	this->text->font_size = font_size;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, this->text);
}

CButton::~CButton()
{
		
}

void CButton::setId(int & id)
{
	this->id = id;
}

void CButton::setX(const int &x)
{
	this->pos_x = x;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, text);
}

void CButton::setY(const int &y)
{
	this->pos_y = y;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, text);
}

void CButton::setWidth(const int &width)
{
	this->width = width;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, text);
}

void CButton::setHeight(const int &height)
{
	this->height = height;
	coord_calc(this->pos_x, this->pos_y, this->width, this->height);
	text_update(coord, text);
}

void CButton::setText(const std::string &text)
{
	this->text->text = text;
	text_update(coord, this->text);
}

void CButton::setState(const bool &state)
{
	this->state = state;
}

void CButton::setButtonColorUp(const float &r, const float &g, const float &b)
{
	this->button_color_up[0] = r;
	this->button_color_up[1] = g;
	this->button_color_up[2] = b;
}

void CButton::setButtonColorUp(float * color_3f)
{
	this->button_color_up[0] = color_3f[0];
	this->button_color_up[1] = color_3f[1];
	this->button_color_up[2] = color_3f[2];
}

void CButton::setButtonColorDown(const float & r, const float & g, const float & b)
{
	this->button_color_down[0] = r;
	this->button_color_down[1] = g;
	this->button_color_down[2] = b;
}

void CButton::setButtonColorDown(float * color_3f)
{
	this->button_color_down[0] = color_3f[0];
	this->button_color_down[1] = color_3f[1];
	this->button_color_down[2] = color_3f[2];
}

void CButton::setTextColor(const float & r, const float & g, const float & b)
{
	this->text->text_color[0] = r;
	this->text->text_color[1] = g;
	this->text->text_color[2] = b;
}

void CButton::setTextColor(float * color_3f)
{
	this->text->text_color[0] = color_3f[0];
	this->text->text_color[1] = color_3f[1];
	this->text->text_color[2] = color_3f[2];
}

void CButton::setFont(void * font)
{
	this->text->font = font;
	text_update(coord, text);
}

void CButton::setFontSize(int &size)
{
	this->text->font_size = size;
	text_update(coord, text);
}

int CButton::getId(void)
{
	return this->id;
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
	return this->text->text;
}

bool CButton::getState(void)
{
	return this->state;
}

float * CButton::getButtonColorUp(void)
{
	return button_color_up;
}

float * CButton::getButtonColorDown(void)
{
	return button_color_down;
}

float * CButton::getTextColor(void)
{
	return text->text_color;
}

void * CButton::getFont(void)
{
	return this->text->font;
}

int CButton::getFontSize(void)
{
	return this->text->font_size;
}

void CButton::Draw(void)
{
	if (mouse_state == MOUSE_UP)
	{
		engine->setOrthographicProjection2D_Mi(0, engine->getWindow_width(), 0, engine->getWindow_height());
		glColor3fv(button_color_up);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2iv(coord->Point_1);
		glVertex2iv(coord->Point_2);
		glVertex2iv(coord->Point_3);
		glVertex2iv(coord->Point_4);
		glEnd();

		glColor3fv(text->text_color);
		engine->renderStrokeString_2D_font(text->x, text->y, 0, text->font, text->font_size, text->text);

		engine->restorePerspectiveProjection_Mi();

	}
	else
	{
		engine->setOrthographicProjection2D_Mi(0, engine->getWindow_width(), 0, engine->getWindow_height());
		glColor3fv(button_color_down);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2iv(coord->Point_1);
		glVertex2iv(coord->Point_2);
		glVertex2iv(coord->Point_3);
		glVertex2iv(coord->Point_4);
		glEnd();

		glColor3fv(text->text_color);
		engine->renderStrokeString_2D_font(text->x, text->y, 0, text->font, text->font_size, text->text);

		engine->restorePerspectiveProjection_Mi();
	}
}

bool CButton::Click_Handle(int mouse_state, int x, int y, void(*f)(int button_id))
{
	state = check_entry(x, y);

	//std::cout << "x " << x <<  std::endl;
	//std::cout << "y " << y << std::endl;
	//static int count = 0;
	//count++;
	//std::cout << "Click #" << count << "State   " << state << std::endl;
	//f();
	if (state)
	{
		this->mouse_state = mouse_state;
		if (mouse_state == GLUT_DOWN)
		{
			f(this->id);
		}
	}

	return state;
}


