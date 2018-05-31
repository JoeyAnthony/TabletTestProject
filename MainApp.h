#pragma once

#include "Tablet.h"

#include <glm\common.hpp>
#include <iostream>

using namespace glm;
using namespace TabletGraphicsComonents;

class MainApp : public TabletApp {
	
	Square* s2;
	Text* t;
	Button* b;
	Square* s;
	Picture* p;
public:
	

	MainApp() {};

	void initalize() override;
};