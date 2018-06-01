#pragma once
#include <VrLib/tien/Tien.h>
#include <VrLib/tien/components/Camera.h>
#include "VrLib/tien/Node.h"
#include "VrLib/gl/FBO.h"
#include <functional>
#include <vector>

class VisibilityTester;

class CameraApp
{
private:
	vrlib::tien::Node * tabletHand;
	vrlib::tien::components::Camera* camComponent;

public:
	glm::vec2 fboRes = glm::vec2{ 2048, 2048 };
	glm::vec3 camTabletOffset = glm::vec3(0, 0, 0);
	std::vector<VisibilityTester*> occlusionObjects;
	vrlib::gl::FBO* fbo;
	float fov = 90.0f;

	std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func;

	void initialize();
	void update();
	void addOcclusionObject(vrlib::tien::Node* obj);
	void addOcclusionObject(VisibilityTester* obj);

	CameraApp();
	CameraApp(vrlib::tien::Node* hand, glm::vec2 resolution);
	CameraApp(vrlib::tien::Node* hand, std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func);
	~CameraApp();
};

