#pragma once

#include "api.h"
#include "CButton.h"

class Engine
{
private:
	int window_width;
	int window_height;

public:
	Engine();
	~Engine();
	int getWindow_width(void);
	int getWindow_height(void);
	void Draw(void);
	void Reshape(int width, int height);
	void Init(void);
	void Light(void);
	void setOrthographicProjection3D(int left, int right, int bottom, int top, int o_near, int o_far);
	void setOrthographicProjection3D_Mi(int left, int right, int bottom, int top, int o_near, int o_far);
	void setOrthographicProjection2D(int w_down, int w_up, int h_down, int h_up);
	void setOrthographicProjection2D_Mi(int w_down, int w_up, int h_down, int h_up);
	void restorePerspectiveProjection();
	void restorePerspectiveProjection_Mi();
	void renderBitmapString_3f(const float &x, const float &y, const float &z, void *font, const std::string &string);
	void renderBitmapString_3i(const int &x, const int &y, const int &z, void *font, const std::string &string);
	void renderStrokeString_3i(const int &x, const int &y, const int &z, void *font, const std::string &string);

};

