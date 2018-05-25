#include "stdafx.h"
#include "CameraApp.h"
#include "VrLib/tien/Component.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace vrlib::tien;
using namespace glm;

void CameraApp::initialize() {
	fbo = new vrlib::gl::FBO(fboRes.x, fboRes.y, true, 1);

	camComponent = new components::Camera();
	camComponent->fboSize = fboRes;
	camComponent->target = fbo;
	camComponent->useFbo = true;

	tabletHand->addComponent(camComponent);
}

void CameraApp::update()
{
	fbo->bind();
	
	func(tabletHand->getScene(), glm::perspective(70.0f, fboRes.y / fboRes.x, 0.01f, 1000.0f), translate(glm::mat4(),camTabletOffset), tabletHand, 0);
	
	fbo->unbind();
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
