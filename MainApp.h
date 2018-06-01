#pragma once

#include "Tablet.h"

#include <glm\common.hpp>
#include <iostream>
#include <vector>

using namespace glm;
using namespace TabletGraphicsComonents;

class MainApp : public TabletApp {
	
	Square* background;
	std::vector<Button*> buttons;
public:
	

	MainApp() {};

	void initalize() override;
};