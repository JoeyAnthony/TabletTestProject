#include "stdafx.h"
#include "CameraApp.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace vrlib::tien;
using namespace glm;

void CameraApp::initalize()
{
	settings[Updateable] = true;
	//background = new TabletGraphicsComonents::FBO(fbo, this);
	//background->setGeometry({ {0,0},getGeometry().size });
}

void CameraApp::update(float deltaMS)
{
	mat4 model = translate(glm::mat4(), camTabletOffset);
	mat4 perspective = glm::perspective(glm::radians(fov), fboRes.y / fboRes.x, 0.01f, 1000.0f);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, fboRes.x, fboRes.y);
	fbo->bind();

	func(tabletHand->getScene(), perspective, model, tabletHand, 0);

	for (VisibilityTester* objs : occlusionObjects)
	{
		objs->OcclusionDraw(inverse(tabletHand->transform->globalTransform) * model, perspective);
	}

	//glClearColor(1, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);

	fbo->unbind();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

void CameraApp::addOcclusionObject(Node* obj)
{
	VisibilityTester* vis = obj->getComponent<VisibilityTester>();
	if (vis != nullptr)
		occlusionObjects.push_back(vis);
}

void CameraApp::addOcclusionObject(VisibilityTester * obj)
{
	occlusionObjects.push_back(obj);
}

CameraApp::CameraApp(vrlib::tien::Node* hand) {
	tabletHand = hand;
	fbo = new vrlib::gl::FBO(getGeometry().size.x, getGeometry().size.y, 1, false);
	
}

CameraApp::CameraApp(vrlib::tien::Node * hand, std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func) : CameraApp(hand) {
	this->func = func;
}


CameraApp::~CameraApp()
{
}
