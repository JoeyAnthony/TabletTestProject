#pragma once
#include <list>
#include <glm\common.hpp>
#include <functional>
#include <bitset>

#include <iostream>

class Tablet;

class TabletGraphicsObject {
	friend Tablet;

	std::list<TabletGraphicsObject*> children;

	void addChild(TabletGraphicsObject* child);
	void removeChild(TabletGraphicsObject* child);

	TabletGraphicsObject* parent;

	bool hadHover = false;
public:

	TabletGraphicsObject(TabletGraphicsObject* parent);
	virtual ~TabletGraphicsObject();

	enum Settings {
		Active = 0,
		Visable = 1,
		Clickable = 2,
		Hoverable = 3,
		Updateable = 4,
		DummyLast = 5
	};
	using SettingsStore = typename std::bitset<5>;

	SettingsStore settings;
	
	glm::ivec2 position;
	glm::ivec2 size;

	bool isHovering() { return hadHover; }

	virtual void draw() {};
	virtual void onClick() {};
	virtual void onMouseEnter() {};
	virtual void onMouseLeave() {};
	virtual void update(float deltaMs) {};
};

class TabletApp : public TabletGraphicsObject {
protected:
	friend Tablet;

	Tablet * tablet;
	TabletApp() : TabletGraphicsObject(nullptr) {};

public:

	virtual void initalize() {};
	virtual bool linkToApps() { return true; };
	virtual void updateInactive(float deltaMs) {};
	virtual void onActivation() {};
	virtual void onDeactivation() {};
};

namespace TabletGraphicsComonents {
	class Square : public TabletGraphicsObject {
	public:
		glm::vec3 color, hoverColor;

		Square(glm::vec3 _color, glm::vec3 _hoverColor, TabletGraphicsObject* parent);

		void draw() override;
	};
}