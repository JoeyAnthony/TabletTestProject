#pragma once

#include "Tablet.h"

#include <glm\common.hpp>
#include <iostream>

using namespace glm;
using namespace TabletGraphicsComonents;

class MainApp : public TabletApp {
	Square* s;

public:
	MainApp() {};

	void initalize() override {
		settings[Visable] = true;
		settings[Hoverable] = true;
		settings[Active] = true;

		s = new Square({ 1,0,0 }, { 0,1,0 }, this);
		s->position = { 200, 400 };
		s->size = { 300,300 };
		s->settings[Visable] = true;
		s->settings[Hoverable] = true;
		s->settings[Active] = true;
	}
};