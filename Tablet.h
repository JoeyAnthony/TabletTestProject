#pragma once

#include "stdafx.h"
#include <VrLib\tien\Tien.h>
#include <VrLib\Device.h>

class Tablet : public vrlib::tien::components::Renderable {
public:

	Tablet(vrlib::PositionalDevice& leftHand, vrlib::PositionalDevice& rightHand);

	void update(float elapsedTime, Scene& scene) override;
	void drawDeferredPass() override;
	void postUpdate(Scene& scene) override;
};