#pragma once
#include <VrLib\tien\Tien.h>
#include <VrLib/tien/Component.h>	
#include "OcclusionQuery.h"
#include <VrLib/Singleton.h>
#include <VrLib/tien/components/ModelRenderer.h>
#include "CameraApp.h"

class VisibilityTester : public vrlib::tien::components::Renderable
{
private:
	OcclusionQuery query;
	glm::vec3 minbounds;
	glm::vec3 maxbounds;

public:
	float treshold;
	vrlib::tien::components::ModelRenderer *modelRenderer;
	
	bool isVisible(float& onScreenValue);
	void drawDeferredPass() override {};
	void drawForwardPass() override;
	void drawShadowMap() override {};
	void OcclusionDraw(glm::mat4 view, glm::mat4 proj);

	VisibilityTester(float tresh, vrlib::tien::components::ModelRenderer* model);
	VisibilityTester(float tresh, vrlib::tien::components::ModelRenderer* model, CameraApp* camapp);
	~VisibilityTester();
};

