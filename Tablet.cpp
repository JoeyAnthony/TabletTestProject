#include "stdafx.h"
#include "Tablet.h"

#include <glm\gtx\intersect.hpp>

using namespace vrlib;
using namespace vrlib::tien;
using namespace glm;
using vrlib::gl::FBO;
using std::make_unique;
using std::initializer_list;

Tablet::Tablet(ivec2 resolution, float size, const PositionalDevice& pointer, initializer_list<TabletApp*> apps) :
	m_resolution(resolution), m_size(size), m_withToHeightRatio(((float)m_resolution.y) / m_resolution.x),
	m_pointer(pointer), m_fbo(m_resolution.x, m_resolution.y), m_fboTexture(&m_fbo), 
	
	// We construct a matrix to convert our plane coordinates to pixel coordinates
	// Syntax: [a,b] is the inclusive range between a and b. '=>' is the transformation we want. 'f' is the function that does the conversion
	// x | [ -0.5 * size, 0.5 * size] => [0, resolution.x] | f(x) = x * (resolution.x / size) + resolution.x/2
	// Same for y, but there the ratio is also a factor
	// y | [ -0.5 * size * ratio, 0.5 * size * ratio] => [0, resolution.y] | f(y) = y * ((resolution.y / size) / ratio) + resolution.y/2 
	m_planePosToPixelCoordMat(m_resolution.x / m_size, 0, 0, 0,
							  0, (m_resolution.y / m_withToHeightRatio) / m_size, 0, 0,
							  0, 0, 0, 0,
							  m_resolution.x / 2.f, m_resolution.y / 2.f, 0, 0),

	// We contruct a matrix to convert our pixel coordinates to the fbo's texture coordinates
	// x | [0, resolution.x] => [-1, 1] | f(x) = x * (1/resolution.x) * 2 - 1
	// y | [0, resolution.y] => [-1, 1] | f(y) = y * (1/resolution.y) * 2 - 1
	m_pixelToTexCoordMat( (1.f / m_resolution.x) * 2,0,0,0,
						  0,(1.f / m_resolution.y) * 2,0,0,
						  0,0,1,0,
						  -1,-1,0,1 ),
	apps(apps)
	{
	
	// We setup the fbo as the mesh's texture
	material.texture = &m_fboTexture;
	material.normalmap = nullptr;

	// We clear the fbo
	clear();


	// We settup the mesh
	// @NOTE: this has mostly been copied from NetworkEngine/PanelComponent.cpp/PanelComponent::PanelComponent(...)

	// Setup Normal, tangent, and bi-tangent
	vrlib::gl::VertexP3N2B2T2T2 v;
	vrlib::gl::setN3(v, glm::vec3(0, 0, 1));
	vrlib::gl::setTan3(v, glm::vec3(1, 0, 0));
	vrlib::gl::setBiTan3(v, glm::vec3(0, 1, 0));

	// We create a vector with the plane / mesh's x and y size
	vec2 sizevec{ m_size, m_size * m_withToHeightRatio };

	// We create the plane's four vertecies
	vrlib::gl::setP3(v, glm::vec3(-sizevec.x / 2.0f, -sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(0, 0));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(sizevec.x / 2.0f, -sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(1, 0));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(sizevec.x / 2.0f, sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(1, 1));			vertices.push_back(v);
	vrlib::gl::setP3(v, glm::vec3(-sizevec.x / 2.0f, sizevec.y / 2.0f, 0));			vrlib::gl::setT2(v, glm::vec2(0, 1));			vertices.push_back(v);

	// We create the mesh from the indicies by forming two triangles from the 4 vertecies
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	// We check apps, and ensure proper initialization
	if (apps.size() == 0) throw "you need to pass at leat one app";
	for (auto& app : this->apps) {
		app->tablet = this;
		app->position = { 0,0 };
		app->size = m_resolution;
		app->initalize();
	}

	for (auto& app : this->apps) 
		app->linkToApps();

	activeApp = this->apps[0];
	activeApp->onActivation();
}

void Tablet::clear(vec4 clearColor) {

	// Setup the fbo as a render target
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, m_fbo.getWidth(), m_fbo.getHeight());
	m_fbo.bind();

	// We clear the fbo with the given clear color ( default = {0,0,0,1} )
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	// Remove the fbo as render target
	m_fbo.unbind();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Tablet::updateInput() {

	// We set the input values to valid values, so if we have to abort these are guaranteed to be acceptable
	m_screenPos = { 0,0 };
	m_screenPosInBounds = false;
	if (node == nullptr) return;

	// We take the inverse of our transfrom to convert the 'pointer' position to tablet space
	const mat4 toTabletSpaceMat = inverse(node->transform->transform);

	// We get the position and front of the 'pointer' and convert them to tablet space
	const vec3 pointerPos = vec3(toTabletSpaceMat * (m_pointer.getData() * vec4(0, 0, 0, 1)));
	const vec3 pointerFront = vec3(toTabletSpaceMat * (m_pointer.getData() * vec4(0, 0, -1, 1)));
	const vec3 pointerDir = pointerPos - pointerFront;

	// We use a ray plane intersect to calculate our intersection point
	// @TODO: replace with TIEN's comperable code (Math plane.rayIntersect)
	float intersectionDistance;
	bool intersectSucces = intersectRayPlane(pointerPos, pointerDir, {}, { 0,0,-1 }, intersectionDistance);
	if (intersectSucces == false) return;
	auto intercectionPosition = pointerPos + intersectionDistance * pointerDir;

	// We convert our intersection point to pixel cordinates
	ivec2 intercectionPosition2{ m_planePosToPixelCoordMat * vec4(intercectionPosition, 1) };

	// We set the screen pos and do bounds checks, we also indicate wether the intersection point was within the bounds
	m_screenPos = min(max(ivec2(intercectionPosition2), { 0,0 }), m_resolution);
	m_screenPosInBounds = ivec2(intercectionPosition2) == m_screenPos;
}

void Tablet::updateGraphicsObject(TabletGraphicsObject* obj, float deltaMs, ivec2 mousePos, bool inBounds, TabletGraphicsObject::SettingsStore settings) {
	mousePos -= obj->position;
	inBounds = inBounds ? mousePos.x >= 0 && mousePos.x < obj->size.x && mousePos.y >= 0 && mousePos.y < obj->size.y : false;
	for (int i = 0; i < TabletGraphicsObject::DummyLast; ++i)
		settings[i] = settings[i] & obj->settings[i];

	if (settings[TabletGraphicsObject::Active] && obj->settings[TabletGraphicsObject::Updateable]) obj->update(deltaMs);
	if (settings[TabletGraphicsObject::Active] && obj->settings[TabletGraphicsObject::Hoverable]) {
		if (obj->hadHover && !inBounds) {
			obj->onMouseLeave();
		}
		else if (!obj->hadHover && inBounds) {
			obj->onMouseEnter();
		}
		obj->hadHover = inBounds;
	}
	else if (obj->hadHover) {
		obj->onMouseLeave();
		obj->hadHover = false;
	}

	// Clickable stuff

	for (auto& child : obj->children)
		updateGraphicsObject(child, deltaMs, mousePos, inBounds, settings);
}

void Tablet::updateApps(float deltaMs) {
	updateGraphicsObject(activeApp, deltaMs, m_screenPos, m_screenPosInBounds, activeApp->settings);
	for (auto& app : apps)
		if (app != activeApp)
			app->updateInactive(deltaMs);
}

void Tablet::drawGraphicsObject(TabletGraphicsObject* obj, glm::mat4 transform) {
	if (obj->settings[TabletGraphicsObject::Visable] == false) return;
	
	transform[3][0] += obj->position.x;
	transform[3][1] += obj->position.y;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(value_ptr(transform));

	obj->draw();

	for (auto child : obj->children)
		if (child->settings[TabletGraphicsObject::Visable])
			drawGraphicsObject(child, transform);
}

void Tablet::updateScreen() {
	clear();

	// Setup the fbo as a render target
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, m_fbo.getWidth(), m_fbo.getHeight());
	m_fbo.bind();

	// Setup to allow easy graphics code in app
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(value_ptr(m_pixelToTexCoordMat)); // this matrix wil convert pixel coordinates to texture coordinates
	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);

	drawGraphicsObject(activeApp, { 1,0,0,0,
								    0,1,0,0,
								    0,0,0,0,
								    0,0,0,1 });

	// Remove the fbo as render target
	m_fbo.unbind();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void Tablet::update(float elapsedTime, Scene& scene) {
	updateInput();
	updateApps(elapsedTime);
	updateScreen();
}

void Tablet::postUpdate(Scene& scene) {
	
}

void Tablet::setActiveApp(TabletApp* app) {
	activeApp->onDeactivation();
	activeApp = app;
	activeApp->onActivation();
}