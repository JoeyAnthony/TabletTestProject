#pragma once
#include <VrLib\HtcVive.h>
#include <VrLib\tien\Tien.h>
#include <VrLib\tien\Scene.h>
#include <VrLib\tien\Component.h>

class HandController : public vrlib::tien::components::Renderable
{

private:


	vrlib::Vive::Controller controller;
	float debugspeed = 0.3f;

public:
	void initHand();
	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void postUpdate(vrlib::tien::Scene& scene) override;

	void drawRay(glm::mat4 view, glm::mat4 proj);

	void drawDeferredPass() override;
	void drawForwardPass() override {};
	void drawShadowMap() override {};

	HandController(vrlib::Vive::Controller c);
	~HandController();
};

