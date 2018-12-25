#pragma once

#include <string>
#include "Engine.h"

#include <iostream>				// debug

class CButton
{
private:
	struct TPoint_coord {		
		int Point_1[2];			// x , y
		int Point_2[2];			
		int Point_3[2];
		int Point_4[2];
	};
	TPoint_coord *coord = new TPoint_coord;
	int pos_x;
	int pos_y;
	int width;
	int height;
	std::string text;
	bool state;
	float *button_color = new float[3];
	float *text_color = new float[3];


	void coord_calc(const int &x, const int &y, const int &width, const int &height);
	bool check_entry(const int &x, const int &y);
	void render_text(const TPoint_coord *button_cord, const std::string &text, const float *text_color);

public:
	CButton();
	CButton(const int &x, const int &y, const int &width, const int &height, const std::string &text);
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
	int getX(void);
	int getY(void);
	int getWidth(void);
	int getHeight(void);
	std::string getText(void);
	bool getState(void);
	float *getButtonColor(void);
	float *getTextColor(void);

	void Draw(void);
	bool Click_Handle(int x, int y);
};

