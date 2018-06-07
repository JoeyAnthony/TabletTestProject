#pragma once

#include "Tablet.h"
#include "CameraApp.h"

#include <glm\common.hpp>
#include <iostream>
#include <vector>

using namespace glm;
using namespace TabletGraphicsComonents;

class MainApp : public TabletApp {
	Square* background;
	Text* title;
	Text* counter;

	std::vector<Button*> buttons;

	CameraApp* camApp;
public:
	

	MainApp() {};

	void initalize() override;
	bool linkToApps() override;
};