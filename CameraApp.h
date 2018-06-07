#pragma once
#include "Tablet.h"
#include "VisibilityTester.h"

class CameraApp : public TabletApp
{
public:
	TabletGraphicsComonents::FBO* background;

	vrlib::tien::Node * tabletHand;
	glm::vec2 fboRes = glm::vec2{ 1920, 1080 };
	glm::vec3 camTabletOffset = glm::vec3(0, 0, 0);
	std::vector<VisibilityTester*> occlusionObjects;
	vrlib::gl::FBO* fbo;
	float fov = 90.0f;

	std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func;
	
	void initalize() override;
	void update(float deltaMS) override;

	void addOcclusionObject(vrlib::tien::Node* obj);
	void addOcclusionObject(VisibilityTester* obj);

	CameraApp(vrlib::tien::Node* hand);
	CameraApp(vrlib::tien::Node * hand, std::function<void( const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func);
	~CameraApp();
};

