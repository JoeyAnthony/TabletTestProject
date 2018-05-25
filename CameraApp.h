#pragma once
#include <VrLib/tien/Tien.h>
#include <VrLib/tien/components/Camera.h>
#include "VrLib/tien/Node.h"
#include "VrLib/gl/FBO.h"
#include <functional>


class CameraApp
{
public:
	vrlib::tien::Node * tabletHand;

	vrlib::tien::components::Camera* camComponent;
	glm::vec2 fboRes = glm::vec2{ 1900, 1000 };
	glm::vec3 camTabletOffset = glm::vec3(0, 0, 0);
	vrlib::gl::FBO* fbo;

	std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func;

	void initialize();
	void update();

	

	CameraApp();
	CameraApp(vrlib::tien::Node* hand, glm::vec2 resolution);
	CameraApp(vrlib::tien::Node* hand, std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func);
	~CameraApp();
};

