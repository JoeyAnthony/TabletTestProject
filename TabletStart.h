#pragma once
#include <VrLib\Application.h>
#include <VrLib\tien\Tien.h>
#include <VrLib\HtcVive.h>
#include <VrLib\Device.h>
#include <glm\glm.hpp>
#include "HandController.h"
#include "CameraApp.h"
#include "VisibilityTester.h"


class TabletStart : public vrlib::Application
{
private:


public:
	vrlib::Vive vive;
	vrlib::tien::Tien Engine;
	CameraApp app;


	virtual void init() override;
	virtual void preFrame(double frameTime, double totalTime) override;
	virtual void latePreFrame() override;
	virtual void draw(const glm::mat4 &projectionMatrix, const glm::mat4 &modelViewMatrix) override;

	void loadScene();

	TabletStart();
	~TabletStart();
};

