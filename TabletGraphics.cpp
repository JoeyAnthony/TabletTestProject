#include "stdafx.h"
#include "TabletGraphics.h"

#include <glm\common.hpp>
#include <VrLib\gl\FBO.h>
#include "Tablet.h"

using namespace glm;

TabletGraphicsObject::TabletGraphicsObject(TabletGraphicsObject* _parent) : parent(_parent) {
	if (parent) parent->addChild(this);
}

TabletGraphicsObject::~TabletGraphicsObject() {
	if (parent) parent->removeChild(this);
}

void TabletGraphicsObject::addChild(TabletGraphicsObject* child) {
	children.push_back(child);
}

void TabletGraphicsObject::removeChild(TabletGraphicsObject* child) {
	children.remove(child);
}

namespace TabletGraphicsComonents {

	Square::Square(glm::vec3 _color, glm::vec3 _hoverColor, TabletGraphicsObject* parent) : 
		TabletGraphicsObject(parent), color(_color), hoverColor(_hoverColor) {
	}

	void Square::draw() {
		std::cout << "Square::draw()" << isHovering() << std::endl;

		glBegin(GL_QUADS);

		if (isHovering())  glColor3f(color.r, color.g, color.b );
		else glColor3f(hoverColor.r, hoverColor.g ,hoverColor.b);

		glVertex2fv(value_ptr(vec2(0, 0)));
		glVertex2fv(value_ptr(vec2(size.x, 0)));
		glVertex2fv(value_ptr(vec2(size.x, size.y)));
		glVertex2fv(value_ptr(vec2(0, size.y)));

		glEnd();
	}

}