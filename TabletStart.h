#pragma once
#include <VrLib\Application.h>
#include <glm\glm.hpp>

class TabletStart : public vrlib::Application
{
public:
	virtual void init() override;
	virtual void draw(const glm::mat4 &projectionMatrix, const glm::mat4 &modelViewMatrix) override;

	TabletStart();
	~TabletStart();
};

