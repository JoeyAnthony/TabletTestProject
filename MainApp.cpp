#include "stdafx.h"
#include "MainApp.h"
#include "CameraApp.h"
#include "MapApp.h"

void MainApp::initalize() {
	background = new Square({}, {}, this);
	background->color = background->hoverColor = { 249.f / 255,247.f / 255,153.f / 255 };
	background->setGeometry({ {0,0},getGeometry().size });

	title = new Text({}, {}, "Main Screen", "Arial", 100, this);
	title->setGeometry({ {100, 1920-100-100}, {0,0} });

	counter = new Text({}, {}, "Discrepancies photographed 5 of 23", "Arial", 60, this);
	counter->setGeometry({ {100, 1920 - 200 - 100}, {} });

	buttons.push_back(new Button("Camera App", [tablet = tablet, &camApp = camApp]() {tablet->setActiveApp(camApp); }, this));
	buttons.back()->setGeometry({ {120, 1920 - 300 - 100},{300,0} });

	buttons.push_back(new Button("Map App", [tablet = tablet, &mapApp = mapApp]() {tablet->setActiveApp(mapApp); }, this));
	buttons.back()->setGeometry({ { 120, 1920 - 300 - 200 },{ 300,0 } });
}

bool MainApp::linkToApps() {
	if ((camApp = tablet->getApp<CameraApp>()) == nullptr) return false;
	if ((mapApp = tablet->getApp<MapApp>()) == nullptr) return false;

	return true;
}