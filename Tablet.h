#pragma once

#include "stdafx.h"
#include <VrLib\tien\Tien.h>
#include <VrLib\Device.h>

class Tablet : public vrlib::tien::components::Renderable {
public:

	Tablet(const vrlib::PositionalDevice& pointer);

	void update(float elapsedTime, vrlib::tien::Scene& scene) override;
	void drawDeferredPass() override;
	void postUpdate(vrlib::tien::Scene& scene) override;

private:
	const vrlib::PositionalDevice& m_pointer;
	
	glm::vec2 m_screenPos;
	bool m_screenPosInBounds;
};