#include "stdafx.h"

#include "MapApp.h"
#include <VrLib\Texture.h>

using namespace glm;
using namespace vrlib;

MapApp::MapScroll::MapScroll(std::string map, float wordToMapScale, glm::vec2 centerWorld, TabletGraphicsObject* parent) : 
	TabletGraphicsObject(parent), texture(vrlib::Texture::loadCached(map)), wordToMapScale(wordToMapScale), centerWorld(centerWorld) {
	TabletGraphicsComonents::Details::ensureFontShaderInit();
}

void MapApp::MapScroll::draw(TabletGraphicsRenderInfo renderInfo) {
	using namespace TabletGraphicsComonents::Details;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_CULL_FACE);

	const auto mapPos = (worldPos - centerWorld) / wordToMapScale + vec2(0.5f,0.5f);
	const auto xoffset = mapZoom/2;
	const auto yoffset = (getGeometry().size.y / (float)getGeometry().size.x) * mapZoom/2;

	fontShader->use();
	fontShader->setUniform(FontUniform::modelMatrix, renderInfo.modelViewMatrix);
	fontShader->setUniform(FontUniform::projectionMatrix, renderInfo.projectionMatrix);
	fontShader->setUniform(FontUniform::color, glm::vec4(1, 1, 1, 1));

	std::vector<vrlib::gl::VertexP2T2> verts;

	ivec2 position = { 0,0 };
	ivec2 size = getGeometry().size;

	
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x, position.y),                   mapPos + glm::vec2(-xoffset, -yoffset)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x + size.x, position.y),          mapPos + glm::vec2(+xoffset, -yoffset)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x + size.x, position.y + size.y), mapPos + glm::vec2(+xoffset, +yoffset)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x, position.y + size.y),          mapPos + glm::vec2(-xoffset, +yoffset)));
	
	/*
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x, position.y), glm::vec2(0, 0)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x + size.x, position.y), glm::vec2(1, 0)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x + size.x, position.y + size.y), glm::vec2(1, 1)));
	verts.push_back(vrlib::gl::VertexP2T2(glm::vec2(position.x, position.y + size.y), glm::vec2(0, 1)));
	*/
	texture->bind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	vrlib::gl::setAttributes<vrlib::gl::VertexP2T2>(&verts[0]);

	glDrawArrays(GL_QUADS, 0, verts.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void MapApp::MapScroll::setWorldPos(glm::vec2 worldPos) {
	this->worldPos = worldPos;
}

void MapApp::MapScroll::setMapZoom(float mapZoom) {
	this->mapZoom = mapZoom;
}

MapApp::MapApp() {
	settings[Updateable] = true;
}

void MapApp::initalize() {
	baseMap = new MapScroll("data/TienTest/textures/ground_normal.png", 10, { 5,5 }, this);
	baseMap->setGeometry({ {0,0},{1080,1080} });
	baseMap->setMapZoom(2);
	baseMap->setWorldPos({ 2,5 });
}

float count = 0;

void MapApp::update(float deltaMS) {
	count += deltaMS;

	baseMap->setMapZoom(1 + sin(count/2) / 2);
}