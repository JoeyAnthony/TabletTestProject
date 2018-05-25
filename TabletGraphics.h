#pragma once
#include <list>
#include <glm\common.hpp>
#include <functional>
#include <bitset>
#include <VrLib\Font.h>
#include <map>
#include <VrLib\gl\shader.h>

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
		Updateable = 4
	};
	using SettingsStore = typename std::bitset<5>;

	SettingsStore settings;
	
	struct Geometry {
		glm::ivec2 position;
		glm::ivec2 size;
	};

	Geometry geometry;

	bool isHovering() { return hadHover; }

	virtual void draw(glm::mat4 proj, glm::mat4 model) {};
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

		void draw(glm::mat4 proj, glm::mat4 model) override;
	};

	class Text : public TabletGraphicsObject {
		enum class FontUniform
		{
			projectionMatrix,
			modelMatrix,
			s_texture,
			color,
		};
		static vrlib::gl::Shader<FontUniform>* fontShader;
		static std::map<std::pair<std::string, float>, vrlib::TrueTypeFont*> fonts;
		vrlib::TrueTypeFont* font;
	public:

		glm::vec3 color, hoverColor;
		std::string text;
		const float height;

		Text(glm::vec3 color, glm::vec3 hoverColor, std::string text, std::string font, float heigth, TabletGraphicsObject* parent);

		void draw(glm::mat4 proj, glm::mat4 model) override;
	};
}