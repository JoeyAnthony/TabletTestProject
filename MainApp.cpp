#include "stdafx.h"
#include "MainApp.h"

void MainApp::initalize() {
	s = new Square({ 1,0,0 }, { 0,1,0 }, this);
	s->setGeometry({ { 1000,700 }, { 150,150 } });

	b = new Button("Toggle Square", [this]() { s->settings[Visable].flip(); }, this);
	b->setGeometry({ { 200,300 },{ 400,400 } });

	p = new Picture("data/JohanDemo/marble.jpg", this);
	p->setGeometry({ { 1250,0 }, { 512,512 } });
}