#pragma once

#include "Tablet.h"

#include <glm\common.hpp>
#include <iostream>

using namespace glm;
using namespace TabletGraphicsComonents;

class MainApp : public TabletApp {
	Square* s;
	Square* s2;
	Text* t;

public:
	MainApp() {};

	void initalize() override {

		/*s = new Square({ 1,0,0 }, { 0,1,0 }, this);
		s->geometry = { {200,300}, {300,300} };

		s2 = new Square({ 0,0,0 }, { 1,1,0 }, this);
		s2->geometry = { {600, 800}, {170,170} };*/

		t = new Text({ 1,1,1 }, { 1,1,1 }, "abcdefghijklmnopqrstuvwxyz", "cambriai", 200, this);
		t->geometry = { {200, 300}, {500, 500} };
	}
};