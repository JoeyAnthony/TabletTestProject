#pragma once
#include "Tablet.h"
#include "VisibilityTester.h"
#include <set>
#include <vector>

class MainApp;

struct PollutedObjData
{
	vrlib::tien::Node* node;
	vrlib::gl::FBO photo;

	bool friend operator < (const PollutedObjData& lhs, const PollutedObjData& rhs) {
		return lhs.node < rhs.node;
	}

	bool friend operator == (const PollutedObjData& lhs, const PollutedObjData& rhs) {
		return lhs.node == rhs.node;
	}

	bool friend operator != (const PollutedObjData& lhs, const PollutedObjData& rhs) {
		return lhs.node != rhs.node;
	}
};

class CameraApp : public TabletApp
{

private:
	int imagecount = 0;

	vrlib::gl::FBO* fbo;
	glm::vec2 fboRes;
	float fov = 90.0f;

	TabletGraphicsComonents::FBO* background;

	std::vector<VisibilityTester*> occlusionObjects;
	TabletGraphicsComonents::Button* photoButton;

	glm::vec3 camTabletOffset = glm::vec3(0, 0, 0);
	glm::mat4 perspective;
	glm::mat4 model;
	
	vrlib::tien::Node* largestPollutedObjInScreen;
	std::vector<vrlib::tien::Node*> pollutedObjInScreen;
	std::vector<PollutedObjData> pollutedObjectsFound;

public:
	vrlib::tien::Node * tabletHand;
	MainApp* mainApp;

	std::function<void(const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func;
	
	void initalize() override;
	void update(float deltaMS) override;
	void checkObjects();

	void addOcclusionObject(vrlib::tien::Node* obj);
	void addOcclusionObject(VisibilityTester* obj);

	const glm::vec2 getRes();
	const std::vector<PollutedObjData> pollutedObjsList();

	void savePhoto();
	bool linkToApps();

	CameraApp(vrlib::tien::Node* hand);
	CameraApp(vrlib::tien::Node * hand, std::function<void( const vrlib::tien::Scene&, const glm::mat4&, const glm::mat4&, vrlib::tien::Node*, int)> func);
	~CameraApp();
};

