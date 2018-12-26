#pragma once

#include "api.h"
#include "CButton.h"

const int Stroke_text_height = 100;

class Engine
{
private:
	int window_width;
	int window_height;

	


public:
	//struct TTransformf;
	struct TTransformf {
		TTransformf() {
			Translate.x = 0.0;
			Translate.y = 0.0;
			Translate.z = 0.0;
			Scale.x = 1.0;
			Scale.y = 1.0;
			Scale.z = 1.0;
			Rotate.angle = 0.0;
			Rotate.x = 0.0;
			Rotate.y = 0.0;
			Rotate.z = 0.0;
		}
		struct Tr {
			float x;
			float y;
			float z;
		} Translate;
		struct Ro {
			float angle;
			float x;
			float y;
			float z;
		} Rotate;
		struct Sc {
			float x;
			float y;
			float z;
		} Scale;
	};
	
	Engine();
	~Engine();
	int getWindow_width(void);
	int getWindow_height(void);
	void Draw(void);
	void Reshape(int width, int height);
	void Init(void);
	void Light(void);
	void MouseFunc(int button, int state, int x, int y, void (*f)(int button_id));
	
	void setOrthographicProjection3D(int left, int right, int bottom, int top, int o_near, int o_far);
	void setOrthographicProjection3D_Mi(int left, int right, int bottom, int top, int o_near, int o_far);
	void setOrthographicProjection2D(int w_down, int w_up, int h_down, int h_up);
	void setOrthographicProjection2D_Mi(int w_down, int w_up, int h_down, int h_up);
	void restorePerspectiveProjection();
	void restorePerspectiveProjection_Mi();
	void renderBitmapString_3f(const float &x, const float &y, const float &z, void *font, const std::string &string);
	void renderBitmapString_3i(const int &x, const int &y, const int &z, void *font, const std::string &string);
	void renderStrokeString_3D(const Engine::TTransformf &transform, void * font, const std::string & string);
	void renderStrokeString_2D(const float &x, const float &y, const float &scale_x, const float &scale_y, const float &angle, void *font, const std::string &string);
	void renderStrokeString_2D_smart(const float &x, const float &y, const float &width, const float &height, const float &angle, void *font, const std::string &string);
	void renderStrokeString_2D_font(const float &x, const float &y, const float &angle, void *font, const float &font_size, const std::string &string);
	int StrokeStringWidth(void *font, const std::string &string);
	
	



};

