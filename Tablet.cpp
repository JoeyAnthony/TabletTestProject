#include "stdafx.h"
#include "Tablet.h"

#include <VrLib\tien\components\TransformAttach.h>
#include <glm\gtx\intersect.hpp>

using namespace vrlib;
using namespace vrlib::tien;
using namespace glm;

Tablet::Tablet(const PositionalDevice& pointer) : m_pointer(pointer) {
	
}

void Tablet::update(float elapsedTime, Scene& scene) {
	m_screenPos = { 0,0 };
	m_screenPosInBounds = false;
	if (node == nullptr) return;

	// Calculate screen pos
	const mat4 toTabletSpaceMat = inverse(node->transform->transform);
	const vec3 pointerPos = vec3(toTabletSpaceMat * (vec4(0, 0, 0, 1) * m_pointer.getData()));
	const vec3 pointerFront = vec3(toTabletSpaceMat * (vec4(0, 0, -1, 1) * m_pointer.getData()));
	const vec3 pointerDir = pointerPos - pointerFront;

	float intersectionDistance;
	bool intersectSucces = intersectRayPlane(pointerPos, pointerDir, {}, { 0,0,-1 }, intersectionDistance);
	if (intersectSucces == false) return;
	std::cout << "intersection distance" << intersectionDistance;




		//covert pointer to local space
		//do a vector plane intersect
		//update screen pos
}

void Tablet::drawDeferredPass() {
	// Draw screen
}

void Tablet::postUpdate(Scene& scene) {
	
}
