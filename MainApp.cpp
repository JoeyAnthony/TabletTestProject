#include "stdafx.h"
#include "MainApp.h"

void MainApp::initalize() {
	background = new Square({ 0.9,0.9,0.9 }, { 0.9,0.9,0.9 }, this);
	background->setGeometry({ {0,0},getGeometry().size });

	int h = 15;
	buttons.push_back(new Button("Close", []() {exit(0); }, this));
	buttons.back()->setGeometry({ {15,h},{110,0} });
	h += 110 + 15;

	buttons.push_back(new Button("Red", [this]() {
		background->hoverColor = background->color = { 1,0,0 };
	}, this));
	buttons.back()->setGeometry({ { 15,h },{ 110,0 } });
	h += 110 + 15;

	buttons.push_back(new Button("Green", [this]() {
		background->hoverColor = background->color = { 0,1,0 };
	}, this));
	buttons.back()->setGeometry({ { 15,h },{ 110,0 } });
	h += 110 + 15;

	buttons.push_back(new Button("Blue", [this]() {
		background->hoverColor = background->color = { 0,0,1 };
	}, this));
	buttons.back()->setGeometry({ { 15,h },{ 110,0 } });
	h += 110 + 15;
}