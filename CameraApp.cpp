#include "stdafx.h"
#include "CameraApp.h"
#include "VrLib/tien/Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include <VrLib/math/Ray.h>
#include "VisibilityTester.h"

using namespace vrlib::tien;
using namespace glm;

void CameraApp::initialize() {
	fbo = new vrlib::gl::FBO(fboRes.x, fboRes.y, true, 1);
}

void CameraApp::update()
{
	fbo->bind();
	mat4 model = translate(glm::mat4(), camTabletOffset);
	mat4 perspective = glm::perspective(glm::radians(fov), fboRes.y / fboRes.x, 0.01f, 1000.0f);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, fboRes.x, fboRes.y);


	func(tabletHand->getScene(), perspective, model , tabletHand, 0);

	for (VisibilityTester* objs : occlusionObjects)
	{
		objs->OcclusionDraw(inverse(tabletHand->transform->globalTransform) * model, perspective);
	}
	
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	fbo->unbind();
}

void CameraApp::addOcclusionObject(Node* obj)
{
	VisibilityTester* vis = obj->getComponent<VisibilityTester>();
	if(vis != nullptr)
		occlusionObjects.push_back(vis);
}

void CameraApp::addOcclusionObject(VisibilityTester * obj)
{
	occlusionObjects.push_back(obj);
}

CameraApp::CameraApp() {
}

CameraApp::CameraApp(vrlib::tien::Node * hand, std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func): tabletHand(hand), func(func) {

}

CameraApp::CameraApp(Node * hand, glm::vec2 resolution): tabletHand(hand), fboRes(resolution) {	

}

CameraApp::~CameraApp()
{
}
