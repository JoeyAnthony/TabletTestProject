#include "stdafx.h"
#include "TabletStart.h"
#include <VrLib\Log.h>
#include <VrLib\json.hpp>
#include <fstream>

#include <VrLib\tien\components\TransformAttach.h>
#include <VrLib\tien\components\ModelRenderer.h>

using vrlib::logger;
using namespace vrlib::tien;

void TabletStart::init()
{
	logger << "Initialized" << logger.newline;
	//vive.init();
	Engine.init();

	loadScene();

	Engine.start();
	
	
}

void TabletStart::preFrame(double frameTime, double totalTime)
{
	Engine.update((float)frameTime / 1000.0f);
}

void TabletStart::latePreFrame()
{

}

void TabletStart::draw(const glm::mat4 & projectionMatrix, const glm::mat4 & modelViewMatrix)
{
	Engine.render(projectionMatrix, modelViewMatrix);
}

void TabletStart::loadScene()
{
	Engine.scene.reset();

	std::ifstream str = std::ifstream("data/TabletWorld/TabletWorld.json");
	json scene = json::parse(str);
	Engine.scene.fromJson(scene["scene"], scene, [](auto) {return nullptr; });

	Node* rightHand = new Node("RightHand", &Engine.scene);
	rightHand->addComponent(new components::Transform(glm::vec3(-2, 0, 0)));
	rightHand->addComponent(new components::ModelRenderer("data/vrlib/rendermodels/vr_controller_vive_1_5/vr_controller_vive_1_6.obj"));
	rightHand->addComponent(new components::TransformAttach(vive.controllers[1].transform));
}



TabletStart::TabletStart()
{
	clearColor = glm::vec4(0.2, 0.5, 0.4, 1.0);
}


TabletStart::~TabletStart()
{
}
