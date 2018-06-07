#include "stdafx.h"
#include "CameraApp.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>

#include "MainApp.h"

using namespace vrlib::tien;
using namespace glm;
using namespace std::string_literals;

void CameraApp::initalize()
{
	settings[Updateable] = true;
	auto fbosize = std::min(getGeometry().size.x, getGeometry().size.y);
	fboRes = { fbosize, fbosize };
	fbo = new vrlib::gl::FBO(fboRes.x, fboRes.y, true, 1);
	background = new TabletGraphicsComonents::FBO(fbo, this);
	background->setGeometry({ {0,(getGeometry().size.y - fboRes.y)/2},fboRes });

	//create button
	photoButton = new Button("Photo", [camapp = this]() {camapp->savePhoto(); }, this);
	photoButton->setGeometry({ {getGeometry().size.x/2-100, 20}, {200, 100} });

	//set mat
	perspective = glm::perspective(glm::radians(fov), fboRes.y / fboRes.x, 0.01f, 1000.0f);
	model = translate(glm::mat4(), camTabletOffset);
}

void CameraApp::update(float deltaMS)
{
	model = translate(glm::mat4(), camTabletOffset);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, fboRes.x, fboRes.y);
	fbo->bind();

	func(tabletHand->getScene(), perspective, model, tabletHand, 0);
	checkObjects();

	fbo->unbind();
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

std::vector<Node*> CameraApp::checkObjects()
{
	pollutedObjInScreen.clear();
	for (VisibilityTester* objs : occlusionObjects)
	{
		Node* node = objs->OcclusionDraw(inverse(tabletHand->transform->globalTransform) * model, perspective);
		if (objs->isVisible())
			pollutedObjInScreen.push_back(node);
	}
	return pollutedObjInScreen;
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

const std::set<vrlib::tien::Node*> CameraApp::pollutedObjsList()
{
	return pollutedObjectsFound;
}

const glm::vec2 CameraApp::getRes()
{
	return fboRes;
}

void CameraApp::savePhoto()
{
	std::vector<Node*> nodes = checkObjects();
	pollutedObjectsFound.insert(pollutedObjInScreen.begin(), pollutedObjInScreen.end());
	std::string path = "data/Bodemonderzoek/photos/"s + std::to_string(imagecount++) + ".jpg";
	fbo->saveAsFile(path);
}

bool CameraApp::linkToApps() {
	if ((mainApp = tablet->getApp<MainApp>()) == nullptr) return false;

	return true;
}

CameraApp::CameraApp(vrlib::tien::Node* hand) {
	tabletHand = hand;
}

CameraApp::CameraApp(vrlib::tien::Node * hand, std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func) : CameraApp(hand) {
	this->func = func;
}


CameraApp::~CameraApp()
{
}
