#include "stdafx.h"
#include "TabletGraphics.h"

#include <glm\common.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <VrLib\gl\FBO.h>
#include "Tablet.h"

using namespace glm;



TabletGraphicsObject::TabletGraphicsObject(TabletGraphicsObject* _parent) : parent(_parent) {
	if (parent) parent->addChild(this);
	settings[Active] = true;
	settings[Visable] = true;
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
	vrlib::gl::Shader<Text::FontUniform>* Text::fontShader;
	std::map<std::pair<std::string, float>, vrlib::TrueTypeFont*> Text::fonts;

	Square::Square(vec3 _color, vec3 _hoverColor, TabletGraphicsObject* parent) : 
		TabletGraphicsObject(parent), color(_color), hoverColor(_hoverColor) {
		settings[Hoverable] = true;
	}

	void Square::draw(glm::mat4 proj, glm::mat4 model) {
		glBegin(GL_QUADS); 

		if (isHovering()) glColor3f(hoverColor.r, hoverColor.g, hoverColor.b);
		else glColor3f(color.r, color.g, color.b );

		glVertex2fv(value_ptr(vec2(0, 0)));
		glVertex2fv(value_ptr(vec2(geometry.size.x, 0)));
		glVertex2fv(value_ptr(vec2(geometry.size.x, geometry.size.y)));
		glVertex2fv(value_ptr(vec2(0, geometry.size.y)));

		glEnd();
	}

	Text::Text(vec3 color, vec3 hoverColor, std::string text, std::string fontName, float height, TabletGraphicsObject* parent) : 
		TabletGraphicsObject(parent), color(color), hoverColor(hoverColor), text(text), height(height) {

		if (!fontShader)
		{
			fontShader = new vrlib::gl::Shader<FontUniform>("data/NetworkEngine/shaders/font.vert", "data/NetworkEngine/shaders/font.frag");
			fontShader->bindAttributeLocation("a_position", 0);
			fontShader->bindAttributeLocation("a_color", 1);
			fontShader->link();
			fontShader->registerUniform(FontUniform::projectionMatrix, "projectionMatrix");
			fontShader->registerUniform(FontUniform::modelMatrix, "modelMatrix");
			fontShader->registerUniform(FontUniform::s_texture, "s_texture");
			fontShader->registerUniform(FontUniform::color, "color");
			fontShader->use();
			fontShader->setUniform(FontUniform::s_texture, 0);
			fontShader->setUniform(FontUniform::color, glm::vec4(1, 1, 1, 1));
		}

		if (fonts.find(std::pair<std::string, float>(fontName, height)) == fonts.end())
		{
			vrlib::TrueTypeFont* f = new vrlib::TrueTypeFont(fontName, height);
			fonts[std::pair<std::string, float>(fontName, height)] = f;
		}

		font = fonts[std::pair<std::string, float>(fontName, height)];
		if (!font || !font->fileData)
			throw "Unable To Load Font";

		
	}

	void Text::draw(glm::mat4 proj, glm::mat4 model) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		fontShader->use();

		//float modelF[16];
		//glGetFloatv(GL_MODELVIEW, modelF);
		//proj[1][2] *= -1;
		//proj[3][2] = 0;

		fontShader->setUniform(FontUniform::projectionMatrix, proj);//glm::make_mat4(modelF));

		//glGetFloatv(GL_PROJECTION, modelF);

		fontShader->setUniform(FontUniform::modelMatrix, model);// glm::make_mat4(modelF));
		fontShader->setUniform(FontUniform::color, color);
		font->drawText<vrlib::gl::VertexP2T2>(text);

		std::vector<vrlib::gl::VertexP2T2> verts;

		verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(0, 0), glm::vec2(0, 0)));
		verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(geometry.size.x,0), glm::vec2(1, 0)));
		verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(geometry.size.x, geometry.size.y), glm::vec2(1, 1)));
		verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(0,geometry.size.y), glm::vec2(0, 1)));


		//t->bind();
		font->texture->bind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		vrlib::gl::setAttributes<vrlib::gl::VertexP2T2>(&verts[0]);

		//glDrawArrays(GL_QUADS, 0, verts.size());

	}
}