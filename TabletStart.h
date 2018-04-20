#pragma once
#include <VrLib\Application.h>
#include <VrLib\tien\Tien.h>
#include <glm\glm.hpp>

class TabletStart : public vrlib::Application
{
	//vrlib::DigitalDevice leftbutton;
private:
	vrlib::tien::Tien Engine;

public:
	virtual void init() override;
	virtual void preFrame(double frameTime, double totalTime) override;
	virtual void latePreFrame() override;
	virtual void draw(const glm::mat4 &projectionMatrix, const glm::mat4 &modelViewMatrix) override;

	TabletStart();
	~TabletStart();
};

