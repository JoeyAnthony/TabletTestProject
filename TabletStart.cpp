#include "stdafx.h"
#include "TabletStart.h"
#include <VrLib\Log.h>

#include <VrLib\tien\components\ModelRenderer.h>

using vrlib::logger;
using namespace vrlib::tien;

void TabletStart::init()
{
	logger << "Initialized" << logger.newline;
	Engine.init();

	//Node* handR = new Node("RightHand", &Engine.scene);
	//handR->addComponent(new components::Transform(glm::vec3(-2, 0, 0)));
	//handR->addComponent(new components::ModelRenderer("data/vrlib/rendermodels/vr_controller_vive_1_5/vr_controller_vive_1_6.obj"));
}

void TabletStart::preFrame(double frameTime, double totalTime)
{
	Engine.update(frameTime);
}

void TabletStart::latePreFrame()
{
}

void TabletStart::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & modelViewMatrix)
{
	Engine.render(projectionMatrix, modelViewMatrix);
}

TabletStart::TabletStart()
{
	clearColor = glm::vec4(0.2, 0.5, 0.4, 1.0);
}


TabletStart::~TabletStart()
{
}
