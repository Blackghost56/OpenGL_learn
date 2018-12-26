#pragma once

#include <string>
#include "Engine.h"

#include <iostream>				// debug

class CButton
{
private:
	/*struct TText_border {
	TText_border() {
		top = 20;
		down = 20;
		left = 10;
		right = 10;
	};
	int top;
	int down;
	int left;
	int right;
	} text_border;*/
	


	int pos_x;
	int pos_y;
	int width;
	int height;
	bool state;
	float *button_color = new float[3];
	
	struct TPoint_coord {
		int Point_1[2];						// x , y
		int Point_2[2];
		int Point_3[2];
		int Point_4[2];
	};
	TPoint_coord *coord = new TPoint_coord;

	struct TText_container {
		TText_container() {
			x = 0;
			y = 0;
			text = "";
			text_color[0] = 0.0;			// def set black
			text_color[1] = 0.0;
			text_color[2] = 0.0;
			font = GLUT_STROKE_MONO_ROMAN;	//GLUT_STROKE_ROMAN
			font_size = 20;
		};
		int x;
		int y;
		std::string text;
		float *text_color = new float[3];
		void *font;
		int font_size;		// pix
	};
	TText_container *text = new TText_container;

	void coord_calc(const int &x, const int &y, const int &width, const int &height);
	bool check_entry(const int &x, const int &y);
	void text_update(const TPoint_coord *button_cord, TText_container *text);

public:
	CButton();
	CButton(const int &x, const int &y, const int &width, const int &height, const std::string &text, const int font_size);
	~CButton();
	void setX(const int &x);
	void setY(const int &y);
	void setWidth(const int &width);
	void setHeight(const int &height);
	void setText(const std::string &text);
	void setState(const bool &state);
	void setButtonColor(const float &r, const float &g, const float &b);
	void setButtonColor(float *color_3f);
	void setTextColor(const float &r, const float &g, const float &b);
	void setTextColor(float *color_3f);
	void setFont(void *font);
	void setFontSize(int &size);
	int getX(void);
	int getY(void);
	int getWidth(void);
	int getHeight(void);
	std::string getText(void);
	bool getState(void);
	float *getButtonColor(void);
	float *getTextColor(void);
	void *getFont(void);
	int getFontSize(void);

	void Draw(void);
	bool Click_Handle(int x, int y, void (*f)(void));
	
};

