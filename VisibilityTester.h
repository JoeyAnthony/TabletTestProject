#pragma once
#include <VrLib\tien\Tien.h>
#include <VrLib/tien/Component.h>	
#include "OcclusionQuery.h"

class VisibilityTester : public vrlib::tien::components::Renderable
{
private:
	OcclusionQuery query;
	//float onScreenValue = 0;
	//bool isVisible = false;

public:
	float treshold;

	bool isVisible(float& onScreenValue);
	void drawDeferredPass() override {};
	void drawForwardPass() override;
	void drawShadowMap() override {};

	VisibilityTester(float treshold);
	~VisibilityTester();
};

