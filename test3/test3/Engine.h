#pragma once

#include "api.h"

class Engine
{
private:
	int window_width;
	int window_height;

public:
	Engine();
	~Engine();
	void Draw(void);
	void Reshape(int width, int height);
};

